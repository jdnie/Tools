/*
All contributions by Jiadong Nie:
Copyright (c) 2015 Jiadong Nie
All rights reserved.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <memory.h>
#include "encrypt.h"

/********************************************************************************************
 * **************************************M D 5***********************************************
 * *****************************************************************************************/

#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

/* POINTER defines a generic pointer type */
typedef unsigned char* POINTER;

/* UINT2 defines a two byte word */
typedef unsigned short  UINT2;

/* UINT4 defines a four byte word */
typedef unsigned long  UIN;

/* MD5 context. */
typedef struct
{
    UIN state[4];        /* state (ABCD) */
    UIN count[2];        /* number of bits, modulo 2^64 (lsb first) */
    unsigned char buffer[64];        /* input buffer */
}
MD5_CTX;

unsigned char PADDING[64] =
{
    0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
/* F, G, H and I are basic MD5 functions. */
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

/* ROTATE_LEFT rotates x left n bits.
 */
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32 - (n))))
/* FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
Rotation is separate from addition to prevent recomputation.
 */
#define FF(a, b, c, d, x, s, ac) { \
    (a) += F ((b), (c), (d)) + (x) + (UIN)(ac); \
    (a) = ROTATE_LEFT ((a), (s)); \
    (a) += (b); \
}

#define GG(a, b, c, d, x, s, ac) { \
    (a) += G ((b), (c), (d)) + (x) + (UIN)(ac); \
    (a) = ROTATE_LEFT ((a), (s)); \
    (a) += (b); \
}

#define HH(a, b, c, d, x, s, ac) { \
    (a) += H ((b), (c), (d)) + (x) + (UIN)(ac); \
    (a) = ROTATE_LEFT ((a), (s)); \
    (a) += (b); \
}

#define II(a, b, c, d, x, s, ac) { \
    (a) += I ((b), (c), (d)) + (x) + (UIN)(ac); \
    (a) = ROTATE_LEFT ((a), (s)); \
    (a) += (b); \
}

/* Encodes input (UINT4) into output (unsigned char). Assumes len is
  a multiple of 4.
 */
static void MD5_Encode(unsigned char *output, UIN *input, unsigned int len)
{
    unsigned int i, j;

    for (i = 0, j = 0; j < len; i++, j += 4)
    {
        output[j] = (unsigned char)(input[i] & 0xff);
        output[j+1] = (unsigned char)((input[i] >> 8) & 0xff);
        output[j+2] = (unsigned char)((input[i] >> 16) & 0xff);
        output[j+3] = (unsigned char)((input[i] >> 24) & 0xff);
    }
}

/* Decodes input (unsigned char) into output (UINT4). Assumes len is
  a multiple of 4.
 */
static void MD5_Decode(UIN *output, unsigned char *input, unsigned int len)
{
    unsigned int i, j;

    for (i = 0, j = 0; j < len; i++, j += 4)
    {
        output[i] = ((UIN)input[j]) | (((UIN)input[j + 1]) << 8) |
                    (((UIN)input[j + 2]) << 16) | (((UIN)input[j + 3]) << 24);
    }
}

/* Note: Replace "for loop" with standard memcpy if possible.
 */
static void MD5_Memcpy(POINTER output, POINTER input, unsigned int len)
{
    unsigned int i;

    for (i = 0; i < len; i++)
    {
        output[i] = input[i];
    }
}

/* Note: Replace "for loop" with standard memset if possible.
 */
static void MD5_Memset(POINTER output, int value, unsigned int len)
{
    unsigned int i;

    for (i = 0; i < len; i++)
    {
        ((char *)output)[i] = (char)value;
    }
}

/* MD5 basic transformation. Transforms state based on block.
 */
