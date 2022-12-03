#include "s21_helpers.h"

int fill_zero_decimal(s21_decimal *arr) {
    for (int i = 0; i < 4; i++) {
        arr -> bits[i] = 0;
    }
    return 1;
}

int check_bit(int position, s21_decimal arr) {
    int result = 0;
    int define_byte = position / 32;
    int define_position_in_byte = position % 32;
    if (arr.bits[define_byte] & (1 << define_position_in_byte))
        result = 1;
    return result;
}

int check_bit_int(unsigned int number, int position) {
    return(number & (1 << position));
}

int getscale(s21_decimal decimal) {
    int scale = 0;
    for (int i = 119; i >= 112; i--)
        scale += check_bit(i, decimal) * pow(2, i - 112);
    return scale;
}

void sub_mantissa(s21_decimal value_1, \
    s21_decimal value_2, s21_decimal* result) {
    fill_zero_decimal(result);
    if (!s21_is_equal(value_1, value_2)) {
        int value_1_last_bit = last_mean_bit_mantissa(value_1);
        int buffer = 0;
        for (int i = 0; i <= value_1_last_bit; i++) {
            int current_bit_of_value_1 = check_bit(i, value_1);
            int current_bit_of_value_2 = check_bit(i, value_2);
            if (!current_bit_of_value_1 && !current_bit_of_value_2) {
                if (buffer) {
                    buffer = 1;
                    set_bit_dec(result, i);
                } else {
                    clean_bit_dec(result, i);
                }
            } else if (current_bit_of_value_1 && !current_bit_of_value_2) {
                if (buffer) {
                    buffer = 0;
                    clean_bit_dec(result, i);
                } else {
                    set_bit_dec(result, i);
                }
            } else if (!current_bit_of_value_1 && current_bit_of_value_2) {
                if (buffer) {
                    buffer = 1;
                    clean_bit_dec(result, i);
                } else {
                    buffer = 1;
                    set_bit_dec(result, i);
                }
            } else if (current_bit_of_value_1 && current_bit_of_value_2) {
                if (buffer) {
                    buffer = 1;
                    set_bit_dec(result, i);
                } else {
                    clean_bit_dec(result, i);
                }
            }
        }
    }
}

int last_mean_bit_mantissa(s21_decimal value) {
    int last_bit = 95;
    for (; last_bit >= 0 && check_bit(last_bit, value) == 0; last_bit--) {
    }
    return  last_bit;
}

void shift_left(s21_decimal* value, int step) {
    if (step > 0) {
        for (int i = 0; i < step; i++) {
            int zero_block_arr_last_bit = check_bit(31, *value);
            int one_block_arr_last_bit = check_bit(63, *value);
            value->bits[0] <<= 1;
            value->bits[1] <<= 1;
            value->bits[2] <<= 1;
            if (zero_block_arr_last_bit) {
                set_bit_dec(value, 32);
            }
            if (one_block_arr_last_bit) {
                set_bit_dec(value, 64);
            }
        }
    } else {
        for (int i = 0; i < (-1) * step; i++) {
            int zero_block_arr_last_bit = check_bit(31, *value);
            int one_block_arr_last_bit = check_bit(63, *value);
            value->bits[0] <<= 1;
            value->bits[1] <<= 1;
            value->bits[2] <<= 1;
            if (zero_block_arr_last_bit) {
                set_bit_dec(value, 32);
            }
            if (one_block_arr_last_bit) {
                set_bit_dec(value, 64);
            }
        }
    }
}

void div_mantissa(s21_decimal dividend, s21_decimal divider, \
    s21_decimal *remainder, s21_decimal *result) {
    fill_zero_decimal(remainder);
    fill_zero_decimal(result);
    for (int i = last_mean_bit_mantissa(dividend); i >= 0; i--) {
        if (check_bit(i, dividend)) {
            set_bit_dec(remainder, 0);
        }
        if (s21_is_greater_or_equal(*remainder, divider)) {
            sub_mantissa(*remainder, divider, remainder);
            if (i != 0) {
                shift_left(remainder, 1);
            }
            if (check_bit(i - 1, dividend)) {
                set_bit_dec(remainder, 0);
            }
            shift_left(result, 1);
            set_bit_dec(result, 0);
        } else {
            shift_left(result, 1);
            if (i != 0) {
                shift_left(remainder, 1);
            }
            if ((i - 1) >= 0 && check_bit(i - 1, dividend)) {
                set_bit_dec(remainder, 0);
            }
        }
    }
}

int get_bit(s21_decimal dec, int pos) {
    int is_set = (dec.bits[pos / 32] >> (pos % 32)) & 1;
    return is_set;
}

void set_bit_dec(s21_decimal *dec, int bit) {
    dec->bits[bit/ 32] |= (1 << (bit % 32));
}

void clean_bit_dec(s21_decimal *dec, int bit) {
    dec->bits[bit/ 32] &= ~(1 << (bit % 32));
}
// int clean_bit(int integer, int bit) {return integer &= ~(1 << bit); }

unsigned int set_bit(unsigned int integer, int bit) { return integer |= (1U << bit); }
unsigned int clean_bit(unsigned int integer, int bit) {return integer &= ~(1U << bit); }


