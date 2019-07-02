#include <stdio.h>

#include <stdlib.h>

#include "AES.h"

int main() {

  // char input[]={"GoodMorningMrCao"};


  unsigned char InitialKey[4*4]
            ={0x0 ,0x01 ,0x02 ,0x03 ,0x4 ,0x5 ,0x06 ,0x07 ,0x08 ,0x09 ,
              0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
    unsigned char input[] = {
            0xc0, 0x21, 0x32, 0x43,
            0x89, 0x55, 0x66, 0x77,
            0x88, 0xa4, 0xaa, 0xbb,
            0x45, 0x25, 0xee, 0xff};


    printf("Initial Key : \n");
    for (int i=0;i<16;i++){
        printf("%x ",InitialKey[i]);
        if(i==15) printf("\n");
    }


    printf("plaintext : \n");
    for (int i=0;i<16;i++){
        printf("%x ",input[i]);
        if(i==15) printf("\n");
    }

    encryption(input, InitialKey);
    printf("ciphertext : \n");
    for (int i=0;i<16;i++){
        printf("%x ",input[i]);
        if(i==15) printf("\n");
    }

    decryption(input, InitialKey);
    printf("Decrypt Output : \n");
    for (int i=0;i<16;i++){
        printf("%2x ",input[i]);
        if(i==15) printf("\n");
    }

    return 0;
}

