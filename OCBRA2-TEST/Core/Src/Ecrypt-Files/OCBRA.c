#include <stdio.h> 
#include "aes.h"
#include "internal-aes.h"

#define key_size 32

void print_array(uint8_t * plaintext, uint32_t size);

        
void divide_key(unsigned char* key, unsigned char * key0, unsigned char * key1);
void divide_plaintext(unsigned char* plaintext, unsigned char* ptext0,  unsigned char* ptext1,unsigned int plaintext_size);
void add_nonce(unsigned int * add_nonce, unsigned int * nonce, unsigned int * nonce_result, unsigned int size);
void xor_nonce(unsigned char * plaintext, unsigned char * nonce, unsigned int size);
void union_ciphertext(unsigned char* ciphertext, unsigned char* ctext0,  unsigned char* ctext1,unsigned int plaintext_size);
void PMAC( unsigned char* nonce, unsigned char* asociated_data, unsigned int asociated_data_size, unsigned char* key, unsigned char* tag);
void PMAC_1( unsigned char* nonce, unsigned char* asociated_data, unsigned int asociated_data_size,unsigned char* key, unsigned char* tag);
void OCB(unsigned char* plaintext, unsigned char* ciphertext, unsigned char* nonce,unsigned char* asociated_data, unsigned int plaintext_size, unsigned int asociated_data_size,unsigned char* key, unsigned char* tag);




