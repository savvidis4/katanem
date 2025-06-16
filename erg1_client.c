#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 9696

int main(void) {

    int sock = 0;
    struct sockaddr_in serv_addr;
    
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\nSocket creation error\n");
        return -1;
    }
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported\n");
        return -1;
    }
    
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed\n");
        return -1;
    }
    
    while (1) {

        int choice, n;
        printf("\n1:Εσωτερικό γινόμενο\n2:Μέσες τιμές\n3:Πολλαπλασιασμός r\n0:Έξοδος\nΕπιλογή: ");
        scanf("%d", &choice);
        
        if (choice == 0) break;
        
        printf("Δώσε το μήκος των διανυσμάτων (n): ");
        scanf("%d", &n);
        
        int *a = (int *)malloc(n * sizeof(int));
        int *b = (int *)malloc(n * sizeof(int));
        
        printf("Δώσε το διάνυσμα a (χωρίζοντας τα στοιχεία με κενά): ");
        for (int i = 0; i < n; i++) scanf("%d", &a[i]);
        
        printf("Δώσε το διάνυσμα b (χωρίζοντας τα στοιχεία με κενά): ");
        for (int i = 0; i < n; i++) scanf("%d", &b[i]);
        
        write(sock, &choice, sizeof(int));
        write(sock, &n, sizeof(int));
        write(sock, a, n * sizeof(int));
        write(sock, b, n * sizeof(int));
        
        if (choice == 3) {
            double r;
            printf("Δώσε τον πραγματικό αριθμό r: ");
            scanf("%lf", &r);
            write(sock, &r, sizeof(double));
        }
        
        if (choice == 1) {
            int result;
            read(sock, &result, sizeof(int));
            printf("Εσωτερικό γινόμενο: %d\n", result);
        } else if (choice == 2) {
            double avg[2];
            read(sock, avg, 2 * sizeof(double));
            printf("Μέση τιμή a: %.2f, Μέση τιμή b: %.2f\n", avg[0], avg[1]);
        } else if (choice == 3) {
            double *result = (double *)malloc(n * sizeof(double));
            read(sock, result, n * sizeof(double));
            printf("Αποτέλεσμα πολλαπλασιασμού: ");
            for (int i = 0; i < n; i++) printf("%.2f ", result[i]);
            printf("\n");
            free(result);
        }
        
        free(a);
        free(b);
    }
    
    close(sock);
    return 0;


}