//
// Created by a on 2019/6/7.
//
#ifndef AES_AES_H
#define AES_AES_H
#endif //AES_AES_H

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
void decryption(unsigned char *ciphertext,  unsigned char *key);
unsigned char gadd(unsigned char a, unsigned char b); 
unsigned char gsub(unsigned char a, unsigned char b);
unsigned char gmul(unsigned char a, unsigned char b);
void SubBytes(unsigned char * state);
void InvSubBytes(unsigned char * state);
void ShiftRows(unsigned char *state);
void InvShiftRows(unsigned char *state);
void MixColumns(unsigned char *state);
void InvMixColumns(unsigned char *state);
void AddRoundKey(unsigned char *state, unsigned char *key, int round);
void KeyGeneration(unsigned char *InitialKey,unsigned char *key);
void TopShift(unsigned char* v); 
unsigned char Rcon(int i);
void encryption(unsigned char *plaintex, unsigned char *InitialKey);