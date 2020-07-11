/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_larges.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 02:08:26 by tsedigi           #+#    #+#             */
/*   Updated: 2017/12/22 02:08:27 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void		*realloc_larges(t_rea_s *rea, void *ptr, size_t size)
{
	void	*ret;
	void	*mem;
	size_t	to_cpy;

	if (rea->err || !rea->page)
	{
		if (rea->err == REA_NOT_ALLOCATED)
		{
			if (get_malloc_env(NULL)->opt_flags & MA_ABORT)
				abort_msg("Ptr beeing reallocated was not allocated, abort.");
			return (NULL);
		}
		return (call_malloc(size));
	}
	ret = call_malloc(size);
	mem = rea->page->mem;
	to_cpy = ((t_large_head *)rea->page->headers)->size < size ?
		((t_large_head *)rea->page->headers)->size : size;
	ma_mem_cpy(mem, ret, to_cpy);
	call_free(ptr);
	return (ret);
}
