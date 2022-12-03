
#include "s21_test.h"


//  value_1 = 4,294,967,295 value_2 = 36 result = 119,304,647.08333333333333333333
START_TEST(same_sign_small_positive_whole_nowerfl) {
    s21_decimal value_1 = {{4294967295, 0, 0, 0}};
    s21_decimal value_2 = {{36, 0, 0, 0}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{3652277589, 3336468037, 646751787, 1310720}};
    int function_return = s21_div(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
} END_TEST

//  value_1 = 4,294,967,295 value_2 = -36 result = -119,304,647.08333333333333333333
START_TEST(diff_sign_first_small_whole_nowerfl) {
    s21_decimal value_1 = {{4294967295, 0, 0, 0}};
    s21_decimal value_2 = {{36, 0, 0, 2147483648}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{3652277589, 3336468037, 646751787, 2148794368}};
    int function_return = s21_div(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
} END_TEST

//  value_1 = -4,294,967,299 value_2 = 36 result = -119,304,647.08333333333333333333
START_TEST(diff_sign_second_small_whole_nowerfl) {
    s21_decimal value_1 = {{4294967295, 0, 0, 2147483648}};
    s21_decimal value_2 = {{36, 0, 0, 0}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{3652277589, 3336468037, 646751787, 2148794368}};
    int function_return = s21_div(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
} END_TEST

//  value_1 = -4,294,967,295 value_2 = -36 result = 119,304,647.08333333333333333333
START_TEST(same_sign_small_negative_whole_nowerfl) {
  s21_decimal value_1 = {{4294967295, 0, 0, 2147483648}};
  s21_decimal value_2 = {{36, 0, 0, 2147483648}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{3652277589, 3336468037, 646751787, 1310720}};
    int function_return = s21_div(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
} END_TEST

//  value_1 = 4,294,967,299 value_2 = 4,294,967,295 result = 1.0000000009313225748323189502
START_TEST(same_sign_medium_positive_whole_nowerfl) {
    s21_decimal value_1 = {{3, 1, 0, 0}};
    s21_decimal value_2 = {{4294967295, 0, 0, 0}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{2312323838, 3211017178, 542101086, 1835008}};
    int function_return = s21_div(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
} END_TEST

//  value_1 = 4,294,967,299 value_2 = -4,294,967,295 result = -1.0000000009313225748323189502
START_TEST(diff_sign_first_medium_whole_nowerfl) {
    s21_decimal value_1 = {{3, 1, 0, 0}};
    s21_decimal value_2 = {{4294967295, 0, 0, 2147483648}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{2312323838, 3211017178, 542101086, 2149318656}};
    int function_return = s21_div(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
} END_TEST

//  value_1 = -4,294,967,299 value_2 = 4,294,967,295 result = -1.0000000009313225748323189502
START_TEST(diff_sign_second_medium_whole_nowerfl) {
    s21_decimal value_1 = {{3, 1, 0, 2147483648}};
    s21_decimal value_2 = {{4294967295, 0, 0, 0}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{2312323838, 3211017178, 542101086, 2149318656}};
    int function_return = s21_div(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
} END_TEST

//  value_1 = -4,294,967,299 value_2 = -4,294,967,295 result = 1.0000000009313225748323189502
START_TEST(same_sign_medium_negative_whole_nowerfl) {
    s21_decimal value_1 = {{3, 1, 0, 2147483648}};
    s21_decimal value_2 = {{4294967295, 0, 0, 2147483648}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{2312323838, 3211017178, 542101086, 1835008}};
    int function_return = s21_div(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
} END_TEST

//  value_1 = 36,893,488,344,987,598,975 value_2 = 110,680,464,442,257,309,695
//  result = 0.3333333351183682691634594602
START_TEST(same_sign_high_positive_whole_nowerfl) {
    s21_decimal value_1 = {{127, 46, 2, 0}};
    s21_decimal value_2 = {{4294967295, 4294967295, 5, 0}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{2407564074, 208678645, 180700363, 1835008}};
    int function_return = s21_div(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
} END_TEST

//  value_1 = -36,893,488,344,987,598,975 value_2 = 110,680,464,442,257,309,695
//  result = -0.3333333351183682691634594602
START_TEST(diff_sign_first_high_whole_nowerfl) {
    s21_decimal value_1 = {{127, 46, 2, 2147483648}};
    s21_decimal value_2 = {{4294967295, 4294967295, 5, 0}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{2407564074, 208678645, 180700363, 2149318656}};
    int function_return = s21_div(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
} END_TEST

//  value_1 = 36,893,488,344,987,598,975 value_2 = -110,680,464,442,257,309,695
//  result = -0.3333333351183682691634594602
START_TEST(diff_sign_second_high_whole_nowerfl) {
    s21_decimal value_1 = {{127, 46, 2, 0}};
    s21_decimal value_2 = {{4294967295, 4294967295, 5, 2147483648}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{2407564074, 208678645, 180700363, 2149318656}};
    int function_return = s21_div(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
} END_TEST

//  value_1 = -36,893,488,344,987,598,975 value_2 = -110,680,464,442,257,309,695
//  result = -0.3333333351183682691634594602
START_TEST(same_sign_high_negative_whole_nowerfl) {
    s21_decimal value_1 = {{127, 46, 2, 2147483648}};
    s21_decimal value_2 = {{4294967295, 4294967295, 5, 2147483648}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{2407564074, 208678645, 180700363, 1835008}};
    int function_return = s21_div(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
} END_TEST

//  positive_overflow
//  value_1 = 79,228,162,514,264,337,593,543,950,335 value_2 = 0.0000000000000000000000000001
START_TEST(positive_overflow) {
    s21_decimal value_1 = {{4294967295, 4294967295, 4294967295, 0}};
    s21_decimal value_2 = {{1, 0, 0, 1835008}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{0, 0, 0, 0}};
    int function_return = s21_div(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, POS_OVERFLOW);
} END_TEST

//  negative_overflow
//  value_1 = -79,228,162,514,264,337,593,543,950,335 value_2 = 0.0000000000000000000000000001
START_TEST(negative_overflow) {
    s21_decimal value_1 = {{4294967295, 4294967295, 4294967295, 2147483648}};
    s21_decimal value_2 = {{1, 0, 0, 1835008}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{0, 0, 0, 0}};
    int function_return = s21_div(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NEG_OVERFLOW);
} END_TEST

//  value_1 = 3,689,348,834,498.7598975 value_2 = 110,680,464,442.257309695
//  result = 33.333333511836826916345946021
START_TEST(same_sign_positive_mantissa_nowerfl) {
    s21_decimal value_1 = {{127, 46, 2, 458752}};
    s21_decimal value_2 = {{4294967295, 4294967295, 5, 589824}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{2600804261, 2086786455, 1807003630, 1769472}};
    int function_return = s21_div(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
} END_TEST

//  value_1 = -3,689,348,834,498.7598975 value_2 = 110,680,464,442.257309695
//  result = -33.333333511836826916345946021
START_TEST(diff_sign_first_mantissa_nowerfl) {
    s21_decimal value_1 = {{127, 46, 2, 2147942400}};
    s21_decimal value_2 = {{4294967295, 4294967295, 5, 589824}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{2600804261, 2086786455, 1807003630, 2149253120}};
    int function_return = s21_div(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
} END_TEST

//  value_1 = 3,689,348,834,498.7598975 value_2 = -110,680,464,442.257309695
//  result = -33.333333511836826916345946021
START_TEST(diff_sign_second_mantissa_nowerfl) {
    s21_decimal value_1 = {{127, 46, 2, 458752}};
    s21_decimal value_2 = {{4294967295, 4294967295, 5, 2148073472}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{2600804261, 2086786455, 1807003630, 2149253120}};
    int function_return = s21_div(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
} END_TEST

//  value_1 = -3,689,348,834,498.7598975 value_2 = -110,680,464,442.257309695
//  result = 33.333333511836826916345946021
START_TEST(same_sign_negative_mantissa_nowerfl) {
    s21_decimal value_1 = {{127, 46, 2, 2147942400}};
    s21_decimal value_2 = {{4294967295, 4294967295, 5, 2148073472}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{2600804261, 2086786455, 1807003630, 1769472}};
    int function_return = s21_div(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
} END_TEST

//  value_1 = 11.0680464442257309695 value_2 = 110,680,464,442,257,309.695 result = 0.0000000000000001
START_TEST(same_sign_positive_huge_mantissa_nowerfl) {
    s21_decimal value_1 = {{4294967295, 4294967295, 5, 1245184}};
    s21_decimal value_2 = {{4294967295, 4294967295, 5, 196608}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{1, 0, 0, 1048576}};
    int function_return = s21_div(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
} END_TEST

//  value_1 = 11.0680464442257309695 value_2 = 11.0680464442257309695 result = 1
START_TEST(division_by_same_value) {
    s21_decimal value_1 = {{4294967295, 4294967295, 5, 1245184}};
    s21_decimal value_2 = {{4294967295, 4294967295, 5, 1245184}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{1, 0, 0, 0}};
    int function_return = s21_div(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
} END_TEST

//  value_1 = 11.0680464442257309695 value_2 = 1 result = 11.0680464442257309695
START_TEST(division_by_one_value) {
    s21_decimal value_1 = {{4294967295, 4294967295, 5, 1245184}};
    s21_decimal value_2 = {{1, 0, 0, 0}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{4294967295, 4294967295, 5, 1245184}};
    int function_return = s21_div(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
} END_TEST

//  value_1 = 11.0680464442257309695 value_2 = 0 result = NAN
START_TEST(division_by_zero_value) {
    s21_decimal value_1 = {{4294967295, 4294967295, 5, 2148728832}};
    s21_decimal value_2 = {{0, 0, 0, 0}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{0, 0, 0, 0}};
    int function_return = s21_div(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, ZERO_DIVISION);
} END_TEST

//  value_1 = 0 value_2 = 11.0680464442257309695 result = 0
START_TEST(zero_divided_by_value) {
    s21_decimal value_1 = {{0, 0, 0, 0}};
    s21_decimal value_2 = {{4294967295, 4294967295, 4294967295, 0}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{0, 0, 0, 0}};
    int function_return = s21_div(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
}




Suite *suite_s21_div(void) {
    Suite *s = suite_create("s21_div");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, same_sign_small_positive_whole_nowerfl);
    tcase_add_test(tc, diff_sign_first_small_whole_nowerfl);
    tcase_add_test(tc, diff_sign_second_small_whole_nowerfl);
    tcase_add_test(tc, same_sign_small_negative_whole_nowerfl);
    tcase_add_test(tc, same_sign_medium_positive_whole_nowerfl);
    tcase_add_test(tc, diff_sign_first_medium_whole_nowerfl);
    tcase_add_test(tc, diff_sign_second_medium_whole_nowerfl);
    tcase_add_test(tc, same_sign_medium_negative_whole_nowerfl);
    tcase_add_test(tc, same_sign_high_positive_whole_nowerfl);
    tcase_add_test(tc, diff_sign_first_high_whole_nowerfl);
    tcase_add_test(tc, diff_sign_second_high_whole_nowerfl);
    tcase_add_test(tc, same_sign_high_negative_whole_nowerfl);
    tcase_add_test(tc, positive_overflow);
    tcase_add_test(tc, negative_overflow);
    tcase_add_test(tc, same_sign_positive_mantissa_nowerfl);
    tcase_add_test(tc, diff_sign_first_mantissa_nowerfl);
    tcase_add_test(tc, diff_sign_second_mantissa_nowerfl);
    tcase_add_test(tc, same_sign_negative_mantissa_nowerfl);
    tcase_add_test(tc, same_sign_positive_huge_mantissa_nowerfl);
    tcase_add_test(tc, division_by_same_value);
    tcase_add_test(tc, division_by_one_value);
    tcase_add_test(tc, division_by_zero_value);
    tcase_add_test(tc, zero_divided_by_value);

    suite_add_tcase(s, tc);
    return s;
}


