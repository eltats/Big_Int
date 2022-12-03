#include "s21_test.h"

START_TEST(int_conversion_1) {
    int a = INT_MAX;
    int b = 0;
    s21_decimal num = {'\0'};
    s21_from_int_to_decimal(a, &num);
    s21_from_decimal_to_int(num, &b);
    ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(int_conversion_2) {
    int a = INT_MIN;
    int b = 0;
    s21_decimal num = {'\0'};
    s21_from_int_to_decimal(a, &num);
    s21_from_decimal_to_int(num, &b);
    ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(int_conversion_3) {
    int a = UINT32_MAX;
    int b = 0;
    s21_decimal num = {'\0'};
    s21_from_int_to_decimal(a, &num);
    s21_from_decimal_to_int(num, &b);
    ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(int_conversion_4) {
    s21_decimal num = {'\0'};
    s21_from_int_to_decimal(5678, &num);
    int a = UINT32_MAX;
    int b = 0;
    s21_from_int_to_decimal(a, &num);
    s21_from_decimal_to_int(num, &b);
    ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(int_conversion_5) {
    int a = -0;
    int b = 0;
    s21_decimal num = {'\0'};
    s21_from_int_to_decimal(a, &num);
    s21_from_decimal_to_int(num, &b);
    ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(int_conversion_6) {
    int a = -1234567;
    int b = 0;
    s21_decimal num = {'\0'};
    s21_from_int_to_decimal(a, &num);
    s21_from_decimal_to_int(num, &b);
    ck_assert_int_eq(a, b);
}
END_TEST

Suite *suite_s21_int_conversion(void) {
    Suite *s12;
    TCase *tc12;
    s12 = suite_create("s21_int_conversion");
    tc12 = tcase_create("case_int_conversion");

    tcase_add_test(tc12, int_conversion_1);
    tcase_add_test(tc12, int_conversion_2);
    tcase_add_test(tc12, int_conversion_3);
    tcase_add_test(tc12, int_conversion_4);
    tcase_add_test(tc12, int_conversion_5);
    tcase_add_test(tc12, int_conversion_6);

    suite_add_tcase(s12, tc12);
    return s12;
}