static void MD5_Transform(UIN state[4], unsigned char block[64])
{
    UIN a = state[0], b = state[1], c = state[2], d = state[3], x[16];

    MD5_Decode (x, block, 64);

    /* Round 1 */
    FF (a, b, c, d, x[ 0], S11, 0xd76aa478); /* 1 */
    FF (d, a, b, c, x[ 1], S12, 0xe8c7b756); /* 2 */
    FF (c, d, a, b, x[ 2], S13, 0x242070db); /* 3 */
    FF (b, c, d, a, x[ 3], S14, 0xc1bdceee); /* 4 */
    FF (a, b, c, d, x[ 4], S11, 0xf57c0faf); /* 5 */
    FF (d, a, b, c, x[ 5], S12, 0x4787c62a); /* 6 */
    FF (c, d, a, b, x[ 6], S13, 0xa8304613); /* 7 */
    FF (b, c, d, a, x[ 7], S14, 0xfd469501); /* 8 */
    FF (a, b, c, d, x[ 8], S11, 0x698098d8); /* 9 */
    FF (d, a, b, c, x[ 9], S12, 0x8b44f7af); /* 10 */
    FF (c, d, a, b, x[10], S13, 0xffff5bb1); /* 11 */
    FF (b, c, d, a, x[11], S14, 0x895cd7be); /* 12 */
    FF (a, b, c, d, x[12], S11, 0x6b901122); /* 13 */
    FF (d, a, b, c, x[13], S12, 0xfd987193); /* 14 */
    FF (c, d, a, b, x[14], S13, 0xa679438e); /* 15 */
    FF (b, c, d, a, x[15], S14, 0x49b40821); /* 16 */

    /* Round 2 */
    GG (a, b, c, d, x[ 1], S21, 0xf61e2562); /* 17 */
    GG (d, a, b, c, x[ 6], S22, 0xc040b340); /* 18 */
    GG (c, d, a, b, x[11], S23, 0x265e5a51); /* 19 */
    GG (b, c, d, a, x[ 0], S24, 0xe9b6c7aa); /* 20 */
    GG (a, b, c, d, x[ 5], S21, 0xd62f105d); /* 21 */
    GG (d, a, b, c, x[10], S22,  0x2441453); /* 22 */
    GG (c, d, a, b, x[15], S23, 0xd8a1e681); /* 23 */
    GG (b, c, d, a, x[ 4], S24, 0xe7d3fbc8); /* 24 */
    GG (a, b, c, d, x[ 9], S21, 0x21e1cde6); /* 25 */
    GG (d, a, b, c, x[14], S22, 0xc33707d6); /* 26 */
    GG (c, d, a, b, x[ 3], S23, 0xf4d50d87); /* 27 */
    GG (b, c, d, a, x[ 8], S24, 0x455a14ed); /* 28 */
    GG (a, b, c, d, x[13], S21, 0xa9e3e905); /* 29 */
    GG (d, a, b, c, x[ 2], S22, 0xfcefa3f8); /* 30 */
    GG (c, d, a, b, x[ 7], S23, 0x676f02d9); /* 31 */
    GG (b, c, d, a, x[12], S24, 0x8d2a4c8a); /* 32 */

    /* Round 3 */
    HH (a, b, c, d, x[ 5], S31, 0xfffa3942); /* 33 */
    HH (d, a, b, c, x[ 8], S32, 0x8771f681); /* 34 */
    HH (c, d, a, b, x[11], S33, 0x6d9d6122); /* 35 */
    HH (b, c, d, a, x[14], S34, 0xfde5380c); /* 36 */
    HH (a, b, c, d, x[ 1], S31, 0xa4beea44); /* 37 */
    HH (d, a, b, c, x[ 4], S32, 0x4bdecfa9); /* 38 */
    HH (c, d, a, b, x[ 7], S33, 0xf6bb4b60); /* 39 */
    HH (b, c, d, a, x[10], S34, 0xbebfbc70); /* 40 */
    HH (a, b, c, d, x[13], S31, 0x289b7ec6); /* 41 */
    HH (d, a, b, c, x[ 0], S32, 0xeaa127fa); /* 42 */
    HH (c, d, a, b, x[ 3], S33, 0xd4ef3085); /* 43 */
    HH (b, c, d, a, x[ 6], S34,  0x4881d05); /* 44 */
    HH (a, b, c, d, x[ 9], S31, 0xd9d4d039); /* 45 */
    HH (d, a, b, c, x[12], S32, 0xe6db99e5); /* 46 */
    HH (c, d, a, b, x[15], S33, 0x1fa27cf8); /* 47 */
    HH (b, c, d, a, x[ 2], S34, 0xc4ac5665); /* 48 */

    /* Round 4 */
    II (a, b, c, d, x[ 0], S41, 0xf4292244); /* 49 */
    II (d, a, b, c, x[ 7], S42, 0x432aff97); /* 50 */
    II (c, d, a, b, x[14], S43, 0xab9423a7); /* 51 */
    II (b, c, d, a, x[ 5], S44, 0xfc93a039); /* 52 */
    II (a, b, c, d, x[12], S41, 0x655b59c3); /* 53 */
    II (d, a, b, c, x[ 3], S42, 0x8f0ccc92); /* 54 */
    II (c, d, a, b, x[10], S43, 0xffeff47d); /* 55 */
    II (b, c, d, a, x[ 1], S44, 0x85845dd1); /* 56 */
    II (a, b, c, d, x[ 8], S41, 0x6fa87e4f); /* 57 */
    II (d, a, b, c, x[15], S42, 0xfe2ce6e0); /* 58 */
    II (c, d, a, b, x[ 6], S43, 0xa3014314); /* 59 */
    II (b, c, d, a, x[13], S44, 0x4e0811a1); /* 60 */
    II (a, b, c, d, x[ 4], S41, 0xf7537e82); /* 61 */
    II (d, a, b, c, x[11], S42, 0xbd3af235); /* 62 */
    II (c, d, a, b, x[ 2], S43, 0x2ad7d2bb); /* 63 */
    II (b, c, d, a, x[ 9], S44, 0xeb86d391); /* 64 */

    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;

    /* Zeroize sensitive information.
    */
    MD5_Memset ((POINTER)x, 0, sizeof (x));
}

