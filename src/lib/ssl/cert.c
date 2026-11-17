#include "ssl.h"

int generate_jwk_thumbprint(EVP_PKEY *pkey, unsigned char *out_thumbprint)
{
  BIO *bio = BIO_new(BIO_s_mem());
  PEM_write_bio_PUBKEY(bio, pkey);
   BIO_free(bio);
  return 0;
}
