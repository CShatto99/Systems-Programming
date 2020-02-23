#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#pragma warning(disable : 4996) // Coding this in Visual Studio, was necessary to make it not complain about fopen being depracated.

/*
Program Description: Decompiler for RiSC-16 processor code.
Authors: Merddyn Sheeley, Cameron Shatto, and Megan Dexter.
Creation Date: 02/16/2020
Revisions:
Date:							Modified By:
*/

void printMnemonic(unsigned long Data);
void print_RRR_type(unsigned long Data);
void print_RRI_type(unsigned long Data);
void print_RI_type(unsigned long Data);

int main(int argc, char* argv[]) // Can alternatively use char **argv instead of *argv[]
{
	FILE* f;
	unsigned long line;
	if (argc > 1)
	{
		f = fopen(argv[1], "r");
		if (f == NULL)
		{
			perror(argv[1]);
			printf("Error opening %s)\n", argv[1]);

			exit(1);
		}

	}
	else
	{
		exit(1);
	}
	while (!feof(f))
	{
		if (!feof(f))
		{
			if (fread(&line, 2, 1, f) == 0) // Reads two bytes into the Line variable.
			{
				break;
			}
			line = (line << 16); // Shifts Line so that the 16-bit binary code is at the front.
			printMnemonic(line);
		}
		else
		{
			break;
		}
		printf("\n");
	}
	return 0;
}

/*
*******************************************************************************
* printMnemonic function by Merddyn.
* Prints which RiSC-16 opp code the first 3 bits in Data correspond to, followed
* by the variables used with that operation. Input is a 32-bit integer which will
* be treated as binary input. The corresponding opp code should be in the three 
* most significant bits, followed by the remainder of the 16-bit line in the upper
* half of the 32-bit integer.
*
* Edits:
* Added print_RRI_type calls for applicable operations - Cameron.
* Added print_RRR_type calls for applicable operations - Merddyn.
*******************************************************************************
*/
void printMnemonic(unsigned long Data)
{
	unsigned long c = (Data >> 29);
	switch (c)
	{
	case 0:
		printf("ADD\t");
		print_RRR_type(Data);
		break;
	case 1:
		printf("ADDI\t");
		print_RRI_type(Data);
		break;
	case 2:
		printf("NAND\t");
		print_RRR_type(Data);
		break;
	case 3:
		printf("LUI\t");
		print_RI_type(Data);
		break;
	case 4:
		printf("SW\t");
		print_RRI_type(Data);
		break;
	case 5:
		printf("LW\t");
		print_RRI_type(Data);
		break;
	case 6:
		printf("BEQ\t");
		print_RRI_type(Data);
		break;
	case 7:
		printf("JALR\t");
		print_RRI_type(Data);
		break;
	default:
		printf("Invalid opp code");
	}
}

/*
*******************************************************************************
* print_RRR_type function by Merddyn
* Prints the RRR_type format from the RiSC-16 Architecture.
* Uses bitwise shift and 'AND' operators to extract three register numbers
* from a 16-bit value.
* Input is an unsigned long with the first (most significant) 16 bits containing
* the entire 16-bit line from the RiSC-16 code.
*
* Let's be real here - I just edited Cameron's code for RRI types for this.
*******************************************************************************
*/
void print_RRR_type(unsigned long Data) {
	unsigned long regA = (Data >> 26);
	regA = (regA & 0x7);

	unsigned long regB = (Data >> 23);
	regB = (regB & 0x7);

	unsigned long regC = (Data >> 16);
	regC = (regC & 0x7);

	printf("R%lu, R%lu, R%lu", regA, regB, regC);
}

/*
*******************************************************************************
* print_RRI_type function by Cameron
* Prints the RRI_type format from the RiSC-16 Architecture.
* Uses various bitwise operators to extract two register numbers
* and a signed immediate value from a 16-bit value.
* Input is an unsigned long with the first (most significant) 16 bits containing
* the entire 16-bit line from the RiSC-16 code.
*******************************************************************************
*/
void print_RRI_type(unsigned long Data) {
	unsigned long regA = (Data >> 26) & 0x7;

	unsigned long regB = (Data >> 23) & 0x7;

	unsigned long imm = (Data >> 16) & 0x7F;

	if (imm & 0x40) {
		long sImm = -1 * ((~((imm)-1)) & 0x7F);
		printf("R%lu, R%lu, %ld", regA, regB, sImm);
	}
	else
		printf("R%lu, R%lu, %lu", regA, regB, imm);
}

/*
*******************************************************************************
* print_RI_type function by Megan
* Prints the RI_type format from the RiSC-16 Architecture.
* Uses various bitwise operators to extract one register number
* and a signed immediate value from a 16-bit value.
* Input is an unsigned long with the first (most significant) 16 bits containing
* the entire 16-bit line from the RiSC-16 code.
*
*Like Merddyn, I also modified Cameron's code for the RI type.
*******************************************************************************
*/
void print_RI_type(unsigned long Data) {
	unsigned int regA = (Data >> 26) & 0x7;
  
	unsigned int uImm = (Data >> 16) & 0x3FF;
	
	printf("R%u, 0x%X", regA, uImm);
 
}
