/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mun_tiny.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 05:36:23 by tsedigi           #+#    #+#             */
/*   Updated: 2017/12/20 05:36:24 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void		mun_tiny(t_alloc_page *p)
{
	size_t	size;
	int		ret;

	size = SZ_T_P;
	ret = munmap((void *)p, size);
	if (ret && get_malloc_env(NULL)->opt_flags & MA_ABORT)
		abort_msg("Error munmap call failed, abort.");
}

void		mun_small(t_alloc_page *p)
{
	size_t	size;
	int		ret;

	size = SZ_S_P;
	ret = munmap((void *)p, size);
	if (ret && get_malloc_env(NULL)->opt_flags & MA_ABORT)
		abort_msg("Error munmap call failed, abort.");
}
