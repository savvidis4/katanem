struct pin_args {
    int n;
    int pina<>;
    int pinb<>;
};

struct ginom_r_args {
    int n;
    int pin<>;
    double r;
};

struct averages_ret {
    double avg_a;
    double avg_b;
};

struct ginom_r_ret {
    double epistr<>;
};

program ERG1_PROG {
    version ERG1_VERS {
        int ESWT_GINOM(pin_args) = 1;
        averages_ret AVERAGES(pin_args) = 2;
        ginom_r_ret GINOM_R(ginom_r_args) = 3;
    } = 1;
} = 0x2345EDCB;