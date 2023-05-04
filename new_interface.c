#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <ncurses.h>
#include <math.h>

#define MAX_WORD_LENGTH 50
#define MAX_NUM_WORDS 10000

void play_game(char words[MAX_NUM_WORDS][MAX_WORD_LENGTH], int min_len, int max_len, int num_rounds) {
    char input[MAX_WORD_LENGTH];
    int i, len, score = 0, used[MAX_NUM_WORDS] = {0}, word_index;
    time_t start_time, end_time;
    float total_time = 0;
    int correct_words = 0;

    for (i = 0; i < num_rounds; i++) {
        start_time = time(NULL);
        do {
            word_index = rand() % MAX_NUM_WORDS;
            len = strlen(words[word_index]);
        } while (used[word_index] || len < min_len || len > max_len);
        used[word_index] = 1;
        clear();
        printw("%s\n", words[word_index]);
        refresh();
        int ch, pos = 0;
        while (1) {
            ch = getch();
            if (ch == KEY_BACKSPACE || ch == 127) {
                if (pos > 0) {
                    pos--;
                    input[pos] = '\0';
                }
            } else if (ch == KEY_ENTER || ch == '\n') {  // If user pressed Enter
                if (strcasecmp(input, words[word_index]) == 0) {
                    score++;
                    correct_words++;
                } else {
                    printw("Incorrect!\n");
                }
                break;
            } else if (isalpha(ch)) {
                if (pos < MAX_WORD_LENGTH - 1) {
                    input[pos] = toupper(ch);
                    pos++;
                    input[pos] = '\0';
                }
            }
            clear();
            printw("%s\n%s", words[word_index], input);
            refresh();
        }
        end_time = time(NULL);
        total_time += difftime(end_time, start_time);
    }

    // Calculate accuracy
    float accuracy = ((float) score / num_rounds) * 100;
    float f_score = (float) score / (total_time / 60);

    // Display results
    clear();
    printw("Accuracy: %.2f%%\n", accuracy);
    printw("Time taken: %.0f:%02.0f\n", total_time / 60, fmod(total_time, 60));
    printw("%.2f words per minute\n", f_score);
    printw("Correctly entered words: %d out of %d\n", correct_words, num_rounds);
    printw("End time: %s", ctime(&end_time)); // вывод времени окончания игры

    //highscore.txt
    // Read high score from file
    int high_score = 0;
    FILE *fp = fopen("highscore.txt", "r");
    if (fp != NULL) {
    fscanf(fp, "%d", &high_score);
    fclose(fp);
    }
    // Check if current score is higher than high score
    if (score > high_score) {
    // Update high score
    high_score = score;

    // Write new high score to file
    fp = fopen("highscore.txt", "w");
    if (fp != NULL) {
        fprintf(fp, "%d", high_score);
        fclose(fp);
    }

    // Display message about new high score
    printw("New high score: %d!\n", high_score);
    } else {
    // Display message about current high score
    printw("Current high score: %d\n", high_score);
    }

    // Wait for user input before exiting
    printw("\nPress any key to exit...");
    getch();
}

int main() {
    srand(time(NULL));
    char words[MAX_NUM_WORDS][MAX_WORD_LENGTH];
    int num_words = 0;
    int min_len = 4, max_len = 8, num_rounds = 10;
    // Open file containing words
    FILE *fp = fopen("words.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    // Read words from file
    char word[MAX_WORD_LENGTH];
    while (fgets(word, MAX_WORD_LENGTH, fp)) {
        // Remove trailing newline character
        word[strcspn(word, "\n")] = '\0';

        // Add word to array if it is the right length
        int len = strlen(word);
        if (len >= min_len && len <= max_len && num_words < MAX_NUM_WORDS) {
            strcpy(words[num_words], word);
            num_words++;
        }
    }

    // Close file
    fclose(fp);

    // Initialize ncurses
    initscr();
    cbreak();
    noecho();

    // Play game
    play_game(words, min_len, max_len, num_rounds);

    // Clean up ncurses
    endwin();

    return 0;
}