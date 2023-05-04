#include <gtk/gtk.h>
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

int main(int argc, char *argv[]) {
    GtkBuilder      *builder; 
    GtkWidget       *window;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "interface.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));

    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(builder);

    gtk_widget_show(window);                
    gtk_main();

    return 0;
}