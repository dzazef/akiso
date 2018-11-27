//Kolory sprawdzone przez 'tput colors'
#include <stdio.h>
int main(){
	for (int i=0; i<256; i++){
		printf("\x1B[38;5;%dmHello, world!\n", i);
	}
}
