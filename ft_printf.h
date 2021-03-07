#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stddef.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>

typedef struct  s_flag
{
    char flag;
    int prec;
    int width;
    int zero;
    int minus;
    int prec_nb;
}               t_flag;

typedef struct  s_conv
{
    char c;
    int bool_x;
}               t_conv;

typedef struct test
{
    int test_int;
    unsigned int test_uint;
    unsigned long long test_long;
    char* test_string;
    char test_c;
}               t_test;

typedef struct  s_print
{
    t_flag flag;
    t_conv conv;
    t_test test;
    char *arg;
    int ret;
}               t_print;

int ft_printf(const char *format, ...);
int ft_parse(char *string, int i, t_print *rules, va_list args);
int ft_record_flags(char *string, int count, t_print *rules, va_list args);
int ft_isvalue(char *string, int count, t_print *rules, va_list args);
char *ft_itoa_u(unsigned int n);
char *ft_itoa(int n);
char *ft_to_hex(unsigned long long n, char *base);
int ft_atoi_revised(char *str);
int ft_putchar_revised(char c, t_print *rules, char type);
int ft_putstr_revised(char *str, t_print *rules, char type);
int ft_calculate_minus(int i, int j, int k);
int ft_adjust_flags(char *str, t_print *rules, char type);
int ft_strlen(char *str);
int ft_isdigit(char c);
int ft_is_conv(char c);
int is_flag(char c);
int	len_int(int n);
int	ft_pow(int nb, int pow);
unsigned int ft_pow_u(unsigned int nb, unsigned int pow);
unsigned int len_int_u(unsigned int n);
char *ft_toupper(char *str);
char *ft_strjoin(char *s1, char *s2);
char *revstr(char *str);
void init_ret(t_print *rules);
void init_structs(t_print *rules);
int ft_write_arg(char *string, int count, t_print *rules, va_list args);



#endif