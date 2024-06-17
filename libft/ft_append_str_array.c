/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_str_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez-a <bperez-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:02:27 by bperez-a          #+#    #+#             */
/*   Updated: 2024/05/29 12:04:57 by bperez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_append_str_array(char ***array, char *str)
{
	int		len;
	char	**new_array;
	int		i;

	len = 0;
	i = 0;
	if (**array)
	{
		while ((*array)[len])
			len++;
	}
	new_array = (char **)malloc(sizeof(char *) * (len + 2));
	while (i < len)
	{
		new_array[i] = (*array)[i];
		(*array)[i++] = NULL;
	}
	new_array[len] = ft_strdup(str);
	new_array[len + 1] = NULL;
	while (len >= 0)
		free((*array)[len--]);
	free(*array);
	*array = new_array;
}
