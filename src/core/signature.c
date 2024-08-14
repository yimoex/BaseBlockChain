#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
//#include <openssl/sha.h>

RSA* signature_rsa(const char* key, int isPublic){
    BIO* bio = BIO_new_mem_buf((void *)key, -1);
    if(bio == NULL){
        printf("[Error]: bio is null\n");
        exit(0);
    }
    RSA* rsa = isPublic ? PEM_read_bio_RSA_PUBKEY(bio, NULL, NULL, NULL) : PEM_read_bio_RSAPrivateKey(bio, NULL, NULL, NULL);
    BIO_free(bio);
    if(rsa == NULL){
        printf("[Error]: rsa is null(%d)\n", isPublic);
        exit(0);
    }
    return rsa;
}

int signature_sign(const char* key, const char* hash, char* buffer, unsigned int* signSize){
    //char* buf = file_content("private.key");
    RSA* rsa = signature_rsa(key, false);
    int rec = RSA_sign(HASH_TYPE, hash, HASH_DIGEST_LENGTH, buffer, signSize, rsa);
    RSA_free(rsa);
    return rec;
}

int signature_verify(const char* publicKey, const char* hash, unsigned char* signature, unsigned int signSize) {
    RSA* rsa = signature_rsa(publicKey, true);
    int rec = RSA_verify(HASH_TYPE, hash, HASH_DIGEST_LENGTH, signature, signSize, rsa);
    RSA_free(rsa);
    return rec;
}