/* MD5 initialization. Begins an MD5 operation, writing a new context.
 */
static void MD5_Init(MD5_CTX *context)
{
    context->count[0] = context->count[1] = 0;

    /* Load magic initialization constants.
    */
    context->state[0] = 0x67452301;
    context->state[1] = 0xefcdab89;
    context->state[2] = 0x98badcfe;
    context->state[3] = 0x10325476;
}

/* MD5 block update operation. Continues an MD5 message-digest
  operation, processing another message block, and updating the
  context.
 */
static void MD5_Update(MD5_CTX *context, unsigned char *input, unsigned int inputLen)
{
    unsigned int i, index, partLen;

    /* Compute number of bytes mod 64 */
    index = (unsigned int)((context->count[0] >> 3) & 0x3F);

    /* Update number of bits */
    if ((context->count[0] += ((UIN)inputLen << 3))
        < ((UIN)inputLen << 3))
    {
        context->count[1]++;
    }
    context->count[1] += ((UIN)inputLen >> 29);

    partLen = 64 - index;

    /* Transform as many times as possible.
    */
    if (inputLen >= partLen)
    {
        MD5_Memcpy((POINTER)&context->buffer[index], (POINTER)input, partLen);
        MD5_Transform (context->state, context->buffer);

        for (i = partLen; i + 63 < inputLen; i += 64)
        {
            MD5_Transform (context->state, &input[i]);
        }

        index = 0;
    }
    else
    {
        i = 0;
    }

    /* Buffer remaining input */
    MD5_Memcpy((POINTER)&context->buffer[index], (POINTER)&input[i],\
               inputLen - i);
}

/* MD5 finalization. Ends an MD5 message-digest operation, writing the
  the message digest and zeroizing the context.
 */
static void MD5_Final(unsigned char digest[16], MD5_CTX  *context)
{
    unsigned char bits[8];
    unsigned int index, padLen;

    /* Save number of bits */
    MD5_Encode (bits, context->count, 8);

    /* Pad out to 56 mod 64.
    */
    index = (unsigned int)((context->count[0] >> 3) & 0x3f);
    padLen = (index < 56) ? (56 - index) : (120 - index);
    MD5_Update (context, PADDING, padLen);

    /* Append length (before padding) */
    MD5_Update (context, bits, 8);

    /* Store state in digest */
    MD5_Encode (digest, context->state, 16);

    /* Zeroize sensitive information.
    */
    MD5_Memset ((POINTER)context, 0, sizeof (*context));
}

