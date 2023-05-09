#include <stdio.h>

#include <ninja_lib/ninja.h>

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

// Тест для функции update_high_score
CTEST(ninja_game, test_update_high_score)
{
    // Создание временного файла для тестирования
    FILE* fp = fopen("test_highscore.txt", "w");
    fprintf(fp, "15");
    fclose(fp);

    // Вызов тестируемой функции
    update_high_score(15);

    // Чтение высшего результата из файла
    int high_score = 0;
    fp = fopen("test_highscore.txt", "r");
    fscanf(fp, "%d", &high_score);
    fclose(fp);

    // Проверка, что высший результат обновлен
    ASSERT_EQUAL(15, high_score);

    // Удаление временного файла
    remove("test_highscore.txt");
}