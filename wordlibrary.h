#pragma once
#pragma once
#ifndef WORDLIBRARY_H
#define WORDLIBRARY_H

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>

struct key {
	char * word;
	char * hint;
};

struct WordList {
	char** words;
	int size;
	char topic[15];
};

void readFile(char * filename, struct WordList** list);
void cleanList(struct WordList** list);
struct key getWord(struct WordList* wordList, struct WordList * hintList);
#endif // !1

