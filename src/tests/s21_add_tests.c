#include "../s21_decimal.h"
#include "../additional/s21_helpers.h"
#include <stdio.h>
#include <check.h>


/* TABLE OF INT REPRESENTATION OF bits[3]
*  EXPONENT | SIGN +     | SIGN -                       SIGN + BINARY                 |      SIGN - BINARY
*  0        |    0       |   2147483648             00000000000000000000000000000000  |  10000000000000000000000000000000
*  1        |   65536    |   2147549184             00000000000000010000000000000000  |  10000000000000010000000000000000
*  2        |   131072   |   2147614720             00000000000000100000000000000000  |  10000000000000100000000000000000
*  3        |   196608   |   2147680256             00000000000000110000000000000000  |  10000000000000110000000000000000
*  4        |   262144   |   2147745792             00000000000001000000000000000000  |  10000000000001000000000000000000
*  5        |   327680   |   2147811328             00000000000001010000000000000000  |  10000000000001010000000000000000
*  6        |   393216   |   2147876864             00000000000001100000000000000000  |  10000000000001100000000000000000
*  7        |   458752   |   2147942400             00000000000001110000000000000000  |  10000000000001110000000000000000
*  8        |   524288   |   2148007936             00000000000010000000000000000000  |  10000000000010000000000000000000
*  9        |   589824   |   2148073472             00000000000010010000000000000000  |  10000000000010010000000000000000
*  10       |   655360   |   2148139008             00000000000010100000000000000000  |  10000000000010100000000000000000
*  11       |   720896   |   2148204544             00000000000010110000000000000000  |  10000000000010110000000000000000
*  12       |   786432   |   2148270080             00000000000011000000000000000000  |  10000000000011000000000000000000
*  13       |   851968   |   2148335616             00000000000011010000000000000000  |  10000000000011010000000000000000
*  14       |   917504   |   2148401152             00000000000011100000000000000000  |  10000000000011100000000000000000
*  15       |   983040   |   2148466688             00000000000011110000000000000000  |  10000000000011110000000000000000
*  16       |  1048576   |   2148532224             00000000000100000000000000000000  |  10000000000100000000000000000000
*  17       |  1114112   |   2148597760             00000000000100010000000000000000  |  10000000000100010000000000000000
*  18       |  1179648   |   2148663296             00000000000100100000000000000000  |  10000000000100100000000000000000
*  19       |  1245184   |   2148728832             00000000000100110000000000000000  |  10000000000100110000000000000000
*  20       |  1310720   |   2148794368             00000000000101000000000000000000  |  10000000000101000000000000000000
*  21       |   1376256  |   2148859904             00000000000101010000000000000000  |  10000000000101010000000000000000
*  22       |   1441792  |   2148925440             00000000000101100000000000000000  |  10000000000101100000000000000000
*  23       |   1507328  |   2148990976             00000000000101110000000000000000  |  10000000000101110000000000000000
*  24       |   1572864  |   2149056512             00000000000110000000000000000000  |  10000000000110000000000000000000
*  25       |   1638400  |   2149122048             00000000000110010000000000000000  |  10000000000110010000000000000000
*  26       |   1703936  |   2149187584             00000000000110100000000000000000  |  10000000000110100000000000000000
*  27       |   1769472  |   2149253120             00000000000110110000000000000000  |  10000000000110110000000000000000
*  28       |   1835008  |   2149318656             00000000000111000000000000000000  |  10000000000111000000000000000000
*/


