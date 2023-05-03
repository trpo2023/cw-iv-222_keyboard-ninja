#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 50
#define MAX_NUM_WORDS 10000

void play_game(char words[MAX_NUM_WORDS][MAX_WORD_LENGTH], int min_len, int max_len, int num_rounds) {
    char input[MAX_WORD_LENGTH];
    int i, len, score = 0, used[MAX_NUM_WORDS] = {0}, word_index;
    time_t start_time, end_time;

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
    printf("Accuracy: %.2f%%\n", accuracy);
    printf("Time taken: %d seconds\n", (int) (end_time - start_time));
    printf("%.2f words per minute\n", f_score);
    
    //highscore.txt
    // Read high score from file
    FILE *highscore_file = fopen("thirdparty/highscore.txt", "r");
    int high_score = 0;
    if (highscore_file != NULL) {
        fscanf(highscore_file, "%d", &high_score);
        fclose(highscore_file);
    }
    // Update high score if necessary
    if (f_score > high_score) {
        high_score = f_score;
        highscore_file = fopen("thirdparty/highscore.txt", "w");
        if (highscore_file != NULL) {
            fprintf(highscore_file, "%d", high_score);
            fclose(highscore_file);
        }
    }
    // Display high score
    printf("High score: %d\n", high_score);
}