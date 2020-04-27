#include <assert.h>
#include <string.h>

#include <plat/common/platform.h>
#include <platform_def.h>

static unsigned char dc_der[] = \
    "\x30\x82\x01\xdd\x30\x82\x01\x81\xa0\x03\x02\x01\x02\x02" \
    "\x09\x00\xbb\xdf\xa0\x4f\x34\x9a\xac\x4a\x30\x0c\x06\x08" \
    "\x2a\x86\x48\xce\x3d\x04\x03\x02\x05\x00\x30\x36\x31\x0b" \
    "\x30\x09\x06\x03\x55\x04\x06\x13\x02\x50\x54\x31\x0f\x30" \
    "\x0d\x06\x03\x55\x04\x0a\x0c\x06\x48\x61\x73\x6c\x61\x62" \
    "\x31\x16\x30\x14\x06\x03\x55\x04\x03\x0c\x0d\x48\x61\x73" \
    "\x6c\x61\x62\x20\x44\x65\x76\x69\x63\x65\x30\x1e\x17\x0d" \
    "\x31\x39\x31\x32\x33\x31\x32\x33\x35\x39\x35\x39\x5a\x17" \
    "\x0d\x32\x31\x31\x32\x33\x31\x32\x33\x35\x39\x35\x39\x5a" \
    "\x30\x36\x31\x0b\x30\x09\x06\x03\x55\x04\x06\x13\x02\x50" \
    "\x54\x31\x0f\x30\x0d\x06\x03\x55\x04\x0a\x0c\x06\x48\x61" \
    "\x73\x6c\x61\x62\x31\x16\x30\x14\x06\x03\x55\x04\x03\x0c" \
    "\x0d\x48\x61\x73\x6c\x61\x62\x20\x44\x65\x76\x69\x63\x65" \
    "\x30\x59\x30\x13\x06\x07\x2a\x86\x48\xce\x3d\x02\x01\x06" \
    "\x08\x2a\x86\x48\xce\x3d\x03\x01\x07\x03\x42\x00\x04\x10" \
    "\x88\xe3\xea\xc6\xaa\xdb\xcd\x69\x43\xc1\x2c\x36\x25\x2d" \
    "\xd0\xd7\x1f\x1d\x70\x4c\xb6\x60\x2f\xbb\xfd\x4d\x81\x8f" \
    "\xaf\x87\xe4\xae\x89\xb1\x73\xa8\xaf\xeb\x74\xaf\x86\x1d" \
    "\x03\x3d\x63\x02\xb8\x83\x30\x44\x27\xde\x9f\x49\x92\xcc" \
    "\xab\xfd\xdb\x30\x97\x65\xe7\xa3\x76\x30\x74\x30\x0f\x06" \
    "\x03\x55\x1d\x13\x04\x08\x30\x06\x01\x01\xff\x02\x01\x00" \
    "\x30\x1d\x06\x03\x55\x1d\x0e\x04\x16\x04\x14\xee\x38\x51" \
    "\xe2\x7b\xe7\xac\x1f\xc9\xc5\xd3\xdd\xc7\x80\x31\x58\xbf" \
    "\x62\x5c\x1b\x30\x1f\x06\x03\x55\x1d\x23\x04\x18\x30\x16" \
    "\x80\x14\xee\x38\x51\xe2\x7b\xe7\xac\x1f\xc9\xc5\xd3\xdd" \
    "\xc7\x80\x31\x58\xbf\x62\x5c\x1b\x30\x0e\x06\x03\x55\x1d" \
    "\x0f\x01\x01\xff\x04\x04\x03\x02\x06\xc0\x30\x11\x06\x09" \
    "\x60\x86\x48\x01\x86\xf8\x42\x01\x01\x04\x04\x03\x02\x04" \
    "\x10\x30\x0c\x06\x08\x2a\x86\x48\xce\x3d\x04\x03\x02\x05" \
    "\x00\x03\x48\x00\x30\x45\x02\x21\x00\xd8\x6f\xd0\x8d\x35" \
    "\xef\x8c\x4b\x4b\xaa\x2b\x5d\x70\xfa\x36\xcf\x84\x97\xbb" \
    "\xae\x88\x4a\x3d\x2d\x92\x82\x02\x36\x93\xab\x99\x41\x02" \
    "\x20\x72\xdc\xb1\x0f\x76\xbc\x6b\x82\xc9\x94\x10\x9a\x8a" \
    "\xed\xe1\x2b\xad\x5b\x30\x5d\xb5\x68\xe7\x23\x56\x5e\xe4" \
    "\x36\xc6\x81\x8e\xd9";

