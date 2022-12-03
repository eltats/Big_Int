#include "s21_test.h"
#include <assert.h>
#define IS_SET(X, POS) ((X >> POS) & 1U)
#define ADD_BIT(X, POS) ((X) |= (1U << (POS)))

float get_random_float(float min, float max) {
    assert(max > min);
    float random = ((float)rand()) / (float)RAND_MAX;
    float range = max - min;
    return random * range + min;
}

long long get_random_ll(void) {
    long long int val = 0;
    unsigned int seed = time(NULL);
    for (uint64_t i = 0; i < 64; i++)
        if (rand_r(&seed) % 2)
            val |= (1U << i);

    return val;
}

s21_decimal bigint_to_decimal(__int128_t src) {
    s21_decimal res = {0};

    if (src < 0) {
        set_sign(&res, 1);
        src = -src;
    }
    for (int i = 0, k = 0; i < 3; i++)
        for (int j = 0; j < 32; j++, k++)
            if (IS_SET(src, k))
                ADD_BIT(res.bits[i], j);

    return res;
}

s21_decimal ll_to_decimal(long long val) {
    s21_decimal res = {0};
    if (val < 0) {
        set_sign(&res, 1);
        val = -val;
    }

    for (uint64_t i = 0; val; i++, val /= 2) {
        if (val % 2)
            res.bits[i / 32] |= (1U << i);
    }

    return res;
}

START_TEST(simple_multiply_1) {
    s21_decimal value_1;
    s21_decimal value_2;
    s21_decimal result = {{}};
    int out;

    ck_assert_int_eq(s21_from_int_to_decimal(2, &value_1), 0);
    ck_assert_int_eq(s21_from_int_to_decimal(2, &value_2), 0);
    ck_assert_int_eq(s21_mul(value_1, value_2, &result), 0);
    ck_assert_int_eq(s21_from_decimal_to_int(result, &out), 0);
    ck_assert_int_eq(result.bits[0], 4);
} END_TEST

START_TEST(simple_multiply_2) {
    s21_decimal value_1;
    s21_decimal value_2;
    s21_decimal result = {{}};
    int out;

    ck_assert_int_eq(s21_from_int_to_decimal(5, &value_1), 0);
    ck_assert_int_eq(s21_from_int_to_decimal(10, &value_2), 0);
    ck_assert_int_eq(s21_mul(value_1, value_2, &result), 0);
    ck_assert_int_eq(s21_from_decimal_to_int(result, &out), 0);
    ck_assert_int_eq(out, 50);
} END_TEST


START_TEST(simple_multiply_3) {
    s21_decimal value_1;
    s21_decimal value_2;
    s21_decimal result = {{}};
    int out;

    ck_assert_int_eq(s21_from_int_to_decimal(-5, &value_1), 0);
    ck_assert_int_eq(s21_from_int_to_decimal(10, &value_2), 0);
    ck_assert_int_eq(s21_mul(value_1, value_2, &result), 0);
    ck_assert_int_eq(s21_from_decimal_to_int(result, &out), 0);
    ck_assert_int_eq(out, -50);
} END_TEST

START_TEST(simple_multiply_4) {
    s21_decimal value_1 = {{}};
    s21_decimal value_2 = {{}};
    s21_decimal result = {{}};
    int out = 0;

    ck_assert_int_eq(s21_from_int_to_decimal(14315, &value_1), 0);
    ck_assert_int_eq(s21_from_int_to_decimal(10, &value_2), 0);
    ck_assert_int_eq(s21_mul(value_1, value_2, &result), 0);
    ck_assert_int_eq(s21_from_decimal_to_int(result, &out), 0);
    ck_assert_int_eq(out, 143150);
} END_TEST

