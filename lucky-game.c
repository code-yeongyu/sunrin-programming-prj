#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>

typedef struct _StructScore {
	int total_score;
	char nickname[10];

} StructScore;

StructScore ranks[100];

void sortScore();
void clearScreen();
void waitMilliseconds(unsigned long milliseconds);
StructScore playGame(unsigned int seconds);
void addRank(StructScore score);
void printRank();
void swapInteger(int *a, int *b);
void swapString(char a[], char b[]);
int getRankLength();

int main(void) {
	int i, selection, currentUserIndex=0;
	srand(time(NULL));
	for(i = 0; i < 100; i++)
		ranks[i].total_score = -1;
	for(;;){
		printf("play game: 0, see rank: 1\nType here: ");
		scanf("%d", &selection);
		if(selection) {
			sortScore();
			printRank();
		}else{
			ranks[currentUserIndex++] = playGame(10);
		}
	}
	return 0;
}

void clearScreen() {
	system("cls");
}

void waitMilliseconds(unsigned long milliseconds) {
	clock_t currentTime = clock();
	while (clock() - currentTime < milliseconds);
}

StructScore playGame(unsigned int seconds) {
	StructScore score;
	score.total_score = 0;
	int cache_score, gamePlayCount;
	unsigned int timer;
	for(gamePlayCount = 0; gamePlayCount < 3; gamePlayCount++) {
		cache_score = 0;
		for(;;){
			timer = clock();
			while (clock() - timer < seconds) {
				Sleep(1); // hack for optimization
				while (_kbhit())
					if(getch() == 32)
						goto out;
			}
			cache_score = (cache_score + 1)%10;
			clearScreen();
			printf("Enter to get: %d\n", cache_score);
		}
		out:
		printf("You've got %d points!", cache_score);
		score.total_score += cache_score;
		Sleep(1500);
	}
	clearScreen();
	printf("Your total score = %d\n", score.total_score);
	printf("Type your name: ");
	scanf("%9s", score.nickname);
	return score;
}

void swapInteger(int *a, int *b) {
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void swapString(char a[], char b[]) {
	char temp[10];
	strcpy(temp, a);
	strcpy(a, b);
	strcpy(b, temp);
}
int getRankLength() { // linear search
	int length;
	for(length = 0; length<100;length++)
		if(ranks[length].total_score == -1)
			break;
	return length;
}

void sortScore() {
	int temp, i, j, len = getRankLength();
	for(i = 0; i < len-1; i++) {
		for(j = i + 1; j < len; j++) {
			if(ranks[i].total_score < ranks[j].total_score) {
				swapInteger(&ranks[i].total_score, &ranks[j].total_score);
				swapString(ranks[i].nickname, ranks[j].nickname);
			}
		}
	}
}

void addRank(StructScore score) {
	ranks[getRankLength()+1] = score;
}

void printRank() {
	int i;
	for(i = 0; i < getRankLength(); i++)
		printf("Rank %d\t| nickname: %s, score: %d\n", i+1, ranks[i].nickname, ranks[i].total_score);
}

