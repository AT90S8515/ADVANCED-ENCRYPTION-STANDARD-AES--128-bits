
//AES implementation
 

/*
In this assignment you have to implement AES algorithm. The Advanced Encryption Standard (AES) 
specifies a FIPS-approved cryptographic algorithm that can be used to protect electronic data.
The AES algorithm is a symmetric block cipher that can encrypt (encipher) and decrypt (decipher)
information. Encryption converts data to an unintelligible form called ciphertext; decrypting the
ciphertext converts the data back into its original form, called plaintext. The AES algorithm can
use cryptographic keys of 128, 192, and 256 bits to encrypt and decrypt data in blocks of 128 bits.
*/

//adding the dirrectives which are requied to code AES

#include<iostream>//input output stream Header File
#include<math.h>////Directive of Math operations
using namespace std;
// substitutes a byte
//A SBOX based table that will substitute the values in mix
//Column against the values that are being multiplied
//with 2
unsigned char sub2(unsigned char byte) {
	//it contains 256 values as 256 hexa decimal values
	static unsigned char sbox[256] = {
	   0x00,0x02,0x04,0x06,0x08,0x0a,0x0c,0x0e,0x10,0x12,0x14,0x16,0x18,0x1a,0x1c,0x1e,
0x20,0x22,0x24,0x26,0x28,0x2a,0x2c,0x2e,0x30,0x32,0x34,0x36,0x38,0x3a,0x3c,0x3e,
0x40,0x42,0x44,0x46,0x48,0x4a,0x4c,0x4e,0x50,0x52,0x54,0x56,0x58,0x5a,0x5c,0x5e,
0x60,0x62,0x64,0x66,0x68,0x6a,0x6c,0x6e,0x70,0x72,0x74,0x76,0x78,0x7a,0x7c,0x7e,
0x80,0x82,0x84,0x86,0x88,0x8a,0x8c,0x8e,0x90,0x92,0x94,0x96,0x98,0x9a,0x9c,0x9e,
0xa0,0xa2,0xa4,0xa6,0xa8,0xaa,0xac,0xae,0xb0,0xb2,0xb4,0xb6,0xb8,0xba,0xbc,0xbe,
0xc0,0xc2,0xc4,0xc6,0xc8,0xca,0xcc,0xce,0xd0,0xd2,0xd4,0xd6,0xd8,0xda,0xdc,0xde,
0xe0,0xe2,0xe4,0xe6,0xe8,0xea,0xec,0xee,0xf0,0xf2,0xf4,0xf6,0xf8,0xfa,0xfc,0xfe,
0x1b,0x19,0x1f,0x1d,0x13,0x11,0x17,0x15,0x0b,0x09,0x0f,0x0d,0x03,0x01,0x07,0x05,
0x3b,0x39,0x3f,0x3d,0x33,0x31,0x37,0x35,0x2b,0x29,0x2f,0x2d,0x23,0x21,0x27,0x25,
0x5b,0x59,0x5f,0x5d,0x53,0x51,0x57,0x55,0x4b,0x49,0x4f,0x4d,0x43,0x41,0x47,0x45,
0x7b,0x79,0x7f,0x7d,0x73,0x71,0x77,0x75,0x6b,0x69,0x6f,0x6d,0x63,0x61,0x67,0x65,
0x9b,0x99,0x9f,0x9d,0x93,0x91,0x97,0x95,0x8b,0x89,0x8f,0x8d,0x83,0x81,0x87,0x85,
0xbb,0xb9,0xbf,0xbd,0xb3,0xb1,0xb7,0xb5,0xab,0xa9,0xaf,0xad,0xa3,0xa1,0xa7,0xa5,
0xdb,0xd9,0xdf,0xdd,0xd3,0xd1,0xd7,0xd5,0xcb,0xc9,0xcf,0xcd,0xc3,0xc1,0xc7,0xc5,
0xfb,0xf9,0xff,0xfd,0xf3,0xf1,0xf7,0xf5,0xeb,0xe9,0xef,0xed,0xe3,0xe1,0xe7,0xe5
	};
	//returning the required value
	return sbox[byte];
}
// substitutes a byte
//A SBOX based table that will substitute the values in mix
//Column against the values that are being multiplied
//with 2
unsigned char sub3(unsigned char byte) {
	//it contains 256values as of Hexa decimal tvalues
	static unsigned char sbox[256] = {
	0x00,0x03,0x06,0x05,0x0c,0x0f,0x0a,0x09,0x18,0x1b,0x1e,0x1d,0x14,0x17,0x12,0x11,
0x30,0x33,0x36,0x35,0x3c,0x3f,0x3a,0x39,0x28,0x2b,0x2e,0x2d,0x24,0x27,0x22,0x21,
0x60,0x63,0x66,0x65,0x6c,0x6f,0x6a,0x69,0x78,0x7b,0x7e,0x7d,0x74,0x77,0x72,0x71,
0x50,0x53,0x56,0x55,0x5c,0x5f,0x5a,0x59,0x48,0x4b,0x4e,0x4d,0x44,0x47,0x42,0x41,
0xc0,0xc3,0xc6,0xc5,0xcc,0xcf,0xca,0xc9,0xd8,0xdb,0xde,0xdd,0xd4,0xd7,0xd2,0xd1,
0xf0,0xf3,0xf6,0xf5,0xfc,0xff,0xfa,0xf9,0xe8,0xeb,0xee,0xed,0xe4,0xe7,0xe2,0xe1,
0xa0,0xa3,0xa6,0xa5,0xac,0xaf,0xaa,0xa9,0xb8,0xbb,0xbe,0xbd,0xb4,0xb7,0xb2,0xb1,
0x90,0x93,0x96,0x95,0x9c,0x9f,0x9a,0x99,0x88,0x8b,0x8e,0x8d,0x84,0x87,0x82,0x81,
0x9b,0x98,0x9d,0x9e,0x97,0x94,0x91,0x92,0x83,0x80,0x85,0x86,0x8f,0x8c,0x89,0x8a,
0xab,0xa8,0xad,0xae,0xa7,0xa4,0xa1,0xa2,0xb3,0xb0,0xb5,0xb6,0xbf,0xbc,0xb9,0xba,
0xfb,0xf8,0xfd,0xfe,0xf7,0xf4,0xf1,0xf2,0xe3,0xe0,0xe5,0xe6,0xef,0xec,0xe9,0xea,
0xcb,0xc8,0xcd,0xce,0xc7,0xc4,0xc1,0xc2,0xd3,0xd0,0xd5,0xd6,0xdf,0xdc,0xd9,0xda,
0x5b,0x58,0x5d,0x5e,0x57,0x54,0x51,0x52,0x43,0x40,0x45,0x46,0x4f,0x4c,0x49,0x4a,
0x6b,0x68,0x6d,0x6e,0x67,0x64,0x61,0x62,0x73,0x70,0x75,0x76,0x7f,0x7c,0x79,0x7a,
0x3b,0x38,0x3d,0x3e,0x37,0x34,0x31,0x32,0x23,0x20,0x25,0x26,0x2f,0x2c,0x29,0x2a,
0x0b,0x08,0x0d,0x0e,0x07,0x04,0x01,0x02,0x13,0x10,0x15,0x16,0x1f,0x1c,0x19,0x1a
	};
	//returning a value
	return sbox[byte];
}
// substitutes a byte
//A SBOX based table that will substitute the values in incverse mix
//Column against the values that are being multiplied
//with 9
unsigned char sub9(unsigned char byte) {
	//contains 256 values as of the hexadecimal values
	static unsigned char sbox[256] = {
	   0x00,0x09,0x12,0x1b,0x24,0x2d,0x36,0x3f,0x48,0x41,0x5a,0x53,0x6c,0x65,0x7e,0x77,
0x90,0x99,0x82,0x8b,0xb4,0xbd,0xa6,0xaf,0xd8,0xd1,0xca,0xc3,0xfc,0xf5,0xee,0xe7,
0x3b,0x32,0x29,0x20,0x1f,0x16,0x0d,0x04,0x73,0x7a,0x61,0x68,0x57,0x5e,0x45,0x4c,
0xab,0xa2,0xb9,0xb0,0x8f,0x86,0x9d,0x94,0xe3,0xea,0xf1,0xf8,0xc7,0xce,0xd5,0xdc,
0x76,0x7f,0x64,0x6d,0x52,0x5b,0x40,0x49,0x3e,0x37,0x2c,0x25,0x1a,0x13,0x08,0x01,
0xe6,0xef,0xf4,0xfd,0xc2,0xcb,0xd0,0xd9,0xae,0xa7,0xbc,0xb5,0x8a,0x83,0x98,0x91,
0x4d,0x44,0x5f,0x56,0x69,0x60,0x7b,0x72,0x05,0x0c,0x17,0x1e,0x21,0x28,0x33,0x3a,
0xdd,0xd4,0xcf,0xc6,0xf9,0xf0,0xeb,0xe2,0x95,0x9c,0x87,0x8e,0xb1,0xb8,0xa3,0xaa,
0xec,0xe5,0xfe,0xf7,0xc8,0xc1,0xda,0xd3,0xa4,0xad,0xb6,0xbf,0x80,0x89,0x92,0x9b,
0x7c,0x75,0x6e,0x67,0x58,0x51,0x4a,0x43,0x34,0x3d,0x26,0x2f,0x10,0x19,0x02,0x0b,
0xd7,0xde,0xc5,0xcc,0xf3,0xfa,0xe1,0xe8,0x9f,0x96,0x8d,0x84,0xbb,0xb2,0xa9,0xa0,
0x47,0x4e,0x55,0x5c,0x63,0x6a,0x71,0x78,0x0f,0x06,0x1d,0x14,0x2b,0x22,0x39,0x30,
0x9a,0x93,0x88,0x81,0xbe,0xb7,0xac,0xa5,0xd2,0xdb,0xc0,0xc9,0xf6,0xff,0xe4,0xed,
0x0a,0x03,0x18,0x11,0x2e,0x27,0x3c,0x35,0x42,0x4b,0x50,0x59,0x66,0x6f,0x74,0x7d,
0xa1,0xa8,0xb3,0xba,0x85,0x8c,0x97,0x9e,0xe9,0xe0,0xfb,0xf2,0xcd,0xc4,0xdf,0xd6,
0x31,0x38,0x23,0x2a,0x15,0x1c,0x07,0x0e,0x79,0x70,0x6b,0x62,0x5d,0x54,0x4f,0x46
	};
	//returning a value
	return sbox[byte];
}
// substitutes a byte
//A SBOX based table that will substitute the values in incverse mix
//Column against the values that are being multiplied
//with 11
unsigned char sub11(unsigned char byte) {
	//contains 256 values as of the hexadecimal values
	static unsigned char sbox[256] = {
	 0x00,0x0b,0x16,0x1d,0x2c,0x27,0x3a,0x31,0x58,0x53,0x4e,0x45,0x74,0x7f,0x62,0x69,
0xb0,0xbb,0xa6,0xad,0x9c,0x97,0x8a,0x81,0xe8,0xe3,0xfe,0xf5,0xc4,0xcf,0xd2,0xd9,
0x7b,0x70,0x6d,0x66,0x57,0x5c,0x41,0x4a,0x23,0x28,0x35,0x3e,0x0f,0x04,0x19,0x12,
0xcb,0xc0,0xdd,0xd6,0xe7,0xec,0xf1,0xfa,0x93,0x98,0x85,0x8e,0xbf,0xb4,0xa9,0xa2,
0xf6,0xfd,0xe0,0xeb,0xda,0xd1,0xcc,0xc7,0xae,0xa5,0xb8,0xb3,0x82,0x89,0x94,0x9f,
0x46,0x4d,0x50,0x5b,0x6a,0x61,0x7c,0x77,0x1e,0x15,0x08,0x03,0x32,0x39,0x24,0x2f,
0x8d,0x86,0x9b,0x90,0xa1,0xaa,0xb7,0xbc,0xd5,0xde,0xc3,0xc8,0xf9,0xf2,0xef,0xe4,
0x3d,0x36,0x2b,0x20,0x11,0x1a,0x07,0x0c,0x65,0x6e,0x73,0x78,0x49,0x42,0x5f,0x54,
0xf7,0xfc,0xe1,0xea,0xdb,0xd0,0xcd,0xc6,0xaf,0xa4,0xb9,0xb2,0x83,0x88,0x95,0x9e,
0x47,0x4c,0x51,0x5a,0x6b,0x60,0x7d,0x76,0x1f,0x14,0x09,0x02,0x33,0x38,0x25,0x2e,
0x8c,0x87,0x9a,0x91,0xa0,0xab,0xb6,0xbd,0xd4,0xdf,0xc2,0xc9,0xf8,0xf3,0xee,0xe5,
0x3c,0x37,0x2a,0x21,0x10,0x1b,0x06,0x0d,0x64,0x6f,0x72,0x79,0x48,0x43,0x5e,0x55,
0x01,0x0a,0x17,0x1c,0x2d,0x26,0x3b,0x30,0x59,0x52,0x4f,0x44,0x75,0x7e,0x63,0x68,
0xb1,0xba,0xa7,0xac,0x9d,0x96,0x8b,0x80,0xe9,0xe2,0xff,0xf4,0xc5,0xce,0xd3,0xd8,
0x7a,0x71,0x6c,0x67,0x56,0x5d,0x40,0x4b,0x22,0x29,0x34,0x3f,0x0e,0x05,0x18,0x13,
0xca,0xc1,0xdc,0xd7,0xe6,0xed,0xf0,0xfb,0x92,0x99,0x84,0x8f,0xbe,0xb5,0xa8,0xa3
	};
	//returning a value
	return sbox[byte];
}
// substitutes a byte
//A SBOX based table that will substitute the values in incverse mix
//Column against the values that are being multiplied
//with 13
unsigned char sub13(unsigned char byte) {

	//contains 256 values as of the hexadecimal values
	static unsigned char sbox[256] = {
	  0x00,0x0d,0x1a,0x17,0x34,0x39,0x2e,0x23,0x68,0x65,0x72,0x7f,0x5c,0x51,0x46,0x4b,
0xd0,0xdd,0xca,0xc7,0xe4,0xe9,0xfe,0xf3,0xb8,0xb5,0xa2,0xaf,0x8c,0x81,0x96,0x9b,
0xbb,0xb6,0xa1,0xac,0x8f,0x82,0x95,0x98,0xd3,0xde,0xc9,0xc4,0xe7,0xea,0xfd,0xf0,
0x6b,0x66,0x71,0x7c,0x5f,0x52,0x45,0x48,0x03,0x0e,0x19,0x14,0x37,0x3a,0x2d,0x20,
0x6d,0x60,0x77,0x7a,0x59,0x54,0x43,0x4e,0x05,0x08,0x1f,0x12,0x31,0x3c,0x2b,0x26,
0xbd,0xb0,0xa7,0xaa,0x89,0x84,0x93,0x9e,0xd5,0xd8,0xcf,0xc2,0xe1,0xec,0xfb,0xf6,
0xd6,0xdb,0xcc,0xc1,0xe2,0xef,0xf8,0xf5,0xbe,0xb3,0xa4,0xa9,0x8a,0x87,0x90,0x9d,
0x06,0x0b,0x1c,0x11,0x32,0x3f,0x28,0x25,0x6e,0x63,0x74,0x79,0x5a,0x57,0x40,0x4d,
0xda,0xd7,0xc0,0xcd,0xee,0xe3,0xf4,0xf9,0xb2,0xbf,0xa8,0xa5,0x86,0x8b,0x9c,0x91,
0x0a,0x07,0x10,0x1d,0x3e,0x33,0x24,0x29,0x62,0x6f,0x78,0x75,0x56,0x5b,0x4c,0x41,
0x61,0x6c,0x7b,0x76,0x55,0x58,0x4f,0x42,0x09,0x04,0x13,0x1e,0x3d,0x30,0x27,0x2a,
0xb1,0xbc,0xab,0xa6,0x85,0x88,0x9f,0x92,0xd9,0xd4,0xc3,0xce,0xed,0xe0,0xf7,0xfa,
0xb7,0xba,0xad,0xa0,0x83,0x8e,0x99,0x94,0xdf,0xd2,0xc5,0xc8,0xeb,0xe6,0xf1,0xfc,
0x67,0x6a,0x7d,0x70,0x53,0x5e,0x49,0x44,0x0f,0x02,0x15,0x18,0x3b,0x36,0x21,0x2c,
0x0c,0x01,0x16,0x1b,0x38,0x35,0x22,0x2f,0x64,0x69,0x7e,0x73,0x50,0x5d,0x4a,0x47,
0xdc,0xd1,0xc6,0xcb,0xe8,0xe5,0xf2,0xff,0xb4,0xb9,0xae,0xa3,0x80,0x8d,0x9a,0x97
	};
	//returning a value
	return sbox[byte];
}
// substitutes a byte
//A SBOX based table that will substitute the values in incverse mix
//Column against the values that are being multiplied
//with 14
unsigned char sub14(unsigned char byte) {
	//contains 256 values	
	static unsigned char sbox[256] = {
	  0x00,0x0e,0x1c,0x12,0x38,0x36,0x24,0x2a,0x70,0x7e,0x6c,0x62,0x48,0x46,0x54,0x5a,
0xe0,0xee,0xfc,0xf2,0xd8,0xd6,0xc4,0xca,0x90,0x9e,0x8c,0x82,0xa8,0xa6,0xb4,0xba,
0xdb,0xd5,0xc7,0xc9,0xe3,0xed,0xff,0xf1,0xab,0xa5,0xb7,0xb9,0x93,0x9d,0x8f,0x81,
0x3b,0x35,0x27,0x29,0x03,0x0d,0x1f,0x11,0x4b,0x45,0x57,0x59,0x73,0x7d,0x6f,0x61,
0xad,0xa3,0xb1,0xbf,0x95,0x9b,0x89,0x87,0xdd,0xd3,0xc1,0xcf,0xe5,0xeb,0xf9,0xf7,
0x4d,0x43,0x51,0x5f,0x75,0x7b,0x69,0x67,0x3d,0x33,0x21,0x2f,0x05,0x0b,0x19,0x17,
0x76,0x78,0x6a,0x64,0x4e,0x40,0x52,0x5c,0x06,0x08,0x1a,0x14,0x3e,0x30,0x22,0x2c,
0x96,0x98,0x8a,0x84,0xae,0xa0,0xb2,0xbc,0xe6,0xe8,0xfa,0xf4,0xde,0xd0,0xc2,0xcc,
0x41,0x4f,0x5d,0x53,0x79,0x77,0x65,0x6b,0x31,0x3f,0x2d,0x23,0x09,0x07,0x15,0x1b,
0xa1,0xaf,0xbd,0xb3,0x99,0x97,0x85,0x8b,0xd1,0xdf,0xcd,0xc3,0xe9,0xe7,0xf5,0xfb,
0x9a,0x94,0x86,0x88,0xa2,0xac,0xbe,0xb0,0xea,0xe4,0xf6,0xf8,0xd2,0xdc,0xce,0xc0,
0x7a,0x74,0x66,0x68,0x42,0x4c,0x5e,0x50,0x0a,0x04,0x16,0x18,0x32,0x3c,0x2e,0x20,
0xec,0xe2,0xf0,0xfe,0xd4,0xda,0xc8,0xc6,0x9c,0x92,0x80,0x8e,0xa4,0xaa,0xb8,0xb6,
0x0c,0x02,0x10,0x1e,0x34,0x3a,0x28,0x26,0x7c,0x72,0x60,0x6e,0x44,0x4a,0x58,0x56,
0x37,0x39,0x2b,0x25,0x0f,0x01,0x13,0x1d,0x47,0x49,0x5b,0x55,0x7f,0x71,0x63,0x6d,
0xd7,0xd9,0xcb,0xc5,0xef,0xe1,0xf3,0xfd,0xa7,0xa9,0xbb,0xb5,0x9f,0x91,0x83,0x8d
	};
	//returnsa value
	return sbox[byte];
}
unsigned char substitute(unsigned char byte) {

	static unsigned char sbox[256] = {
	   0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
	   0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
	   0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
	   0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
	   0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
	   0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
	   0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
	   0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
	   0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
	   0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
	   0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
	   0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
	   0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
	   0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
	   0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
	   0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
	};

	return sbox[byte];
}

