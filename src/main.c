#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "libs/ninja.h"

int main(void) {
    char words[MAX_NUM_WORDS][MAX_WORD_LENGTH], difficulty;
    int num_words = 0;
    
    // Load words from a file
    FILE *fp = fopen("thirdparty/words.txt", "r");
    if (fp == NULL) {
        printf("Error: Unable to open file\n");
        exit(1);
    }
    while (fgets(words[num_words], MAX_WORD_LENGTH, fp) != NULL) {
        int len = strlen(words[num_words]);
        if (words[num_words][len - 1] == '\n') {
            words[num_words][len - 1] = '\0';
        }
        num_words++;
    }
    fclose(fp);

    // Seed the random number generator
    srand(time(NULL));

    // Ask the user for the difficulty
    printf("Choose difficulty: easy, medium or hard\n");
    scanf("%s", &difficulty);
    switch (difficulty) {
        case 'e':
        case 'E':
            play_game(words, 4, 7, 10);
            break;
        case 'm':
        case 'M':
            play_game(words, 7, 12, 10);
            break;
        case 'h':
        case 'H':
            play_game(words, 12, 20, 10);
            break;
        default:
            printf("Error: no such difficulty\n");
            return 1;
    }
    return 0;
}