#include "ft_printf.h"

void init_structs(t_print *rules)
{

    rules->conv.c = -1;
    rules->flag.zero = -1;
    rules->flag.minus = -1;
    rules->flag.width = -1;
    rules->flag.prec = -1;
    rules->flag.prec_nb = -1;
}

void init_ret(t_print *rules)
{
    rules->ret = 0;
}

char *ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = -1;
	j = -1;
	if (!s1 || !s2)
		return (0);
	if (!(ptr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (0);
	while (s1[++i])
		ptr[i] = s1[i];
	while (s2[++j])
		ptr[i + j] = s2[j];
	ptr[i + j] = '\0';
	return ((char *)ptr);
}

char *revstr(char *str)
{
	size_t	i;
	size_t	j;
	char	*newstr;

	j = 0;
	i = ft_strlen(str) + 1;
	if (!(newstr = malloc(sizeof(char) * i)))
		return (0);
	while (i - 1 > 0)
	{
		newstr[j] = str[--i - 1];
		j++;
	}
	newstr[j] = '\0';
	free(str);
	return (newstr);
}

int	len_int(int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
		return (11);
	else if (n <= 2147483647 && n > -2147483648)
	{
		if (n == 0)
			return (1);
		if (n < 0)
		{
			n = -n;
			i += 1;
		}
		while (n > 0)
		{
			n = n / 10;
			i++;
		}
	}
	return (i);
}

int	ft_pow(int nb, int pow)
{
	int	i;
	int	res;

	i = 0;
	res = 1;
	while (i < pow)
	{
		res = res * nb;
		i++;
	}
	return (res);
}

unsigned int ft_pow_u(unsigned int nb, unsigned int pow)
{
	unsigned int	i;
	unsigned int	res;

	i = 0;
	res = 1;
	while (i < pow)
	{
		res = res * nb;
		i++;
	}
	return (res);
}

unsigned int len_int_u(unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char *ft_toupper(char *str)
{
	size_t i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 97 && str[i] <= 122)
			str[i] = str[i] - 32;
		i++;
	}
	return (str);
}

int ft_is_flag(char c)
{
    if (c == '0' || c == '-' || c == '*' || c == '.')
        return (1);
    return (0);
}

int ft_is_conv(char c)
{
    if (c == 'd' || c == 'i' || c == 'u' || c == 'x' || c == 'X' || c == 'p' || c == 's' || c == 'c')
        return (1);
    return (0);
}

int ft_isdigit(char c)
{
    if (c >= 48 && c <= 57)
        return (1);
    return (0);
}

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

int ft_adjust_flags(char *str, t_print *rules, char type)
{
    if (rules->flag.zero != -1 && rules->flag.prec != -1 && (type == 'd' || type == 'i' || type == 'u' || type == 'x' || type == 'X' || type == 'p'))
        rules->flag.zero = -1;
    if (rules->flag.minus != -1 && rules->flag.zero != -1)
        rules->flag.zero == -1;
    if (rules->flag.prec == -1)
        rules->flag.prec = ft_strlen(str);
    if (rules->flag.width <= ft_strlen(str))
        rules->flag.width = 0;
    if (rules->flag.prec >= ft_strlen(str) && (type == 's' || type == 'c'))
        rules->flag.prec = ft_strlen(str);
    else if (rules->flag.prec >= ft_strlen(str)
    && (type == 'd' || type == 'i' || type == 'u' || type == 'x' || type == 'X' || type == 'p'))
    {
        rules->flag.prec_nb = rules->flag.prec;
        rules->flag.prec = -1;
    }
    else if (rules->flag.prec < ft_strlen(str)
    && (type == 'd' || type == 'i' || type == 'u' || type == 'x' || type == 'X' || type == 'p'))
    {
        rules->flag.prec_nb = ft_strlen(str);
        rules->flag.prec = -1;
    }
    if (rules->flag.width > ft_strlen(str) && rules->flag.prec_nb != -1)
        rules->flag.width = rules->flag.width - rules->flag.prec_nb;
    else if (rules->flag.width > ft_strlen(str) && rules->flag.prec != -1)
        rules->flag.width = rules->flag.width - rules->flag.prec;
}

int ft_calculate_minus(int i, int j, int k)
{
    int res;

    res = 0;
    if (i != -1)
        res = i;
    if (j != -1)
        res = res + j;
    if (k != -1)
        res = res + k;
    return (res);
}

