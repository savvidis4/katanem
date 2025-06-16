#define _GNU_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "erg1.h"
#include <rpc/rpc.h>      
#include <rpc/clnt.h>     
#include <rpc/svc.h>      
#include <rpc/xdr.h>      
#include <netinet/in.h>  
#include <arpa/inet.h>    

#define PORT 9696

void handle_client(int client_socket) {

    int choice, n;
    int *a, *b;
    double r;
    CLIENT *clnt;
    
    clnt = clnt_create("localhost", ERG1_PROG, ERG1_VERS, "tcp");
    if (clnt == NULL) {
        clnt_pcreateerror("localhost");
        return;
    }
    
    while (1) {

        read(client_socket, &choice, sizeof(int));

        if (choice == 0) {
            break;
        } 
        
        read(client_socket, &n, sizeof(int));

        a = (int *)malloc(n * sizeof(int));
        b = (int *)malloc(n * sizeof(int));
        
        read(client_socket, a, n * sizeof(int));
        read(client_socket, b, n * sizeof(int));
        
        switch (choice) {
            case 1: { 

                pin_args args;

                args.n = n;
                args.pina.pina_val = a;
                args.pina.pina_len = n;
                args.pinb.pinb_val = b;
                args.pinb.pinb_len = n;
                
                int *result = eswt_ginom_1(&args, clnt);
                write(client_socket, result, sizeof(int));
                break;

            } case 2: { 
                pin_args args;

                args.n = n;
                args.pina.pina_val = a;
                args.pina.pina_len = n;
                args.pinb.pinb_val = b;
                args.pinb.pinb_len = n;
                
                averages_ret *avg = averages_1(&args, clnt);
                write(client_socket, &avg->avg_a, sizeof(double));
                write(client_socket, &avg->avg_b, sizeof(double));
                break;
            } case 3: { 
                read(client_socket, &r, sizeof(double));
                
                ginom_r_args args;
                args.n = n;
                args.pin.pin_val = a;
                args.pin.pin_len = n;
                args.r = r;
                
                ginom_r_ret *vec = ginom_r_1(&args, clnt);
                write(client_socket, vec->epistr.epistr_val, n * sizeof(double));
                break;


            }
        }
        
        free(a);
        free(b);
    }
    
    clnt_destroy(clnt);
    close(client_socket);
}

int main(void) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    int reuse = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        perror("setsockopt(SO_REUSEADDR) failed");
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    // Bind
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 96) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
    
    printf("Server listening on port %d\n", PORT);
    
    while (1) {

        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);

        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        
        // Δημιουργία νέου process για κάθε client
        if (fork() == 0) {
            close(server_fd); // Κλείνουμε το αρχικό socket στο child
            handle_client(new_socket);
            exit(0);
        }
        
        close(new_socket); // Κλείνουμε το νέο socket στο parent
    }
    
    return 0;

}


