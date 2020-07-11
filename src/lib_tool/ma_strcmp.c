/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ma_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 10:01:32 by tsedigi           #+#    #+#             */
/*   Updated: 2018/01/19 10:01:33 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

int		ma_strcmp(const char *s1, const char *s2)
{
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	while (*a && *b && *a == *b)
	{
		a++;
		b++;
	}
	return (*a - *b);
}
