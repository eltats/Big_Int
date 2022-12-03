#include "s21_test.h"

//  value = 0.0000 result = 0
START_TEST(test_zero) {
    s21_decimal value = {{0, 0, 0, 262144}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{0, 0, 0, 0}};
    s21_floor(value, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
}
END_TEST

//  value = 36,893,488,344,987,598,975 result = 36,893,488,344,987,598,975
START_TEST(whole_positive) {
    s21_decimal value = {{127, 46, 2, 0}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{127, 46, 2, 0}};
    s21_floor(value, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
}
END_TEST

//  value = -36,893,488,344,987,598,975 result = -36,893,488,344,987,598,975
START_TEST(whole_negative) {
    s21_decimal value = {{127, 46, 2, 2147483648}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{127, 46, 2, 2147483648}};
    s21_floor(value, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
}
END_TEST

//  value = 3,689,348,834,498.2598975 result = 3,689,348,834,498
START_TEST(fraction_lt_half_positive) {
    s21_decimal value = {{4289967423, 45, 2, 458752}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{4266894530, 858, 0, 0}};
    s21_floor(value, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
}
END_TEST

//  value = 3,689,348,834,498.7598975 result = 3,689,348,834,498
START_TEST(fraction_gt_half_positive) {
    s21_decimal value = {{127, 46, 2, 458752}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{4266894530, 858, 0, 0}};
    s21_floor(value, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
}
END_TEST

//  value = -3,689,348,834,498.2598975 result = -3,689,348,834,499
START_TEST(fraction_lt_half_negative) {
    s21_decimal value = {{4289967423, 45, 2, 2147942400}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{4266894531, 858, 0, 2147483648}};
    s21_floor(value, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
}
END_TEST

//  value = -3,689,348,834,498.7598975 result = -3,689,348,834,499
START_TEST(fraction_gt_half_negative) {
    s21_decimal value = {{127, 46, 2, 2147942400}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{4266894531, 858, 0, 2147483648}};
    s21_floor(value, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
}
END_TEST


Suite *suite_s21_floor(void) {
    Suite *s = suite_create("s21_floor");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_zero);
    tcase_add_test(tc, whole_positive);
    tcase_add_test(tc, whole_negative);
    tcase_add_test(tc, fraction_lt_half_positive);
    tcase_add_test(tc, fraction_gt_half_positive);
    tcase_add_test(tc, fraction_lt_half_negative);
    tcase_add_test(tc, fraction_gt_half_negative);

    suite_add_tcase(s, tc);
    return s;
}

