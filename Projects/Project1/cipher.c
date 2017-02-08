// Project: 	Caesar Ciphers
// Author:	Yonglei Tao

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

/**
	Encrypts a character using the Caesar cipher.
	@param ch the character to encrypt
	@param k the encryption key
	@return the encrypted character
*/
char encrypt(char ch, int k){
	if (k < 0)
		k = k + 26;

	if (isupper(ch))
		return (ch - 'A' + k) % 26 + 'A';

	if (islower(ch))
		return (ch - 'a' + k) % 26 + 'a';

	return ch;
}

int main(int argc, char* argv[]){
	int choice, key;
	char ch;
	FILE *fin, *fout;

	if (argc != 5){
		printf ("Usage: cipher option key infile, outfile\n");
		printf ("Option 1 for encryption and 2 for decryption");
		exit(1);
	}

	choice = atoi(argv[1]);
	key = atoi(argv[2]);

	if (choice == 2)
		key = -key;

  fin = fopen(argv[3], "r");
	fout = fopen(argv[4], "w");

  if (fin ==  NULL || fout == NULL) {
		printf("File could not be opened\n");
		exit(1);
	}

	while (fscanf(fin, "%c", &ch) != EOF){
		fprintf(fout, "%c", encrypt(ch, key));
	}

	fclose(fin);
	fclose(fout);

	return 0;
}

// Load array given with the letter frequencies for English from file LetFreq.txt
void readFreq (float given[]， FILE * letFreq){

}

// Read the encoded text from an input file and accumulate the letter frequency
// data for the encoded text. Store the frequency data in array found.
void calcFreq (float found[]， FILE * datafile){

}

// Rotate the character in parameter ch down the alphabet for the number of
// positions as given in parameter num and return the resulting character.
char rotate (char ch, int num){

}

// Compare the data in array found with the frequency data in array given, looking
// for a key that will give you the best match. To do this, try each of the 26 rotations,
// and remember which gives the smallest difference between the frequencies you
// observed and the frequencies given. Return the key.
int findKey (float given[], float found[]){

}

// Decrypt the encoded text in the input file using the key and display the decoded text
void decrypt (int key， FILE* datafile){

}
