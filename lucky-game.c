#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define LINUX
#ifdef LINUX
#include <unistd.h>
#else
#include "windows.h"
#endif

typedef struct _StructScore {
	int total_score;
	char nickname[10];

} StructScore;

StructScore ranks[100];

void sortScore();
void clearScreen();
void waitMilliseconds(unsigned long milliseconds);
StructScore playGame(unsigned long milliseconds);
void addRank(StructScore score);
void printRank();

int main(void) {
	int i;
	for(i = 0; i < 100; i++)
		ranks[i].total_score = -1;
	srand(time(NULL));
	playGame(100000);
	return 0;
}

void clearScreen() {
#ifdef LINUX
	system("clear");
	return;
#else
	system("cls");
#endif
}

void waitMilliseconds(unsigned long milliseconds) {
#ifdef LINUX
	usleep(milliseconds);
#else
	sleep(milliseconds);
#endif
}

StructScore playGame(unsigned long milliseconds) {
	StructScore score;
	score.total_score = 0;
	int cache_score, gamePlayCount, timerOverall;
	char nextChapterVar;
	for(gamePlayCount = 0; gamePlayCount < 3; gamePlayCount++) {
		timerOverall = clock();
		while (clock() - timerOverall < milliseconds) {
			clearScreen();
			cache_score = rand()%10+1;
			printf("%3d\n", cache_score);
			waitMilliseconds(20000);
		}
		printf("Your Score: %d\nType Any key and press enter to continue.\n", cache_score);
		scanf("%c", &nextChapterVar);
		score.total_score += cache_score;
	}
	clearScreen();
	printf("Your total score = %d\n", score.total_score);
	printf("Type your name: ");
	scanf("%9s", score.nickname);
	return score;
}

void addRank(StructScore score) {
	int cursor;
	for(cursor = 0; cursor < 100; cursor++)
		if(ranks[cursor].total_score == -1)
			break;
	// find where to add new score information
	
	ranks[cursor] = score;
}

void printRank() {
	int i;
	for(i = 0; i < 100; i++) {
		if(ranks[i].total_score == -1)
			break;
		printf("Rank %d\t| nickname: %s, score: %d\n", i+1, ranks[i].nickname, ranks[i].total_score);
	}
}
