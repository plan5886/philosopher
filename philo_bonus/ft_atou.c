/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atou.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mypark <mypark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 15:39:33 by mypark            #+#    #+#             */
/*   Updated: 2022/04/18 23:09:30 by mypark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t'
		|| c == '\r' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

static int	get_sign(const char **str)
{
	int	sign;

	sign = 1;
	if (**str == '+' || **str == '-')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

static void	jump_spaces(const char **str)
{
	while (is_space(**str))
		(*str)++;
}

static int	_ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atou(const char *str)
{
	long int	num;
	long int	pre;

	jump_spaces(&str);
	if (get_sign(&str) == -1)
		return (-1);
	num = 0;
	while (*str)
	{
		pre = num;
		num = num * 10 + (*str - '0');
		if (num > 2147483647 || num < pre || !_ft_isdigit(*str))
			return (-1);
		str++;
	}
	return (num);
}
