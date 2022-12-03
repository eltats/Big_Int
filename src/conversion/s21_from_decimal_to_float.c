#include "s21_conversion.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
    if (dst == NULL) return 1;
    int status = 0;
    if (is_nan(src)) {
        *dst = NAN;
        status = 1;
    }
    if (is_neg_inf(src)) {
        *dst = INFINITY;
        status = 1;
    }
    if (is_pos_inf(src)) {
        *dst = -INFINITY;
        status = 1;
    }
    if (status == 0) {
        int exp = get_scale(src);
        long double fl_copy = 0;
        for (int i = 0; i != 96; i++) {
            if (get_bit(src, i)) {
                fl_copy += pow(2, i);
            } else {
                continue;
            }
        }
        while (exp--) fl_copy /= 10.0;
        if (get_sign(&src)) fl_copy = -fl_copy;
        *dst = fl_copy;
    }
    return status;
}
