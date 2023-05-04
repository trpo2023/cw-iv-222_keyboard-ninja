#include <gtk/gtk.h>

void on_difficulty_changed(GtkComboBox *widget, gpointer data)
{
    // Получаем выбранное значение сложности
    gchar *difficulty = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(widget));

    // Используем выбранную сложность для установки уровня сложности
    // ...

    g_free(difficulty);
}

void on_color_button_clicked(GtkButton *button, gpointer data)
{
    // Получаем выбранный цвет
    gchar *color = gtk_button_get_label(GTK_BUTTON(button));

    // Используем выбранный цвет для изменения цвета интерфейса
    // ...

    g_free(color);
}

int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *hbox;
    GtkWidget *difficulty_label;
    GtkWidget *difficulty_combo;
    GtkWidget *color_label;
    GtkWidget *color_red_button;
    GtkWidget *color_green_button;
    GtkWidget *color_blue_button;

    gtk_init(&argc, &argv);

    // Создаем окно
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Keyboard Trainer");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Создаем вертикальный контейнер
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Создаем горизонтальный контейнер для сложности
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    // Создаем метку для сложности
    difficulty_label = gtk_label_new("Difficulty:");
    gtk_box_pack_start(GTK_BOX(hbox), difficulty_label, FALSE, FALSE, 0);

    // Создаем выпадающий список для сложности
    difficulty_combo = gtk_combo_box_text_new();
    // Добавляем варианты сложности в выпадающий список
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(difficulty_combo), "Easy");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(difficulty_combo), "Medium");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(difficulty_combo), "Hard");

    // Устанавливаем значение по умолчанию
    gtk_combo_box_set_active(GTK_COMBO_BOX(difficulty_combo), 0);

    // Добавляем обработчик события выбора сложности
    g_signal_connect(difficulty_combo, "changed", G_CALLBACK(on_difficulty_changed), NULL);

    // Добавляем выпадающий список в горизонтальный контейнер
    gtk_box_pack_start(GTK_BOX(hbox), difficulty_combo, FALSE, FALSE, 0);

    // Создаем горизонтальный контейнер для цвета
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    // Создаем метку для цвета
    color_label = gtk_label_new("Color:");
    gtk_box_pack_start(GTK_BOX(hbox), color_label, FALSE, FALSE, 0);

    // Создаем кнопки для выбора цвета
    color_red_button = gtk_button_new_with_label("Red");
    color_green_button = gtk_button_new_with_label("Green");
    color_blue_button = gtk_button_new_with_label("Blue");

    // Добавляем обработчики события клика по кнопкам цвета
    g_signal_connect(color_red_button, "clicked", G_CALLBACK(on_color_button_clicked), NULL);
    g_signal_connect(color_green_button, "clicked", G_CALLBACK(on_color_button_clicked), NULL);
    g_signal_connect(color_blue_button, "clicked", G_CALLBACK(on_color_button_clicked), NULL);

    // Добавляем кнопки цвета в горизонтальный контейнер
    gtk_box_pack_start(GTK_BOX(hbox), color_red_button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), color_green_button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), color_blue_button, FALSE, FALSE, 0);

    // Отображаем окно
    gtk_widget_show_all(window);

    // Запускаем главный цикл обработки событий
    gtk_main();

    return 0;
}