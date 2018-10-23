#include "wordlibrary.h"
void menu();
void topicMenu(struct WordList ** wordList, struct WordList ** hintList);
int gameloop(const char * keyword, const char * hint);

int main() {
	menu();
	return 0;
}

void menu() {
	int option;
	struct WordList * wordList = NULL;
	struct WordList * hintList = NULL;
	wordList = (struct WordList *)malloc(sizeof(struct WordList));
	hintList = (struct WordList *)malloc(sizeof(struct WordList));
	readFile("library/Animals.txt", &wordList);
	readFile("library/Animals_Hint.txt", &hintList);
	strcpy(wordList->topic, "Animals");

	do {
		printf("*************************************************\n");
		printf("*               **WORD GAME**                   *\n");
		printf("            CURRENT TOPIC: %s\n", wordList->topic);
		printf("*   1. PLAY                                     *\n");
		printf("*   2. CHANGE TOPIC                             *\n");
		printf("*   3. QUIT                                     *\n");
		printf("*                                               *\n");
		printf("*************************************************\n");
		printf("Enter an option: ");
		while (scanf("%d", &option) != 1) {
			printf("\tINVALID OPTION. TRY AGAIN!\n\n");
			while (getchar() != '\n');
			printf("Enter an option: ");
		}
		while (getchar() != '\n');

		if (option == 1) {
			printf("\n\n\n");
			struct key keyword = getWord(wordList,hintList);
			gameloop(keyword.word, keyword.hint);
		}
		else if (option == 2) {
			topicMenu(&wordList, &hintList);
			printf("You chose %s\n\n\n", wordList->topic);
		}
		else if (option == 3) {
			printf("\n\n*************************************************\n");
			printf("*      GOODBYE! THANKS FOR PLAYING!             *\n");
			printf("*************************************************\n\n");
		}
		else
			printf("\tINVALID OPTION. TRY AGAIN!\n\n");

	} while (option != 3);
	//Clean the list
	cleanList(&wordList);
	cleanList(&hintList);
}

void topicMenu(struct WordList ** wordList, struct WordList ** hintList) {
	int option;
	int good = 0;
	if (*wordList != NULL)
		cleanList(wordList);
	if (*hintList != NULL)
		cleanList(hintList);
	(*wordList) = (struct WordList *)malloc(sizeof(struct WordList));
	(*hintList) = (struct WordList *)malloc(sizeof(struct WordList));
	while (!good) {
		printf("\n\n\n*************************************************\n");
		printf("*            **CHOOSE A TOPIC**                 *\n");
		printf("*   1. Animals                                  *\n");
		printf("*   2. Greek Mythology                          *\n");
		printf("*   3. Video Games                              *\n");
		printf("*                                               *\n");
		printf("*************************************************\n");
		printf("Enter an option: ");
		scanf("%d", &option);
		switch (option) {
		case 1:
			readFile("library/Animals.txt", wordList);
			readFile("library/Animals_Hint.txt", hintList);
			strcpy((*wordList)->topic, "Animals");
			//printf("You chose %s\n\n\n", wordList->topic);
			good = 1;
			break;
		case 2:
			readFile("library/Greek_Mythology.txt", wordList);
			readFile("library/Greek_Mythology_Hint.txt", hintList);
			strcpy((*wordList)->topic, "Greek Mythology");
			//printf("You chose %s\n\n\n", wordList->topic);
			good = 1;
			break;
		case 3:
			readFile("library/Video_Games.txt", wordList);
			readFile("library/Video_Games_Hint.txt", hintList);
			strcpy((*wordList)->topic, "Video Games");
			//printf("You chose %s\n\n\n", wordList->topic);
			good = 1;
			break;
		default:
			printf("Invalid Input. Retry!\n\n\n");
			break;
		}
	}
}

int gameloop(const char * keyword, const char * hint) {
	char * answer = (char *)malloc(sizeof(char)*(strlen(keyword) + 1));
	answer[strlen(keyword)] = '\0';
	unsigned int i;
	for (i = 0; i < strlen(answer); i++) {
		if (keyword[i] != ' ')
			answer[i] = '-';
		else
			answer[i] = ' ';
	}

	int attempt = 0;
	while ((strcmp(keyword, answer) != 0) && attempt < 6) {
		char temp;
		int count = 0;
		printf("           *************************************************\n");
		printf("YOUR WORD: \t\t%s\n", answer);
		printf("           *************************************************\n\n");
		printf("Press ENTER (RETURN) to continue...\n\n");
		getchar();
		printf("Attempt #: %d out of 6\n", attempt + 1);
		printf("HINT: %s\n\n", hint);

		int charCount;
		do {
			charCount = 0;
			printf("Guess a character: ");
			scanf(" %c", &temp);
			while (getchar() != '\n')
				charCount++;

			if (charCount > 0)
				printf("Slow down. Only enter 1 character at a time.\n\n");
		} while (charCount > 0);

		if (islower(temp))
			temp = toupper(temp);
		for (i = 0; i < strlen(keyword); i++) {
			if (keyword[i] == temp) {
				answer[i] = temp;
				count++;
			}
		}
		printf("\n\n\n           *************************************************");
		if (count == 0) {
			printf("\n\t   There is no %c.\n", temp);
			attempt++;
		}
		else if (count == 1)
			printf("\n\t   There is 1 %c.\n", temp);
		else
			printf("\n\t   There are %d %cs.\n", count, temp);
	}
	printf("           *************************************************\n");
	if (attempt < 6) {
		printf("\t    ****%s****\n", keyword);
		printf("\t    CONGRATULATION! ");
		if (attempt < 2)
			printf("Should I call you A GENIUS?\n");
		else if (attempt < 5)
			printf("You did very well!\n");
		else
			printf("You barely made it. Was that luck or skill?\n");
	}
	else
		printf("\t   OUT OF ATTEMPTS! THE CORRECT WORD IS:\n\t    ****%s****\n", keyword);
	printf("           *************************************************\n\n\n\n");
	printf("Press ENTER (RETURN) to continue...\n\n");
	getchar();

	free(answer);

	return 1;
}