unsigned char reverse_substitute(unsigned char byte) {
	static unsigned char rsbox[256] = {
	0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb
	, 0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb
	, 0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e
	, 0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25
	, 0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92
	, 0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84
	, 0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06
	, 0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b
	, 0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73
	, 0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e
	, 0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b
	, 0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4
	, 0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f
	, 0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef
	, 0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61
	, 0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d };

	return rsbox[byte];
}

/*
void rotate_left(unsigned char* byte_array) {
	unsigned char a = byte_array[12];
	for (int i = 12; i <= 14; i++) {
		byte_array[i] = byte_array[i + 1];
	}
	byte_array[15] = a;
}*/

//A provided function prototype which is being used for the substitution of Bytes from the S_BOx
void SubBytes(unsigned char* state) {
	for (int i = 0; i < 16; i++) {
		state[i] = substitute(state[i]);//index by index
	}
}
//A provided function prototype which is being used for the substitution of Bytes from the inv S_BOx
void InvSubBytes(unsigned char* state) {
	for (int i = 0; i < 16; i++) {
		state[i] = reverse_substitute(state[i]);//index by index
	}
}

void InvShiftRows(unsigned char* state) {
	//A function with provided prototype that will be actually 
	//Shifting rows into columns 
	//tried it to do with the loop but i destroyed my code 2 times
	//using loops to do the same process was showing error  as it was having linking error
	//dont need to  convert ist 4 elements of the provided array
	//as per implementation requirements
	unsigned char a, b, c, d;
	/*unsigned char myarr[4];
	for (int i = 0; i < 4; i++) {
		myarr[i] = state[i + 4];
	}
	for (int i = 0; i < 3; i++) {
		state[i + 5] = myarr[i];
	}
	state[4] = myarr[4];*/
	a = state[4];
	b = state[5];
	c = state[6];
	d = state[7];
	state[4] = d;
	state[5] = a;
	state[6] = b;
	state[7] = c;


	a = state[8];
	b = state[9];
	c = state[10];
	d = state[11];
	state[8] = c;
	state[9] = d;
	state[10] = a;
	state[11] = b;
	a = state[12];
	b = state[13];
	c = state[14];
	d = state[15];
	state[12] = b;
	state[13] = c;
	state[14] = d;
	state[15] = a;

}

