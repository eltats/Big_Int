#include "../s21_decimal.h"
#include "../additional/s21_big_decimal.h"

#include <stdio.h>
#include <check.h>


//  value_1 = 4,294,967,295 value_2 = 5 whole = 858,993,459 fraction = 0
START_TEST(finite_fraction_small_positive) {
    s21_decimal value_1 = {{4294967295, 0, 0, 0}};
    s21_decimal value_2 = {{5, 0, 0, 0}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{0, 0, 0, 0}};
    int function_return = s21_mod(value_1, value_2, &result);

    ck_assert_uint_eq(function_return, NORMAL);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
}
END_TEST

//  value_1 = 222,222 value_2 = 333.333 whole = 666 fraction = 222.222
START_TEST(infinite_fraction_small_positive) {
    s21_decimal value_1 = {{222222, 0, 0, 0}};
    s21_decimal value_2 = {{333333, 0, 0, 196608}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{222222, 0, 0, 196608}};
    int function_return = s21_mod(value_1, value_2, &result);

    ck_assert_uint_eq(function_return, NORMAL);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
}
END_TEST


//  value_1 = 35,005,377,191.7777841918593603  value_2 = 1,805,013,907,612,479.62627538
//  whole = 0 fraction = 35,005,377,191.7777841918593603
START_TEST(infinite_fraction_huge_positive) {
    s21_decimal value_1 = {{26495555, 0, 18976453, 1048576}};
    s21_decimal value_2 = {{64978, 0, 9785, 524288}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{26495555, 0, 18976453, 1048576}};
    int function_return = s21_mod(value_1, value_2, &result);

    ck_assert_uint_eq(function_return, NORMAL);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
}
END_TEST

//  value_1 = 35,005,377,191.7777841918593603  value_2 = -18,050,139.0761247962627538
//  whole = -1939 fraction = 6,157,523.1718042383797421
START_TEST(infinite_fraction_huge_dif_sign) {
    s21_decimal value_1 = {{26495555, 0, 18976453, 1048576}};
    s21_decimal value_2 = {{64978, 0, 9785, 2148532224}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{4195470509, 4294967295, 3337, 1048576}};
    int function_return = s21_mod(value_1, value_2, &result);

    ck_assert_uint_eq(function_return, NORMAL);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
}
END_TEST

//  value_1 = -35,005,377,191.7777841918593603  value_2 = -18,050,139.0761247962627538
//  whole = -1939 fraction = 6,157,523.1718042383797421
START_TEST(infinite_fraction_huge_negative) {
    s21_decimal value_1 = {{26495555, 0, 18976453, 2148532224}};
    s21_decimal value_2 = {{64978, 0, 9785, 2148532224}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{4195470509, 4294967295, 3337, 1048576}};
    int function_return = s21_mod(value_1, value_2, &result);

    ck_assert_uint_eq(function_return, NORMAL);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
}
END_TEST


//  value_1 = 35,005,377,191.7777841918593603  value_2 = 0 whole = NAN fraction = NAN
START_TEST(division_by_zero) {
    s21_decimal value_1 = {{26495555, 0, 18976453, 1048576}};
    s21_decimal value_2 = {{0, 0, 0, 0}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{0, 0, 0, 0}};
    int function_return = s21_mod(value_1, value_2, &result);

    ck_assert_uint_eq(function_return, ZERO_DIVISION);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
}
END_TEST

//  value_1 = 0  value_2 = 35,005,377,191.7777841918593603 whole = 0 fraction = 0
START_TEST(divide_zero_by_value) {
    s21_decimal value_1 = {{0, 0, 0, 0}};
    s21_decimal value_2 = {{26495555, 0, 18976453, 1048576}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{0, 0, 0, 1048576}};
    int function_return = s21_mod(value_1, value_2, &result);

    ck_assert_uint_eq(function_return, NORMAL);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
}
END_TEST

//  value_1 = 79,228,162,514,264,337,593,543,950,335  value_2 = 0.001
//  whole = 79,228,162,514,264,337,593,543,950,335,000 fraction = 0.000
START_TEST(overflow_fraction) {
    s21_decimal value_1 = {{4294967295, 4294967295, 4294967295, 0}};
    s21_decimal value_2 = {{1, 0, 0, 196608}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{0, 0, 0, 196608}};
    int function_return = s21_mod(value_1, value_2, &result);

    ck_assert_uint_eq(function_return, NORMAL);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
}
END_TEST

Suite *suite_s21_mod(void) {
    Suite *s = suite_create("s21_mod");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, finite_fraction_small_positive);
    tcase_add_test(tc, infinite_fraction_small_positive);
    tcase_add_test(tc, infinite_fraction_huge_positive);
    tcase_add_test(tc, infinite_fraction_huge_dif_sign);
    tcase_add_test(tc, infinite_fraction_huge_negative);
    tcase_add_test(tc, division_by_zero);
    tcase_add_test(tc, divide_zero_by_value);
    tcase_add_test(tc, overflow_fraction);

    suite_add_tcase(s, tc);
    return s;
}

