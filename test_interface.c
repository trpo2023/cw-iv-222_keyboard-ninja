#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <ncurses.h>

#define MAX_WORD_LENGTH 50
#define MAX_NUM_WORDS 10000

int main(void) {
    char words[MAX_NUM_WORDS][MAX_WORD_LENGTH];
    int num_words = 0;
    char input[MAX_WORD_LENGTH];
    int i, j, k, len;
    int score = 0;
    int max_num_words;
    time_t start_time, end_time;

    // Load words from a file
    FILE *fp = fopen("words.txt", "r");
    if (fp == NULL) {
        printf("Error: Unable to open file\n");
        exit(1);
    }
    while (fgets(words[num_words], MAX_WORD_LENGTH, fp) != NULL) {
        len = strlen(words[num_words]);
        if (words[num_words][len - 1] == '\n') {
            words[num_words][len - 1] = '\0';
        }
        num_words++;
    }
    fclose(fp);

    // Initialize ncurses
    initscr();
    cbreak();
    noecho();

    // Ask the user for the number of words to play with
    mvprintw(0, 0, "Enter the number of words to play with: ");
    scanw("%d", &max_num_words);

    // Validate user input
    if (max_num_words > num_words) {
        mvprintw(1, 0, "Error: The number of words to play with cannot be greater than the total number of words.");
        getch();
        endwin();
        exit(1);
    }

    // Shuffle the words
    srand(time(NULL));
    for (i = 0; i < num_words - 1; i++) {
        j = i + rand() / (RAND_MAX / (num_words - i) + 1);
        strcpy(input, words[j]);
        strcpy(words[j], words[i]);
        strcpy(words[i], input);
    }

    // Game loop
    start_time = time(NULL);
    for (i = 0; i < max_num_words; i++) {
        mvprintw(3 + i, 0, "%s\n", words[i]);
        refresh();
        scanw("%s", input);
        if (strcmp(input, words[i]) == 0) {
            score++;
        } else {
            mvprintw(3 + i, strlen(words[i]) + 1, "Incorrect!");
            refresh();
            getch();
        }
    }
    end_time = time(NULL);

    // Calculate accuracy
    float accuracy = ((float) score / max_num_words) * 100;

    // Display results
    mvprintw(3 + max_num_words, 0, "Score: %d/%d", score, max_num_words);
    mvprintw(4 + max_num_words, 0, "Accuracy: %.2f%%", accuracy);
    mvprintw(5 + max_num_words, 0, "Time taken: %d seconds", (int) (end_time - start_time));
    refresh();
    getch();

    // Clean up ncurses
    endwin();

    return 0;
}