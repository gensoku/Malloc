/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_is_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 08:39:40 by tsedigi           #+#    #+#             */
/*   Updated: 2018/01/19 08:39:41 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

char		env_var_is_set(char *value, char **array)
{
	size_t	i;
	char	*chr;
	char	ret;

	i = 0;
	ret = 0;
	chr = NULL;
	if (!array || !value)
		return (0);
	while (array[i])
	{
		chr = ma_strchr(array[i], '=');
		if (chr)
		{
			chr[0] = 0;
			if (!ma_strcmp(array[i], value))
				ret = 1;
			chr[0] = '=';
			if (ret)
				break ;
		}
		i++;
	}
	return (ret);
}
