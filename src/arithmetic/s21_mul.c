#include "s21_arithmetic.h"

int multiply_mantissa(big_decimal value_1, big_decimal value_2, big_decimal *result);
int multiply_bit(big_decimal *result, int m);

// nan
// if m over 96 should be it infinite?
// can mul be -infinity?
// 192
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int ret = 0;
    int m = 0;
    big_decimal v_1, v_2, res = {{}};
    convert_s21_decimal_to_big_decimal(value_1, &v_1);
    convert_s21_decimal_to_big_decimal(value_2, &v_2);
    if (multiply_mantissa(v_1, v_2, &res) && (!is_nan(value_1) || !is_nan(value_2))) {
        if (get_sign_big_decimal(&v_1) ^ get_sign_big_decimal(&v_2))
            set_sign_big_decimal(&res, 1);
        for (int i = 0; i < 192; i++) {
            m = i;
            for (int j = 0; j < 192 && m < 192; j++, m++) {
                if (get_bit_big_decimal(v_1, i) & get_bit_big_decimal(v_2, j)) {
                    m = multiply_bit(&res, m);
                }
            }
        }
    } else {
        set_inf(result, 0);
        ret = 1;
    }
    if (m > 192) {
        set_inf(result, 0);
        ret = 1;
    }
    if (ret == 0) {
        convert_big_decimal_to_s21_decimal(res, result);
    }
    return ret;
}

int multiply_mantissa(big_decimal value_1, big_decimal value_2, big_decimal *result) {
    int error = 1;
    int memory = 0, k = 0;
    unsigned char mask = 0;
    for (int i = 16; i <= 23; i++) {
        k = get_bit_big_decimal(value_1, 192 + i) + get_bit_big_decimal(value_2, 192 + i) + memory;
        if (k % 2 != 0) {
            set_bit_big_decimal(result, 192 + i, 1);
            mask = set_bit(mask, i - 16);
        } else {
            set_bit_big_decimal(result, 192 + i, 0);
            mask = clean_bit(mask, i - 16);
        }
        memory = k / 2;
    }
    mask = mask >> 1;
    if (mask > 28)
        error = 0;
    return error;
}

int multiply_bit(big_decimal *result, int m) {
    if (get_bit_big_decimal(*result, m)) {
        set_bit_big_decimal(result, m, 0);
        if (m + 1 < 192)
            multiply_bit(result, m + 1);
    } else {
        set_bit_big_decimal(result, m, 1);
    }
    return m;
}
