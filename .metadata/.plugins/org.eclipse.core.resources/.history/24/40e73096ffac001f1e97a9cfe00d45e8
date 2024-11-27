
#include <stdio.h>
void divide_key(unsigned char* key, unsigned char * key0, unsigned char * key1);
void divide_plaintext(unsigned char* plaintext, unsigned char* ptext0,  unsigned char* ptext1,unsigned int plaintext_size);
void add_nonce(unsigned int * add_nonce, unsigned int * nonce, unsigned int * nonce_result, unsigned int size);
void xor_nonce(unsigned char * plaintext, unsigned char * nonce, unsigned int size);
void union_ciphertext(unsigned char* ciphertext, unsigned char* ctext0,  unsigned char* ctext1,unsigned int plaintext_size);
void PMAC( unsigned char* nonce, unsigned char* asociated_data, unsigned int asociated_data_size, unsigned char* key, unsigned char* tag);
void PMAC_1( unsigned char* nonce, unsigned char* asociated_data, unsigned int asociated_data_size,unsigned char* key, unsigned char* tag);
void OCB(unsigned char* plaintext, unsigned char* ciphertext, unsigned char* nonce,unsigned char* asociated_data, unsigned int plaintext_size, unsigned int asociated_data_size,unsigned char* key, unsigned char* tag);