int ft_putstr_revised(char *str, t_print *rules, char type)
{
    int i;
    int j;
    int res;

    i = 0;
    j = 0;
    res = 0;
    ft_adjust_flags(str, rules, type);
    while (rules->flag.minus == -1 && rules->flag.zero == -1 && rules->flag.width > 0 && i < rules->flag.width)
    {
        rules->ret += write(1, " ", sizeof(char));
        i++;
    }
    if (str[0] == '-' && (type == 'd' || type == 'u' || type == 'i'))
    {
        write(1, "-", sizeof(char));
        j++;
    }
    while (rules->flag.minus == -1 && rules->flag.prec_nb != -1 && i < rules->flag.prec_nb - ft_strlen(str))
    {
        rules->ret += write(1, "0", sizeof(char));
        i++;
    }
    while (str[j] && (((j < rules->flag.prec) || (rules->flag.prec_nb != -1)) || (rules->flag.prec == -1 || rules->flag.width == -1)))
    {
        rules->ret += write(1, &str[j], sizeof(char));
        j++;
    }
    if (rules->flag.minus != -1)
    {
        res = ft_calculate_minus(rules->flag.prec_nb, rules->flag.prec, rules->flag.width);
        while (i < res)
        {
           rules->ret += write(1, " ", sizeof(char));
           i++;
        }
    }
    return (i + j);
}

int ft_putchar_revised(char c, t_print *rules, char type)
{
    int i;
    int j;
    int res;

    i = 0;
    j = 0;
    res = 0;
    ft_adjust_flags("1", rules, type);
    while (rules->flag.minus == -1 && rules->flag.zero == -1 && rules->flag.width != -1 && i < rules->flag.width)
    {
        rules->ret += write(1, " ", sizeof(char));
        i++;
    }
    while (rules->flag.minus == -1 && rules->flag.prec_nb != -1 && i < rules->flag.prec_nb - 1)
    {
        rules->ret += write(1, "0", sizeof(char));
        i++;
    }
    if (rules->flag.prec != -1 || rules->flag.prec_nb != -1 || rules->flag.prec == -1 || rules->flag.prec_nb == -1)
    {
        rules->ret += write(1, &c, sizeof(char));
        j++;
    }
    if (rules->flag.minus != -1)
    {
        res = ft_calculate_minus(rules->flag.prec_nb, rules->flag.prec, rules->flag.width);
        while (i < res)
        {
            rules->ret += write(1, " ", sizeof(char));
            i++;
        }
    }
    return (i + j);
}

int			ft_atoi_revised(char *str)
{
	int i;
	int j;
	int res;

	i = 0;
	j = 0;
	res = 0;
//	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
//		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			j = (str[i] == '-') ? -1 : 1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
    	res = res * 10 + (str[i] - 48);
        i++;
    }
	if (res == -2147483648)
		return (res);
	if (j < 0)
		res = res * j;
	return (res);
}

char	*ft_to_hex(unsigned long long n, char *base)
{
	int					i;
	char				*str;
	unsigned long long	k;

	k = n;
	i = 0;
	while (k > 0)
	{
		k = k / ft_strlen(base);
		i++;
	}
	if (!(str = malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (n > 0)
	{
		str[i] = base[n % ft_strlen(base)];
		n = n / ft_strlen(base);
		i++;
	}
	str[i] = '\0';
	str = revstr(str);
//	if (c == 'X')
//		str = str_toupper(str);
	return (str);
}

char	*ft_itoa(int n)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	if (n == -2147483648)
		return (ft_strjoin("-2147483648", ""));
	i = -1;
	k = n;
	j = len_int(k);
	if (!(str = malloc(sizeof(char) * (len_int(n) + 1))))
		return (0);
	n = (n < 0) ? -n : n;
	while (j-- > 0)
		if (i++ <= len_int(k))
			str[j] = ((n / ft_pow(10, i)) % 10) + '0';
	str[len_int(k)] = '\0';
	str[0] = (k < 0) ? '-' : str[0];
	return (str);
}

char *ft_itoa_u(unsigned int n)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;
	char			*str;

	i = 0;
	k = n;
	j = len_int_u(k);
	if (!(str = malloc(sizeof(char) * (len_int_u(n) + 1))))
		return (0);
	while (j-- > 0)
		if (i < len_int_u(k))
		{
			str[j] = ((n / ft_pow_u(10, i)) % 10) + '0';
			i++;
		}
	str[len_int_u(k)] = '\0';
	return (str);
}


int ft_isvalue(char *string, int count, t_print *rules, va_list args)
{
    if (ft_isdigit(string[count]))
       return (1);
    if (ft_is_flag(string[count]))
        return (1);
    else if (ft_is_conv(string[count]))
        return (2);
    return (0);
}

