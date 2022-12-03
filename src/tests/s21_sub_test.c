#include "s21_test.h"

START_TEST(sub_test_1) {
    int num1 = -10;
    int num2 = -10;
    int dif_int = 0;
    s21_decimal a = {0};
    s21_decimal b = {0};
    s21_from_int_to_decimal(num1, &a);
    s21_from_int_to_decimal(num2, &b);
    s21_decimal res_dec = {0};
    int res_int = 0;
    s21_sub(a, b, &res_dec);
    s21_from_decimal_to_int(res_dec, &res_int);
    ck_assert_int_eq(res_int, dif_int);
}
END_TEST

Suite *suite_s21_sub(void) {
    Suite *s = suite_create("s21_sub");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, sub_test_1);

    suite_add_tcase(s, tc);
    return s;
}
