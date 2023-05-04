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

int main(void) {

    initscr();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    wbkgd(stdscr, COLOR_PAIR(1));
    
    char words[MAX_NUM_WORDS][MAX_WORD_LENGTH], difficulty;
    int num_words = 0;

    // Initialize ncurses
    initscr();
    cbreak();
    noecho();

    // Load words from a file
    FILE *fp = fopen("words.txt", "r");
    if (fp == NULL) {
        printw("Error: Unable to open file\n");
        refresh();
        endwin();
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

    // Main menu
    do {
        clear();
        printw("Typing Speed Test\n");
        printw("------------------\n\n");
        printw("Choose difficulty level:\n");
        printw("1) Easy (words of length 3-5)\n");
        printw("2) Medium (words of length 6-8)\n");
        printw("3) Hard (words of length 9-12)\n");
        printw("4) Expert (words of length 13+)\n");
        printw("5) Quit\n");
        refresh();
        difficulty = getch();
        clear();
        switch (difficulty) {
            case '1':
                play_game(words, 3, 5, 10);
                break;
            case '2':
                play_game(words, 6, 8, 10);
                break;
            case '3':
                play_game(words, 9, 12, 10);
                break;
            case '4':
                play_game(words, 13, MAX_WORD_LENGTH, 10);
                break;
            case '5':
                break;
            default:
                printw("Invalid choice\n");
                break;
        }
        if (difficulty >= '1' && difficulty <= '4') {
            printw("\nPress any key to continue\n");
            refresh();
            getch();
        }
    } while (difficulty != '5');

    // Clean up ncurses
    endwin();

    return 0;
}