START_TEST(simple_multiply_5) {
    s21_decimal value_1 = {{}};
    s21_decimal value_2 = {{}};
    s21_decimal result = {{}};
    int out = 0;
    ck_assert_int_eq(s21_from_int_to_decimal(14315, &value_1), 0);
    ck_assert_int_eq(s21_from_int_to_decimal(112435, &value_2), 0);
    ck_assert_int_eq(s21_mul(value_1, value_2, &result), 0);
    ck_assert_int_eq(s21_from_decimal_to_int(result, &out), 0);
    ck_assert_int_eq(out, 1609507025);
} END_TEST

START_TEST(medium_multiply_1) {
    s21_decimal value_1 = {{}};
    s21_decimal value_2 = {{}};
    s21_decimal result = {{}};
    int out = 0;
    ck_assert_int_eq(s21_from_int_to_decimal(14315, &value_1), 0);
    ck_assert_int_eq(s21_from_int_to_decimal(-112435, &value_2), 0);
    ck_assert_int_eq(s21_mul(value_1, value_2, &result), 0);
    ck_assert_int_eq(s21_from_decimal_to_int(result, &out), 0);
    ck_assert_int_eq(out, -1609507025);
} END_TEST

START_TEST(simple_float_multiply_1) {
    s21_decimal value_1 = {{125, 0, 0, 0b0000000000000100000000000000000}};
    s21_decimal value_2 = {{125, 0, 0, 0b0000000000000100000000000000000}};
    s21_decimal result = {{}};
    float out = 0, res = 1.5625;
    ck_assert_int_eq(s21_mul(value_1, value_2, &result), 0);
    ck_assert_int_eq(s21_from_decimal_to_float(result, &out), 0);
    ck_assert_float_eq_tol(out, res, 1e-4);
} END_TEST

START_TEST(hard_big_int_1) {
    long long long_a = get_random_ll();
    long long long_b = get_random_ll();
    unsigned int seed = time(NULL);
    if (rand_r(&seed) % 2)
        long_a *= -1;

    if (rand_r(&seed) % 2)
        long_b *= -1;

    __int128_t a = long_a;
    __int128_t b = long_b;
    __int128_t mul = a * b;

    s21_decimal res128 = bigint_to_decimal(mul);

    s21_decimal dec_a = ll_to_decimal(long_a);
    s21_decimal dec_b = ll_to_decimal(long_b);

    s21_decimal dec_mul = {0};

    s21_mul(dec_a, dec_b, &dec_mul);
    ck_assert_int_eq(s21_is_equal(res128, dec_mul), 1);
}
START_TEST(random_float) {
    float float_a = get_random_float(-85818.51851, 85818.51851);
    float float_b = get_random_float(-85818.51851, 85818.51851);
    unsigned int seed = time(NULL);

    if (rand_r(&seed) % 2)
        float_a *= -1;

    if (rand_r(&seed) % 2)
        float_b *= -1;

    float float_res = float_a * float_b;

    s21_decimal expected = {0};
    s21_from_float_to_decimal(float_res, &expected);

    s21_decimal dec_a = {0};
    s21_from_float_to_decimal(float_a, &dec_a);
    s21_decimal dec_b = {0};
    s21_from_float_to_decimal(float_b, &dec_b);

    s21_decimal result = {0};

    /* Always INF */
    int code = s21_mul(dec_a, dec_b, &result);

    float expected_float = 0;
    s21_from_decimal_to_float(result, &expected_float);

    ck_assert_int_eq(code, 0);
    ck_assert_float_eq_tol(expected_float, float_res, 1e-06);
}


Suite *suite_s21_mul(void) {
    Suite *s = suite_create("s21_mul");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, simple_multiply_1);
    tcase_add_test(tc, simple_multiply_2);
    tcase_add_test(tc, simple_multiply_3);
    tcase_add_test(tc, simple_multiply_4);
    tcase_add_test(tc, simple_multiply_5);
    tcase_add_test(tc, medium_multiply_1);
    tcase_add_test(tc, hard_big_int_1);
    tcase_add_test(tc, simple_float_multiply_1);
    tcase_add_test(tc, random_float);

    suite_add_tcase(s, tc);
    return s;
}