void ShiftRows(unsigned char* state) {
	//A function with provided prototype that will be actually 
	//Shifting rows into columns 
	//tried it to do with the loop but i destroyed my code 2 times
	//using loops to do the same process was showing error  as it was having linking error

	unsigned char a = state[4];
	unsigned char b = state[4];
	unsigned char c = state[4];
	unsigned char d = state[4];
	/*unsigned char myarr[4];
for (int i = 0; i < 4; i++) {
	myarr[i] = state[i + 4];
}
for (int i = 0; i < 3; i++) {
	state[i + 5] = myarr[i];
}
state[4] = myarr[4];*/
//using loops to do the same process was showing error  as it was having linking error

	for (int i = 4; i < 7; i++) {
		state[i] = state[i + 1];
	}
	state[7] = a;
	a = state[10];
	b = state[11];
	c = state[8];
	d = state[9];
	state[8] = a;
	state[9] = b;
	state[10] = c;
	state[11] = d;
	a = state[12];
	b = state[13];
	c = state[14];
	d = state[15];
	state[12] = d;
	state[13] = a;
	state[14] = b;
	state[15] = c;
}
//a provided function that was suposed to XOR the given values
//and it is done in this way by using the Xor operator
void addRoundKey(unsigned char* state, unsigned char* roundKey) {

	for (int i = 0; i < 16; i++) {//a provided prototyped function that willl be used for the 
		//xoring of the given two arrays
		//in unsigned form
		state[i] = state[i] ^ roundKey[i];
	}
}
//a provided function  that will do the left shift working
// a self created function that will be used for the working of shiftinng pf rows
void leftshift(unsigned char* ptr, int size) {
	unsigned char x = ptr[0];
	for (int i = 0; i < size - 1; i++) {
		ptr[i] = ptr[i + 1];
	}
	ptr[size - 1] = x;
}
//Helper functions to get the round constatt while expanding the given cipher key
unsigned char getRoundCons(int u) {
	//it wil be providing th e
	//constants for each round of generation of the cipher key
	//it will just receive an int as index and will return the supposed 
	//constant value that will be used  
	//in adding the round contant
	unsigned char round_cons[10] = { 0x01,0x02,0x04,0x08,
	0x10, 0x20, 0x40, 0x80,
	0x1b, 0x36 };
	return round_cons[u];
}
//another copy function that will be just  copying elements of one arraay
//into another array as we need to copy sipher key into arrays as w0,w1,w2,w3, etc
void copy(int start, int end, unsigned char* to, unsigned char* from) {
	for (int i = 0; i < 4; i++) {
		to[i] = from[start];
		start++;
	}
}
void generateKey(unsigned char* cipherkey, int u) {
	//initializing 9 arrays so that 
	// we can perform operation on ist 4 and gw3 and the 
	// we can go for the implementation of other arrays
	//as w4 w5 w6 w7
	//as per instructions
	unsigned char w0[4] = { 0,0,0,0 };
	unsigned char w1[4] = { 0,0,0,0 };
	unsigned char w2[4] = { 0,0,0,0 };
	unsigned char w3[4] = { 0,0,0,0 };
	unsigned char gw3[4] = { 0,0,0,0 };
	unsigned char w4[4] = { 0,0,0,0 };
	unsigned char w5[4] = { 0,0,0,0 };
	unsigned char w6[4] = { 0,0,0,0 };
	unsigned char w7[4] = { 0,0,0,0 };
	unsigned char round_cons[4] = { 01,00,00,00 };
	round_cons[0] = getRoundCons(u);// getting round constant
	//against the round of the generation of cipher key

	//ist 4 to w0
	copy(0, 4, w0, cipherkey);
	//4 to 8 into w1
	copy(4, 8, w1, cipherkey);
	//8 to 12 into w2
	copy(8, 12, w2, cipherkey);
	//12 to 16 into w3
	copy(12, 16, w3, cipherkey);
	//12 to 16 into gw3
	copy(12, 16, gw3, cipherkey);

	//performing ist operation of left shifting
		//on gw3
	leftshift(gw3, 4);
	for (int i = 0; i < 4; i++) {
		//substitution of elements 
		//from 12 to 16
		gw3[i] = substitute(gw3[i]);
	}

	for (int i = 0; i < 4; i++) {
		//xoring with round constant
		gw3[i] = gw3[i] ^ round_cons[i];
	}

	for (int i = 0; i < 4; i++) {
		w4[i] = w0[i] ^ gw3[i];//generating w4
	}
	for (int i = 0; i < 4; i++) {
		w5[i] = w4[i] ^ w1[i];//generating w5
	}
	for (int i = 0; i < 4; i++) {
		w6[i] = w5[i] ^ w2[i];//generating w6
	}
	for (int i = 0; i < 4; i++) {
		w7[i] = w6[i] ^ w3[i];//generating w7
	}

	int j = 0;
	//now copying the elements from w4,w5,w6,w7
	//into the cipher key
	for (int i = 0; i < 16; i++) {
		if (i >= 0 && i < 4) {
			cipherkey[i] = w4[j];
			//ist 4 elements
			j++;
		}
		else if (i >= 4 && i < 8) {
			cipherkey[i] = w5[j];
			//2nd 4 elements
			j++;
		}
		else if (i >= 8 && i < 12) {
			cipherkey[i] = w6[j];
			//3rd 4 elements
			j++;
		}
		else if (i >= 12 && i < 16) {
			cipherkey[i] = w7[j];
			//last 4 elements
			j++;
		}
		if (i == 3 || i == 7 || i == 11 || i == 15) {
			j = 0;
		}
	}
}
//given function
void KeyExpansion(unsigned char* cipherkey, unsigned char* expandedkey) {
	//a provided function prototypt that will be just 
	//caling the user defined helper
	//function which will be calling urthur helper(user defined functions)
	int j = 0;
	int k = 0;
	for (int i = 0; i <= 10; i++) {
		k = 0;
		for (; j < (i + 1) * 16; j++) {
			expandedkey[j] = cipherkey[k];
			k++;
		}
		if (i != 10) {
			generateKey(cipherkey, i);
		}
	}
}
//Most difficult implementation
void MixColumn(unsigned char* state) {
	//it ist declares two arrays of 4X4
	//ordinary as a temporary array
	unsigned char ordinary[4][4];
	//mul as an array for the mix constant 
	//table as per instructed
	unsigned char mul[4][4];
	int k = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			ordinary[i][j] = state[k];
			k++;
		}
	}
	//debugging with printing

