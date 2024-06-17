/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrs_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez-a <bperez-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:14:23 by eagranat          #+#    #+#             */
/*   Updated: 2024/05/27 10:07:36 by bperez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstrs_fd(char *before, char *str, char *after, int fd)
{
	if (before)
		write(fd, before, ft_strlen(before));
	if (str)
		write(fd, str, ft_strlen(str));
	if (after)
		write(fd, after, ft_strlen(after));
	return (1);
}
