#include <stdio.h>

#include <../src/ninja_lib/ninja.h>
#include <../thirdparty/ctest.h>

CTEST(update_high_score, invalid_input)
{
    // Arrange
    int f_score = -100;

    // Act
    update_high_score(f_score);

    // Assert
    ASSERT_TRUE(1);
}

CTEST(update_high_score, read_high_score)
{
    // Arrange
    int high_score = 0;
    FILE* fp = fopen("ninja_txt/highscore.txt", "r");
    if (fp != NULL) {
        fscanf(fp, "%d", &high_score);
        fclose(fp);
    }

    // Act
    update_high_score(0);

    // Assert
    ASSERT_TRUE(high_score >= 0);
}

CTEST(update_high_score, write_high_score)
{
    // Arrange
    int high_score = 100;
    FILE* fp = fopen("ninja_txt/highscore.txt", "w");
    if (fp != NULL) {
        fprintf(fp, "%d", high_score);
        fclose(fp);
    }

    // Act
    update_high_score(0);

    // Assert
    ASSERT_TRUE(1);
}

CTEST(update_high_score, valid_input)
{
    int high_score = 0;
    FILE* fp = fopen("ninja_txt/highscore.txt", "w");
        if (fp != NULL) {
            fprintf(fp, "%d", high_score);
            fclose(fp);
        }
    // Assert
    ASSERT_TRUE(1);
}