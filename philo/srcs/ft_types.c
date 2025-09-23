/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_types.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 01:07:04 by marvin            #+#    #+#             */
/*   Updated: 2025/09/21 01:31:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Checks  for white-space characters.
The white-space characters include space, form-feed ('\f'), newline ('\n'),
carriage return ('\r'), horizontal tab ('\t'), and vertical tab ('\v').
Returns 1 if True, 0 if False.
*/
int	ft_isspace(char c)
{
	if (c == ' '
		|| c == '\t'
		|| c == '\r'
		|| c == '\n'
		|| c == '\f'
		|| c == '\v'
	)
		return (1);
	return (0);
}

int	ft_isdigit(char c)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	if ('0' <= uc && uc <= '9')
		return (1);
	return (0);
}

int	ft_is_alphasign(const char *str)
{
	const char	*p;

	if (str == NULL)
		return (0);
	p = str;
	if (ft_isdigit(*p) == 1 || *p == '-' || *p == '+')
		p++;
	while (*p != '\0')
	{
		if (ft_isdigit(*p) == 0)
			return (0);
		p++;
	}
	return (1);
}
