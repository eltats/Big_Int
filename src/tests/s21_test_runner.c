#include "s21_test.h"

static int failed_tests = 0;

int main(void) {
    run_tests();

    if (failed_tests) {
        fprintf(stderr, "FAILED TESTS: %d\n", failed_tests);
    }

    return 0;
}

void run_testcase(Suite *testcase) {
    static int counter_testcase = 1;

    if (counter_testcase > 1)
        putchar('\n');

    printf("%s%d%s", "CURRENT TEST: ", counter_testcase, "\n");
    counter_testcase++;

    SRunner *sr = srunner_create(testcase);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    failed_tests += srunner_ntests_failed(sr);

    srunner_free(sr);
}

void run_tests(void) {
    Suite *list_cases[] = {
                           suite_s21_add(),
                           suite_s21_comparison(),
                           suite_s21_int_conversion(),
                           suite_s21_float_conversion(),
                           suite_s21_div(),
                           suite_s21_mod(),
                           suite_s21_mul(),
                           suite_s21_sub(),
                           suite_s21_floor(),
                           suite_s21_round(),
                           suite_s21_negate(),
                           suite_s21_truncate(),
                           NULL};

    for (Suite **current_testcase = list_cases; *current_testcase != NULL; current_testcase++) {
        run_testcase(*current_testcase);
    }
}
