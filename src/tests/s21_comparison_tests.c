#include "s21_test.h"

/* ---------------- is_equal function ---------------- */

START_TEST(is_equal_1) {
    s21_decimal num = {'\0'};
    s21_decimal num1 = {'\0'};
    ck_assert_int_eq(s21_is_equal(num, num1), 1);
}
END_TEST

START_TEST(is_equal_2) {
    s21_decimal num = {'\0'};
    s21_decimal num1 = {'\0'};
    set_inf(&num, 0);
    set_inf(&num1, 0);
    ck_assert_int_eq(s21_is_equal(num, num1), 1);
}
END_TEST

START_TEST(is_equal_3) {
    s21_decimal num = {'\0'};
    s21_decimal num1 = {'\0'};
    set_inf(&num, 1);
    set_inf(&num1, 1);
    ck_assert_int_eq(s21_is_equal(num, num1), 1);
}
END_TEST

START_TEST(is_equal_4) {
    s21_decimal num = {{UINT32_MAX, 0, 0, 0}};
    s21_decimal num1 = {{UINT32_MAX, 0, 0, 0}};
    ck_assert_int_eq(s21_is_equal(num, num1), 1);
}
END_TEST

START_TEST(is_equal_5) {
    s21_decimal num = {{UINT32_MAX, 0, 0, 0}};
    s21_decimal num1 = {{UINT32_MAX, 0, 0, 0}};
    set_sign(&num1, 1);
    ck_assert_int_eq(s21_is_equal(num, num1), 0);
}
END_TEST

START_TEST(is_equal_6) {
    s21_decimal num = {'\0'};
    s21_decimal num1 = {'\0'};
    set_sign(&num1, 1);
    ck_assert_int_eq(s21_is_equal(num, num1), 1);
}
END_TEST

START_TEST(is_equal_7) {
    s21_decimal num = {{0, UINT32_MAX, 0, 0}};
    s21_decimal num1 = {{UINT32_MAX, 0, 0, 0}};
    ck_assert_int_eq(s21_is_equal(num, num1), 0);
}
END_TEST

START_TEST(is_equal_8) {
    s21_decimal num = {{0, UINT32_MAX, 0, 0}};
    s21_decimal num1 = {{0, UINT32_MAX, 0, 0}};
    set_scale(&num, 7);
    set_scale(&num1, 5);
    set_sign(&num, 0);
    set_sign(&num1, 0);
    ck_assert_int_eq(s21_is_equal(num, num1), 0);
}
END_TEST

START_TEST(is_equal_9) {
    s21_decimal num = {{0, UINT32_MAX, 0, 0}};
    s21_decimal num1 = {{0, UINT32_MAX, 0, 0}};
    set_scale(&num, 5);
    set_scale(&num1, 5);
    ck_assert_int_eq(s21_is_equal(num, num1), 1);
}
END_TEST

START_TEST(is_equal_10) {
    s21_decimal num = {{0, UINT32_MAX, 0, 0}};
    s21_decimal num1 = {{0, UINT32_MAX, 0, 0}};
    set_scale(&num, 3);
    set_scale(&num1, 9);
    set_sign(&num, 1);
    set_sign(&num1, 1);
    ck_assert_int_eq(s21_is_equal(num, num1), 0);
}
END_TEST

START_TEST(is_equal_11) {
    s21_decimal num = {{6789345, 9375, 0, 0}};
    s21_decimal num1 = {{6789344, 9375, 0, 0}};
    ck_assert_int_eq(s21_is_equal(num, num1), 0);
}
END_TEST

START_TEST(is_equal_12) {
    s21_decimal num = {{6789345, 9375, 0, 0}};
    s21_decimal num1 = {{6789344, 9365, 0, 0}};
    ck_assert_int_eq(s21_is_equal(num, num1), 0);
}
END_TEST

START_TEST(is_equal_13) {
    s21_decimal num = {{6789345, 9375, 10111, 0}};
    s21_decimal num1 = {{6789344, 9365, 10111, 0}};
    ck_assert_int_eq(s21_is_equal(num, num1), 0);
}
END_TEST

