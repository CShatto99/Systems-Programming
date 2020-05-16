// Name: Cameron Shatto
// EUID: chs0090

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// converts a hex character its integer equivalent
int hexToInt(char c) {
	if(c >= 97)
		c = c - 32;
	int left = (c / 16) - 3;
	int right = c % 16;
	int result = left * 10 + right;

	if(result > 9)
		result--;
	
	return result;
}

// converts an integer to its ascii equivalent
int intToASCII(char a, char b) {
	int left = hexToInt(a) * 16;
	int right = hexToInt(b);

	return left + right;
}

int main(int argc, char **argv) {
	FILE *f;
	char currentByte[8], allBytes[81];
	int byte, index = 1, ascii, charLimit;

	// check if the input file exists
	if(argc > 1) {
		f = fopen(argv[1], "r");
		if(f == NULL) {
			perror("Error opening file\n");
			exit (1);
		}
	}

	// read the binary data, convert it to hex, and store it in a char array
	while(!feof(f)) {
		if(fread(&byte, 1, 1, f) == 0)
			break;

		sprintf(currentByte, "%x", byte);

		allBytes[index++] = currentByte[6];
		allBytes[index++] = currentByte[7];
	}

	// get an upper limit index to print out the last line of data
	charLimit = index;
	while(charLimit % 32 != 0) charLimit++;

	// print the initial hex offset
	printf("%08x ", 0);

	for(int i = 0; i < index-1; i+=2) {
		if(i != 0 && i % 16 == 0)
			printf(" ");

		// after sixteen bytes have been printed, display the ascii equivalents
		if(i != 0 && i % 32 == 0) {
			printf("|");	
			for(int j = i-32; j < i; j+=2) {
				ascii = intToASCII(allBytes[j+1], allBytes[j+2]);
				if(isprint(ascii))
					printf("%c", ascii);
				else
					printf(".");
			}
			// hex offset
			printf("|\n%08x ", i/2);
		}

		// if all bytes have been printed, display the remaining ascii equivalents
		if(i == index-3) {
                        printf("|");
                        for(int j = charLimit-32; j < index-1; j+=2) {
                                ascii = intToASCII(allBytes[j+1], allBytes[j+2]);
                                if(isprint(ascii))
                                        printf("%c", ascii);
                                else
                                        printf(".");
                        }
			// hex offset
                        printf("|\n%08x ", (index-1)/2);
                }
		// display the two-digit hex
		printf("%c%c ", allBytes[i+1], allBytes[i+2]);
	}
}
