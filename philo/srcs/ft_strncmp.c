/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:59:26 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/10/03 21:28:36 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			iter;
	int				diff;
	unsigned char	*us1;
	unsigned char	*us2;

	if (s1 == NULL || s2 == NULL)
		return (1);
	iter = 0;
	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	while (iter < n)
	{
		diff = *us1 - *us2;
		if (diff != 0 || *us1++ == '\0' || *us2++ == '\0')
			return (diff);
		iter++;
	}
	return (0);
}
