/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:40:08 by tkatsuma          #+#    #+#           */
/*   Updated: 2025/10/17 22:26:54 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	digit2chr(long n)
{
	char	map[10];

	map[0] = '0';
	map[1] = '1';
	map[2] = '2';
	map[3] = '3';
	map[4] = '4';
	map[5] = '5';
	map[6] = '6';
	map[7] = '7';
	map[8] = '8';
	map[9] = '9';
	return (map[n]);
}

static int	get_digits(int ln)
{
	int			digit;
	long long	lln;

	if (ln == 0)
		return (1);
	digit = 1;
	lln = (long long) ln;
	if (lln < 0)
	{
		lln *= -1;
		digit++;
	}
	while (lln / 10 > 0)
	{
		digit++;
		lln = lln / 10;
	}
	return (digit);
}

char	*ft_ltoa(long ln)
{
	int			a_len;
	long long	lln;
	char		*arr;

	a_len = get_digits(ln);
	arr = (char *)malloc(sizeof(char) * (a_len + 1));
	if (arr == NULL)
		return (NULL);
	lln = (long long)ln;
	if (lln < 0)
	{
		arr[0] = '-';
		lln *= -1;
	}
	arr[a_len--] = '\0';
	if (lln == 0)
		arr[0] = '0';
	while (lln != 0)
	{
		arr[a_len--] = digit2chr(lln % 10);
		lln = lln / 10;
	}
	return (arr);
}