START_TEST(is_equal_14) {
    s21_decimal num = {{6789345, 9375, 10111, 0}};
    s21_decimal num1 = {{6789345, 9375, 10115, 0}};
    ck_assert_int_eq(s21_is_equal(num, num1), 0);
}
END_TEST

START_TEST(is_equal_15) {
    s21_decimal num = {{0, 9375, 10115, 0}};
    s21_decimal num1 = {{0, 9375, 10115, 0}};
    set_scale(&num, 3);
    set_scale(&num1, 9);
    set_sign(&num, 1);
    set_sign(&num1, 1);
    ck_assert_int_eq(s21_is_equal(num, num1), 0);
}
END_TEST

/* ---------------- other comparison functions ---------------- */

START_TEST(comparison_1) {
    s21_decimal num = {{UINT32_MAX, 0, 0, 2149318656}};
    s21_decimal num1 = {{UINT32_MAX, 0, 0, 2149318656}};
    ck_assert_int_eq(s21_is_equal(num, num1), 1);
    ck_assert_int_eq(s21_is_greater(num, num1), 0);
    ck_assert_int_eq(s21_is_less(num, num1), 0);
    ck_assert_int_eq(s21_is_greater_or_equal(num, num1), 1);
    ck_assert_int_eq(s21_is_less_or_equal(num, num1), 1);
    ck_assert_int_eq(s21_is_not_equal(num, num1), 0);
}
END_TEST

START_TEST(comparison_2) {
    s21_decimal num = {{UINT32_MAX, 0, 0, 2149318656}};
    s21_decimal num1 = {{UINT32_MAX, 0, 0, 1835008}};
    ck_assert_int_eq(s21_is_equal(num, num1), 0);
    ck_assert_int_eq(s21_is_greater(num, num1), 0);
    ck_assert_int_eq(s21_is_less(num, num1), 1);
    ck_assert_int_eq(s21_is_greater_or_equal(num, num1), 0);
    ck_assert_int_eq(s21_is_less_or_equal(num, num1), 1);
    ck_assert_int_eq(s21_is_not_equal(num, num1), 1);
}
END_TEST

START_TEST(comparison_3) {
    s21_decimal num = {{UINT32_MAX, 0, 0, 1835008}};
    s21_decimal num1 = {{UINT32_MAX, 0, 0, 1310720}};
    ck_assert_int_eq(s21_is_equal(num, num1), 0);
    ck_assert_int_eq(s21_is_greater(num, num1), 0);
    ck_assert_int_eq(s21_is_less(num, num1), 1);
    ck_assert_int_eq(s21_is_greater_or_equal(num, num1), 0);
    ck_assert_int_eq(s21_is_less_or_equal(num, num1), 1);
    ck_assert_int_eq(s21_is_not_equal(num, num1), 1);
}
END_TEST

START_TEST(comparison_4) {
    s21_decimal num = {{UINT32_MAX, 123, 456, 2149318656}};
    s21_decimal num1 = {{UINT32_MAX, 123, 456, 2148794368}};
    ck_assert_int_eq(s21_is_equal(num, num1), 0);
    ck_assert_int_eq(s21_is_greater(num, num1), 1);
    ck_assert_int_eq(s21_is_less(num, num1), 0);
    ck_assert_int_eq(s21_is_greater_or_equal(num, num1), 1);
    ck_assert_int_eq(s21_is_less_or_equal(num, num1), 0);
    ck_assert_int_eq(s21_is_not_equal(num, num1), 1);
}
END_TEST

START_TEST(comparison_5) {
    s21_decimal num = {{0, 0, 1, 0}};
    s21_decimal num1 = {{0, 0, 1, 0}};
    ck_assert_int_eq(s21_is_equal(num, num1), 1);
    ck_assert_int_eq(s21_is_greater(num, num1), 0);
    ck_assert_int_eq(s21_is_less(num, num1), 0);
    ck_assert_int_eq(s21_is_greater_or_equal(num, num1), 1);
    ck_assert_int_eq(s21_is_less_or_equal(num, num1), 1);
    ck_assert_int_eq(s21_is_not_equal(num, num1), 0);
}
END_TEST

