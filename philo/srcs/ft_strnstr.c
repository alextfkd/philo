/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:42:37 by tkatsuma          #+#    #+#           */
/*   Updated: 2025/10/17 22:27:20 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	blen;
	size_t	llen;
	size_t	idx;

	if (big == NULL)
		return (NULL);
	blen = ft_strlen(big);
	llen = ft_strlen(little);
	if (llen == 0)
		return ((char *) big);
	if (blen < llen || len < llen)
		return (NULL);
	idx = 0;
	while (idx < len && idx + llen <= len)
	{
		if (ft_strncmp(big, little, llen) == 0)
			return ((char *) big);
		big++;
		idx++;
	}
	return (NULL);
}
