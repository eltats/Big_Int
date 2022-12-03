#include "s21_conversion.h"

int get_float_exp(float value) {
    unsigned  mask = 0xFF << M_LEN;
    int bin_float = *((int *)&value);
    return ((bin_float & mask) >> M_LEN) - 127;
}

/* getting mantissa with (in)visible leading bit */
int get_float_mantissa(float value) {
    int i_float = *((int *)&value);
    int mantissa = i_float & 0x007fffff;
    mantissa |= (1 << M_LEN);
    return mantissa;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    if (dst == NULL) return 1;
    int status = 0;
    memset(dst, 0, sizeof(s21_decimal));
    if (isnan_f(src)) {
        set_nan(dst);
        status = 1;
    }
    if (isinf_f(src) && src < 0) {
        set_inf(dst, 1);
        status = 1;
    }
    if (isinf_f(src) && src > 0) {
        set_inf(dst, 0);
        status = 1;
    }
    int exp = get_float_exp(src);
    status = (exp >= 96) | (fabs(src) <= 1e-28);
    if (status == 0) {
        int sign = src < 0.f;
        if (sign) src = -src;
        if (exp >= M_LEN) {
            dst->bits[0] = get_float_mantissa(src);
            shift_left(dst, exp - M_LEN);
        } else if (exp < M_LEN) {
            long double dsrc = src * 1e7;
            dsrc = roundl(dsrc);
            uint64_t isrc = dsrc;
            dst->bits[0] = isrc & 0xFFFFFFFF;
            dst->bits[1] = isrc >> 32;
            set_scale(dst, 7);
        }
        set_sign(dst, sign);
    }
    return status;
}
