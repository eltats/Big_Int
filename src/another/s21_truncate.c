#include "s21_another.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
    fill_zero_decimal(result);
    s21_decimal ten = {{10, 0, 0, 0}};
    s21_decimal tmp = {{0, 0, 0, 0}};
    int sign_value = check_bit(127, value);
    int scale = getscale(value);
    if (scale) {
        for (int i = scale; i > 0; i--) {
            div_mantissa(value, ten, &tmp, result);
            value = *result;
        }
    } else {
        *result = value;
    }
    if (sign_value)
        set_bit_dec(result, 127);
    return 0;
}
