#pragma once
#include <string>
#include <iostream>
using namespace std;


#define CRYPT_EXPORTS __declspec(dllexport)

extern "C" CRYPT_EXPORTS int DisplayHelloFromDLL(int a,int b);

extern "C" CRYPT_EXPORTS char* CryptData(char* data);

extern "C" CRYPT_EXPORTS char* DecryptData(char*, int);