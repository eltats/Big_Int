#include "s21_test.h"

START_TEST(float_conversion_1) {
    float a = 2.125;
    float b = 0;
    s21_decimal num = {'\0'};
    s21_from_float_to_decimal(a, &num);
    s21_from_decimal_to_float(num, &b);
    ck_assert_float_eq_tol(a, b, 1e-6);
}
END_TEST

START_TEST(float_conversion_2) {
    float a = -2.125;
    float b = 0;
    s21_decimal num = {'\0'};
    s21_from_float_to_decimal(a, &num);
    s21_from_decimal_to_float(num, &b);
    ck_assert_float_eq_tol(a, b, 1e-6);
}
END_TEST

START_TEST(float_conversion_3) {
    float a = 0.9;
    float b = 0;
    s21_decimal num = {'\0'};
    s21_from_float_to_decimal(a, &num);
    s21_from_decimal_to_float(num, &b);
    ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_conversion_4) {
    float a = 0.9;
    float b = 123;
    s21_decimal num = {'\0'};
    s21_from_float_to_decimal(a, &num);
    s21_from_decimal_to_float(num, &b);
    ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_conversion_5) {
    float a = -0;
    float b = 0;
    s21_decimal num = {'\0'};
    s21_from_float_to_decimal(a, &num);
    s21_from_decimal_to_float(num, &b);
    ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_conversion_6) {
    float a = 123456.987654;
    float b = 0;
    s21_decimal num = {'\0'};
    s21_from_float_to_decimal(a, &num);
    s21_from_decimal_to_float(num, &b);
    ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_conversion_7) {
    float a = -123456.987654;
    float b = 0;
    s21_decimal num = {'\0'};
    s21_from_float_to_decimal(a, &num);
    s21_from_decimal_to_float(num, &b);
    ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_conversion_8) {
    float a = NAN;
    float b = 0;
    s21_decimal num = {'\0'};
    s21_from_float_to_decimal(a, &num);
    s21_from_decimal_to_float(num, &b);
    ck_assert_int_eq(is_nan(num), 1);
    ck_assert_float_nan(b);
}
END_TEST

START_TEST(float_conversion_9) {
    float a = INFINITY;
    float b = 0;
    s21_decimal num = {'\0'};
    s21_from_float_to_decimal(a, &num);
    s21_from_decimal_to_float(num, &b);
    ck_assert_int_eq(is_pos_inf(num), 1);
    ck_assert_float_infinite(b);
}
END_TEST

START_TEST(float_conversion_10) {
    float a = -INFINITY;
    float b = 0;
    s21_decimal num = {'\0'};
    s21_from_float_to_decimal(a, &num);
    s21_from_decimal_to_float(num, &b);
    ck_assert_int_eq(is_neg_inf(num), 1);
    ck_assert_float_infinite(b);
}
END_TEST

START_TEST(float_conversion_11) {
    float a = 100000.0000001;
    float b = 0;
    s21_decimal num = {{0, 10000, 10000, 1835008}};
    s21_from_float_to_decimal(a, &num);
    s21_from_decimal_to_float(num, &b);
    ck_assert_float_eq_tol(a, b, 1e-6);
}
END_TEST

Suite *suite_s21_float_conversion(void) {
    Suite *s12;
    TCase *tc12;
    s12 = suite_create("s21_float_conversion");
    tc12 = tcase_create("case_float_conversion");

    tcase_add_test(tc12, float_conversion_1);
    tcase_add_test(tc12, float_conversion_2);
    tcase_add_test(tc12, float_conversion_3);
    tcase_add_test(tc12, float_conversion_4);
    tcase_add_test(tc12, float_conversion_5);
    tcase_add_test(tc12, float_conversion_6);
    tcase_add_test(tc12, float_conversion_7);
    tcase_add_test(tc12, float_conversion_8);
    tcase_add_test(tc12, float_conversion_9);
    tcase_add_test(tc12, float_conversion_10);
    tcase_add_test(tc12, float_conversion_11);

    suite_add_tcase(s12, tc12);
    return s12;
}
