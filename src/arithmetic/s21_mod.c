#include "../s21_decimal.h"
#include "../additional/s21_big_decimal.h"

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    big_decimal value_1_big_decimal = {0};
    big_decimal value_2_big_decimal = {0};
    s21_decimal zero_s21_decimal = {0};
    big_decimal div_result_big_decimal = {0};
    big_decimal div_remainder_big_decimal = {0};
    s21_decimal div_remainder_s21_decimal = {0};
    int function_result = NORMAL;
    int scale;
    unsigned int shift;
    unsigned int mantissa_size_1;
    unsigned int mantissa_size_2;
    unsigned int mantissa_pow_1;
    unsigned int mantissa_pow_2;
    convert_s21_decimal_to_big_decimal(value_1, &value_1_big_decimal);
    convert_s21_decimal_to_big_decimal(value_2, &value_2_big_decimal);
    mantissa_size_1 = get_scale_big_decimal(value_1_big_decimal);
    mantissa_size_2 = get_scale_big_decimal(value_2_big_decimal);
    mantissa_pow_1 = pow_to_int_big_decimal(value_1_big_decimal);
    mantissa_pow_2 = pow_to_int_big_decimal(value_2_big_decimal);

    if (mantissa_pow_1 > mantissa_pow_2) {
        shift = mantissa_pow_1 - mantissa_pow_2;
        normalization_big_decimal(&value_2_big_decimal, shift);
        scale = mantissa_size_1 << 17 >> 1;
    } else if (mantissa_pow_1 < mantissa_pow_2) {
        shift = mantissa_pow_2 - mantissa_pow_1;
        normalization_big_decimal(&value_1_big_decimal, shift);
        scale = mantissa_size_2 << 17 >> 1;
     } else {
        scale = mantissa_size_1 << 17 >> 1;
     }

    if (value_2.bits[0] == 0 && value_2.bits[1] == 0 && value_2.bits[2] == 0) {
        function_result = ZERO_DIVISION;
    } else if (value_1.bits[0] == 0 && value_1.bits[1] == 0 && value_1.bits[2] == 0) {
        function_result = NORMAL;
        *result =  zero_s21_decimal;
        result->bits[3] = scale;
    } else {
        div_mantissa_big_decimal(value_1_big_decimal, value_2_big_decimal,
                                 &div_result_big_decimal, &div_remainder_big_decimal);
        div_remainder_big_decimal.bits[6] = scale;
        function_result = convert_big_decimal_to_s21_decimal(div_remainder_big_decimal,
                                                             &div_remainder_s21_decimal);
        if (function_result == NORMAL) {
            copy_s21_decimal(div_remainder_s21_decimal, result);
        }
    }
    return function_result;
}
