/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_log_msg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 01:32:34 by marvin            #+#    #+#             */
/*   Updated: 2025/10/10 06:43:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*create_id_msg(int id, char *msg)
{
	char	*strid;
	char	*space_strid;
	char	*space_strid_space;
	char	*s3_msg;
	char	*s3_msgnl;

	strid = ft_itoa(id);
	if (strid == NULL)
		return (NULL);
	space_strid = ft_strjoin(" ", strid);
	if (space_strid == NULL)
		return (free_str_set_null(&strid), NULL);
	free_str_set_null(&strid);
	space_strid_space = ft_strjoin(space_strid, " ");
	if (space_strid_space == NULL)
		return (free_str_set_null(&space_strid), NULL);
	free_str_set_null(&space_strid);
	s3_msg = ft_strjoin(space_strid_space, msg);
	if (s3_msg == NULL)
		return (free_str_set_null(&space_strid_space), NULL);
	free_str_set_null(&space_strid_space);
	s3_msgnl = ft_strjoin(s3_msg, "\n");
	return (free_str_set_null(&s3_msg), s3_msgnl);
}
