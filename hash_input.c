#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

int main(int argc, char *argv[])
{
    EVP_MD_CTX *mdctx;
    EVP_MD *md;
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len;

    if (argc < 2) {
        printf("Usage: mdtest message\n");
        exit(1);
    }

    md = EVP_MD_fetch(NULL, "md5", NULL);

    for(int i = 1; i < argc; i++){
        mdctx = EVP_MD_CTX_new();
        EVP_DigestInit_ex(mdctx, md, NULL);
        EVP_DigestUpdate(mdctx, argv[i], strlen(argv[i]));
        EVP_DigestFinal_ex(mdctx, md_value, &md_len);
        
        char *digest = calloc(2 * md_len, sizeof(char));

        for (int j = 0; j < md_len; j++){
            char *token = malloc(2 * sizeof(char));
            sprintf(token, "%02x", md_value[j]);
            strcat(digest, token);
            free(token);
        }
        printf("%s --> %s\n", argv[i], digest);
        
        
        free(digest);
    }

    EVP_MD_CTX_free(mdctx);
    EVP_MD_free(md);

    exit(0);
}