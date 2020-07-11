/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_large_page.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 02:47:50 by tsedigi           #+#    #+#             */
/*   Updated: 2017/12/14 02:47:53 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

size_t			size_large_page(size_t size, char opt_flags)
{
	size_t		ret;
	size_t		add;

	ret = SZ_LHD;
	add = size;
	add += opt_flags & PRE_GUARD ? GD_LG_PR : 0;
	add += opt_flags & POST_GUARD ? GD_LG_PO : 0;
	add = mod_pg(add, 0);
	ret = mod_pg(ret + add, 0);
	return (ret);
}