int ft_write_arg(char *string, int count, t_print *rules, va_list args)
{
//    printf("string[ocunt] %c\n", string[count]);
        if (string[count] == 'd' || string[count] == 'i')
        {
            rules->test.test_int = va_arg(args, int);
            ft_putstr_revised(ft_itoa(rules->test.test_int), rules, string[count]);
        }
        else if (string[count] == 'u')
        {
            rules->test.test_uint = va_arg(args, unsigned int);
            ft_putstr_revised(ft_itoa_u(rules->test.test_uint), rules, string[count]);
        }
        else if (string[count] == 'x')
        {
            rules->test.test_long = va_arg(args, unsigned long long);
            ft_putstr_revised(ft_to_hex(rules->test.test_long, "0123456789ABCDEF"), rules, string[count]);
        }
        else if (string[count] == 'X')
        {
            rules->test.test_long = va_arg(args, unsigned long long);
            ft_putstr_revised(ft_toupper(ft_to_hex(rules->test.test_long, "0123456789ABCDEF")), rules, string[count]);
        }
        else if (string[count] == 's')
        {
            if ((rules->test.test_string = va_arg(args, char*)))
                ft_putstr_revised(rules->test.test_string, rules, string[count]);
            else
                ft_putstr_revised("(null)", rules, string[count]);
        }
        else if (string[count] == 'c')
        {
            if ((rules->test.test_c = va_arg(args, int)))
                ft_putchar_revised(rules->test.test_c, rules, string[count]);
            else
                ft_putstr_revised("(null)", rules, string[count]);
        }
        rules->conv.bool_x = 0;
}

int ft_record_flags(char *string, int count, t_print *rules, va_list args)
{
    int index;
    int tmp;
    int bool;

    count++;
    tmp = count;
    index = 0;
    bool = 0;
    if (string[count])
    {
//        printf("B");
        while (ft_isvalue(string, count + index, rules, args) == 1)
            index++;
//        printf("strcountindex %c\n", string[count + index]);
        if (ft_isvalue(string, count + index, rules, args) == 2)
        {
            while (string[count] == '0' || string[count] == '-')
            {
                if (string[count] == '-')
                    rules->flag.minus = 1;
                if (string[count] == '0')
                    rules->flag.zero = 1;
                count++;
            }
            if (string[count] == '*')
            {
                rules->flag.width = va_arg(args, int);
                    count++;
            }
            if (ft_isdigit(string[count]))
                {
                    rules->flag.width = ft_atoi_revised(&string[count]);
                    count += ft_strlen(ft_itoa(rules->flag.width));
//                    printf("rules flag width %d\n", rules->flag.width);
                }
            if (string[count] == '.' && ft_isdigit(string[count + 1]))
                {
                    rules->flag.prec = ft_atoi_revised(&string[count + 1]);
                    count += ft_strlen(ft_itoa(rules->flag.prec));
                }
            if (string[count] == '.' && string[count + 1] == '*')
                {
                    rules->flag.prec = va_arg(args, int);
                    count++;
                }
            }
            return (count);
        }
        rules->conv.bool_x = 1;
        return (-1);
    }
    return (-1);
}

int ft_parse(char *string, int i, t_print *rules, va_list args)
{
    int count;
    int tmp;

    count = 0;
    tmp = 1;
    init_structs(rules);
    while (count < ft_strlen(string) && tmp < ft_strlen(string))
    {
//       printf("strcount %c\n", string[count]);
        if (string[count] == '%' && string[count + 1] == '%')
        {
            write(1, "%", sizeof(char));
            count++;
        }
        else if (string[count] == '%' && (tmp = ft_record_flags(string, count, rules, args)) > -1)
        {
            ft_write_arg(string, tmp, rules, args);
            count = (tmp) ? tmp + 1 : count;
            init_structs(rules);
        }
        else
        {
            write(1, &string[count], sizeof(char));
            rules->ret++;
            count++;
        }
        tmp = -1;
        rules->conv.bool_x = 0;
//        printf("tmp - %d\n", tmp);
//        count = (tmp != -1) ? tmp + 1 : ++count;
//        printf("count %d\n", count);
    }
    return (count);
}

int ft_printf(const char *format, ...)
{
    va_list args;
    t_print rules;
    int i;

    i = 0;
    init_ret(&rules);
    rules.conv.bool_x = 0;
    va_start(args, format);
    ft_parse((char *)format, i, &rules, args);
    va_end(args);
 //   printf("%d\n", rules.flag.prec);
 //   printf("%d\n", rules.flag.width);
    return (rules.ret);
}