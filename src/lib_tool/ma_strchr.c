/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ma_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 08:44:29 by tsedigi           #+#    #+#             */
/*   Updated: 2018/01/19 08:44:30 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

char	*ma_strchr(const char *s, int c)
{
	size_t	i;
	char	*temp;

	i = 0;
	temp = (char *)s;
	if (!s || !temp)
		return (NULL);
	while (temp[i])
	{
		if (temp[i] == c)
			return (&temp[i]);
		i++;
	}
	if (temp[i] == c)
		return (&temp[i]);
	return (NULL);
}
