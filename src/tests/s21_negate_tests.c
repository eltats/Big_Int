#include "s21_test.h"

START_TEST(s21_negate_pos_float) {
    float A[5] = {3456.9876, 0.789, 1234567, 0.000056, 0};
    s21_decimal value;
    s21_decimal result;
    float res = 0;

    for (int i = 0; i < 5; i++) {
        s21_from_float_to_decimal(A[i], &value);
        s21_negate(value, &result);
        s21_from_decimal_to_float(result, &res);
        ck_assert_float_eq_tol((-1)*(A[i]), res, 1e-6);
    }
}
END_TEST

START_TEST(s21_negate_neg_float) {
    float A[4] = {-3456.9876, -0.789, -1234567, -0.000056};
    s21_decimal value;
    s21_decimal result;
    float res = 0;

    for (int i = 0; i < 4; i++) {
        s21_from_float_to_decimal(A[i], &value);
        s21_negate(value, &result);
        s21_from_decimal_to_float(result, &res);
        ck_assert_float_eq_tol((-1)*(A[i]), res, 1e-6);
    }
}
END_TEST

START_TEST(s21_negate_pos_int) {
    int A[4] = {3456, 1234567, INT_MAX, 0};
    s21_decimal value;
    s21_decimal result;
    int res = 0;

    for (int i = 0; i < 4; i++) {
        s21_from_int_to_decimal(A[i], &value);
        s21_negate(value, &result);
        s21_from_decimal_to_int(result, &res);
        ck_assert_int_eq((-1)*(A[i]), res);
    }
}
END_TEST

START_TEST(s21_negate_neg_int) {
    int A[3] = {-3456, -1234567, -INT_MAX};
    s21_decimal value;
    s21_decimal result;
    int res = 0;

    for (int i = 0; i < 3; i++) {
        s21_from_int_to_decimal(A[i], &value);
        s21_negate(value, &result);
        s21_from_decimal_to_int(result, &res);
        ck_assert_int_eq((-1)*(A[i]), res);
    }
}
END_TEST


Suite *suite_s21_negate(void) {
    Suite *s = suite_create("s21_negate");
    TCase *tc = tcase_create("case_negate");

    tcase_add_test(tc, s21_negate_pos_float);
    tcase_add_test(tc, s21_negate_neg_float);
    tcase_add_test(tc, s21_negate_pos_int);
    tcase_add_test(tc, s21_negate_neg_int);

    suite_add_tcase(s, tc);
    return s;
}
