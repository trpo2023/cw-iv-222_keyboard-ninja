#include <ninja_lib/ninja.h>

int main(void)
{
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    wbkgd(stdscr, COLOR_PAIR(1));
    char words[MAX_NUM_WORDS][MAX_WORD_LENGTH], difficulty;
    int num_words = 0;
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    // Load words from a file
    FILE* fp = fopen("ninja_txt/words.txt", "r");
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
        printw("Welcome to keyboard ninja!\n");
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
            play_game(words, 3, 5, 25);
            break;
        case '2':
            play_game(words, 6, 8, 25);
            break;
        case '3':
            play_game(words, 9, 12, 25);
            break;
        case '4':
            play_game(words, 13, MAX_WORD_LENGTH, 25);
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