/*for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout<<hex<<(int)ordinary[i][j];

		}
	}
	*/
	k = 0;
	//provided constant one d array
	unsigned char mix[16] = {
		0x02, 0x03, 0x01, 0x01,
		0x01, 0x02, 0x03, 0x01,
		0x01, 0x01, 0x02, 0x03,
		0x03, 0x01, 0x01, 0x02
	};
	//converting the provided one d array of mix column constant into 2d array
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			mul[i][j] = mix[k];
			k++;
		}
	}
	/*printing for self check/*
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << hex << (int)mul[i][j];
		}
	}
*/
//Multiplication based on 4X4 matrix
//a count int to populate the array
//starting with 0
//mul val to xor the operation of ist row with ist 
//column of 2nd matrix
//i am using the implementation based on 
//Rijndael mix columns 
//provided at ipfs.io/ipfs/QmXoypizjW3WknFiJnKLwHCnL72vedxjQkDDP1mXWo6uco/wiki/Rijndael_mix_columns.html
//FIPS PUB 197: the official AES standard (PDF file)
//as same based on the sbox and invrse s box

	int count = 0;
	unsigned char mul_val = NULL;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			mul_val = NULL;
			for (int k = 0; k < 4; k++) {
				if (mul[i][k] == 2) {//if 2 then substitute value from the 
					//table of 2
					mul_val = mul_val ^ sub2(ordinary[k][j]);
				}
				else if (mul[i][k] == 3) {
					//if 3 then substitute value from the 
					//table of 3
					mul_val = mul_val ^ sub3(ordinary[k][j]);
				}
				else if (mul[i][k] == 1) {
					//if 1 then simply xor the values
					mul_val = mul_val ^ ordinary[k][j];
				}
			}
			state[count] = mul_val;
			//putting values in one d array and the incrementing count integer
			count++;

		}
	}
	/*
	for(int i=0;i<16;i++){
	cout<<hex<<(int)state[i];
	}
	*/


}
void Transpose(unsigned char* to, unsigned char* from) {
	// a function that actually pefrforms the task of shifting rows into the columns

//actually performing the transpose
	//it will acepts two parameters 
	//one d arrays as to, from

	to[0] = from[0];
	to[4] = from[1];
	to[8] = from[2];
	to[12] = from[3];
	to[1] = from[4];
	to[5] = from[5];
	to[9] = from[6];
	to[13] = from[7];
	to[2] = from[8];
	to[6] = from[9];
	to[10] = from[10];
	to[14] = from[11];
	to[3] = from[12];
	to[7] = from[13];
	to[11] = from[14];
	to[15] = from[15];
	for (int i = 0; i < 16; ++i) {
		from[i] = to[i];
	}
}
void Encrypt(unsigned char* plaintext, unsigned char* cipherkey, unsigned char* ciphertext) {
	//copying the cipher key for expansion purpose
	unsigned char temp4[16];
	for (int i = 0; i < 16; i++) {
		temp4[i] = cipherkey[i];
	}
	unsigned char expandedkey[176];
	KeyExpansion(temp4, expandedkey);
	//array of 176 elemens that will have total of 11 round cipher keys
	unsigned char temp[16];
	unsigned char temp2[16];
	//taking transpose of plainn text
	Transpose(temp, plaintext);
	//taking transpose of cipher key
	Transpose(temp2, cipherkey);


	int key = 16;
	int popo = 0;
	//adding plaintext and cipher key
	addRoundKey(plaintext, cipherkey);

	for (int i = 0; i <= 9; i++) {
		SubBytes(plaintext);//substitution the plain text
		ShiftRows(plaintext);//shifting rows of plain text
		if (i != 9) {
			MixColumn(plaintext);
			//if it is not the last round
			//hen must mix the columns
		}
		popo = 0;
		for (; popo < 16; popo++) {
			//copying the 16 elements of 
			cipherkey[popo] = expandedkey[key];
			key++;
		}
		Transpose(temp2, cipherkey);
		//again taking transpose of the extracted cipher key
		addRoundKey(plaintext, cipherkey);
		//now adding cipher key of round 1 and the plain text after few operation 
		//to complete the operations
	}

	Transpose(temp2, plaintext);
	//transpose of the lastly generated plain text
	//so that we can compare it with the expected result
	for (int i = 0; i < 16; i++) {
		ciphertext[i] = temp2[i];
	}
	/*
	for (int u = 0; u < 16; u++) {
		cout << hex << (int)ciphertext[u];
	}*/

}


