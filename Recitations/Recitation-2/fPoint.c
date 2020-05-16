// Name: Cameron Shatto
// EUID: chs0090

#include <stdio.h>
#include <stdlib.h>

void print_exponent(int exponent);

int main() {
    float input;
    unsigned long *f = (unsigned long *) &input;
    
    printf("Enter a value: ");
    scanf("%f", &input);

    int decimal = abs((int) input), exponent = -1;

    while(decimal > 0) {
        exponent++;
        decimal /= 2;
    }
    
    input < 0 ? printf("\n-1.") : printf("\n+1.");
    
    for (int i=9; i<=31; i++) {
        if(i > 9 && (i-9) % 4 == 0)
            printf(" ");
        if ((*f >> (31-i)) & 1)
            printf("1");
        else
            printf("0");
    }
    
    print_exponent(exponent);
    
    return 0;
}

void print_exponent(int exponent) {
    int i = 0, binary[8] = {};
	
    printf(" * 2^(");
    while(exponent > 0) {
    	binary[i++] = exponent % 2;
    	exponent /= 2;
    }
    
    for(int j = 7; j >= 0; j--) {
        if(j == 3)
            printf(" ");
        	
        printf("%d", binary[j]);
    }
    printf(")\n");
}
