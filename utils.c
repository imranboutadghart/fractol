#include "fractol.h"

int ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] == s2[i]);
}

int ft_isnum(char c)
{
	return (c <= '9' && c >= '0');
}

double	ft_atof(char *s)
{
	double res;
	int		sign;
	int		i;

	sign = 1;
	res = 0;
	i = 0;
	if ('+' == *s || '-' == *s)
		if ('-' == *(s++))
			sign = -1;
	while (*s && ft_isnum(*s))
	{
		res = res * 10 + *(s++) - '0';
		if (res > 1000)
			 return (sign * res);
	}
	if (*(s++) != '.')
		return (sign * res);
	while (*s && ft_isnum(*s))
	{
		res += (*(s++) - '0') * pow(10, --i);
		if (i <= -10)
			return (sign * res);
	}
	return (res);
}