void OCB(unsigned char* plaintext, unsigned char* ciphertext, unsigned char* nonce, 
        unsigned char* asociated_data, unsigned int plaintext_size, unsigned int asociated_data_size,
        unsigned char* key, unsigned char* tag){
        



    if (asociated_data_size!=0)
    {
        PMAC(nonce,asociated_data,asociated_data_size,key,tag);

    }
    

    uint32_t size_ptext = (plaintext_size/2) + 16;
    uint32_t size = 0;

    if (plaintext_size%16 == 0 ){
        size = plaintext_size/16;
    }else{
        size = plaintext_size/16+1;
    }

    unsigned char ptext0[size_ptext];
    unsigned char ptext1[size_ptext];

    unsigned char ctext0[size_ptext];
    unsigned char ctext1[size_ptext];
    for (size_t i = 0; i < size_ptext; i++){
        ptext0[i]=0;
        ptext1[i]=0;
        ctext0[i]=0;
        ctext1[i]=0;
    }
    
    unsigned char key0[key_size];
    unsigned char key1[key_size];
    
    const unsigned char key_2AES[key_size] = {0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3};

    unsigned char N_0[16];
    unsigned char N_1[16];

    unsigned char N_0_t[16];
    unsigned char N_1_t[16];

    unsigned char c_N_0[16];
    unsigned char c_N_1[16];
    unsigned char checksum[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    unsigned char S[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    unsigned int add_nonce_0[4] = {0,0,0,0};
    unsigned int add_nonce_1[4] = {1,1,1,1};

    unsigned int add_nonce_2[4] = {2,2,2,2};
    
    divide_plaintext(plaintext, ptext0,  ptext1, plaintext_size);
    divide_key(key, key0, key1);

    //key schedule
	uint32_t rkeys_ffs[88];
    uint32_t two_AES_keys_ffs[88];

	aes128_keyschedule_ffs(rkeys_ffs, key0, key1);
    aes128_2rounds_keyschedule_ffs(two_AES_keys_ffs, key_2AES, key_2AES);

	//generate the N from nonce using 10 aes rounds
    aes128_encrypt_ffs(N_0, N_1, nonce, nonce, rkeys_ffs);

    for (size_t i = 0; i < size/2; i++){

        add_nonce(add_nonce_0, (unsigned int *)N_0,(unsigned int *)N_0_t, 4);
        add_nonce(add_nonce_1, (unsigned int *)N_1,(unsigned int *)N_1_t, 4);

        two_Rounds_aes128_encrypt_ffs(c_N_0,  c_N_1, N_0_t,  N_1_t, two_AES_keys_ffs);

        // print_array(ptext0+ (i*16),16);
        // print_array(ptext1+ (i*16),16);

        xor_nonce( checksum, ptext0 + (i*16), 16);
        xor_nonce( checksum, ptext1 + (i*16), 16);

        xor_nonce( ptext0 +  (i*16), c_N_0, 16);
        xor_nonce( ptext1 + (i*16), c_N_1, 16);




	    aes128_encrypt_ffs(ctext0+ (i*16), ctext1+ (i*16), ptext0+ ((i)*16), ptext1 + (i*16), rkeys_ffs);
        xor_nonce( ctext0 + (i*16), c_N_0, 16);
        xor_nonce( ctext1 + (i*16), c_N_1, 16);
        
        // print_array(ctext0+ (i*16),16);
        // print_array(ctext1+ (i*16),16);

        add_nonce(add_nonce_2, add_nonce_0,add_nonce_0, 4);
        add_nonce(add_nonce_2, add_nonce_1,add_nonce_1, 4);
        
    }
    
    union_ciphertext(ciphertext,ctext0,ctext1,plaintext_size);

    if (1)//condicion de bloques completos
    {
        add_nonce(add_nonce_1, (unsigned int *)N_0,(unsigned int *)N_0_t, 4);
        two_Rounds_aes128_encrypt_ffs(c_N_0,  c_N_1, N_0_t,  N_0_t, two_AES_keys_ffs);
        xor_nonce( checksum, c_N_0, 16);
	    aes128_encrypt_ffs(checksum, checksum, checksum, checksum, rkeys_ffs);
        xor_nonce( checksum, S, 16);
        xor_nonce( tag, checksum, 16);
    }



}

void PMAC( unsigned char* nonce, unsigned char* asociated_data, unsigned int asociated_data_size,unsigned char* key, unsigned char* tag){




    unsigned char ptext0[asociated_data_size];
    unsigned char ptext1[asociated_data_size];


    for (size_t i = 0; i < asociated_data_size; i++){
        ptext0[i]=0;
        ptext1[i]=0;

    }
    
    unsigned char key_2AES[key_size] = {0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3};

    unsigned char N_0[16]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};;
    unsigned char N_1[16]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};;

    unsigned char N_0_t[16]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};;
    unsigned char N_1_t[16]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};;

    unsigned char c_N_0[16]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};;
    unsigned char c_N_1[16]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};;
    //unsigned char checksum[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    unsigned int add_nonce_0[4] = {0,0,0,0};
    unsigned int add_nonce_1[4] = {1,1,1,1};

    unsigned int add_nonce_2[4] = {2,2,2,2};
    
    divide_plaintext(asociated_data, ptext0,  ptext1, asociated_data_size);

    //key schedule
	uint32_t rkeys_ffs[88];
    uint32_t two_AES_keys_ffs[88];

	aes128_keyschedule_ffs(rkeys_ffs, key, key);
	aes128_keyschedule_ffs(two_AES_keys_ffs, key_2AES, key_2AES);
    //aes128_2rounds_keyschedule_ffs(two_AES_keys_ffs, key_2AES, key_2AES);

	//generate the N from nonce using 10 aes rounds
    aes128_encrypt_ffs(N_0, N_1, nonce, nonce, rkeys_ffs);

    int block_size = asociated_data_size/32;

    for (size_t i = 0; i < block_size; i++){

        add_nonce(add_nonce_0, (unsigned int *)N_0,(unsigned int *)N_0_t, 4);
        add_nonce(add_nonce_1, (unsigned int *)N_1,(unsigned int *)N_1_t, 4);

        two_Rounds_aes128_encrypt_ffs(c_N_0,  c_N_1, N_0_t,  N_1_t, two_AES_keys_ffs);

        xor_nonce( ptext0 + (i*16), c_N_0, 16);
        xor_nonce( ptext1 + (i*16), c_N_1, 16);
	    
        aes128_encrypt_ffs(ptext0+ (i*16), ptext1+ (i*16), ptext0+ ((i)*16), ptext1 + (i*16), rkeys_ffs);

        xor_nonce( tag, ptext0 + (i*16), 16);
        // print_array(checksum,16);
        xor_nonce( tag, ptext1 + (i*16), 16);
        // print_array(checksum,16);
        add_nonce(add_nonce_2, add_nonce_0,add_nonce_0, 4);
        add_nonce(add_nonce_2, add_nonce_1,add_nonce_1, 4);
        

    }

        /*add_nonce(add_nonce_1, (unsigned int *)N_0,(unsigned int *)N_0_t, 4);
        two_Rounds_aes128_encrypt_ffs(c_N_0,  c_N_1, N_0_t,  N_0_t, two_AES_keys_ffs);
        xor_nonce( checksum, c_N_0, 16);
	    aes128_encrypt_ffs(checksum, checksum, checksum, checksum, rkeys_ffs);
        xor_nonce( tag, checksum, 16);*/

}