START_TEST(comparison_6) {
    s21_decimal num = {{0, 0, UINT32_MAX - 20, 327680}};
    s21_decimal num1 = {{0, 0, UINT32_MAX, 327680}};
    ck_assert_int_eq(s21_is_equal(num, num1), 0);
    ck_assert_int_eq(s21_is_greater(num, num1), 0);
    ck_assert_int_eq(s21_is_less(num, num1), 1);
    ck_assert_int_eq(s21_is_greater_or_equal(num, num1), 0);
    ck_assert_int_eq(s21_is_less_or_equal(num, num1), 1);
    ck_assert_int_eq(s21_is_not_equal(num, num1), 1);
}
END_TEST

START_TEST(comparison_7) {
    s21_decimal num = {{0, 0, 0, 0}};
    s21_decimal num1 = {{0, 0, 0, 2147483648}};
    ck_assert_int_eq(s21_is_equal(num, num1), 1);
    ck_assert_int_eq(s21_is_greater(num, num1), 0);
    ck_assert_int_eq(s21_is_less(num, num1), 0);
    ck_assert_int_eq(s21_is_greater_or_equal(num, num1), 1);
    ck_assert_int_eq(s21_is_less_or_equal(num, num1), 1);
    ck_assert_int_eq(s21_is_not_equal(num, num1), 0);
}
END_TEST

START_TEST(comparison_8) {
    s21_decimal num = {{0, 0, 0, 0}};
    s21_decimal num1 = {{0, 0, 0, 0}};
    ck_assert_int_eq(s21_is_equal(num, num1), 1);
    ck_assert_int_eq(s21_is_greater(num, num1), 0);
    ck_assert_int_eq(s21_is_less(num, num1), 0);
    ck_assert_int_eq(s21_is_greater_or_equal(num, num1), 1);
    ck_assert_int_eq(s21_is_less_or_equal(num, num1), 1);
    ck_assert_int_eq(s21_is_not_equal(num, num1), 0);
}
END_TEST

START_TEST(comparison_9) {
    s21_decimal num = {{UINT32_MAX, UINT32_MAX, UINT32_MAX, 327680}};
    s21_decimal num1 = {{UINT32_MAX, UINT32_MAX, UINT32_MAX, 2147811328}};
    ck_assert_int_eq(s21_is_equal(num, num1), 0);
    ck_assert_int_eq(s21_is_greater(num, num1), 1);
    ck_assert_int_eq(s21_is_less(num, num1), 0);
    ck_assert_int_eq(s21_is_greater_or_equal(num, num1), 1);
    ck_assert_int_eq(s21_is_less_or_equal(num, num1), 0);
    ck_assert_int_eq(s21_is_not_equal(num, num1), 1);
}
END_TEST

START_TEST(comparison_10) {
    s21_decimal num = {{UINT32_MAX, 0, 0, 2147811328}};
    s21_decimal num1 = {{UINT32_MAX, 0, 0, 2147811328}};
    ck_assert_int_eq(s21_is_equal(num, num1), 1);
    ck_assert_int_eq(s21_is_greater(num, num1), 0);
    ck_assert_int_eq(s21_is_less(num, num1), 0);
    ck_assert_int_eq(s21_is_greater_or_equal(num, num1), 1);
    ck_assert_int_eq(s21_is_less_or_equal(num, num1), 1);
    ck_assert_int_eq(s21_is_not_equal(num, num1), 0);
}
END_TEST

START_TEST(comparison_11) {
    s21_decimal num = {'\0'};
    s21_decimal num1 = {'\0'};
    s21_from_int_to_decimal(-987654, &num);
    s21_from_int_to_decimal(987654, &num1);
    ck_assert_int_eq(s21_is_equal(num, num1), 0);
    ck_assert_int_eq(s21_is_greater(num, num1), 0);
    ck_assert_int_eq(s21_is_less(num, num1), 1);
    ck_assert_int_eq(s21_is_greater_or_equal(num, num1), 0);
    ck_assert_int_eq(s21_is_less_or_equal(num, num1), 1);
    ck_assert_int_eq(s21_is_not_equal(num, num1), 1);
}
END_TEST

