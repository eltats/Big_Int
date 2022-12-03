#ifndef SRC_TESTS_S21_TEST_H_
#define SRC_TESTS_S21_TEST_H_

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../s21_decimal.h"
#include "../additional/s21_helpers.h"
Suite *suite_s21_add(void);
Suite *suite_s21_mul(void);
Suite *suite_s21_is_equal(void);
Suite *suite_s21_round(void);
Suite *suite_s21_mod(void);
Suite *suite_s21_int_conversion(void);
Suite *suite_s21_floor(void);
Suite *suite_s21_comparison(void);
Suite *suite_s21_div(void);
Suite *suite_s21_float_conversion(void);
Suite *suite_s21_negate(void);
Suite *suite_s21_truncate(void);
Suite *suite_s21_sub(void);

void run_tests(void);
void run_testcase(Suite *testcase);
#endif  // SRC_TESTS_S21_TEST_H_
