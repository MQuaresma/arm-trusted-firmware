#include <assert.h>
#include <string.h>

#include <plat/common/platform.h>
#include <platform_def.h>

static unsigned char dc_der[] = \
	"\x30\x82\x01\xf1\x30\x82\x01\x50\xa0\x03\x02\x01\x02\x02" \
	"\x01\x01\x30\x0c\x06\x08\x2a\x86\x48\xce\x3d\x04\x03\x02" \
	"\x05\x00\x30\x11\x31\x0f\x30\x0d\x06\x03\x55\x04\x03\x0c" \
	"\x06\x48\x61\x73\x6c\x61\x62\x30\x1e\x17\x0d\x32\x30\x30" \
	"\x34\x31\x37\x31\x36\x34\x35\x35\x37\x5a\x17\x0d\x32\x30" \
	"\x30\x37\x31\x36\x31\x36\x34\x35\x35\x37\x5a\x30\x18\x31" \
	"\x16\x30\x14\x06\x03\x55\x04\x03\x0c\x0d\x48\x61\x73\x6c" \
	"\x61\x62\x20\x44\x65\x76\x69\x63\x65\x30\x81\x9b\x30\x10" \
	"\x06\x07\x2a\x86\x48\xce\x3d\x02\x01\x06\x05\x2b\x81\x04" \
	"\x00\x23\x03\x81\x86\x00\x04\x01\x70\x32\x21\x9c\x57\x6c" \
	"\xb7\x85\xe0\x76\x6e\xf4\xec\xa3\x49\x75\x53\x72\x39\x45" \
	"\x3b\x5c\x20\x2f\x74\xd3\xec\xbb\x3c\x3d\x4e\x7d\x28\x3a" \
	"\xff\x46\x9b\xfb\x45\x97\x49\x0f\xa4\x84\x05\x60\xca\x45" \
	"\x01\xc1\x45\x1a\x52\xbc\xe2\x74\x40\xa2\xfa\x0e\x4f\xfb" \
	"\x83\x77\x71\x00\x9a\x4e\xf4\x29\x08\x72\xea\x4c\x6d\xca" \
	"\x6d\xd1\x4d\xaa\x67\xed\x17\xbf\xd6\x02\x30\xad\x20\xc3" \
	"\xcb\xd3\xb1\x6f\xe0\xe6\xc0\x4f\x37\x9c\x32\x83\x1a\x16" \
	"\x7f\x28\x89\xb6\xc2\x13\xdc\x8f\xc7\xed\xac\x1e\xc8\x55" \
	"\x56\x43\xfe\x6b\x12\x01\x18\x92\xc2\x8a\xe7\x5e\xa1\xa3" \
	"\x4d\x30\x4b\x30\x1f\x06\x03\x55\x1d\x23\x04\x18\x30\x16" \
	"\x80\x14\x35\x80\x27\xb4\xb3\xdc\xf3\xe1\xf5\xe4\xd4\xcd" \
	"\x6c\xef\x4e\xeb\x84\x03\x48\x8b\x30\x1d\x06\x03\x55\x1d" \
	"\x0e\x04\x16\x04\x14\x17\xdf\x6e\x8a\x05\x29\x30\x7d\x9e" \
	"\x06\x4b\x7d\x84\x82\xde\x34\x4c\x8f\x6d\x88\x30\x09\x06" \
	"\x03\x55\x1d\x13\x04\x02\x30\x00\x30\x0c\x06\x08\x2a\x86" \
	"\x48\xce\x3d\x04\x03\x02\x05\x00\x03\x81\x8c\x00\x30\x81" \
	"\x88\x02\x42\x00\xba\x4a\x4b\x8a\x42\x46\x62\x1e\xf2\x72" \
	"\x0a\x0b\x34\x48\x2e\xdb\xa5\x59\xc4\x8b\xbe\x2e\xa7\x46" \
	"\x1a\x52\x5a\x10\x7b\x08\xf7\x7c\x42\x57\x7c\x8a\x5c\x08" \
	"\x08\xb4\xdb\x6f\xb7\xb3\xd5\x66\x04\x33\x9c\x1c\x4d\xc3" \
	"\x9a\x47\xe0\xce\x87\x6a\x57\x2b\xb2\xf9\x28\x36\xf1\x02" \
	"\x42\x01\xd2\x13\x3d\x8c\x4e\xc3\x0a\x84\x70\x77\xab\x8f" \
	"\x78\x34\x2c\x55\x46\xa2\x6f\xc5\x6c\x54\xa8\x2f\xf6\x09" \
	"\xea\x20\xa8\x29\x93\x65\xc2\xd3\x86\xa1\xcc\xb2\x8f\x4f" \
	"\xaa\xa9\x7b\x1c\x4c\x86\x61\xa6\xc7\xa3\x6e\xef\x33\x57" \
	"\xd1\xd1\xd5\x4b\x0b\x2b\x5b\x35\x63\x18\x23";	

static unsigned char ak_blob[] = \
	"\xf5\xd3\x00\xe1\x8a\xb9\x52\x8d\xc2\xee\xed\xf9\x01\x6e" \
	"\xd7\x23\x8b\x2f\x39\xe5\x3f\x65\x86\x9c\xa2\x3f\xf7\x3f" \
	"\xa5\xc8\x3c\x48\x04\x58\x6f\xf5\xc7\x1e\xc8\xc8\x46\xd0" \
	"\x01\x78\x85\x44\x96\xdf\x1b\x2e\x50\xa1\xd5\x97\x54\xb9" \
	"\x7d\x58\x12\x75\xb8\x38\x5f\xfc\x76\x02";

