#include "wordlibrary.h"

void readFile(char * filename, struct WordList** list) {
	FILE* fd;
	char buffer[500];
	char** wordList = NULL;
	int size = 0;
	if ((fd = fopen(filename, "r")) == NULL) {
		printf("Failed to open %s\n", filename);
	}
	else {
		while ((fgets(buffer, sizeof(buffer), fd)) != NULL) {	//Read 1 string from file until EOF
			if (buffer[strlen(buffer) - 1] == '\n')
				buffer[strlen(buffer) - 1] = '\0';	//Take out the '\n'
			char * temp = NULL;
			temp = (char *)malloc(sizeof(char) * (strlen(buffer) + 1));
			if (temp != NULL) {
				strcpy(temp, buffer);
				size++;
				if (wordList == NULL) {	//malloc if list is empty
					wordList = (char**)malloc(sizeof(char*));
					wordList[size - 1] = temp;
				}
				else {					//realloc if list is not empty
					wordList = (char**)realloc(wordList, sizeof(char*) * size);
					wordList[size - 1] = temp;
				}
			}
		}
		(*list)->words = wordList;
		(*list)->size = size;
		fclose(fd);
	}
}

void cleanList(struct WordList** list) {
	if ((*list) != NULL) {
		int i;
		if ((*list)->words != NULL) {
			for (i = 0; i < (*list)->size; i++) {	//Clean individual string
				if ((*list)->words[i] != NULL) {
					free((*list)->words[i]);
					(*list)->words[i] = NULL;
				}
			}
			free((*list)->words);	//Then clean the string list
			(*list)->words = NULL;
		}
		free((*list));	//Then clean the struct itself
		(*list) = NULL;
	}
}

struct key getWord(struct WordList * wordList, struct WordList * hintList) {
	srand(time(0));
	struct key keyword;

	unsigned int num = rand() % (wordList->size);
	keyword.word = wordList->words[num];
	keyword.hint = hintList->words[num];
	return keyword;
}