#include <ctest.h>
#include <lib/lib.h>
#include <math.h>
#include <stdio.h>

CTEST(update_high_score, invalid_input)
{
    // Arrange
    int f_score = -100;
    char pr_f_score[50];

    // Act
    update_high_score(f_score);

    FILE* fp = fopen("ninja_txt/test_inv.txt", "r");
    if (fp != NULL) {
        fscanf(fp, "%s", pr_f_score);
        fclose(fp);
    }

    // Assert
    ASSERT_STR("Invalid", pr_f_score);

    FILE* ft = fopen("ninja_txt/highscore.txt", "w");
    if (ft != NULL) {
        fprintf(ft, "0");
        fclose(ft);
    }
}

CTEST(update_high_score, read_high_score)
{
    int high_score = -1;
    FILE* fp = fopen("ninja_txt/highscore.txt", "r");
    if (fp != NULL) {
        fscanf(fp, "%d", &high_score);
        fclose(fp);
    }

    // Act
    update_high_score(high_score);

    // Assert
    ASSERT_NOT_EQUAL(high_score, -1);

    FILE* ft = fopen("ninja_txt/highscore.txt", "w");
    if (ft != NULL) {
        fprintf(ft, "0");
        fclose(ft);
    }
}

CTEST(update_high_score, write_high_score)
{
    // Arrange
    int high_score = 1;

    update_high_score(high_score);

    int pr_high_score = 0;
    FILE* fp = fopen("ninja_txt/highscore.txt", "r");
    if (fp != NULL) {
        fscanf(fp, "%d", &pr_high_score);
        fclose(fp);
    }

    // Assert
    ASSERT_EQUAL(pr_high_score, 1);

    FILE* ft = fopen("ninja_txt/highscore.txt", "w");
    if (ft != NULL) {
        fprintf(ft, "0");
        fclose(ft);
    }
}

CTEST(update_high_score, valid_input)
{
    int high_score = 2;
    update_high_score(high_score);

    int pr_high_score = 0;
    FILE* fp = fopen("ninja_txt/highscore.txt", "r");
    if (fp != NULL) {
        fscanf(fp, "%d", &pr_high_score);
        fclose(fp);
    }
    // Assert
    ASSERT_EQUAL(pr_high_score, 2);
}

CTEST(update_high_score, save_previos_record)
{
    int high_score = 1;
    update_high_score(high_score);

    int pr_high_score = 0;
    FILE* fp = fopen("ninja_txt/highscore.txt", "r");
    if (fp != NULL) {
        fscanf(fp, "%d", &pr_high_score);
        fclose(fp);
    }
    // Assert
    ASSERT_EQUAL(pr_high_score, 2);

    FILE* ft = fopen("ninja_txt/highscore.txt", "w");
    if (ft != NULL) {
        fprintf(ft, "0");
        fclose(ft);
    }
}