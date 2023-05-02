#include <ncurses.h>

int main() {
    // Initialize ncurses
    initscr();

    // Create a new window
    WINDOW* win = newwin(10, 30, 5, 10);

    // Draw a border around the window
    box(win, 0, 0);

    // Add text to the window
    mvwprintw(win, 1, 1, "Hello, world!");

    // Refresh the window to display changes
    wrefresh(win);

    // Wait for user input
    getch();

    // Clean up and exit ncurses
    endwin();

    return 0;
}