void encrypt::MD5_Encrypt(unsigned char *output, unsigned char *input, unsigned int inlen)
{
    MD5_CTX context;

    MD5_Init(&context);
    MD5_Update(&context, input, inlen);
    MD5_Final(output, &context);
}
/********************************************************************************************
 * **************************************H A S H*********************************************
 * *****************************************************************************************/

/*RSHash*/
long encrypt::RSHash(char str[])
{
    int b = 378551;
    int a = 63689;
    int size = strlen(str), i;
    long hash = 0;
    for(i = 0; i < size; i++)
    {
        hash = hash * a + str[i];
        a = a * b;
    }
    return hash;
}
/*JSHash*/
long encrypt::JSHash(char str[])
{
    long hash = 1315423911;
    int size = strlen(str), i;
    for(i = 0; i < size; i++)
    {
        hash ^= ((hash << 5) + str[i] + (hash >> 2));
    }
    return hash;
}
/*PJWHash*/
long encrypt::PJWHash(char str[])
{
    long BitsInUnsignedInt = (long)(4 * 8);
    long ThreeQuarters = (long)((BitsInUnsignedInt * 3) / 4);
    long OneEighth = (long)(BitsInUnsignedInt / 8);
    long HighBits = (long)(0xFFFFFFFF)<<(BitsInUnsignedInt-OneEighth);
    long hash = 0;
    long test = 0;
    int size = strlen(str), i;
    for(i = 0; i < size; i++)
    {
        hash = (hash << OneEighth) + str[i];
        if((test = hash & HighBits) != 0)
        {
            hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
        }
    }
    return hash;
}
/*ELFHash*/
long encrypt::ELFHash(char str[])
{
    long hash = 0;
    long x = 0;
    int size = strlen(str), i;
    for(i = 0; i < size; i++)
    {
        hash = (hash << 4) + str[i];
        if(( x = hash & 0xF0000000L) != 0)
        {
            hash ^= ( x >> 24);
        }
        hash &= ~x;
    }
    return hash;
}
/*BKDRHash*/
long encrypt::BKDRHash(char str[])
{
    long seed = 131;//31131131313131131313etc..
    long hash = 0;
    int size = strlen(str), i;
    for(i = 0; i < size; i++)
    {
        hash = (hash * seed) + str[i];
    }
    return hash;
}
/*SDBMHash*/
long encrypt::SDBMHash(char str[])
{
    long hash = 0;
    int size = strlen(str), i;
    for(i = 0; i < size; i++)
    {
        hash = str[i] + (hash << 6) + (hash << 16) - hash;
    }
    return hash;
}
/*DJBHash*/
long encrypt::DJBHash(char str[])
{
    long hash = 5381;
    int size = strlen(str), i;
    for(i = 0; i < size; i++)
    {
        hash = ((hash << 5) + hash) + str[i];
    }
    return hash;
}
/*DEKHash*/
long encrypt::DEKHash(char str[])
{
    int size = strlen(str), i;
    long hash = size;
    for(i = 0; i < size; i++)
    {
        hash = ((hash << 5) ^ (hash >> 27)) ^ str[i];
    }
    return hash;
}
/*BPHash*/
long encrypt::BPHash(char str[])
{
    long hash=0;
    int size = strlen(str), i;
    for(i = 0;i < size; i++)
    {
        hash = hash << 7 ^ str[i];
    }
    return hash;
}
/*FNVHash*/
long encrypt::FNVHash(char str[])
{
    long fnv_prime = 0x811C9DC5;
    long hash = 0;
    int size = strlen(str), i;
    for(i = 0; i < size; i++)
    {
        hash *= fnv_prime;
        hash ^= str[i];
    }
    return hash;
}
/*APHash*/
long encrypt::APHash(char str[])
{
    long hash = 0xAAAAAAAA;
    int size = strlen(str), i;
    for(i = 0; i < size; i++)
    {
        if((i & 1) == 0)
        {
            hash ^=((hash << 7) ^ str[i] ^ (hash >> 3));
        }
        else
        {
            hash ^= (~((hash << 11) ^ str[i] ^ (hash >> 5)));
        }
    }
    return hash;
}

/********************************************************************************************
 * **************************************D E S***********************************************
 * *****************************************************************************************/

