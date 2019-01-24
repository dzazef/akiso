#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 200

char* dec_to_base_char(int dec, int base) {
    if (dec==0) {
        return "0";
    }
    if (base>16) fprintf(stderr, "ERROR: Base>16");
    char digits[] = {"0123456789ABCDEF"};
    int minus = 0;
    if (dec<0) {
        minus = 1;
        dec*=(-1);
    }
    char *value = (char *) malloc(MAX * sizeof(char));
    char *value_inv = (char *) malloc(MAX * sizeof(char));
    int pos=0;
    while (dec) {
        value[pos++] = digits[dec%base];
        dec /= base;
    }
    int j = 0;
    if (minus) {
        j=1;
        value_inv[0] = '-';
    }
    for (int i = pos-1; i>=0; i--) {
        value_inv[j++] = value[i];
    }
    return value_inv;
}

int multiply(char* num) {
    int length = (int) strlen(num);
    int carry = 0;
    int temp;
    for (int i=length-1; i>0; i--) {
        temp = (int)num[i]-48;
        temp = temp*2 + carry;
        carry = 0;
        if (temp<10) {
            num[i] = (char)(temp+48);
        } else {
            carry = 1;
            num[i] = (char)(temp%10+48);
        }
    }
    temp = (int)num[0]-48;
    temp = temp*2 + carry;
    if (temp<10) {
        num[0] = (char)(temp+48);
        return 0;
    }
    else {
        num[0] = (char)(temp%10+48);
        return 1;
    }
}

int main(int argc, char** argv) {
    if (argc!=3) {
        fprintf(stderr, "Składnia: ./f2b <liczba> <dokładność>\n");
        return 1;
    }

    char* delim = ".";
    char* fract = strtok(argv[1], delim);
    int num = atoi(fract); // NOLINT(cert-err34-c)
    fract = strtok(NULL, delim);

    printf("%s.", dec_to_base_char(num, 2));
    for(int i=0; i<atoi(argv[2]); i++){ //NOLINT(cert-err34-c)
        printf("%d", multiply(fract));
    }
    printf("\n");
    return 0;
}
