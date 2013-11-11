#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINESIZE 100

void read_input_file(FILE *, FILE *, char [], char []);
int search_substr(char [], char [], int );

int main(int argc, char *argv[]){
	FILE *fin, *fout;

	if(argc < 5){
		printf("To few arguments passed.\n");
		exit(0);
	}

	fin = fopen(argv[2], "r");
	fout = fopen(argv[4], "w");

	if(fin == NULL || fout == NULL){
		printf("Couldn't open input or output file.\n");
		exit(0);
	}

	read_input_file(fin, fout, argv[1], argv[3]);

	return 0;
}

void read_input_file(FILE *fin, FILE *fout, char needle[], char haystack[]){
	char buff[MAX_LINESIZE+1];
	while(fgets(buff, MAX_LINESIZE, fin) != NULL){
		search_substr(needle, buff, 0);
	}
}

int search_substr(char needle[], char haystack[], int from){
	int i, j, found;
	i = from;

	while(i < strlen(haystack)-strlen(needle)){
		found = 1;
		j = 0;

		while(j < strlen(needle) && found == 1){
			if(needle[j] != haystack[i+j]){
				found = 0;
			}

			++j;
		}

		if(found == 1){
			printf("found \"%s\" in \"%s\"- %d\n", needle, haystack, i);
			return 1;
		}

		++i;
	}

	return 0;
}