#include "s21_big_decimal.h"

//  convert s21_decimal to big_decimal
void convert_s21_decimal_to_big_decimal(s21_decimal value, big_decimal *result) {
    result->bits[0] = value.bits[0];
    result->bits[1] = value.bits[1];
    result->bits[2] = value.bits[2];
    result->bits[3] = 0;
    result->bits[4] = 0;
    result->bits[5] = 0;
    result->bits[6] = value.bits[3];
}

//  copy meaning part of big_decimal to another big_decimal
void copy_big_decimal_value(big_decimal value_to_copy, big_decimal *dest) {
    for (unsigned int i = 0 ; i < 6; i++) {
        dest->bits[i] = value_to_copy.bits[i];
    }
}

int get_bit_big_decimal(big_decimal value, int index) {
    int max_bit = 32;
    int value_index = index / max_bit;
    int shift = index % max_bit;
    return (value.bits[value_index] >> shift) & 1U;
}

void set_bit_big_decimal(big_decimal* result, int index, unsigned int bit) {
    int max_bit = 32;
    int value_index = index / max_bit;
    int shift = index % max_bit;
    int shifted_inversion =  ~(1U << shift);
    int shifted_bit = bit << shift;
    result->bits[value_index] = (result->bits[value_index] & shifted_inversion) | shifted_bit;
}

int get_sign_big_decimal(big_decimal *dst) {
    int sign_index = 6;
    int sign_offset = 31;
    return (dst->bits[sign_index] >> sign_offset) & 1U;
}

int get_scale_big_decimal(big_decimal dst) {
    int sign_index = 6;
    return dst.bits[sign_index] >> 16;
}

void add_mantissa_big_decimal(big_decimal value_1, big_decimal value_2, big_decimal *result) {
    int additional = 0;
    for (int i = 0; i < 6; i++) {
        unsigned long long sum = (unsigned long long)value_1.bits[i]
                               + (unsigned long long)value_2.bits[i] + additional;
        additional = sum >> 32;
        result->bits[i] = sum;
    }
}

void sub_mantissa_big_decimal(big_decimal value_1, big_decimal value_2, big_decimal *result) {
    int borrow = 0;
    for (unsigned int i = 0; i < 6; i++) {
        result->bits[i] = value_1.bits[i] - value_2.bits[i] - borrow;
        borrow = (unsigned long long)value_1.bits[i] < (unsigned long long)value_2.bits[i] + borrow;
    }
}

bool eq_mantissa_big_decimal(big_decimal value1, big_decimal value2) {
    bool is_equal = true;
    for (unsigned i = 0; i < 6 ; i++) {
        if (value1.bits[i] != value2.bits[i]) {
            is_equal = false;
            break;
        }
    }
    return is_equal;
}

bool lt_mantissa_big_decimal(big_decimal value1, big_decimal value2) {
    bool isLess = false;
    for (int i = 5; i >= 0; i--) {
        if (value1.bits[i] == value2.bits[i]) {
            continue;
        }
        if (value1.bits[i] < value2.bits[i]) {
            isLess = true;
        } else {
            isLess = false;
        }
        break;
    }
    return isLess;
}

bool gt_mantissa_big_decimal(big_decimal value1, big_decimal value2) {
    bool isGreater = false;
    for (int i = 5; i >= 0; i--) {
        if (value1.bits[i] == value2.bits[i]) {
            continue;
        }
        if (value1.bits[i] > value2.bits[i]) {
            isGreater = true;
        } else {
            isGreater = false;
        }
        break;
    }
    return isGreater;
}

unsigned int get_highest_non_zero_bit_big_decimal(big_decimal value) {
    int result = 191;
    for (unsigned int i = result; i != 0 && !get_bit_big_decimal(value, i); i--) {
        result = i;
    }
    return result;
}

void div_mantissa_big_decimal(big_decimal value1, big_decimal value2,
                              big_decimal *div_result, big_decimal *div_remainder) {
    for (unsigned int i = 0; i < 7; i++) {
        div_result->bits[i] = 0;
    }
    *div_remainder = value1;

    big_decimal big_decimal_zero = {0};
    big_decimal big_decimal_one = {{1}};

    for (int i = get_highest_non_zero_bit_big_decimal(value1)
                 - get_highest_non_zero_bit_big_decimal(value2); i >= 0;  i--) {
        big_decimal tmp1, tmp2;
        left_shift_big_decimal(value2, i, &tmp1);
        if ((lt_mantissa_big_decimal(tmp1, *div_remainder)
             || eq_mantissa_big_decimal(tmp1, *div_remainder))
             && !eq_mantissa_big_decimal(tmp1, big_decimal_zero)) {
            sub_mantissa_big_decimal(*div_remainder, tmp1, div_remainder);
            left_shift_big_decimal(big_decimal_one, i, &tmp2);
            add_mantissa_big_decimal(*div_result, tmp2, div_result);
        }
    }
}

