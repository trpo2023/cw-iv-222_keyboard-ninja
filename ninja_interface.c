#include <gtk/gtk.h>

// Глобальная переменная для хранения цвета
GdkRGBA color = {0, 0, 0, 1};

// Обработчик события выбора сложности
void on_difficulty_changed(GtkComboBox *widget, gpointer data)
{
    // Получаем выбранное значение сложности
    gchar *difficulty = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(widget));

    // Используем выбранную сложность для установки уровня сложности
    // ...

    g_free(difficulty);
}

// Обработчик события клика по кнопкам цвета
void on_color_button_clicked(GtkButton *button, gpointer data)
{
    // Получаем выбранный цвет
    const gchar *color_str = gtk_button_get_label(GTK_BUTTON(button));

    // Устанавливаем значение цвета в соответствии с выбранным цветом
    if (g_strcmp0(color_str, "Red") == 0) {
        color.red = 1.0;
        color.green = 0;
        color.blue = 0;
    } else if (g_strcmp0(color_str, "Green") == 0) {
        color.red = 0;
        color.green = 1.0;
        color.blue = 0;
    } else if (g_strcmp0(color_str, "Blue") == 0) {
        color.red = 0;
        color.green = 0;
        color.blue = 1.0;
    }

    // Используем выбранный цвет для изменения цвета интерфейса
    GtkStyleContext *context = gtk_widget_get_style_context(GTK_WIDGET(data));
    gtk_style_context_add_class(context, "custom-background");
    gtk_style_context_set_background_color(context, &color);

    // Обновляем стиль элементов интерфейса
    gtk_style_context_invalidate(context);

    // Обновляем элементы интерфейса, чтобы отобразить изменения
    gtk_widget_queue_draw(GTK_WIDGET(data));
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

    // Создаем выпадающий список для выбора сложности
    difficulty_combo = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(difficulty_combo), "Easy");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(difficulty_combo), "Medium");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(difficulty_combo), "Hard");
    g_signal_connect(difficulty_combo, "changed", G_CALLBACK(on_difficulty_changed), NULL);
    gtk_box_pack_start(GTK_BOX(hbox), difficulty_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), difficulty_combo, FALSE, FALSE, 0);
    // Создаем горизонтальный контейнер для цвета
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    // Создаем метку для цвета
    color_label = gtk_label_new("Color:");

    // Создаем кнопки для выбора цвета
    color_red_button = gtk_button_new_with_label("Red");
    g_signal_connect(color_red_button, "clicked", G_CALLBACK(on_color_button_clicked), window);
    color_green_button = gtk_button_new_with_label("Green");
    g_signal_connect(color_green_button, "clicked", G_CALLBACK(on_color_button_clicked), window);
    color_blue_button = gtk_button_new_with_label("Blue");
    g_signal_connect(color_blue_button, "clicked", G_CALLBACK(on_color_button_clicked), window);

    // Устанавливаем класс для кнопок цвета
    gtk_widget_set_name(color_red_button, "red-button");
    gtk_widget_set_name(color_green_button, "green-button");
    gtk_widget_set_name(color_blue_button, "blue-button");

    // Добавляем метку и кнопки на контейнер цвета
    gtk_box_pack_start(GTK_BOX(hbox), color_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), color_red_button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), color_green_button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), color_blue_button, FALSE, FALSE, 0);

    // Устанавливаем стиль для окна и виджетов
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
                                    "window {\n"
                                    "  background-color: #e1e1e1;\n"
                                    "}\n"
                                    ".custom-background {\n"
                                    "  background-color: #ffffff;\n"
                                    "  border-radius: 5px;\n"
                                    "}\n"
                                    ".red-button {\n"
                                    "  background-color: #ff0000;\n"
                                    "}\n"
                                    ".green-button {\n"
                                    "  background-color: #00ff00;\n"
                                    "}\n"
                                    ".blue-button {\n"
                                    "  background-color: #0000ff;\n"
                                    "}\n", -1, NULL);
    GtkStyleContext *context = gtk_widget_get_style_context(window);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_style_context_add_class(context, "custom-background");

    // Отображаем окно
    gtk_widget_show_all(window);

    // Запускаем цикл обработки событий
    gtk_main();

    return 0;
}