/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putils2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 05:57:40 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/10/23 05:59:12 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	ft_min(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
