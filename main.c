#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 50
#define MAX_NUM_WORDS 10000

void play_game(char words[MAX_NUM_WORDS][MAX_WORD_LENGTH], int min_len, int max_len, int num_rounds) {
    char input[MAX_WORD_LENGTH];
    int i, len, score = 0;
    time_t start_time, end_time;
    int used[MAX_NUM_WORDS] = {0};
    int word_index;

    start_time = time(NULL);
    for (i = 0; i < num_rounds; i++) {
        do {
            word_index = rand() % MAX_NUM_WORDS;
            len = strlen(words[word_index]);
        } while (used[word_index] || len < min_len || len > max_len);
        used[word_index] = 1;
        printf("%s\n", words[word_index]);
        scanf("%s", input);
        if (strcasecmp(input, words[word_index]) == 0) {
            score++;
        } else {
            printf("Incorrect!\n");
        }
    }
    end_time = time(NULL);

    // Calculate accuracy
    float accuracy = ((float) score / num_rounds) * 100;
    float f_score = (float) score / (end_time - start_time) * 60;

    // Display results
    printf("Correct words: %d/%d\n", score, num_rounds);
    printf("Accuracy: %.2f%%\n", accuracy);
    printf("Time taken: %d seconds\n", (int) (end_time - start_time));
    printf("%.2f words per minute\n", f_score);
}

int main(void) {
    char words[MAX_NUM_WORDS][MAX_WORD_LENGTH];
    int num_words = 0;
    char difficulty;
    
    // Load words from a file
    FILE *fp = fopen("words.txt", "r");
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