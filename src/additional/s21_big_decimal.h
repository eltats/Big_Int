#ifndef SRC_ADDITIONAL_S21_BIG_DECIMAL_H_
#define SRC_ADDITIONAL_S21_BIG_DECIMAL_H_

#include <stdbool.h>
#include <stdio.h>
#include "../s21_decimal.h"
#include "s21_helpers.h"

/*
Тип для расссчетов переполнения в [s21_decimal]
индексы с 0 по 5 включая - значения
индекс 6 - знак и порядок, как в [s21_decimal]
*/
typedef struct {
    unsigned int bits[7];
} big_decimal;

// конвертация [s21_decimal] в [big_decimal], старшие биты в [big_decimal] 3,4,5 нули
void convert_s21_decimal_to_big_decimal(s21_decimal value, big_decimal *result);
// конвертация [big_decimal] в [s21_decimal], возвращает [arithmetics_status]
int convert_big_decimal_to_s21_decimal(big_decimal value, s21_decimal *result);

// debug only
// распечатать в консоли [big_decimal] в бинарном виде
void printf_big_decimal(big_decimal value);
// debug only
// распечатать в консоли [int] в бинарном виде
void printf_single_bit(int src);

// банковское округление
void bank_rounding_big_decimal(big_decimal *value, big_decimal div_remainder);

unsigned int get_highest_non_zero_bit_big_decimal(big_decimal value);
// вернуть порядок степени (от 0 до 28)
unsigned int pow_to_int_big_decimal(big_decimal value);
// вырвнивание порядке в [big_decimal]
void normalization_big_decimal(big_decimal *value, unsigned int shift);
// смещение битов в [big_decimal] и запись результата в [result]
void left_shift_big_decimal(big_decimal value, unsigned int shift, big_decimal *result);

bool eq_mantissa_big_decimal(big_decimal value1, big_decimal value2);
bool gt_mantissa_big_decimal(big_decimal value1, big_decimal value2);
bool lt_mantissa_big_decimal(big_decimal value1, big_decimal value2);

void div_mantissa_big_decimal(big_decimal value1, big_decimal value2,
                              big_decimal *div_result, big_decimal *div_remainder);
void add_mantissa_big_decimal(big_decimal value_1, big_decimal value_2, big_decimal *result);
void sub_mantissa_big_decimal(big_decimal value_1, big_decimal value_2, big_decimal *result);

void add_big_decimal(big_decimal value_1, big_decimal value_2, big_decimal *result);
void set_sign_big_decimal(big_decimal *value, int sign);
void set_bit_big_decimal(big_decimal* result, int index, unsigned int bit);
int get_bit_big_decimal(big_decimal value, int index);
int get_sign_big_decimal(big_decimal *dst);
int get_scale_big_decimal(big_decimal dst);
void div_big_decimal(big_decimal value_1, big_decimal value_2, big_decimal *result);
void copy_big_decimal_value(big_decimal value_to_copy, big_decimal *dest);

#endif  //  SRC_ADDITIONAL_S21_BIG_DECIMAL_H_
