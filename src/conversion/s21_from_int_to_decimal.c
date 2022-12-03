#include "s21_conversion.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
    if (dst == NULL) return 1;
    memset(dst, 0, sizeof(s21_decimal));
    int sign = src < 0;
    dst->bits[0] = abs(src);
    set_sign(dst, sign);
    return 0;
}

