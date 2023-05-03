#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 50
#define MAX_NUM_WORDS 10000

GtkWidget *word_display_label;
GtkWidget *input_entry;
GtkWidget *rounds_entry;
GtkWidget *min_len_entry;
GtkWidget *max_len_entry;

char words[MAX_NUM_WORDS][MAX_WORD_LENGTH];
int num_words = 0;

void play_game(int min_len, int max_len, int num_rounds) {
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
        gtk_label_set_text(GTK_LABEL(word_display_label), words[word_index]);
        gtk_entry_set_text(GTK_ENTRY(input_entry), "");
        gtk_widget_grab_focus(input_entry);
        gtk_main_iteration_do(FALSE);
        while (gtk_events_pending()) {
            gtk_main_iteration();
        }
        strcpy(input, gtk_entry_get_text(GTK_ENTRY(input_entry)));
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
    char results[100];
    sprintf(results, "Correct words: %d/%d\nAccuracy: %.2f%%\nTime taken: %d seconds\n%.2f words per minute", score, num_rounds, accuracy, (int) (end_time - start_time), f_score);
    gtk_label_set_text(GTK_LABEL(word_display_label), results);
}

void start_game(GtkWidget *widget, gpointer data) {
    int min_len = atoi(gtk_entry_get_text(GTK_ENTRY(min_len_entry)));
    int max_len = atoi(gtk_entry_get_text(GTK_ENTRY(max_len_entry)));
    int num_rounds = atoi(gtk_entry_get_text(GTK_ENTRY(rounds_entry)));
    if (min_len >= max_len) {
        gtk_label_set_text(GTK_LABEL(word_display_label), "Error: Minimum word length must be less than maximum word length.");
    } else {
        play_game(min_len, max_len, num_rounds);
    }
}

void load_words() {
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
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *start_button;
    GtkWidget *min_len_label;
    GtkWidget *max_len_label;
    GtkWidget *rounds_label;
    GtkWidget *title_label;
    GtkWidget *min_len_box;
    GtkWidget *max_len_box;
    GtkWidget *rounds_box;
    // Initialize GTK+
    gtk_init(&argc, &argv);

    // Create the main window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Typing Game");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    // Create the grid
    grid = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Load the words
    load_words();

    // Create the title label
    title_label = gtk_label_new("Typing Game");
    gtk_grid_attach(GTK_GRID(grid), title_label, 0, 0, 2, 1);

    // Create the minimum length label and entry
    min_len_label = gtk_label_new("Minimum Word Length:");
    gtk_grid_attach(GTK_GRID(grid), min_len_label, 0, 1, 1, 1);
    min_len_entry = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(min_len_entry), 5);
    gtk_entry_set_text(GTK_ENTRY(min_len_entry), "3");
    gtk_grid_attach(GTK_GRID(grid), min_len_entry, 1, 1, 1, 1);

    // Create the maximum length label and entry
    max_len_label = gtk_label_new("Maximum Word Length:");
    gtk_grid_attach(GTK_GRID(grid), max_len_label, 0, 2, 1, 1);
    max_len_entry = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(max_len_entry), 5);
    gtk_entry_set_text(GTK_ENTRY(max_len_entry), "6");
    gtk_grid_attach(GTK_GRID(grid), max_len_entry, 1, 2, 1, 1);

    // Create the number of rounds label and entry
    rounds_label = gtk_label_new("Number of Rounds:");
    gtk_grid_attach(GTK_GRID(grid), rounds_label, 0, 3, 1, 1);
    rounds_entry = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(rounds_entry), 5);
    gtk_entry_set_text(GTK_ENTRY(rounds_entry), "10");
    gtk_grid_attach(GTK_GRID(grid), rounds_entry, 1, 3, 1, 1);

    // Create the start button
    start_button = gtk_button_new_with_label("Start Game");
    g_signal_connect(start_button, "clicked", G_CALLBACK(start_game), NULL);
    gtk_grid_attach(GTK_GRID(grid), start_button, 0, 4, 2, 1);

    // Create the word display label
    word_display_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), word_display_label, 0, 5, 2, 1);

    // Show the window and start the main loop
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}