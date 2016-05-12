#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 1000


/*
Author: Michelle Liao
Student Info: 999139640 
cdf: g3michhy

Author2: Fan Yi Kung (Eva)
Student Info: 998137572
cdf: c2kungfa

*/


int file_exists(const char *filename);

int main( int argc, char *argv[] ){

	FILE *inputFile; //file pointer
	FILE *newFile;

	char filename[LENGTH] = "";

	if(argv[2] == NULL){ //handles invalid user input
		fprintf(stderr, "Please add in a shift value\n");
		exit(1);
	}

	if (file_exists(argv[1]) == 0){
		inputFile = fopen(argv[1], "rt");

		//renaming new filename for output
		strcat(filename, argv[1]);
		strcat(filename, ".enc");

		int s;
		int shift, diff, index;

		shift = atoi(argv[2]); //changes from char * to int

		newFile = fopen(filename, "w"); // Made new file .enc

		while((s = getc(inputFile)) != EOF){ //loops until reaches the end of the file or new char line 
			if ((s >='a' && s <='z')){
				diff = (s - 'a');
				s = (diff + shift) % 26 + 'a';
			}else if ((s >= 'A' && s <= 'Z')){
				diff = (s - 'A');
				s = (diff + shift) % 26 + 'A';
			}else{
				s = s;
			}
			putc(s, newFile); //put each shifted char into new file
		}
		fclose(inputFile);
		fclose(newFile);
	}else{
		fprintf(stderr, "File does not exist\n"); //Error message
	}
	return 0;
}



/*Checks if file exitst or not. Returns 0 if true*/
int file_exists(const char * filename){
	FILE *file;
	if (file = fopen(filename, "r")){
		fclose(file);
		return 0;
	}else{
		return 1;
	}
}