static unsigned char dck_blob[] = \
	"\x30\x82\x01\xf1\x30\x82\x01\x50\xa0\x03\x02\x01\x02\x02" \
	"\x01\x01\x30\x0c\x06\x08\x2a\x86\x48\xce\x3d\x04\x03\x02" \
	"\x05\x00\x30\x11\x31\x0f\x30\x0d\x06\x03\x55\x04\x03\x0c" \
	"\x06\x48\x61\x73\x6c\x61\x62\x30\x1e\x17\x0d\x32\x30\x30" \
	"\x34\x31\x37\x31\x36\x34\x35\x35\x37\x5a\x17\x0d\x32\x30" \
	"\x30\x37\x31\x36\x31\x36\x34\x35\x35\x37\x5a\x30\x18\x31" \
	"\x16\x30\x14\x06\x03\x55\x04\x03\x0c\x0d\x48\x61\x73\x6c" \
	"\x61\x62\x20\x44\x65\x76\x69\x63\x65\x30\x81\x9b\x30\x10" \
	"\x06\x07\x2a\x86\x48\xce\x3d\x02\x01\x06\x05\x2b\x81\x04" \
	"\x00\x23\x03\x81\x86\x00\x04\x01\x70\x32\x21\x9c\x57\x6c" \
	"\xb7\x85\xe0\x76\x6e\xf4\xec\xa3\x49\x75\x53\x72\x39\x45" \
	"\x3b\x5c\x20\x2f\x74\xd3\xec\xbb\x3c\x3d\x4e\x7d\x28\x3a" \
	"\xff\x46\x9b\xfb\x45\x97\x49\x0f\xa4\x84\x05\x60\xca\x45" \
	"\x01\xc1\x45\x1a\x52\xbc\xe2\x74\x40\xa2\xfa\x0e\x4f\xfb" \
	"\x83\x77\x71\x00\x9a\x4e\xf4\x29\x08\x72\xea\x4c\x6d\xca" \
	"\x6d\xd1\x4d\xaa\x67\xed\x17\xbf\xd6\x02\x30\xad\x20\xc3" \
	"\xcb\xd3\xb1\x6f\xe0\xe6\xc0\x4f\x37\x9c\x32\x83\x1a\x16" \
	"\x7f\x28\x89\xb6\xc2\x13\xdc\x8f\xc7\xed\xac\x1e\xc8\x55" \
	"\x56\x43\xfe\x6b\x12\x01\x18\x92\xc2\x8a\xe7\x5e\xa1\xa3" \
	"\x4d\x30\x4b\x30\x1f\x06\x03\x55\x1d\x23\x04\x18\x30\x16" \
	"\x80\x14\x35\x80\x27\xb4\xb3\xdc\xf3\xe1\xf5\xe4\xd4\xcd" \
	"\x6c\xef\x4e\xeb\x84\x03\x48\x8b\x30\x1d\x06\x03\x55\x1d" \
	"\x0e\x04\x16\x04\x14\x17\xdf\x6e\x8a\x05\x29\x30\x7d\x9e" \
	"\x06\x4b\x7d\x84\x82\xde\x34\x4c\x8f\x6d\x88\x30\x09\x06" \
	"\x03\x55\x1d\x13\x04\x02\x30\x00\x30\x0c\x06\x08\x2a\x86" \
	"\x48\xce\x3d\x04\x03\x02\x05\x00\x03\x81\x8c\x00\x30\x81" \
	"\x88\x02\x42\x00\xba\x4a\x4b\x8a\x42\x46\x62\x1e\xf2\x72" \
	"\x0a\x0b\x34\x48\x2e\xdb\xa5\x59\xc4\x8b\xbe\x2e\xa7\x46" \
	"\x1a\x52\x5a\x10\x7b\x08\xf7\x7c\x42\x57\x7c\x8a\x5c\x08" \
	"\x08\xb4\xdb\x6f\xb7\xb3\xd5\x66\x04\x33\x9c\x1c\x4d\xc3" \
	"\x9a\x47\xe0\xce\x87\x6a\x57\x2b\xb2\xf9\x28\x36\xf1\x02" \
	"\x42\x01\xd2\x13\x3d\x8c\x4e\xc3\x0a\x84\x70\x77\xab\x8f" \
	"\x78\x34\x2c\x55\x46\xa2\x6f\xc5\x6c\x54\xa8\x2f\xf6\x09" \
	"\xea\x20\xa8\x29\x93\x65\xc2\xd3\x86\xa1\xcc\xb2\x8f\x4f" \
	"\xaa\xa9\x7b\x1c\x4c\x86\x61\xa6\xc7\xa3\x6e\xef\x33\x57" \
	"\xd1\xd1\xd5\x4b\x0b\x2b\x5b\x35\x63\x18\x23\xf5\xd3\x00" \
	"\xe1\x8a\xb9\x52\x8d\xc2\xee\xed\xf9\x01\x6e\xd7\x23\x8b" \
	"\x2f\x39\xe5\x3f\x65\x86\x9c\xa2\x3f\xf7\x3f\xa5\xc8\x3c" \
	"\x48\x04\x58\x6f\xf5\xc7\x1e\xc8\xc8\x46\xd0\x01\x78\x85" \
	"\x44\x96\xdf\x1b\x2e\x50\xa1\xd5\x97\x54\xb9\x7d\x58\x12" \
	"\x75\xb8\x38\x5f\xfc\x76\x02";

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
	*ak_len = sizeof(ak_blob) - 1;

    return 0;
}


/* TODO
 * Update the device certificate used for attestation
 */
int plat_update_device_cert(void *hwkey, void *new_cert, unsigned int *cert_len){
    //Not implemented
    return 0;
}