static unsigned char ak_blob[] = \
    "\xb8\x73\x0b\xfa\x0e\x22\xab\xa3\x51\xd3\xe4\x8d\x2f\x70" \
    "\x66\xe2\xa8\x78\x18\xb2\x29\x24\x6b\xf4\xaa\xda\x89\x45" \
    "\x10\x57\xd2\x31\x10\x88\xe3\xea\xc6\xaa\xdb\xcd\x69\x43" \
    "\xc1\x2c\x36\x25\x2d\xd0\xd7\x1f\x1d\x70\x4c\xb6\x60\x2f" \
    "\xbb\xfd\x4d\x81\x8f\xaf\x87\xe4\xae\x89\xb1\x73\xa8\xaf" \
    "\xeb\x74\xaf\x86\x1d\x03\x3d\x63\x02\xb8\x83\x30\x44\x27" \
    "\xde\x9f\x49\x92\xcc\xab\xfd\xdb\x30\x97\x65\xe7";

static unsigned char dck_blob[] = \
    "\x30\x82\x01\xdd\x30\x82\x01\x81\xa0\x03\x02\x01\x02\x02" \
    "\x09\x00\xbb\xdf\xa0\x4f\x34\x9a\xac\x4a\x30\x0c\x06\x08" \
    "\x2a\x86\x48\xce\x3d\x04\x03\x02\x05\x00\x30\x36\x31\x0b" \
    "\x30\x09\x06\x03\x55\x04\x06\x13\x02\x50\x54\x31\x0f\x30" \
    "\x0d\x06\x03\x55\x04\x0a\x0c\x06\x48\x61\x73\x6c\x61\x62" \
    "\x31\x16\x30\x14\x06\x03\x55\x04\x03\x0c\x0d\x48\x61\x73" \
    "\x6c\x61\x62\x20\x44\x65\x76\x69\x63\x65\x30\x1e\x17\x0d" \
    "\x31\x39\x31\x32\x33\x31\x32\x33\x35\x39\x35\x39\x5a\x17" \
    "\x0d\x32\x31\x31\x32\x33\x31\x32\x33\x35\x39\x35\x39\x5a" \
    "\x30\x36\x31\x0b\x30\x09\x06\x03\x55\x04\x06\x13\x02\x50" \
    "\x54\x31\x0f\x30\x0d\x06\x03\x55\x04\x0a\x0c\x06\x48\x61" \
    "\x73\x6c\x61\x62\x31\x16\x30\x14\x06\x03\x55\x04\x03\x0c" \
    "\x0d\x48\x61\x73\x6c\x61\x62\x20\x44\x65\x76\x69\x63\x65" \
    "\x30\x59\x30\x13\x06\x07\x2a\x86\x48\xce\x3d\x02\x01\x06" \
    "\x08\x2a\x86\x48\xce\x3d\x03\x01\x07\x03\x42\x00\x04\x10" \
    "\x88\xe3\xea\xc6\xaa\xdb\xcd\x69\x43\xc1\x2c\x36\x25\x2d" \
    "\xd0\xd7\x1f\x1d\x70\x4c\xb6\x60\x2f\xbb\xfd\x4d\x81\x8f" \
    "\xaf\x87\xe4\xae\x89\xb1\x73\xa8\xaf\xeb\x74\xaf\x86\x1d" \
    "\x03\x3d\x63\x02\xb8\x83\x30\x44\x27\xde\x9f\x49\x92\xcc" \
    "\xab\xfd\xdb\x30\x97\x65\xe7\xa3\x76\x30\x74\x30\x0f\x06" \
    "\x03\x55\x1d\x13\x04\x08\x30\x06\x01\x01\xff\x02\x01\x00" \
    "\x30\x1d\x06\x03\x55\x1d\x0e\x04\x16\x04\x14\xee\x38\x51" \
    "\xe2\x7b\xe7\xac\x1f\xc9\xc5\xd3\xdd\xc7\x80\x31\x58\xbf" \
    "\x62\x5c\x1b\x30\x1f\x06\x03\x55\x1d\x23\x04\x18\x30\x16" \
    "\x80\x14\xee\x38\x51\xe2\x7b\xe7\xac\x1f\xc9\xc5\xd3\xdd" \
    "\xc7\x80\x31\x58\xbf\x62\x5c\x1b\x30\x0e\x06\x03\x55\x1d" \
    "\x0f\x01\x01\xff\x04\x04\x03\x02\x06\xc0\x30\x11\x06\x09" \
    "\x60\x86\x48\x01\x86\xf8\x42\x01\x01\x04\x04\x03\x02\x04" \
    "\x10\x30\x0c\x06\x08\x2a\x86\x48\xce\x3d\x04\x03\x02\x05" \
    "\x00\x03\x48\x00\x30\x45\x02\x21\x00\xd8\x6f\xd0\x8d\x35" \
    "\xef\x8c\x4b\x4b\xaa\x2b\x5d\x70\xfa\x36\xcf\x84\x97\xbb" \
    "\xae\x88\x4a\x3d\x2d\x92\x82\x02\x36\x93\xab\x99\x41\x02" \
    "\x20\x72\xdc\xb1\x0f\x76\xbc\x6b\x82\xc9\x94\x10\x9a\x8a" \
    "\xed\xe1\x2b\xad\x5b\x30\x5d\xb5\x68\xe7\x23\x56\x5e\xe4" \
    "\x36\xc6\x81\x8e\xd9\xb8\x73\x0b\xfa\x0e\x22\xab\xa3\x51" \
    "\xd3\xe4\x8d\x2f\x70\x66\xe2\xa8\x78\x18\xb2\x29\x24\x6b" \
    "\xf4\xaa\xda\x89\x45\x10\x57\xd2\x31\x10\x88\xe3\xea\xc6" \
    "\xaa\xdb\xcd\x69\x43\xc1\x2c\x36\x25\x2d\xd0\xd7\x1f\x1d" \
    "\x70\x4c\xb6\x60\x2f\xbb\xfd\x4d\x81\x8f\xaf\x87\xe4\xae" \
    "\x89\xb1\x73\xa8\xaf\xeb\x74\xaf\x86\x1d\x03\x3d\x63\x02" \
    "\xb8\x83\x30\x44\x27\xde\x9f\x49\x92\xcc\xab\xfd\xdb\x30" \
    "\x97\x65\xe7";


/* 
 * Return the device certificate, used for attestation, in DER format
 */
int plat_get_device_cert(void **dc_ptr, unsigned int *dc_len){
    assert(dc_ptr != NULL);
    assert(dc_len != NULL);

    *dc_ptr = (void *)dc_der;
	*dc_len = sizeof(dc_der) - 1;

    return 0;
}

int plat_get_acc_key(void **ak_ptr, unsigned int *ak_len){
	assert(ak_ptr != NULL);
	assert(ak_len != NULL);

	*ak_ptr = (void *)ak_blob;
	*ak_len = sizeof(ak_blob) - 1;

	return 0;
}


int plat_get_dck_blob(void **dck_ptr, unsigned int *dc_len, unsigned int *ak_len){
    assert(dck_ptr != NULL);
    assert(dc_len != NULL);
	assert(ak_len != NULL);

    *dck_ptr = (void *)dck_blob;
	*dc_len = sizeof(dc_der) - 1;
	*ak_len = (sizeof(ak_blob) - 1)/3;

    return 0;
}


/* TODO
 * Update the device certificate used for attestation
 */
int plat_update_device_cert(void *hwkey, void *new_cert, unsigned int *cert_len){
    //Not implemented
    return 0;
}