START_TEST(comparison_12) {
    s21_decimal num = {'\0'};
    s21_decimal num1 = {'\0'};
    s21_from_float_to_decimal(2.125, &num);
    s21_from_float_to_decimal(2.1250000, &num1);
    ck_assert_int_eq(s21_is_equal(num, num1), 1);
    ck_assert_int_eq(s21_is_greater(num, num1), 0);
    ck_assert_int_eq(s21_is_less(num, num1), 0);
    ck_assert_int_eq(s21_is_greater_or_equal(num, num1), 1);
    ck_assert_int_eq(s21_is_less_or_equal(num, num1), 1);
    ck_assert_int_eq(s21_is_not_equal(num, num1), 0);
}
END_TEST

START_TEST(comparison_13) {
    s21_decimal num = {'\0'};
    s21_decimal num1 = {'\0'};
    s21_from_float_to_decimal(-0.9, &num);
    s21_from_float_to_decimal(0.9, &num1);
    ck_assert_int_eq(s21_is_equal(num, num1), 0);
    ck_assert_int_eq(s21_is_greater(num, num1), 0);
    ck_assert_int_eq(s21_is_less(num, num1), 1);
    ck_assert_int_eq(s21_is_greater_or_equal(num, num1), 0);
    ck_assert_int_eq(s21_is_less_or_equal(num, num1), 1);
    ck_assert_int_eq(s21_is_not_equal(num, num1), 1);
}
END_TEST

START_TEST(comparison_14) {
    s21_decimal num = {'\0'};
    s21_decimal num1 = {'\0'};
    float a = NAN;
    s21_from_float_to_decimal(a, &num);
    s21_from_float_to_decimal(0.9, &num1);
    ck_assert_int_eq(s21_is_equal(num, num1), 0);
    ck_assert_int_eq(s21_is_greater(num, num1), 0);
    ck_assert_int_eq(s21_is_less(num, num1), 0);
    ck_assert_int_eq(s21_is_greater_or_equal(num, num1), 0);
    ck_assert_int_eq(s21_is_less_or_equal(num, num1), 0);
    ck_assert_int_eq(s21_is_not_equal(num, num1), 1);
}
END_TEST

START_TEST(comparison_15) {
    s21_decimal num = {'\0'};
    s21_decimal num1 = {'\0'};
    float a = NAN;
    s21_from_float_to_decimal(0.9, &num);
    s21_from_float_to_decimal(a, &num1);
    ck_assert_int_eq(s21_is_equal(num, num1), 0);
    ck_assert_int_eq(s21_is_greater(num, num1), 0);
    ck_assert_int_eq(s21_is_less(num, num1), 0);
    ck_assert_int_eq(s21_is_greater_or_equal(num, num1), 0);
    ck_assert_int_eq(s21_is_less_or_equal(num, num1), 0);
    ck_assert_int_eq(s21_is_not_equal(num, num1), 1);
}
END_TEST

START_TEST(comparison_16) {
    s21_decimal num = {'\0'};
    s21_decimal num1 = {'\0'};
    float a = INFINITY;
    s21_from_float_to_decimal(0.9, &num);
    s21_from_float_to_decimal(a, &num1);
    ck_assert_int_eq(s21_is_equal(num, num1), 0);
    ck_assert_int_eq(s21_is_greater(num, num1), 0);
    ck_assert_int_eq(s21_is_less(num, num1), 1);
    ck_assert_int_eq(s21_is_greater_or_equal(num, num1), 0);
    ck_assert_int_eq(s21_is_less_or_equal(num, num1), 1);
    ck_assert_int_eq(s21_is_not_equal(num, num1), 1);
}
END_TEST

