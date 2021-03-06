/**
* Mobius Software LTD
* Copyright 2015-2018, Mobius Software LTD
*
* This is free software; you can redistribute it and/or modify it
* under the terms of the GNU Lesser General Public License as
* published by the Free Software Foundation; either version 2.1 of
* the License, or (at your option) any later version.
*
* This software is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this software; if not, write to the Free
* Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
* 02110-1301 USA, or see the FSF site: http://www.fsf.org.
*/
#include <cstdlib>
#include <cstdio>
#include <string>


char * utf8_check(unsigned char *s) {
	while (*s) {
		if (*s < 0x80)
			/* 0xxxxxxx */
			s++;
		else if ((s[0] & 0xe0) == 0xc0) {
			/* 110XXXXx 10xxxxxx */
			if ((s[1] & 0xc0) != 0x80 || (s[0] & 0xfe) == 0xc0) /* overlong? */
				return s;
			else
				s += 2;
		} else if ((s[0] & 0xf0) == 0xe0) {
			/* 1110XXXX 10Xxxxxx 10xxxxxx */
			if ((s[1] & 0xc0) != 0x80 || (s[2] & 0xc0) != 0x80
					|| (s[0] == 0xe0 && (s[1] & 0xe0) == 0x80) || /* overlong? */
					(s[0] == 0xed && (s[1] & 0xe0) == 0xa0) || /* surrogate? */
					(s[0] == 0xef && s[1] == 0xbf && (s[2] & 0xfe) == 0xbe)) /* U+FFFE or U+FFFF? */
				return s;
			else
				s += 3;
		} else if ((s[0] & 0xf8) == 0xf0) {
			/* 11110XXX 10XXxxxx 10xxxxxx 10xxxxxx */
			if ((s[1] & 0xc0) != 0x80 || (s[2] & 0xc0) != 0x80
					|| (s[3] & 0xc0) != 0x80
					|| (s[0] == 0xf0 && (s[1] & 0xf0) == 0x80) || /* overlong? */
					(s[0] == 0xf4 && s[1] > 0x8f) || s[0] > 0xf4) /* > U+10FFFF? */
				return s;
			else
				s += 4;
		} else
			return s;
	}
	return NULL;
}

int add_short(unsigned char * buf, unsigned short s) {
	*buf++ = (s >> 8) & 0xff;
	*buf = s & 0xff;
	return 2;
}

unsigned short get_short(unsigned char* array, int offset) {
	return (short) (((short) array[offset]) << 8) | array[offset + 1];
}

int add_int(unsigned char * buf, unsigned int s) {
	*buf++ = (s >> 16);
	return 4;
}

int get_int(unsigned char* array, int offset) {
	return array[offset] << 24 | (array[offset+1] << 16) | (array[offset+2] << 8) | (array[offset+3]);
}

int add_long(unsigned char * buf, long s) {
	*buf++ = (s >> 16);
	return 4;
}

long get_long(unsigned char* array, int offset) {
	long * a;
	memcpy(&a, &array[offset], sizeof(long));
	return *a;
}

int add_double(unsigned char * buf, double s) {
	*buf++ = (s >> 32);
	return 8;
}

double get_double (unsigned char* array, int offset) {
	double * a;
	memcpy(&a, &array[offset], sizeof(double));
	return *a;
}

int add_float(unsigned char * buf, float s) {
	*buf++ = (s >> 16);
	return 4;
}

float get_float (unsigned char* array, int offset) {
	double * a;
	memcpy(&a, &array[offset], sizeof(float));
	return *a;
}

int remaining_length(int length) {

	if (length <= 127)
		return 1;
	else if (length <= 16383)
		return 2;
	else if (length <= 2097151)
		return 3;
	else if (length <= 26843545)
		return 4;
	else {
		printf("header length exceeds maximum of 26843545 bytes");
		return 0;
	}
}

int add_packet_length(int length, unsigned char * remaining_length) {

	char enc_byte;
	int pos = 1, l = length;
	do {
		enc_byte = (char) (l % 128);
		l /= 128;
		if (l > 0)
			remaining_length[pos++] = (char) (enc_byte | 128);
		else
			remaining_length[pos++] = enc_byte;
	} while (l > 0);

	return pos;

}

void reverse (unsigned char * a, int len) {
	int i = len - 1;
	int  j = 0;
	  while(i > j)
	  {
	    char temp = a[i];
	    a[i] = a[j];
	    a[j] = temp;
	    i--;
	    j++;
	  }
}