void PMAC_1( unsigned char* nonce, unsigned char* asociated_data, unsigned int asociated_data_size,unsigned char* key, unsigned char* tag){




    unsigned char ptext0[asociated_data_size];
    unsigned char ptext1[asociated_data_size];


    for (size_t i = 0; i < asociated_data_size; i++){
        ptext0[i]=0;
        ptext1[i]=0;

    }

    unsigned char key_2AES[key_size] = {0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3};

    unsigned char N_0[16]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};;
    unsigned char N_1[16]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};;

    unsigned char N_0_t[16]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};;
    unsigned char N_1_t[16]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};;

    unsigned char c_N_0[16]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};;
    unsigned char c_N_1[16]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};;
    unsigned char checksum[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    unsigned int add_nonce_0[4] = {0,0,0,0};
    unsigned int add_nonce_1[4] = {1,1,1,1};

    unsigned int add_nonce_2[4] = {2,2,2,2};

    divide_plaintext(asociated_data, ptext0,  ptext1, asociated_data_size);

    //key schedule
	uint32_t rkeys_ffs[88];
    uint32_t two_AES_keys_ffs[88];

	aes128_keyschedule_ffs(rkeys_ffs, key, key);
	aes128_keyschedule_ffs(two_AES_keys_ffs, key_2AES, key_2AES);
    //aes128_2rounds_keyschedule_ffs(two_AES_keys_ffs, key_2AES, key_2AES);

	//generate the N from nonce using 10 aes rounds
    aes128_encrypt_ffs(N_0, N_1, nonce, nonce, rkeys_ffs);

    int block_size = asociated_data_size/32;

    for (size_t i = 0; i < block_size; i++){

        add_nonce(add_nonce_0, (unsigned int *)N_0,(unsigned int *)N_0_t, 4);
        add_nonce(add_nonce_1, (unsigned int *)N_1,(unsigned int *)N_1_t, 4);

        two_Rounds_aes128_encrypt_ffs(c_N_0,  c_N_1, N_0_t,  N_1_t, two_AES_keys_ffs);

        if (i != block_size-1 ) {

			xor_nonce( ptext0 + (i*16), c_N_0, 16);
			xor_nonce( ptext1 + (i*16), c_N_1, 16);
			aes128_encrypt_ffs(ptext0+ (i*16), ptext1+ (i*16), ptext0+ ((i)*16), ptext1 + (i*16), rkeys_ffs);
			xor_nonce( checksum, ptext0 + (i*16), 16);
			xor_nonce( checksum, ptext1 + (i*16), 16);

        }
        else{
        	xor_nonce( ptext0 + (i*16), c_N_0, 16);
        	aes128_encrypt_ffs(ptext0+ (i*16), ptext0+ (i*16), ptext0+ ((i)*16), ptext0 + (i*16), rkeys_ffs);
        	xor_nonce( checksum, ptext0 + (i*16), 16);

        	xor_nonce( checksum, ptext1 + (i*16), 16);
        	aes128_encrypt_ffs(tag,ptext1 + (i*16),checksum,checksum, rkeys_ffs);
        }

        add_nonce(add_nonce_2, add_nonce_0,add_nonce_0, 4);
        add_nonce(add_nonce_2, add_nonce_1,add_nonce_1, 4);

    }

}


void add_nonce(unsigned int * add_nonce, unsigned int * nonce, unsigned int * nonce_result, unsigned int size){
    for (size_t i = 0; i < size; i++){
        nonce_result[i]=nonce[i]+ add_nonce[i];
    }
    
}

void xor_nonce(unsigned char * plaintext, unsigned char * nonce, unsigned int size){
    for (size_t i = 0; i < size; i++){
        plaintext[i]=nonce[i]^ plaintext[i];
    }
    
}
void divide_plaintext(unsigned char* plaintext, unsigned char* ptext0,  unsigned char* ptext1,unsigned int plaintext_size){
    int condicion = 1;
    size_t j=0;
    size_t k=0;
    for (size_t i = 0; i < plaintext_size; i++){
        
        if (i%16==0 && i!=0)
            condicion=condicion^1;

        if (condicion)
            ptext0[j] = plaintext[i];
        else
            ptext1[k] = plaintext[i];
        
        if (condicion)
            j++;
        else
            k++;
    }
}


void union_ciphertext(unsigned char* ciphertext, unsigned char* ctext0,  unsigned char* ctext1,unsigned int plaintext_size){

    // bool condicion = 1;
    int condicion = 1;
    size_t j=0;
    size_t k=0;
    for (size_t i = 0; i < plaintext_size; i++){
        if (i%16==0 && i!=0)
            condicion=condicion^1;
        
        if (condicion)
            ciphertext[i] = ctext0[j];
        else
            ciphertext[i] = ctext1[k];
        
        if (condicion)
            j++;
        else
            k++;
        

        

        
        
    }
}


void divide_key(unsigned char* key, unsigned char * key0, unsigned char * key1){

    for (size_t i = 0; i < key_size; i++){
        key0[i] = key[i];
        key1[i] = key[i];
    }
}


void print_array(uint8_t * plaintext, uint32_t size){
    if (size>32)
    {
        for (size_t i = 0; i < 16; i++){
            printf("%02x ", plaintext[i]);
        }
        printf("............");
        for (size_t i = size-16; i < size; i++){
            printf("%02x ", plaintext[i]);
        }
    }else{
        for (size_t i = 0; i < size; i++){
            printf("%02x ", plaintext[i]);
        }
    }
    
    
    
    printf("\n");
}