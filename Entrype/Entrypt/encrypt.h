/*
All contributions by Jiadong Nie:
Copyright (c) 2015 Jiadong Nie
All rights reserved.
*/
#ifndef ENCRYPT_H
#define ENCRYPT_H

class encrypt
{
public:
    encrypt();
    void MD5_Encrypt(unsigned char *output, unsigned char *input, unsigned int inlen);
    long RSHash(char str[]);
    long JSHash(char str[]);
    long PJWHash(char str[]);
    long ELFHash(char str[]);
    long BKDRHash(char str[]);
    long SDBMHash(char str[]);
    long DJBHash(char str[]);
    long DEKHash(char str[]);
    long BPHash(char str[]);
    long FNVHash(char str[]);
    long APHash(char str[]);
    int DesEncrypt(char *pResult, char *pOrig, long iOrigLen,  const char *pKey, int iKeylen);
    int DesDecrypt(char *pResult, char *pOrig, long iOrigLen,  const char *pKey, int iKeylen);
};

#endif // ENCRYPT_H
