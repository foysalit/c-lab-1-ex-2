#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINESIZE 100

void read_input_file(FILE *, FILE *, char [], char []);
int search_substr(char [], char [], int );
void search_and_replace(char [], char [], char [], char[]);

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

void read_input_file(FILE *fin, FILE *fout, char needle[], char replace[]){
	char buff[MAX_LINESIZE+1];
	char filtered[MAX_LINESIZE+1];

	while(fgets(buff, MAX_LINESIZE, fin) != NULL){
		search_and_replace(buff, needle, replace, filtered);
		printf("%s\n", filtered);
	}
}

void search_and_replace(char haystack[], char needle[], char replace[], char s[]){
	int from, to, i, idx, flag;

	idx=from=flag=0;

	do{
		to = search_substr(needle, haystack, from);

		//if the substring does not exist in the line
		//set to=the length of the whole haystack
		//so that in the next block it sets the whole output s value 
		//equal to the haystack string
		//and set the flag to 1 so that the loop doesn't run anymore
		if(to < 0){
			to = strlen(haystack);
			flag = 1;
		}

		//look through each char of the haystack untill the char
		//where the matched substr starts
		//and store all the chars in the output string array
		for (i = from; i < to; ++i){
			s[idx] = haystack[i];
			++idx;
		}

		//if the flag isn't already set to 0 that means
		//we haven found a match yet
		//so we run through each char of the replacing string
		//and store them to the output string using the idx variable
		//as a refference point from previous loop 
		if(flag == 0){
			for (i = 0; i < strlen(replace); ++i){
				s[idx] = replace[i];
				++idx;
			}
		}

		from = to + strlen(needle);
	}while(flag != 1);

	s[idx] = '\0';
	return; 
}

int search_substr(char needle[], char haystack[], int from){
	int i, j, found;
	i = from;

	// we loop through each char of the haystack
	while(i < strlen(haystack)-strlen(needle)){
		found = 1;
		j = 0;

		//for each element we run through the needle 
		//and match it with the haystack string 
		//if one char is different then we abort the loop
		//by setting found = 0
		//if every char matches, we do nothing
		while(j < strlen(needle) && found == 1){
			if(needle[j] != haystack[i+j]){
				found = 0;
			}

			++j;
		}

		//if found = 1 that means we found a match, 
		//if a match is found we return the starting point of
		//the matched substr from the haystack
		if(found == 1){
			return i;
		}

		++i;
	}

	return -1;
}