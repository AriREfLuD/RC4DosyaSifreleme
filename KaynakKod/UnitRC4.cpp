// ---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>

#pragma hdrstop

#include "UnitRC4.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

// Author: Halil Kemal TAÞKIN
// Web: http://hkt.me
// RC4 Implementation Source: http://www.cypherspace.org

// --- RC4 ÞÝFRELEME SÝSTEMÝ KODLARI -----------------------------------------

#define swap_byte(x,y) t = *(x); *(x) = *(y); *(y) = t
#define krktr_size 1024

typedef struct rc4_key {
	unsigned char state[256];
	unsigned char x;
	unsigned char y;
} rc4_key;

void prepare_key(unsigned char *key_data_ptr, int key_data_len, rc4_key *key) {
	int i;
	unsigned char t;
	unsigned char swapByte;
	unsigned char index1;
	unsigned char index2;
	unsigned char* state;
	short counter;

	state = &key->state[0];
	for (counter = 0; counter < 256; counter++)
		state[counter] = counter;
	key->x = 0;
	key->y = 0;
	index1 = 0;
	index2 = 0;
	for (counter = 0; counter < 256; counter++) {
		index2 = (key_data_ptr[index1] + state[counter] + index2) % 256;
		swap_byte(&state[counter], &state[index2]);
		index1 = (index1 + 1) % key_data_len;
	}
}

void rc4(unsigned char *buffer_ptr, int buffer_len, rc4_key *key) {
	unsigned char t;
	unsigned char x;
	unsigned char y;
	unsigned char* state;
	unsigned char xorIndex;
	short counter;

	x = key->x;
	y = key->y;
	state = &key->state[0];
	for (counter = 0; counter < buffer_len; counter++) {
		x = (x + 1) % 256;
		y = (state[x] + y) % 256;
		swap_byte(&state[x], &state[y]);
		xorIndex = (state[x] + state[y]) % 256;
		buffer_ptr[counter] ^= state[xorIndex];
	}
	key->x = x;
	key->y = y;
}

// --- DOSYA ÞÝFRELEME KODLARI -----------------------------------------------

void RC4::DosyaSifrele(char *DosyaKonumu, char *SifreliDosyaKonumu, char *Sifre)
{
	FILE *dosya;
	FILE *sifrelidosya;
	rc4_key key;
	// "rb": r: read b:binary ; dosyayý okumak için binary olarak aç
	dosya = fopen(DosyaKonumu, "rb");

	// w: write b: binary mode
	sifrelidosya = fopen(SifreliDosyaKonumu, "wb");
	int rd;
	char krktr[krktr_size];

	// RC4'ü baþlat
	prepare_key(Sifre, strlen(Sifre), &key);

	// RC4'ü 3072 byte boþa çevir.
	for (int i = 0; i < 3; i++)
		rc4(krktr, krktr_size, &key);

	rd = fread(krktr, 1, krktr_size, dosya);
	while (rd > 0) {
		// ShowMessage(krktr);
		rc4(krktr, rd, &key);
		fwrite(krktr, 1, rd, sifrelidosya);
		rd = fread(krktr, 1, krktr_size, dosya);
	}
	fclose(dosya);
	fclose(sifrelidosya);

}

// ---------------------------------------------------------------------------
void RC4::BMPSifrele(char *DosyaKonumu, char *SifreliDosyaKonumu, char *Sifre) {
	FILE *dosya;
	FILE *sifrelidosya;
	rc4_key key;
	// "rb": r: read b:binary ; dosyayý okumak için binary olarak aç
	dosya = fopen(DosyaKonumu, "rb");

	// w: write b: binary mode
	sifrelidosya = fopen(SifreliDosyaKonumu, "wb");
	int rd;
	char krktr[krktr_size];

	// RC4'ü baþlat
	prepare_key(Sifre, strlen(Sifre), &key);

	// RC4'ü 3072 byte boþa çevir.
	for (int i = 0; i < 3; i++)
		rc4(krktr, krktr_size, &key);

	// ilk 14 byte ý oku ve aynen kopyala
	char header1[14];
	rd = fread(header1, 1, 14, dosya);
	fwrite(header1, 1, rd, sifrelidosya);

	// ilk 14 byte ýn son 4 byte ýný int e çevir
	int databaslangic = 0;
	for (int i = 10; i < 14; i++) {
		databaslangic += ((int)header1[i])*(1 << (8*(i - 10)));
	}

	databaslangic -= 14;

	// databaslangic-header1 kadarlýk kýsmý da aynen kopyala
	rd = fread(krktr, 1, databaslangic, dosya);
	fwrite(krktr, 1, rd, sifrelidosya);

	// þifrelemeye baþla
	rd = fread(krktr, 1, krktr_size, dosya);
	while (rd > 0) {
		// ShowMessage(krktr);
		rc4(krktr, rd, &key);
		fwrite(krktr, 1, rd, sifrelidosya);
		rd = fread(krktr, 1, krktr_size, dosya);
	}
	fclose(dosya);
	fclose(sifrelidosya);

}

// ---------------------------------------------------------------------------