void bank_rounding_big_decimal(big_decimal *value, big_decimal div_remainder) {
    big_decimal big_decimal_five = {{5}};
    big_decimal big_decimal_one = {{1}};
    if (gt_mantissa_big_decimal(div_remainder, big_decimal_five) ||
        (eq_mantissa_big_decimal(div_remainder, big_decimal_five) && get_bit_big_decimal(*value, 0))) {
        add_mantissa_big_decimal(*value, big_decimal_one, value);
    }
}

int convert_big_decimal_to_s21_decimal(big_decimal value, s21_decimal *result) {
    int function_result = 0;
    int sign = get_bits_int(value.bits[6], 31);
    big_decimal last_digit = {{0}};
    big_decimal big_decimal_ten = {{10}};
    unsigned int max = 4294967295;
    big_decimal max_s21_decimal = {{max, max, max}};
    unsigned int scale = pow_to_int_big_decimal(value);

    while (scale != 0 && (gt_mantissa_big_decimal(value, max_s21_decimal) || scale > 28)) {
        div_mantissa_big_decimal(value, big_decimal_ten, &value, &last_digit);
        scale--;
    }

    bank_rounding_big_decimal(&value, last_digit);

    unsigned int new_sign_scale = scale;
    new_sign_scale = new_sign_scale << 16;
    if (sign) {
        set_bits_int(&(new_sign_scale), 31);
    }

    if (value.bits[3] != 0 || value.bits[4] != 0 || value.bits[5] != 0) {
        if (!sign) {
            function_result = 1;
        } else {
            function_result = 2;
        }
    } else {
        result->bits[0] = value.bits[0];
        result->bits[1] = value.bits[1];
        result->bits[2] = value.bits[2];
        result->bits[3] = new_sign_scale;
    }
    return function_result;
}

//  debug only
//  print [int] in binary presentation
void printf_single_bit(int src) {
    for (unsigned int i = (1U << 31); i > 0; i = i / 2) {
        if (src & i) putchar('1');
        if (!(src & i)) putchar('0');
    }
    printf("\n");
}

//  debug only
//  print [big_decimal] in binary presentation
void printf_big_decimal(big_decimal value) {
    printf("0 bits - ");
    printf_single_bit(value.bits[0]);
    printf("1 bits - ");
    printf_single_bit(value.bits[1]);
    printf("2 bits - ");
    printf_single_bit(value.bits[2]);
    printf("3 bits - ");
    printf_single_bit(value.bits[3]);
    printf("4 bits - ");
    printf_single_bit(value.bits[4]);
    printf("5 bits - ");
    printf_single_bit(value.bits[5]);
    printf("6 bits - ");
    printf_single_bit(value.bits[6]);
}


//  convert binary pow to integer pow
unsigned int pow_to_int_big_decimal(big_decimal value) {
    unsigned int pow_value = 0;
    value.bits[6] >>= 16;
    for (unsigned int i = 0; i < 8; i++) {
        unsigned int current_bit_value = get_bits_int(value.bits[6], i);
        if (current_bit_value > 0) {
            pow_value += current_bit_value;
        }
    }
    return pow_value;
}

void left_shift_big_decimal(big_decimal value, unsigned int shift, big_decimal *result) {
    copy_big_decimal_value(value, result);
    for (size_t i = 0; i < shift; i++) {
        unsigned int bits[5] = {0};
        for (unsigned int j = 31; j < 191; j += 32) {
            bits[j / 32] = get_bit_big_decimal(*result, j);
        }
        for (unsigned int j = 0; j < 6; j++) {
            result->bits[j] <<= 1;
        }
        for (unsigned int j = 32; j < 192; j += 32) {
            set_bit_big_decimal(result,  j, bits[j / 32 - 1]);
        }
    }
}

//  normalizes value
void normalization_big_decimal(big_decimal *value, unsigned int shift) {
    big_decimal temp_val_1 = {{0}};
    big_decimal temp_val_2 = {{0}};
    big_decimal temp_val_3 = {{0}};
    big_decimal temp_val_4 = {{0}};
    big_decimal temp_result_value = {{0}};
    big_decimal empty_array = {{0}};

    copy_big_decimal_value(*value, &temp_val_1);
    copy_big_decimal_value(*value, &temp_val_2);
    for (unsigned int k = 1; k <= shift; k++) {
        left_shift_big_decimal(temp_val_1, 1, &temp_val_3);
        left_shift_big_decimal(temp_val_2, 3, &temp_val_4);
        add_mantissa_big_decimal(temp_val_3, temp_val_4, &temp_result_value);
        copy_big_decimal_value(temp_result_value, &temp_val_1);
        copy_big_decimal_value(temp_result_value, &temp_val_2);
        copy_big_decimal_value(empty_array, &temp_val_3);
        copy_big_decimal_value(empty_array, &temp_val_4);
        if (k < shift) copy_big_decimal_value(empty_array, &temp_result_value);
    }
    copy_big_decimal_value(temp_result_value, value);
}

