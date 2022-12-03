#ifndef SRC_CONVERSION_S21_CONVERSION_H_
#define SRC_CONVERSION_S21_CONVERSION_H_

#include "../s21_decimal.h"
#include "../additional/s21_helpers.h"

#define CONVERTATIONAL_ERROR 1
#define INTEGER_OVERFLOW 2
#define SIGN 0x80000000
#define FLOAT_BIAS 127

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal dst, int *src);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

#endif  // SRC_CONVERSION_S21_CONVERSION_H_
