/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez-a <bperez-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 09:30:23 by bperez-a          #+#    #+#             */
/*   Updated: 2024/05/27 10:04:54 by bperez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_copy_array(char **array)
{
	int		len;
	char	**new_array;
	int		i;

	len = 0;
	i = 0;
	if (array)
	{
		while (array[len])
			len++;
	}
	new_array = (char **)malloc(sizeof(char *) * (len + 1));
	while (i < len)
	{
		new_array[i] = ft_strdup(array[i]);
		i++;
	}
	new_array[len] = NULL;
	return (new_array);
}
