#include "s21_conversion.h"

int s21_from_decimal_to_int(s21_decimal dst, int *src) {
    int status = (src == NULL);
    if (dst.bits[1] || dst.bits[2]) status = 1;
    if ((int)dst.bits[0] > INT32_MAX || (int)dst.bits[0] < INT32_MIN) {
      status = 1;
    }
    if (status == 0) {
        if (get_scale(dst)) {
            // s21_truncate()
        }
        *src = dst.bits[0];
        *src *= get_sign(&dst) ? -1 : 1;
    }
    return status;
}
