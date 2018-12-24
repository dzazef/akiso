#include <malloc.h>
#include <unistd.h>
#include <memory.h>

#define MAX 256
char* dec_to_base_char(int dec, int base);

int myprintf(const char* format, ...) {
	char *p = (char *)&format + sizeof format;
	int pos = 0;
	int length = 0;
	while(format[pos]) {
		if (format[pos]=='%') {
			pos++;
			switch(format[pos++]) {
				case 'd' : {
					char* towrite = dec_to_base_char(*(int *)p, 10);
					for (int i = 0; towrite[i]!='\0'; i++) {
						write(1, &towrite[i], sizeof(char));
						length++;
					}
					p+=sizeof(int);
					break;
				} case 'x' : {
					char* towrite = dec_to_base_char(*(int *)p, 16);
					for (int i = 0; towrite[i]!='\0'; i++) {
						write(1, &towrite[i], sizeof(char));
						length++;
					}
					p+= sizeof(int);
					break;
				} case 'b' : {
					char* towrite = dec_to_base_char(*(int *)p, 2);
					for (int i = 0; towrite[i]!='\0'; i++) {
						write(1, &towrite[i], sizeof(char));
						length++;
					}
					p+= sizeof(int);
					break;
				} case 's' : {
					char* towrite = *(char**) p;
					for (int i = 0; towrite[i]!='\0'; i++) {
						write(1, &towrite[i], sizeof(char));
						length++;
					}
					p+= sizeof(char*);
					break;
				}
				default:break;
			}
		} else if (format[pos]=='\\') {
			pos++;
			if(format[pos++]=='n') write (1, "\n", 1);
		} else {
			length++;
			write(1, &format[pos++], sizeof(char));
		}
	}
	return length;
}

void myscanf(const char* format, ...) {
	fflush(stdout);
	char *p = (char *)&format + sizeof format;
	int pos = 0;
	while (format[pos]) {
		if (format[pos]=='%') {
			pos++;
			switch(format[pos++]) {
				case 'd' : {
					int* ptr = *(int**)p;
					char* chararr = malloc(MAX);
					char temp = '\0';
					int p2 = 0;
					while(temp!='\n') {
						read(0, &temp, 1);
						chararr[p2++] = temp;
					}
					int base = 1;
					*ptr=0;
					for (int i = (int)strlen(chararr)-2; i>=0; i--) {
						*ptr += chararr[i]%48*base;
						base *= 10;
					}
					p += sizeof(int*);
					break;
				} case 'x' : {
					int* ptr = *(int**)p;
					char* chararr = malloc(MAX);
					char temp = '\0';
					int p2 = 0;
					while(temp!='\n') {
						read(0, &temp, 1);
						chararr[p2++] = temp;
					}
					int base = 1;
					*ptr=0;
					for (int i = (int)strlen(chararr)-2; i>=0; i--) {
						if (chararr[i]>47 && chararr[i]<58)
							*ptr += chararr[i]%48*base;
						else if (chararr[i]>64 && chararr[i]<71)
							*ptr += chararr[i]%55*base;
						else if (chararr[i]>96 && chararr[i]<103)
							*ptr += chararr[i]%87*base;
						base *= 16;
					}
					p += sizeof(int*);
					break;
				} case 'b' : {
					int* ptr = *(int**)p;
					char* chararr = malloc(MAX);
					char temp = '\0';
					int p2 = 0;
					while(temp!='\n') {
						read(0, &temp, 1);
						chararr[p2++] = temp;
					}
					int base = 1;
					*ptr=0;
					for (int i = (int)strlen(chararr)-2; i>=0; i--) {
						*ptr += chararr[i]%48*base;
						base *= 2;
					}
					p += sizeof(int*);
					break;
				} case 's' : {
					char* ptr = *(char**)p;
					char* chararr = malloc(MAX);
					char temp = '\0';
					int p2 = 0;
					while(temp!='\n') {
						read(0, &temp, 1);
						if (temp=='\n') break;
						chararr[p2++] = temp;
					}
					chararr[p2] = '\0';
					strcpy(ptr, chararr);
					p += sizeof(char*);
					break;
				}
				default:break;
			}
		} else {
			pos++;
		}
	}
}

int main() {
	myprintf("Char*: %s Dec: %d Hex: %x Binary: %b\n", "16", 161616, 16, 16);
	int dec;
	myprintf("Input in DEC, Output in DEC...\n");
	myscanf("%d", &dec);
	myprintf("Value: %d\n", dec);
	int bin;
	myprintf("Input in BIN, Output in DEC...\n");
	myscanf("%b", &bin);
	myprintf("Value: %d\n", bin);
	int hex;
	myprintf("Input in HEX, Output in DEC...\n");
	myscanf("%x", &hex);
	myprintf("Value: %d\n", hex);
	char* str = malloc(MAX);
	myprintf("Input in char*, Output in char*\n");
	myscanf("%s", str);
	myprintf("Value: %s\n", str);
	myprintf("Input in DEC+HEX, Output in DEC...\n");
	myscanf("%d%x", &dec, &hex);
	myprintf("Value1: %d Value2: %d\n", dec, hex);
}

char* dec_to_base_char(int dec, int base) {
	char digits[] = {"0123456789ABCDEF"};
	int minus = 0;
	if (dec<0) {
		minus = 1;
		dec*=(-1);
	}
	char *value = (char *) malloc(MAX * sizeof(char));
	char *value_inv = (char *) malloc(MAX * sizeof(char));
	int pos=0;
	while (dec) {
		value[pos++] = digits[dec%base];
		dec /= base;
	}
	int j = 0;
	if (minus) {
		j=1;
		value_inv[0] = '-';
	}
	for (int i = pos-1; i>=0; i--) {
		value_inv[j++] = value[i];
	}
	return value_inv;
}