// initial permutation IP
const static char IP_Table[64] = {
    58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17,  9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7
};
// final permutation IP^-1
const static char IPR_Table[64] = {
    40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41,  9, 49, 17, 57, 25
};
// expansion operation matrix
static const char E_Table[48] = {
    32,  1,  2,  3,  4,  5,  4,  5,  6,  7,  8,  9,
     8,  9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32,  1
};
// 32-bit permutation function P used on the output of the S-boxes
const static char P_Table[32] = {
    16, 7, 20, 21, 29, 12, 28, 17, 1,  15, 23, 26, 5,  18, 31, 10,
    2,  8, 24, 14, 32, 27, 3,  9,  19, 13, 30, 6,  22, 11, 4,  25
};
// permuted choice table (key)
const static char PC1_Table[56] = {
    57, 49, 41, 33, 25, 17,  9,  1, 58, 50, 42, 34, 26, 18,
    10,  2, 59, 51, 43, 35, 27, 19, 11,  3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,  7, 62, 54, 46, 38, 30, 22,
    14,  6, 61, 53, 45, 37, 29, 21, 13,  5, 28, 20, 12,  4
};
// permuted choice key (table)
const static char PC2_Table[48] = {
    14, 17, 11, 24,  1,  5,  3, 28, 15,  6, 21, 10,
    23, 19, 12,  4, 26,  8, 16,  7, 27, 20, 13,  2,
    41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
};
// number left rotations of pc1
const static char LOOP_Table[16] = {
    1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1
};
// The (in)famous S-boxes
const static char S_Box[8][4][16] = {
    // S1
   {{14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7},
    { 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8},
    { 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0},
    {15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13}},
    // S2
   {{15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10},
    { 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5},
    { 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15},
    {13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9}},
    // S3
   {{10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8},
    {13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1},
    {13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7},
    { 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12}},
    // S4
   {{ 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15},
    {13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9},
    {10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4},
    { 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14}},
    // S5
   {{ 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9},
    {14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6},
    { 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14},
    {11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3}},
    // S6
   {{12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11},
    {10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8},
    { 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6},
    { 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13}},
    // S7
   {{ 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1},
    {13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6},
    { 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2},
    { 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12}},
    // S8
   {{13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7},
    { 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2},
    { 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8},
    { 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11}}
};

enum    {ENCRYPT,DECRYPT};
#define bool unsigned char
#define true 1
#define false 0
typedef bool    (*PSubKey)[16][48];

static bool SubKey[2][16][48];// 16圈子密钥
static bool Is3DES;// 3次DES标志
static char Tmp[256], deskey[16];

// 变换
/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/

static void Transform(bool *Out, bool *In, const char *Table, int len)
{
    int i;
    for(i=0; i<len; ++i)
        Tmp[i] = In[ Table[i]-1 ];
    memcpy(Out, Tmp, len);
}
// 异或
/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/

static void Xor(bool *InA, const bool *InB, int len)
{
    int i;
    for(i=0; i<len; ++i)
        InA[i] ^= InB[i];
}
// 循环左移
/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/

static void RotateL(bool *In, int len, int loop)
{
    memcpy(Tmp, In, loop);
    memcpy(In, In+loop, len-loop);
    memcpy(In+len-loop, Tmp, loop);
}
// 字节组转换成位组
/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/

static void ByteToBit(bool *Out, const char *In, int bits)
{
    int i;
    for(i=0; i<bits; ++i)
        Out[i] = (In[i>>3]>>(i&7)) & 1;
}
// 位组转换成字节组
/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/

static void BitToByte(char *Out, const bool *In, int bits)
{
    int i;
    memset(Out, 0, bits>>3);
    for(i=0; i<bits; ++i)
        Out[i>>3] |= In[i]<<(i&7);
}
// 设置子密钥
/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/

static void SetSubKey(PSubKey pSubKey, const char Key[8])
{
    int i;
    static bool K[64], *KL=&K[0], *KR=&K[28];
    ByteToBit(K, Key, 64);
    Transform(K, K, PC1_Table, 56);
    for(i=0; i<16; ++i) {
        RotateL(KL, 28, LOOP_Table[i]);
        RotateL(KR, 28, LOOP_Table[i]);
        Transform((*pSubKey)[i], K, PC2_Table, 48);
    }
}
// S 盒代替
/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/

