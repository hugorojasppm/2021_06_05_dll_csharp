#pragma once


#include <string>
#include <iostream>
using namespace std;
#include <comutil.h>

#define CRYPT_EXPORTS __declspec(dllexport)

struct Crypt
{
	char* inputStr;
	char* outStr;
	int dataSize;
};

extern "C" CRYPT_EXPORTS BSTR CryptData(char* data);

extern "C" CRYPT_EXPORTS BSTR DecryptData(char*, int);

BSTR ANSItoBSTR(const char* input);

