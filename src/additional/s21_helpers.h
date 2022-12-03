#ifndef SRC_ADDITIONAL_S21_HELPERS_H_
#define SRC_ADDITIONAL_S21_HELPERS_H_

#include "../s21_decimal.h"
#include <time.h>

// check if NAN
#define isnan_f(x) __builtin_isnan(x)
// check for INF
#define isinf_f(x) __builtin_isinf(x)
#define MAX_DEC_EXP 28
#define FLT_EPS = 1e-28
#define M_LEN 23

typedef enum {
    NORMAL,  //  normal result
    POS_OVERFLOW,  //  +inf
    NEG_OVERFLOW,  //  -inf
    ZERO_DIVISION  //  0 div
} error_code_value;

unsigned int clean_bit(unsigned int integer, int bit);
unsigned int set_bit(unsigned int integer, int bit);
int set_inf(s21_decimal *value, int sign);
void set_bit_dec(s21_decimal *dec, int bit);
void clean_bit_dec(s21_decimal *dec, int bit);
int init_decimal(s21_decimal *value, int scale, unsigned long long int mantissa, int sign);
int set_nan(s21_decimal *value);
void set_sign(s21_decimal *value, int sign);
int get_bit(s21_decimal dec, int pos);
int get_bits(s21_decimal value, int index);
int get_bits_int(unsigned int value, int index);
int set_bits(s21_decimal value, int index);
int set_bits_int(unsigned int *value, int index);
int pow_ten(s21_decimal *value, int reps);
int set_scale(s21_decimal *dst, int scale);
int scale_equalize(s21_decimal *value_a, s21_decimal *value_b);
void binary_integer(int src);
int binary_decimal(s21_decimal *value);
int get_sign(s21_decimal *dst);
int get_scale(s21_decimal dst);
int is_pos_inf(s21_decimal value);
int is_zero(s21_decimal value);
int is_neg_inf(s21_decimal value);
int is_nan(s21_decimal value);
int normalize(s21_decimal *value_a, s21_decimal *value_b);
int convert_bin_dec(s21_decimal value);
int left_shift(s21_decimal *value, unsigned int index);
void inversion(s21_decimal *value);
void copy_s21_decimal(s21_decimal value_to_copy, s21_decimal *dest);
void s21_add_single_sign(s21_decimal value_1, s21_decimal value_2,
                         s21_decimal *result, unsigned int *p_temp_bit);
int fill_zero_decimal(s21_decimal *arr);
int check_bit(int position, s21_decimal arr);
int check_bit_int(unsigned int number, int position);
int getscale(s21_decimal decimal);
void sub_mantissa(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int last_mean_bit_mantissa(s21_decimal value);
void shift_left(s21_decimal* value, int step);
void div_mantissa(s21_decimal dividend, s21_decimal divider, s21_decimal *remainder, s21_decimal *result);
#endif  // SRC_ADDITIONAL_S21_HELPERS_H_
