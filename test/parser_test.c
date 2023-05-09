#include <stdio.h>

#include "ninja_lib/ninja.h"

#include <ctest.h>

// Функция для проверки, что два слова равны
CTEST(compare_words, test_equal_words) {
    char word1[] = "apple";
    char word2[] = "apple";

    int result = strcasecmp(word1, word2);

    ASSERT_EQUAL(0, result);
}

// Функция для проверки, что два слова не равны
CTEST(compare_words, test_unequal_words) {
    char word1[] = "apple";
    char word2[] = "banana";

    int result = strcasecmp(word1, word2);

    ASSERT_NOT_EQUAL(0, result);
}

// Пример теста для функции play_game
CTEST(play_game, test_play_game) {
    char words[MAX_NUM_WORDS][MAX_WORD_LENGTH] = {"apple", "banana", "orange"};
    int min_len = 3;
    int max_len = 6;
    int num_rounds = 2;

    play_game(words, min_len, max_len, num_rounds);

    // Добавьте здесь проверки на ожидаемые результаты игры
    // Используйте макросы ASSERT_* для проверки результатов
}