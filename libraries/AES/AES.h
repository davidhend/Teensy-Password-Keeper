#ifndef H__AES
#define H__AES

int aesSetupEncrypt(unsigned long *rk, const unsigned char *key, int keybits);
int aesSetupDecrypt(unsigned long *rk, const unsigned char *key, int keybits);
void aesEncrypt(const unsigned long *rk, int nrounds, const unsigned char plaintext[16], unsigned char ciphertext[16]);
void aesDecrypt(const unsigned long *rk, int nrounds, const unsigned char ciphertext[16], unsigned char plaintext[16]);

#define KEYLENGTH(keybits) ((keybits)/8)
#define RKLENGTH(keybits)  ((keybits)/8+28)
#define NROUNDS(keybits)   ((keybits)/32+6)

#endif
