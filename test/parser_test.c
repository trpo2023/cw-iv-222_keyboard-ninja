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

// Пример теста для функции play_game
CTEST(play_game, test_play_game)
{
    char words[MAX_NUM_WORDS][MAX_WORD_LENGTH] = {"apple", "banana", "orange"};
    int min_len = 3;
    int max_len = 6;
    int num_rounds = 2;

    // Перенаправляем вывод в буфер, чтобы проверить результаты
    FILE* stream = freopen("output.txt", "w", stdout);

    // Вызываем функцию play_game
    play_game(words, min_len, max_len, num_rounds);

    // Закрываем поток вывода
    fclose(stream);

    // Открываем файл для чтения и считываем результаты игры
    FILE* result_file = fopen("output.txt", "r");
    char buffer[100];
    fgets(buffer, sizeof(buffer), result_file);

    // Добавьте проверки на ожидаемые результаты
    ASSERT_STR(
            "Accuracy:",
            buffer); // Проверяем, что строка начинается с "Accuracy:"
    // Добавьте другие проверки для остальных ожидаемых результатов

    // Закрываем файл
    fclose(result_file);
}