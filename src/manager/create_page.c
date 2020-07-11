/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_page.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 04:33:18 by tsedigi           #+#    #+#             */
/*   Updated: 2017/12/13 04:33:21 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void			init_header(void *head, char type)
{
	char			i;
	void			*addr;
	t_tiny_head		*th;
	t_small_head	*sh;
	size_t			to_set;

	addr = head;
	i = -1;
	if (!head)
		return ;
	th = (t_tiny_head *)head;
	sh = (t_small_head *)head;
	to_set = type == TINY_P ? T_ALLOC_BLK * MIN_TINY_SIZE :
		S_ALLOC_BLK * get_malloc_env(NULL)->min_small;
	while (i++ < BLKS_PAGE)
	{
		if (type == TINY_P)
			th->max_empty = to_set;
		else
			sh->max_empty = to_set;
		if (type == TINY_P)
			th++;
		else
			sh++;
	}
}

static void			*create_large_p(size_t size)
{
	t_alloc_page	*ret;
	t_large_head	*h;
	size_t			val;

	val = size_large_page(size, get_malloc_env(NULL)->opt_flags);
	ret = (t_alloc_page *)mmap(NULL, val, MMAP_F, MMAP_O, -1, 0);
	if (ret == MAP_FAILED)
	{
		if (get_malloc_env(NULL)->opt_flags & MA_ABORT)
			abort_msg("Mmap call failed, abort.");
		return (NULL);
	}
	ret->headers = (void *)ret + SZ_G_HD;
	h = (t_large_head *)ret->headers;
	h->size = size;
	ret->mem = ADR_M_L((void *)ret, get_malloc_env(NULL)->opt_flags);
	ret->type = LARGE_P;
	ret->next = NULL;
	ret->prev = NULL;
	return ((void *)ret);
}

static void			*create_small_p(void)
{
	t_alloc_page	*ret;
	size_t			size;

	size = SZ_S_P;
	ret = (t_alloc_page *)mmap(NULL, size, MMAP_F, MMAP_O, -1, 0);
	if (ret == MAP_FAILED)
	{
		if (get_malloc_env(NULL)->opt_flags & MA_ABORT)
			abort_msg("Mmap call failed, abort.");
		return (NULL);
	}
	ret->headers = (void *)ret + SZ_G_HD;
	ret->mem = ADR_M_S((void *)ret);
	ret->type = SMALL_P;
	ret->next = NULL;
	ret->prev = NULL;
	init_header(ret->headers, SMALL_P);
	return ((void *)ret);
}

static void			*create_tiny_p(void)
{
	t_alloc_page	*ret;
	size_t			size;

	size = SZ_T_P;
	ret = (t_alloc_page *)mmap(NULL, size, MMAP_F, MMAP_O, -1, 0);
	if (ret == MAP_FAILED)
	{
		if (get_malloc_env(NULL)->opt_flags & MA_ABORT)
			abort_msg("Mmap call failed, abort.");
		return (NULL);
	}
	ret->headers = (void *)ret + SZ_G_HD;
	ret->mem = ADR_M_T((void *)ret);
	ret->type = TINY_P;
	ret->next = NULL;
	ret->prev = NULL;
	init_header(ret->headers, TINY_P);
	return ((void *)ret);
}

void				*create_page(char type, size_t size)
{
	if (type == TINY_P)
		return (create_tiny_p());
	else if (type == SMALL_P)
		return (create_small_p());
	else if (type == LARGE_P && size)
		return (create_large_p(size));
	return (NULL);
}