void set_sign(s21_decimal *value, int sign) {
    if (sign == 1) value->bits[3] = set_bit(value->bits[3], 31);
    if (sign == 0) value->bits[3] = clean_bit(value->bits[3], 31);
}

int get_sign(s21_decimal *dst) {
    return (dst->bits[3] >> 31) & 1U;
}

int set_scale(s21_decimal *dst, int scale) {
    unsigned error = scale < 0 || scale > MAX_DEC_EXP+1;
    if (!error) {
        dst->bits[3] &= ~(0xFF << 16);
        dst->bits[3] |= scale << 16;
    }
    return error;
}

/* if exponent of decimal is e_max + 1 and non-zero significand */
int is_nan(s21_decimal value) {
    return (get_scale(value) == MAX_DEC_EXP+1) && value.bits[0];
    }

/* if exponent of decimal is e_max + 1 and zero significand */
int is_neg_inf(s21_decimal value) {
    int is_zero = (value.bits[0] == 0) && (value.bits[1] == 0) && (value.bits[2] == 0);
    return (get_sign(&value) && get_scale(value) == MAX_DEC_EXP+1 && is_zero);
}

int is_pos_inf(s21_decimal value) {
    int is_zero = (value.bits[0] == 0) && (value.bits[1] == 0) && (value.bits[2] == 0);
    return (!get_sign(&value) && get_scale(value) == MAX_DEC_EXP+1 && is_zero);
}

int is_zero(s21_decimal value) {
    int res = 0;
    if (value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0 && get_scale(value) == 0) {
        res = 1;
        set_sign(&value, 0);
    }
    return res;
}

/* setting decimal to NaN */
int set_nan(s21_decimal *value) {
    unsigned int seed = time(NULL);
    if (!value) return 1;
    value->bits[0] = rand_r(&seed);
    set_scale(value, MAX_DEC_EXP + 1);
    set_sign(value, 0);
    return 0;
}
/* setting decimal to inf with a sign (1 - negative, 0 - positive) */
int set_inf(s21_decimal *value, int sign) {
    if (!value) return 1;
    memset(value, 0, sizeof(*value));
    set_scale(value, MAX_DEC_EXP + 1);
    set_sign(value, sign);
    return 0;
}

int pow_ten(s21_decimal *value, int reps) {
    int overflow = 0;
    while (reps) {
        uint64_t low_bits = value->bits[0];
        uint64_t mid_bits = value->bits[1];
        uint64_t high_bits = value->bits[2];

        low_bits *= 10; mid_bits *= 10; high_bits *= 10;
        mid_bits += (low_bits >> 32);
        high_bits += (mid_bits >> 32);
        low_bits &= 0xFFFFFFFF;
        mid_bits &= 0xFFFFFFFF;
        high_bits &= 0xFFFFFFFF;

        value->bits[0] = low_bits;
        value->bits[1] = mid_bits;
        value->bits[2] = high_bits;
        reps--;
    }
    return overflow;
}

int get_bits(s21_decimal value, int index) {
    unsigned int mask = 1u << (index % 32);
    return value.bits[index/32]&mask;
}

int get_bits_int(unsigned int value, int index) {
    unsigned int mask = 1u << (index % 32);
    return value&mask;
}

int set_bits(s21_decimal value, int index) {
    value.bits[index/ 32] |= (1 << index);
    return 0;
}

int set_bits_int(unsigned int *value, int index) {
    *value |= (1 << index);
    return 0;
}

int get_scale(s21_decimal dst) {
    return (dst.bits[3] >> 16) & 0xff;
}

void binary_integer(int src) {
    for (unsigned i = (1 << 31); i > 0; i = i / 2) {
        if (src & i) putchar('1');
        if (!(src & i)) putchar('0');
    }
}

int binary_decimal(s21_decimal *value) {
    int error = !value;
    if (!error) {
        printf("Low bits - ");
        binary_integer(value->bits[0]);

        printf("\nMiddle bits - ");
        binary_integer(value->bits[1]);

        printf("\nHigh bits - ");
        binary_integer(value->bits[2]);

        printf("\nLast bits - ");
        binary_integer(value->bits[3]);
    }
    putchar('\n');
    return error;
}

int scale_equalize(s21_decimal *value_a, s21_decimal *value_b) {
    int error = 0;
    if (!value_a || !value_b) error = 1;
    if (!error) {
        int scale_a = get_scale(*value_a);
        int scale_b = get_scale(*value_b);
        int scale_diff = 0;
        if (scale_a > scale_b) {
            scale_diff = scale_a - scale_b;
            set_scale(value_b, scale_b + scale_diff);
            pow_ten(value_b, scale_diff);
        } else {
            scale_diff = scale_b - scale_a;
            set_scale(value_a, scale_a + scale_diff);
            pow_ten(value_a, scale_diff);
        }
    }
    return error;
}

//  copy s21_decimal to another s21_decimal
void copy_s21_decimal(s21_decimal value_to_copy, s21_decimal *dest) {
    dest->bits[0] = value_to_copy.bits[0];
    dest->bits[1] = value_to_copy.bits[1];
    dest->bits[2] = value_to_copy.bits[2];
    dest->bits[3] = value_to_copy.bits[3];
}

