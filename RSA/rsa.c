#include <gmp.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

//p q n phi(n) e d
#define MODULUS_SIZE 1024                   /* This is the number of bits we want in the modulus */
#define BLOCK_SIZE (MODULUS_SIZE/8)         /* This is the size of a block that gets en/decrypted at once */
#define BUFFER_SIZE ((MODULUS_SIZE/8) / 2)  /* This is the number of bytes in n and p */

void encrypt(mpz_t cipher_text, 
			const mpz_t message,
			const mpz_t e,
			const mpz_t n){
	mpz_powm(cipher_text, message, e, n);

}


void decrypt(mpz_t decrypt_text, 
			const mpz_t cipher_text,
			const mpz_t d,
			const mpz_t n){
	mpz_powm(decrypt_text, cipher_text, d, n);

}


void rsa_keys(mpz_t n, mpz_t d, const mpz_t p, const mpz_t q, const mpz_t e){
	mpz_t p_1, q_1, phi_n;
	mpz_init(p_1);
	mpz_init(q_1);mpz_init( q_1);mpz_init( phi_n);

	mpz_mul(n,p,q);
	mpz_sub_ui(p_1, p, 1);
	mpz_sub_ui(q_1, q, 1);
	mpz_mul(phi_n, p_1, q_1);


    // e must be bigger than 1
	if(mpz_cmp_ui(e, 1) <= 0) cout<<"e not bigger than 1"<<endl;
	assert(mpz_cmp_ui(e, 1) > 0);	

    // e shoule smaller than phi_n
	if(mpz_cmp(phi_n, e)<=0) cout<<"e bigger than phi n"<<endl;
	assert(mpz_cmp(phi_n, e)>0);

    // gcd(e, phi(n)) must be 1
    mpz_t gcd; mpz_init(gcd);
    mpz_gcd(gcd, phi_n,e);
    assert(mpz_cmp_ui(gcd ,1)==0);

    mpz_invert(d, e, phi_n);

    mpz_clears(gcd, p_1, q_1, phi_n, NULL);

}





//generating two random big primes p and q 
// p and q will not be identical
void get_primes(mpz_t p, mpz_t q, const mpz_t e){

	char buf[BUFFER_SIZE];
	int i;
	mpz_t tmp1; mpz_init(tmp1);
	mpz_t tmp2; mpz_init(tmp2);

	srand(time(NULL));

	for(i=0; i<BUFFER_SIZE; i++)
		buf[i] = rand() % 0xFF;
	buf[0] |= 0xC0;
        // Set the bottom bit to 1 to ensure int(tmp) is odd
        buf[BUFFER_SIZE - 1] |= 0x01;
        // Interpret this char buffer as an int
        mpz_import(tmp1, (BUFFER_SIZE), 1, sizeof(buf[0]), 0, 0, buf);
        // Pick the next prime starting from that random number
        mpz_nextprime(p, tmp1);
        mpz_mod(tmp2, p, e);
        while(!mpz_cmp_ui(tmp2, 1))
        {
            mpz_nextprime(p, p);
            mpz_mod(tmp2, p, e);
        }


 /* Now select q not identical with p*/
    do {
        for(i = 0; i < BUFFER_SIZE; i++)
            buf[i] = rand() % 0xFF; 
        // Set the top two bits to 1 to ensure int(tmp) is relatively large
        buf[0] |= 0xC0;
        // Set the bottom bit to 1 to ensure int(tmp) is odd
        buf[BUFFER_SIZE - 1] |= 0x01;
        // Interpret this char buffer as an int
        mpz_import(tmp1, (BUFFER_SIZE), 1, sizeof(buf[0]), 0, 0, buf);
        // Pick the next prime starting from that random number
        mpz_nextprime(q, tmp1);
        mpz_mod(tmp2, q, e);
        while(!mpz_cmp_ui(tmp2, 1))
        {
            mpz_nextprime(q, q);
            mpz_mod(tmp2, q, e);
        }
    } while(mpz_cmp(p, q) == 0); 

}





int main(){

	
	cout<<"initializing"<<endl;

	mpz_t p, q, n, e, d;
	mpz_init(p);mpz_init(q);mpz_init(n); mpz_init(e); mpz_init(d);
	mpz_t m,c, m1;
    mpz_init(m);mpz_init(c);mpz_init(m1);



	//choose e to be 65537
	cout<<"choosing e"<<endl;
	mpz_set_ui(e,65537);

	cout<<"chooseing m"<<endl;
	mpz_set_ui(m,2490802340284);



	//generate random p and q
	cout<<"generating p q"<<endl;
	get_primes(p,q , e);

	//calculate n and d
	cout<<"calculating d"<<endl;
	rsa_keys( n, d, p, q, e);



	cout<<"encrypting"<<endl;
	encrypt( c, m,e, n);

	cout<<"decrypting"<<endl;
	decrypt(m1, c,d,n);
	cout<<"p = "<<mpz_get_str(NULL,0,p)<<endl;
	cout<<"q = "<<mpz_get_str(NULL,0,q)<<endl;
	cout<<"e = "<<mpz_get_str(NULL,0,e)<<endl;
	printf("m = %s\n\n", mpz_get_str(NULL, 0, m));
	printf("c = %s\n", mpz_get_str(NULL, 0, c));
	printf("m1 = %s\n", mpz_get_str(NULL, 0, m1));
}