START_TEST(comparison_17) {
    s21_decimal num = {'\0'};
    s21_decimal num1 = {'\0'};
    float a = INFINITY;
    s21_from_float_to_decimal(a, &num);
    s21_from_float_to_decimal(a, &num1);
    ck_assert_int_eq(s21_is_equal(num, num1), 1);
    ck_assert_int_eq(s21_is_greater(num, num1), 0);
    ck_assert_int_eq(s21_is_less(num, num1), 0);
    ck_assert_int_eq(s21_is_greater_or_equal(num, num1), 1);
    ck_assert_int_eq(s21_is_less_or_equal(num, num1), 1);
    ck_assert_int_eq(s21_is_not_equal(num, num1), 0);
}
END_TEST

START_TEST(comparison_18) {
    s21_decimal num = {'\0'};
    s21_decimal num1 = {'\0'};
    float a = -INFINITY;
    float b = INFINITY;
    s21_from_float_to_decimal(a, &num);
    s21_from_float_to_decimal(b, &num1);
    ck_assert_int_eq(s21_is_equal(num, num1), 0);
    ck_assert_int_eq(s21_is_greater(num, num1), 0);
    ck_assert_int_eq(s21_is_less(num, num1), 1);
    ck_assert_int_eq(s21_is_greater_or_equal(num, num1), 0);
    ck_assert_int_eq(s21_is_less_or_equal(num, num1), 1);
    ck_assert_int_eq(s21_is_not_equal(num, num1), 1);
}
END_TEST

START_TEST(comparison_19) {
    s21_decimal num = {'\0'};
    s21_decimal num1 = {'\0'};
    float a = 0;
    float b = NAN;
    s21_from_float_to_decimal(a, &num);
    s21_from_float_to_decimal(b, &num1);
    ck_assert_int_eq(s21_is_equal(num, num1), 0);
    ck_assert_int_eq(s21_is_greater(num, num1), 0);
    ck_assert_int_eq(s21_is_less(num, num1), 0);
    ck_assert_int_eq(s21_is_greater_or_equal(num, num1), 0);
    ck_assert_int_eq(s21_is_less_or_equal(num, num1), 0);
    ck_assert_int_eq(s21_is_not_equal(num, num1), 1);
}
END_TEST


Suite *suite_s21_comparison(void) {
    Suite *s12;
    TCase *tc12;
    s12 = suite_create("s21_comparison");
    tc12 = tcase_create("case_comparison");

    tcase_add_test(tc12, is_equal_1);
    tcase_add_test(tc12, is_equal_2);
    tcase_add_test(tc12, is_equal_3);
    tcase_add_test(tc12, is_equal_4);
    tcase_add_test(tc12, is_equal_5);
    tcase_add_test(tc12, is_equal_6);
    tcase_add_test(tc12, is_equal_7);
    tcase_add_test(tc12, is_equal_8);
    tcase_add_test(tc12, is_equal_9);
    tcase_add_test(tc12, is_equal_10);
    tcase_add_test(tc12, is_equal_11);
    tcase_add_test(tc12, is_equal_12);
    tcase_add_test(tc12, is_equal_13);
    tcase_add_test(tc12, is_equal_14);
    tcase_add_test(tc12, is_equal_15);

    tcase_add_test(tc12, comparison_1);
    tcase_add_test(tc12, comparison_2);
    tcase_add_test(tc12, comparison_3);
    tcase_add_test(tc12, comparison_4);
    tcase_add_test(tc12, comparison_5);
    tcase_add_test(tc12, comparison_6);
    tcase_add_test(tc12, comparison_7);
    tcase_add_test(tc12, comparison_8);
    tcase_add_test(tc12, comparison_9);
    tcase_add_test(tc12, comparison_10);
    tcase_add_test(tc12, comparison_11);
    tcase_add_test(tc12, comparison_12);
    tcase_add_test(tc12, comparison_13);
    tcase_add_test(tc12, comparison_14);
    tcase_add_test(tc12, comparison_15);
    tcase_add_test(tc12, comparison_16);
    tcase_add_test(tc12, comparison_17);
    tcase_add_test(tc12, comparison_18);
    tcase_add_test(tc12, comparison_19);

    suite_add_tcase(s12, tc12);
    return s12;
}
