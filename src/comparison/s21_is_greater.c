#include "s21_comparison.h"

int s21_is_greater(s21_decimal a, s21_decimal b) {
    if (s21_is_equal(a, b)) return 0;
    if (is_zero(a) && is_zero(b)) return 0;
    if (is_nan(a) || is_nan(b)) return 0;
    if (is_pos_inf(a) || is_neg_inf(b)) return 1;
    if (is_pos_inf(b) || is_neg_inf(a)) return 0;
    int result = 0;
    if (get_scale(a) != get_scale(b)) scale_equalize(&a, &b);
    if (!get_sign(&a) && get_sign(&b)) result = 1;
    if (!get_sign(&a) && !get_sign(&b)) {
        for (int i = 95; i >= 0; i--) {
            if (get_bit(a, i) && !get_bit(b, i)) {
                result = 1;
                break;
            }
            if (get_bit(b, i) && !get_bit(a, i)) {
                result = 0;
                break;
            }
        }
    } else if (get_sign(&a) && get_sign(&b)) {
        for (int i = 95; i >= 0; i--) {
            if (!get_bit(a, i) && get_bit(b, i)) {
                result = 1;
                break;
            } else if (!get_bit(b, i) && get_bit(a, i)) {
                result = 0;
                break;
            }
        }
    }
    return result;
}
