#include <gtk/gtk.h>

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *label;
    GtkWidget *entry;
    GtkWidget *button;
    GtkWidget *hbox;
    GtkWidget *vbox;

    gtk_init(&argc, &argv);

    // Создаем окно
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Клавиатурный тренажер");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    // Создаем вертикальный контейнер
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Создаем метку и поле ввода
    label = gtk_label_new("Введите слово:");
    entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);

    // Создаем кнопку "Начать тренировку"
    button = gtk_button_new_with_label("Начать тренировку");
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);

    // Создаем горизонтальный контейнер для отображения результатов
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    // Создаем метку для отображения количества правильных и неправильных ответов
    label = gtk_label_new("Правильных: 0 Неправильных: 0");
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);

    // Связываем сигнал нажатия на кнопку с функцией-обработчиком
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(gtk_button_clicked), entry);

    // Отображаем окно и запускаем главный цикл
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

void on_start_button_clicked(GtkWidget *widget, gpointer data) {
    const char *word = gtk_entry_get_text(GTK_ENTRY(data));
    // Дополнительный код для начала тренировки с введенным словом
}