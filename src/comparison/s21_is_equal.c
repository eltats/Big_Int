#include "s21_comparison.h"

int s21_is_equal(s21_decimal a, s21_decimal b) {
    int res = 0;
    if (is_nan(a) || is_nan(b)) res = 0;
    if (is_pos_inf(a) && is_pos_inf(b)) res = 1;
    if (is_neg_inf(a) && is_neg_inf(b)) res = 1;
    if (is_zero(a) && is_zero(b)) res = 1;
    if ((a.bits[0] == b.bits[0]) && (a.bits[1] == b.bits[1]) &&
        (a.bits[2] == b.bits[2]) && (a.bits[3] == b.bits[3])) res = 1;
    return res;
}
