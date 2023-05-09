#include <stdio.h>

#include "ninja_lib/ninja.h"

#include <ctest.h>

// Функция для имитации пользовательского ввода
void mock_user_input(const char* input)
{
    FILE* input_stream = freopen("input.txt", "w", stdin);
    fputs(input, input_stream);
    fclose(input_stream);
}

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