// Project: 	Caesar Ciphers
// Author:	Yonglei Tao

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char encrypt(char, int);
void readFreq(float[], FILE*);
void calcFreq(float[], FILE*);
char rotate(char, int);
int findKey(float[], float[]);
void decrypt(int, FILE*, FILE*);

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


  fin = fopen(argv[3], "r");
  fout = fopen(argv[4], "w");

  if (fin ==  NULL || fout == NULL) {
    printf("File could not be opened\n");
    exit(1);
  }

  if (choice == 2){
    float* freq = (float*)malloc(26*(sizeof(float)));
    FILE *let_freq = fopen("LetFreq.txt", "r");
    readFreq(freq, let_freq);
    fclose(let_freq);

    float* freq_calc = (float*)malloc(26*(sizeof(float)));
    calcFreq(freq_calc, fin);
    rewind(fin);

    key = findKey(freq, freq_calc);
    printf("\nFound Key: %d\n", key);

    decrypt(key, fin, fout);
  } else {
    while (fscanf(fin, "%c", &ch) != EOF){
      fprintf(fout, "%c", encrypt(ch, key));
    }
  }

  fclose(fin);
  fclose(fout);

  return 0;
}

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

// Load array given with the letter frequencies for English from file LetFreq.txt
void readFreq(float given[], FILE* letFreq){
  char str1[10], str2[10];
  int id = 0;
  //float freq = -1;

  while (id < 26){
    fscanf(letFreq, "%s %s", str1, str2);
    given[id] = atof(str2);
    id++;
  }
}

// Read the encoded text from an input file and accumulate the letter frequency
// data for the encoded text. Store the frequency data in array found.
void calcFreq(float found[], FILE* datafile){
  char c;

  int total = 0;
  int id = 0;
  while ((c = fgetc(datafile)) != EOF){
    if (!isalpha(c)){
      continue;
    }
    if (islower(c)){
      id = c - 'a';
    }
    else if (isupper(c)){
      id = c - 'A';
    }
    found[id] = found [id] + 1;
    total++;
  }
  printf("total; %d\n", total);
  id = 0;
  while (id < 26){
    found[id] = found[id] / total;
    id++;
  }

}

// Rotate the character in parameter ch down the alphabet for the number of
// positions as given in parameter num and return the resulting character.
char rotate(char ch, int num){
  if(isupper(ch)){
    return ('A' + ((ch+num)-'A')%26);
  }
  else if (islower(ch)){
    return ('a' + ((ch+num)-'a')%26);
  }
  else {
    return ch;
  }
  return ch;
}

// Compare the data in array found with the frequency data in array given, looking
// for a key that will give you the best match. To do this, try each of the 26 rotations,
// and remember which gives the smallest difference between the frequencies you
// observed and the frequencies given. Return the key.
int findKey(float given[], float found[]){
  int i, j, key;
  float curDif;
  float bestDif = 0.0;
  for(i = 0; i < 26; i++) {
    curDif = 0.0;
    for(j = 0; j < 26; j++) {
      curDif += power((given[(i+j)%26] - found[j]), 2);
    }
    if(curDif < bestDif || i == 0){
      bestDif = curDif;
      key = i;
    }
  }
  printf("Key in findKey: %d\n", key);
  return key;
}

// Decrypt the encoded text in the input file using the key and display the decoded text
void decrypt(int key, FILE* input, FILE* output){
  char c;

  while ((c = getc(input)) != EOF){
    fputc(rotate(c,key),output);
  }
}