void add_big_decimal(big_decimal value_1, big_decimal value_2, big_decimal *result) {
    big_decimal common_result = {0};
    unsigned int mantissa_pow_1 = pow_to_int_big_decimal(value_1);
    unsigned int mantissa_pow_2 = pow_to_int_big_decimal(value_2);
    unsigned int mantissa_size_1 = get_scale_big_decimal(value_1);
    unsigned int mantissa_size_2 = get_scale_big_decimal(value_2);
    bool is_positive_value_1 = get_bits_int(value_1.bits[6], 31) == 0;
    bool is_positive_value_2 = get_bits_int(value_2.bits[6], 31) == 0;
    unsigned int shift;

    if (mantissa_pow_1 > mantissa_pow_2) {
        shift = mantissa_pow_1 - mantissa_pow_2;
        normalization_big_decimal(&value_2, shift);
        common_result.bits[6] = mantissa_size_1 << 17 >> 1;
    } else if (mantissa_pow_1 < mantissa_pow_2) {
        shift = mantissa_pow_2 - mantissa_pow_1;
        normalization_big_decimal(&value_1, shift);
        common_result.bits[6] = mantissa_size_2 << 17 >> 1;
    } else {
        common_result.bits[6] = mantissa_size_1 << 17 >> 1;
    }

    if (!is_positive_value_1 && !is_positive_value_2) {
        add_mantissa_big_decimal(value_1, value_2, &common_result);
        set_bits_int(&(common_result.bits[6]), 31);
    } else if (!is_positive_value_1 && is_positive_value_2) {
        if (gt_mantissa_big_decimal(value_1, value_2)) {
            sub_mantissa_big_decimal(value_1, value_2, &common_result);
            set_bits_int(&(common_result.bits[6]), 31);
        } else {
            sub_mantissa_big_decimal(value_2, value_1, &common_result);
        }
    } else if (is_positive_value_1 && !is_positive_value_2) {
        if (gt_mantissa_big_decimal(value_1, value_2)) {
            sub_mantissa_big_decimal(value_1, value_2, &common_result);
        } else {
            sub_mantissa_big_decimal(value_2, value_1, &common_result);
            set_bits_int(&(common_result.bits[6]), 31);
        }
    } else if (is_positive_value_1 && is_positive_value_2) {
        add_mantissa_big_decimal(value_1, value_2, &common_result);
    }

    *result = common_result;
}
void set_sign_big_decimal(big_decimal *value, int sign) {
    if (sign == 1) value->bits[6] = set_bit(value->bits[6], 31);
    if (sign == 0) value->bits[6] = clean_bit(value->bits[6], 31);
}

void div_big_decimal(big_decimal value_1, big_decimal value_2, big_decimal *result) {
    big_decimal ten_big_decimal = {{10}};
    big_decimal zero_big_decimal = {{0}};
    unsigned int mantissa_pow_1 = pow_to_int_big_decimal(value_1);
    unsigned int mantissa_pow_2 = pow_to_int_big_decimal(value_2);
    bool is_positive_value_1 = get_bits_int(value_1.bits[6], 31) == 0;
    bool is_positive_value_2 = get_bits_int(value_2.bits[6], 31) == 0;

    int scale = mantissa_pow_1  - mantissa_pow_2;

    normalization_big_decimal(&value_1, 28);
    scale = scale + 28;

    while (true) {
        big_decimal tmp = value_1;
        big_decimal temp_result, temp_remainder;
        normalization_big_decimal(&value_1, 1);
        div_mantissa_big_decimal(value_1, tmp, &temp_result, &temp_remainder);
        if (!eq_mantissa_big_decimal(temp_result, ten_big_decimal)
            || !eq_mantissa_big_decimal(temp_remainder, zero_big_decimal)) {
            value_1 = tmp;
            break;
        }
        scale++;
    }

    big_decimal div_result = {0};
    big_decimal div_remainder = {0};

    div_mantissa_big_decimal(value_1, value_2, &div_result, &div_remainder);

    while (true) {
        big_decimal res_tmp, rem_tmp;
        div_mantissa_big_decimal(div_result, ten_big_decimal, &res_tmp, &rem_tmp);
        if (!eq_mantissa_big_decimal(rem_tmp, zero_big_decimal) || scale == 0)
            break;
        copy_big_decimal_value(res_tmp, &div_result);
        scale--;
    }

    div_result.bits[6] = scale << 16;

    if (is_positive_value_1 != is_positive_value_2) {
        set_bits_int(&(div_result.bits[6]), 31);
    }

    *result = div_result;
}
