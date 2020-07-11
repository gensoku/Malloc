/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ma_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 03:34:30 by tsedigi           #+#    #+#             */
/*   Updated: 2017/12/14 03:34:31 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	ma_bzero(void *s1, size_t n)
{
	size_t			i;
	unsigned char	*temp;

	i = 0;
	temp = (unsigned char *)s1;
	while (i < n)
	{
		temp[i] = 0;
		i++;
	}
}
