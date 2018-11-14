/* From RFC1204  HMAC-MD5
 */

#ifndef HMAC_MD5_H
#define HMAC_MD5_H

#include <string.h>
#include <sys/types.h>
#include <stdint.h>
#if (__BYTE_ORDER == __BIG_ENDIAN)
#  define WORDS_BIGENDIAN 1
#endif

typedef uint32_t UWORD32;

void
hmac_md5(unsigned char *text, int text_len, unsigned char *key, int key_len,
	 unsigned char *digest);

#endif /* !HMAC_MD5_H */