//  value_1 = 54 value_2 = 36 result = 90
START_TEST(same_sign_small_positive_whole_nowerfl) {
    s21_decimal value_1 = {{54, 0, 0, 0}};
    s21_decimal value_2 = {{36, 0, 0, 0}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{90, 0, 0, 0}};
    int function_return = s21_add(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
} END_TEST

//  value_1 = 54 value_2 = -36 result = 18
START_TEST(diff_sign_first_small_whole_nowerfl) {
    s21_decimal value_1 = {{54, 0, 0, 0}};
    s21_decimal value_2 = {{36, 0, 0, 2147483648}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{18, 0, 0, 0}};
    int function_return = s21_add(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
} END_TEST

//  value_1 = -54 value_2 = 36 result = -18
START_TEST(diff_sign_second_small_whole_nowerfl) {
    s21_decimal value_1 = {{54, 0, 0, 2147483648}};
    s21_decimal value_2 = {{36, 0, 0, 0}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{18, 0, 0, 2147483648}};
    int function_return = s21_add(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
} END_TEST

//  value_1 = -54 value_2 = -36 result = -90
START_TEST(same_sign_small_negative_whole_nowerfl) {
    s21_decimal value_1 = {{54, 0, 0, 2147483648}};
    s21_decimal value_2 = {{36, 0, 0, 2147483648}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{90, 0, 0, 2147483648}};
    int function_return = s21_add(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
} END_TEST

//  value_1 = 4,294,967,299 value_2 = 4,294,967,295 result = 8,589,934,594
START_TEST(same_sign_medium_positive_whole_nowerfl) {
    s21_decimal value_1 = {{3, 1, 0, 0}};
    s21_decimal value_2 = {{4294967295, 0, 0, 0}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{2, 2, 0, 0}};
    int function_return = s21_add(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
} END_TEST

//  value_1 = 4,294,967,299 value_2 = -4,294,967,295 result = 4
START_TEST(diff_sign_first_medium_whole_nowerfl) {
    s21_decimal value_1 = {{3, 1, 0, 0}};
    s21_decimal value_2 = {{4294967295, 0, 0, 2147483648}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{4, 0, 0, 0}};
    int function_return = s21_add(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
} END_TEST

//  value_1 = -4,294,967,299 value_2 = 4,294,967,295 result = -4
START_TEST(diff_sign_second_medium_whole_nowerfl) {
    s21_decimal value_1 = {{3, 1, 0, 2147483648}};
    s21_decimal value_2 = {{4294967295, 0, 0, 0}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{4, 0, 0, 2147483648}};
    int function_return = s21_add(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
} END_TEST

//  value_1 = -4,294,967,299 value_2 = -4,294,967,295 result = -8,589,934,594
START_TEST(same_sign_medium_negative_whole_nowerfl) {
    s21_decimal value_1 = {{3, 1, 0, 2147483648}};
    s21_decimal value_2 = {{4294967295, 0, 0, 2147483648}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{2, 2, 0, 2147483648}};
    int function_return = s21_add(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
} END_TEST

//  value_1 = 36,893,488,344,987,598,975 value_2 = 110,680,464,442,257,309,695
//  result = 147,573,952,787,244,908,670
START_TEST(same_sign_high_positive_whole_nowerfl) {
    s21_decimal value_1 = {{127, 46, 2, 0}};
    s21_decimal value_2 = {{4294967295, 4294967295, 5, 0}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{126, 46, 8, 0}};
    int function_return = s21_add(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
} END_TEST

//  value_1 = -36,893,488,344,987,598,975 value_2 = 110,680,464,442,257,309,695
//  result = 73,786,976,097,269,710,720
START_TEST(diff_sign_first_high_whole_nowerfl) {
    s21_decimal value_1 = {{127, 46, 2, 2147483648}};
    s21_decimal value_2 = {{4294967295, 4294967295, 5, 0}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{4294967168, 4294967249, 3, 0}};
    int function_return = s21_add(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
} END_TEST

//  value_1 = 36,893,488,344,987,598,975 value_2 = -110,680,464,442,257,309,695
//  result = -73,786,976,097,269,710,720
START_TEST(diff_sign_second_high_whole_nowerfl) {
    s21_decimal value_1 = {{127, 46, 2, 0}};
    s21_decimal value_2 = {{4294967295, 4294967295, 5, 2147483648}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{4294967168, 4294967249, 3, 2147483648}};
    int function_return = s21_add(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
} END_TEST

//  value_1 = -36,893,488,344,987,598,975 value_2 = -110,680,464,442,257,309,695
//  result = -147,573,952,787,244,908,670
START_TEST(same_sign_high_negative_whole_nowerfl) {
    s21_decimal value_1 = {{127, 46, 2, 2147483648}};
    s21_decimal value_2 = {{4294967295, 4294967295, 5, 2147483648}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{126, 46, 8, 2147483648}};
    int function_return = s21_add(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
} END_TEST

//  positive_overflow
START_TEST(positive_overflow) {
    s21_decimal value_1 = {{4294967295, 4294967295, 4294967295, 0}};
    s21_decimal value_2 = {{1, 0, 0, 0}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{0, 0, 0, 0}};
    int function_return = s21_add(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, POS_OVERFLOW);
} END_TEST

//  negative_overflow
START_TEST(negative_overflow) {
    s21_decimal value_1 = {{4294967295, 4294967295, 4294967295, 2147483648}};
    s21_decimal value_2 = {{1, 0, 0, 2147483648}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{0, 0, 0, 0}};
    int function_return = s21_add(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NEG_OVERFLOW);
} END_TEST

//  value_1 = 3,689,348,834,498.7598975 value_2 = 110,680,464,442.257309695
//  result = 3,800,029,298,941.017207195
START_TEST(same_sign_positive_mantissa_nowerfl) {
    s21_decimal value_1 = {{127, 46, 2, 458752}};
    s21_decimal value_2 = {{4294967295, 4294967295, 5, 589824}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{12699, 4600, 206, 589824}};
    int function_return = s21_add(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
} END_TEST

//  value_1 = -3,689,348,834,498.7598975 value_2 = 110,680,464,442.257309695
//  result = -3,578,668,370,056.502587805
START_TEST(diff_sign_first_mantissa_nowerfl) {
    s21_decimal value_1 = {{127, 46, 2, 2147942400}};
    s21_decimal value_2 = {{4294967295, 4294967295, 5, 589824}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{12701, 4600, 194, 2148073472}};
    int function_return = s21_add(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
} END_TEST

//  value_1 = 3,689,348,834,498.7598975 value_2 = -110,680,464,442.257309695
//  result = 3,578,668,370,056.502587805
START_TEST(diff_sign_second_mantissa_nowerfl) {
    s21_decimal value_1 = {{127, 46, 2, 458752}};
    s21_decimal value_2 = {{4294967295, 4294967295, 5, 2148073472}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{12701, 4600, 194, 589824}};
    int function_return = s21_add(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
} END_TEST

//  value_1 = -3,689,348,834,498.7598975 value_2 = -110,680,464,442.257309695
//  result = -3,800,029,298,941.017207195
START_TEST(same_sign_negative_mantissa_nowerfl) {
    s21_decimal value_1 = {{127, 46, 2, 2147942400}};
    s21_decimal value_2 = {{4294967295, 4294967295, 5, 2148073472}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{12699, 4600, 206, 2148073472}};
    int function_return = s21_add(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
} END_TEST

//  value_1 = 11.0680464442257309695 value_2 = 110,680,464,442,257,309.695
//  result = 110,680,464,442,257,320.7630464442257309695
//  rounded result = 110,680,464,442,257,320.76304644422
START_TEST(same_sign_positive_huge_mantissa_nowerfl) {
    s21_decimal value_1 = {{4294967295, 4294967295, 5, 1245184}};
    s21_decimal value_2 = {{4294967295, 4294967295, 5, 196608}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{2898049350, 257, 600000000, 720896}};
    int function_return = s21_add(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
} END_TEST

//  value_1 = -11.0680464442257309695 value_2 = 110,680,464,442,257,309.695
//  result = 110,680,464,442,257,298.6269535557742690305
//  rounded result = 110,680,464,442,257,298.62695355577
START_TEST(diff_sign_first_huge_mantissa_nowerfl) {
    s21_decimal value_1 = {{4294967295, 4294967295, 5, 2148728832}};
    s21_decimal value_2 = {{4294967295, 4294967295, 5, 196608}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{1196917945, 4294967038, 599999999, 720896}};
    int function_return = s21_add(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
} END_TEST

//  value_1 = 11.0680464442257309695 value_2 = -110,680,464,442,257,309.695
//  result = -110,680,464,442,257,298.6269535557742690305
//  rounded result = -110,680,464,442,257,298.62695355577
START_TEST(diff_sign_second_huge_mantissa_nowerfl) {
    s21_decimal value_1 = {{4294967295, 4294967295, 5, 1245184}};
    s21_decimal value_2 = {{4294967295, 4294967295, 5, 2147680256}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{1196917945, 4294967038, 599999999, 2148204544}};
    int function_return = s21_add(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
} END_TEST

//  value_1 = -11.0680464442257309695 value_2 = -110,680,464,442,257,309.695
//  result = -110,680,464,442,257,320.7630464442257309695
//  rounded result = -110,680,464,442,257,320.76304644422
START_TEST(same_sign_negative_huge_mantissa_nowerfl) {
    s21_decimal value_1 = {{4294967295, 4294967295, 5, 2148728832}};
    s21_decimal value_2 = {{4294967295, 4294967295, 5, 2147680256}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{2898049350, 257, 600000000, 2148204544}};
    int function_return = s21_add(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
} END_TEST

//  value_1 = 79,228,162,514,264,337,593,543,950,335 value_2 = -0.786
//  result = 79,228,162,514,264,337,593,543,950,334.216
//  rounded result = 79,228,162,514,264,337,593,543,950,334
START_TEST(banker_round_max_value) {
    s21_decimal value_1 = {{4294967295, 4294967295, 4294967295, 0}};
    s21_decimal value_2 = {{784, 0, 0, 2147680256}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{4294967294, 4294967295, 4294967295, 0}};
    int function_return = s21_add(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, NORMAL);
}

//  value_1 = 79,228,162,514,264,337,593,543,950,334 value_2 = 2.46
//  result = 79,228,162,514,264,337,593,543,950,336.46
//  rounded result = POS_OVERFLOW
START_TEST(banker_round_max_value_to_pos_inf) {
    s21_decimal value_1 = {{4294967294, 4294967295, 4294967295, 0}};
    s21_decimal value_2 = {{246, 0, 0, 131072}};
    s21_decimal result = {{0}};
    s21_decimal expected_result = {{0, 0, 0, 0}};
    int function_return = s21_add(value_1, value_2, &result);
    ck_assert_uint_eq(result.bits[0], expected_result.bits[0]);
    ck_assert_uint_eq(result.bits[1], expected_result.bits[1]);
    ck_assert_uint_eq(result.bits[2], expected_result.bits[2]);
    ck_assert_uint_eq(result.bits[3], expected_result.bits[3]);
    ck_assert_uint_eq(function_return, POS_OVERFLOW);
}
END_TEST


Suite *suite_s21_add(void) {
    Suite *s = suite_create("s21_add");
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
    tcase_add_test(tc, diff_sign_first_huge_mantissa_nowerfl);
    tcase_add_test(tc, diff_sign_second_huge_mantissa_nowerfl);
    tcase_add_test(tc, same_sign_negative_huge_mantissa_nowerfl);
    tcase_add_test(tc, banker_round_max_value);
    tcase_add_test(tc, banker_round_max_value_to_pos_inf);

    suite_add_tcase(s, tc);
    return s;
}


