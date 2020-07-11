/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ma_fillmem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 04:01:10 by tsedigi           #+#    #+#             */
/*   Updated: 2018/01/22 04:01:12 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void			ma_fillmem(void *ptr, size_t size, char val)
{
	char		*set;
	size_t		i;

	if (!ptr || !size)
		return ;
	i = 0;
	set = (char *)ptr;
	while (i < size)
	{
		set[i] = val;
		i++;
	}
}
