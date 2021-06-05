#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "aes.h"

static const char encoding_table[] = { 
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3',
    '4', '5', '6', '7', '8', '9', '+', '/'
};

static char *decoding_table = NULL;
void build_decoding_table() {
    decoding_table = malloc(256);
    for (int i = 0; i < 64; i++) decoding_table[(unsigned char) encoding_table[i]] = i;
}

char* base64_encode(const char *data, size_t input_length, size_t *output_length) {

    const int mod_table[] = { 0, 2, 1 };

    *output_length = 4 * ((input_length + 2) / 3);

    char *encoded_data = (char*)malloc(*output_length);

    if (encoded_data == NULL)
        return NULL;

    for (int i = 0, j = 0; i < input_length;) {

        uint32_t octet_a = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t octet_b = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t octet_c = i < input_length ? (unsigned char)data[i++] : 0;

        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];

    }

    for (int i = 0; i < mod_table[input_length % 3]; i++)
        encoded_data[*output_length - 1 - i] = '=';

    return encoded_data;

};

 char *base64_decode(const char *data, size_t input_length, size_t *output_length) {
 
    if (decoding_table == NULL) build_decoding_table();
 
    if (input_length % 4 != 0) return NULL; 
 
    *output_length = input_length / 4 * 3;
    if (data[input_length - 1] == '=') (*output_length)--;
    if (data[input_length - 2] == '=') (*output_length)--;
 
    char *decoded_data = (char*) malloc(*output_length);
    if (decoded_data == NULL) return NULL;
 
    for (int i = 0, j = 0; i < input_length;) {
 
        uint32_t sextet_a = data[i] == '=' ? 0 & i++ : decoding_table[(unsigned char) data[i++]];
        uint32_t sextet_b = data[i] == '=' ? 0 & i++ : decoding_table[(unsigned char) data[i++]];
        uint32_t sextet_c = data[i] == '=' ? 0 & i++ : decoding_table[(unsigned char) data[i++]];
        uint32_t sextet_d = data[i] == '=' ? 0 & i++ : decoding_table[(unsigned char) data[i++]];
 
        uint32_t triple = (sextet_a << 3 * 6)
        + (sextet_b << 2 * 6)
        + (sextet_c << 1 * 6)
        + (sextet_d << 0 * 6);
 
        if (j < *output_length) decoded_data[j++] = (triple >> 2 * 8) & 0xFF;
        if (j < *output_length) decoded_data[j++] = (triple >> 1 * 8) & 0xFF;
        if (j < *output_length) decoded_data[j++] = (triple >> 0 * 8) & 0xFF;
    }
 
    return decoded_data;
}

char* decryptData(char* encoded_data, int data_size) {
    uint8_t key[] = "RgPS6ry9nMPnd4lULxUMak2fI2tponjX";
    uint8_t iv[]  = "OiWLtq9QzQHxcwKQ0XsRXS88tGlFGGsC";
    struct AES_ctx ctx;

    size_t decode_size = strlen(encoded_data);
    char * decoded_data = base64_decode(encoded_data, decode_size, &decode_size);
    uint8_t newStr[data_size];
    memcpy(newStr,decoded_data,data_size+1);

    AES_init_ctx_iv(&ctx, key, iv);
    AES_CTR_xcrypt_buffer(&ctx, newStr, data_size);

    char * result = (char*) newStr;
    printf("\nResultado del decode: %s\n", result);
    return result;
}

char* cryptData(char* data) {
    uint8_t key[] = "RgPS6ry9nMPnd4lULxUMak2fI2tponjX";
    uint8_t iv[]  = "OiWLtq9QzQHxcwKQ0XsRXS88tGlFGGsC";
    uint8_t str[strlen(data)];
    memcpy(str,data,strlen(data)+1);
    
    size_t data_size = strlen(data);
    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key, iv);
    AES_CTR_xcrypt_buffer(&ctx, str, data_size);
    const char * plainText = (char*) str;
    size_t input_size = strlen(data);
    char * encoded_data = base64_encode(plainText, input_size, &input_size);
    printf("Encoded Data is: %s \n",encoded_data);

    return encoded_data;
}

int main(void){
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    char* dataToEncrypt = "[6794 x41206','website':'conrad.com'},{'nam332-32342424e':'Clementiñrnñññññéáíóú DuBuque','email':'Rey.Padberg@karina.biz','phone':'024-648-3804','website':'']";
    int data_size = strlen(dataToEncrypt);
    char* resultCrypt = cryptData(dataToEncrypt);
    char* resultDecrypt = decryptData(resultCrypt,data_size);
    //printf("\nResultado decryptData: %s\n",resultDecrypt);
    return 0;
}
