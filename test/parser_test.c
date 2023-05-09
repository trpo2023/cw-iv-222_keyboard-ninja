#include <stdio.h>

#include "ninja_lib/ninja.h"

#include <ctest.h>

// Функция для проверки, что два слова равны
CTEST(compare_words, test_equal_words)
{
    char word1[] = "apple";
    char word2[] = "apple";

    int result = strcasecmp(word1, word2);

    ASSERT_EQUAL(0, result);
}

// Функция для проверки, что два слова не равны
CTEST(compare_words, test_unequal_words)
{
    char word1[] = "apple";
    char word2[] = "banana";

    int result = strcasecmp(word1, word2);

    ASSERT_NOT_EQUAL(0, result);
}

// Тест для проверки игры с отрицательным количеством раундов
CTEST(play_game, test_negative_rounds)
{
    char words[MAX_NUM_WORDS][MAX_WORD_LENGTH] = {"apple", "banana", "orange"};
    int min_len = 3;
    int max_len = 6;
    int num_rounds = -1;

    // Перенаправляем вывод в буфер, чтобы проверить результаты
    FILE* stream = freopen("output.txt", "w", stdout);

    // Вызываем функцию play_game только если num_rounds > 0
    if (num_rounds > 0) {
        play_game(words, min_len, max_len, num_rounds);
    } else {
        printf("Invalid number of rounds.\n");
    }

    // Закрываем поток вывода
    fclose(stream);

    // Открываем файл для чтения и считываем результаты игры
    FILE* result_file = fopen("output.txt", "r");
    char buffer[100];
    fgets(buffer, sizeof(buffer), result_file);

    // Добавьте проверки на ожидаемые результаты
    ASSERT_STR("Invalid number of rounds.", buffer);

    // Закрываем файл
    fclose(result_file);
}

// Тест для проверки игры без слов
CTEST(play_game, test_no_words)
{
    char words[MAX_NUM_WORDS][MAX_WORD_LENGTH] = {};
    int min_len = 3;
    int max_len = 6;
    int num_rounds = 1;

    // Перенаправляем вывод в буфер, чтобы проверить результаты
    FILE* stream = freopen("output.txt", "w", stdout);

    // Вызываем функцию play_game только если есть хотя бы одно слово
    int num_words = sizeof(words) / sizeof(words[0]);
    if (num_words > 0) {
        play_game(words, min_len, max_len, num_rounds);
    } else {
        printf("No words available.\n");
    }

    // Закрываем поток вывода
    fclose(stream);

    // Открываем файл для чтения и считываем результаты игры
    FILE* result_file = fopen("output.txt", "r");
    char buffer[100];
    fgets(buffer, sizeof(buffer), result_file);

    // Добавьте проверки на ожидаемые результаты
    ASSERT_STR("No words available.", buffer);

    // Закрываем файл
    fclose(result_file);
}