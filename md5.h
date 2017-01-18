//
// Created by Alex on 2015/11/24.
//

#ifndef CLION_WORK_MD5_H
#define CLION_WORK_MD5_H

typedef struct {
    unsigned int count[2];
    unsigned int state[4];
    unsigned char buffer[64];
	unsigned char digest[16];
}MD5_CTX;

void MD5Init(MD5_CTX *context);
void MD5Update(MD5_CTX *context,unsigned char *input,unsigned int inputlen);
void MD5Final(MD5_CTX *context);
void MD5Hex(MD5_CTX *ctx,char *out);

#endif //CLION_WORK_MD5_H
