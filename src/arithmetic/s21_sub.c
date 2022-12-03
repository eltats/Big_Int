#include "s21_arithmetic.h"

void invert_bit(s21_decimal *val, int bit);

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_decimal tmp = value_2;
    invert_bit(&tmp, 127);
    s21_add(value_1, tmp, result);
    return 0;
}

void invert_bit(s21_decimal *val, int bit) {
    val->bits[bit / 32] ^= (1 << (bit % 32));
}