void InvMixColumn(unsigned char* state) {

	//it ist declares two arrays of 4X4
//ordinary as a temporary array
	unsigned char ordinary[4][4];
	//mul as an array for the mix constant 
	//table as per instructed
	unsigned char mul[4][4];
	int k = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			ordinary[i][j] = state[k];
			k++;
		}
	}
	k = 0;
	//debugging with printing

/*for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout<<hex<<(int)ordinary[i][j];

		}
	}
	*/
	unsigned char mix[16] = {
		0x0e, 0x0b, 0x0d, 0x09,
		0x09, 0x0e, 0x0b, 0x0d,
		0x0d, 0x09, 0x0e, 0x0b,
		0x0b, 0x0d, 0x09, 0x0e
	};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			mul[i][j] = mix[k];
			k++;
		}
	}
	/*printing for self check/*
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << hex << (int)mul[i][j];
		}
	}
*/
//Multiplication based on 4X4 matrix
//a count int to populate the array
//starting with 0
//mul val to xor the operation of ist row with ist 
//column of 2nd matrix
//i am using the implementation based on 
//Rijndael mix columns 
//provided at ipfs.io/ipfs/QmXoypizjW3WknFiJnKLwHCnL72vedxjQkDDP1mXWo6uco/wiki/Rijndael_mix_columns.html
//FIPS PUB 197: the official AES standard (PDF file)
//as same based on the sbox and invrse s box
	int status = 0;
	unsigned char mul_val = NULL;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			mul_val = NULL;
			for (int k = 0; k < 4; k++) {
				if (mul[i][k] == 9) {//if 9 then substitute value from the 
					//table of 9
					mul_val = mul_val ^ sub9(ordinary[k][j]);
				}
				else if (mul[i][k] == 11) {
					//if 11 then substitute value from the 
					//table of 11
					mul_val = mul_val ^ sub11(ordinary[k][j]);
				}
				else if (mul[i][k] == 13) {
					//if 13 then substitute value from the 
					//table of 13
					mul_val = mul_val ^ sub13(ordinary[k][j]);
				}
				else if (mul[i][k] == 14) {
					//if 14 then substitute value from the 
					//table of 14
					mul_val = mul_val ^ sub14(ordinary[k][j]);
				}
			}
			state[status] = mul_val;
			status++;

		}
	}

}
//it is a helper function to perform few short hand operations it will receive a number
//int as round one d expanded key and cipher key one d array
//it will copy i*16 to (i*16)+16 elements fro the expanded key to the 
//other key
//a cipher key
void copyCipherkey(unsigned char* to, int round, unsigned char* from) {
	int start = round * 16;
	for (int i = 0; i < 16; i++) {
		to[i] = from[start];
		start++;
	}
}
//function to decrypt the given cipher text into the plaintext
//it taskes 3 parameters
void Decrypt(unsigned char* ciphertext, unsigned char* cipherkey, unsigned char* plaintext) {

	unsigned char temp4[16];//an array to copy the cipher key that wil be used to 
	//perfomr addround keyoperation
	for (int i = 0; i < 16; i++) {
		temp4[i] = cipherkey[i];
	}
	unsigned char expandedkey[176];//an aray to keep all 10 rounds keys
	KeyExpansion(temp4, expandedkey);//callling function to keep all the keys for every round
	unsigned char temp[16];//array to take transpose of the cipher text
	unsigned char temp2[16];//array to take transpose of the cipher key

	copyCipherkey(cipherkey, 10, expandedkey);//copyint the 2nd last 16 elements from the 
	//expemded key
	Transpose(temp, ciphertext);//Performing Transpos
	Transpose(temp2, cipherkey);//performing transpose
		//for (int n = 0; n < 16; n++) {
			//cout << hex << (int)ciphertext[n];
		//}
	int key = 16;
	int popo = 0;
	addRoundKey(ciphertext, cipherkey);//Ist initial operation for the decryption
	for (int i = 9; i >= 0; i--) {

		InvShiftRows(ciphertext);//calling shiftrows function
		InvSubBytes(ciphertext);//Calling inv  subbytes function

		copyCipherkey(cipherkey, i, expandedkey);//copying ith*16 elements to the cipher key
		Transpose(temp2, cipherkey);//Again tranpose of the cipher key 
		//for (int n = 0; n < 16; n++) {
			//cout << hex << (int)cipherkey[n];
		//}
		//because it comes as a strainght one d array form key
		//Adding the round key and cipher text to perform next operations
		addRoundKey(ciphertext, cipherkey);
		//for (int n = 0; n < 16; n++) {
			//cout << hex << (int)ciphertext[n];
		//}
		if (i != 0) {
			InvMixColumn(ciphertext);
			// printing debug
			//for (int n = 0; n < 16; n++) {
				//cout << hex << (int)ciphertext[n];
			//}
		}

	}
	Transpose(temp2, ciphertext);
	//converting the last round text into the one d form so thatt
	//we can compare it with ne d form
	for (int i = 0; i < 16; i++) {
		plaintext[i] = ciphertext[i];
		//cout << hex << (int)plaintext[i] << ",";
	}
}