static void S_func(bool Out[32], const bool In[48])
{
    int i,j,k;
    for(i=0; i<8; ++i,In+=6,Out+=4) {
        j = (In[0]<<1) + In[5];
        k = (In[1]<<3) + (In[2]<<2) + (In[3]<<1) + In[4];
        ByteToBit(Out, &S_Box[i][j][k], 4);
    }
}
// f 函数
/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/

static void F_func(bool In[32], const bool Ki[48])
{
    static bool MR[48];
    Transform(MR, In, E_Table, 48);
    Xor(MR, Ki, 48);
    S_func(In, MR);
    Transform(In, In, P_Table, 32);
}
// 设置密钥
/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
static void SetKey(const char* Key, int len)
{
    memset(deskey, 0, 16);
    memcpy(deskey, Key, len>16?16:len);
    SetSubKey(&SubKey[0], &deskey[0]);
    Is3DES = len>8 ? (SetSubKey(&SubKey[1], &deskey[8]), true) : false;
}
//标准DES加/解密
/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/

static void DES(char Out[8], char In[8], const PSubKey pSubKey, bool Type)
{
    int i;
    static bool M[64], tmp[32], *Li=&M[0], *Ri=&M[32];
    ByteToBit(M, In, 64);
    Transform(M, M, IP_Table, 64);
    if( Type == ENCRYPT ){
        for(i=0; i<16; ++i) {
            memcpy(tmp, Ri, 32);
            F_func(Ri, (*pSubKey)[i]);
            Xor(Ri, Li, 32);
            memcpy(Li, tmp, 32);
        }
    }else{
        for(i=15; i>=0; --i) {
            memcpy(tmp, Li, 32);
            F_func(Li, (*pSubKey)[i]);
            Xor(Li, Ri, 32);
            memcpy(Ri, tmp, 32);
        }
    }
    Transform(M, M, IPR_Table, 64);
    BitToByte(Out, M, 64);
}

/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/

int encrypt::DesEncrypt(char *pResult,
                char *pOrig,
                long iOrigLen,
                const char *pKey,
                int iKeylen)
{
    long i,j;
    if( !( pResult && pOrig && pKey && (iOrigLen=(iOrigLen+7)&0xfffffff8) ) )
        return -1;
    SetKey(pKey, iKeylen);
    if( !Is3DES ) {   // 1次DES
        for(i=0,j=iOrigLen>>3; i<j; ++i,pResult+=8,pOrig+=8)
            DES(pResult, pOrig, &SubKey[0], ENCRYPT);
    } else{   // 3次DES 加密:加(key0)-解(key1)-加(key0) 解密::解(key0)-加(key1)-解(key0)
        for(i=0,j=iOrigLen>>3; i<j; ++i,pResult+=8,pOrig+=8) {
            DES(pResult, pOrig,  &SubKey[0], ENCRYPT);
            DES(pResult, pResult, &SubKey[1], !ENCRYPT);
            DES(pResult, pResult, &SubKey[0], ENCRYPT);
        }
    }
    return ((iOrigLen+7)&0xfffffff8);
}

/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/

int encrypt::DesDecrypt(char *pResult,
                char *pOrig,
                long iOrigLen,
                const char *pKey,
                int iKeylen)
{
    long i,j;
    if( !( pResult && pOrig && pKey && (iOrigLen=(iOrigLen+7)&0xfffffff8) ) )
        return -1;
    SetKey(pKey, iKeylen);
    if( !Is3DES ) {   // 1次DES
        for(i=0,j=iOrigLen>>3; i<j; ++i,pResult+=8,pOrig+=8)
            DES(pResult, pOrig, &SubKey[0], DECRYPT);
    } else{   // 3次DES 加密:加(key0)-解(key1)-加(key0) 解密::解(key0)-加(key1)-解(key0)
        for(i=0,j=iOrigLen>>3; i<j; ++i,pResult+=8,pOrig+=8) {
            DES(pResult, pOrig,  &SubKey[0], DECRYPT);
            DES(pResult, pResult, &SubKey[1], !DECRYPT);
            DES(pResult, pResult, &SubKey[0], DECRYPT);
        }
    }
    return iOrigLen;
}

/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/


encrypt::encrypt()
{
}
