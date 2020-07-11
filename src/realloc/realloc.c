/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 00:44:10 by tsedigi           #+#    #+#             */
/*   Updated: 2017/12/22 00:44:14 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static t_rea_s		check_rea_larges(void *ptr)
{
	t_rea_s			ret;
	t_alloc_page	*p;
	void			*mem;

	ma_bzero(&ret, sizeof(t_rea_s));
	p = get_malloc_env(NULL)->larges;
	while (p)
	{
		mem = p->mem;
		if (ptr == mem)
		{
			ret.found = 1;
			ret.page = p;
			ret.type = LARGE_P;
			return (ret);
		}
		if (ptr >= mem && ptr <= mem + ((t_large_head *)p->headers)->size)
		{
			ret.found = 1;
			ret.err = REA_NOT_ALLOCATED;
			return (ret);
		}
		p = p->next;
	}
	return (ret);
}

static t_rea_s		check_rea_smalls(void *ptr)
{
	t_rea_s			ret;
	t_alloc_page	*p;
	void			*mem;

	ma_bzero(&ret, sizeof(t_rea_s));
	p = get_malloc_env(NULL)->smalls;
	while (p)
	{
		mem = p->mem;
		if (ptr >= mem && ptr <= mem + MEM_S_SZ)
		{
			ret.found = 1;
			ret.page = p;
			ret.type = SMALL_P;
			get_infos_rea_s(p, ptr, &ret);
			return (ret);
		}
		p = p->next;
	}
	return (ret);
}

static t_rea_s		check_rea_tinys(void *ptr)
{
	t_rea_s			ret;
	t_alloc_page	*p;
	void			*mem;

	ma_bzero(&ret, sizeof(t_rea_s));
	p = get_malloc_env(NULL)->tinys;
	while (p)
	{
		mem = p->mem;
		if (ptr >= mem && ptr <= mem + MEM_T_SZ)
		{
			ret.found = 1;
			ret.page = p;
			ret.type = TINY_P;
			get_infos_rea_t(p, ptr, &ret);
			return (ret);
		}
		p = p->next;
	}
	return (ret);
}

void				*call_realloc(void *ptr, size_t size)
{
	void			*ret;
	t_rea_s			check;

	if (!ptr)
	{
		ret = call_malloc(size);
		return (ret);
	}
	else if (!size)
	{
		call_free(ptr);
		ret = call_malloc(MIN_TINY_SIZE);
		return (ret);
	}
	else
	{
		if ((check = check_rea_tinys(ptr)).found)
			return (realloc_tinys(&check, ptr, size));
		else if ((check = check_rea_smalls(ptr)).found)
			return (realloc_smalls(&check, ptr, size));
		else if ((check = check_rea_larges(ptr)).found)
			return (realloc_larges(&check, ptr, size));
	}
	ret = call_malloc(size);
	return (ret);
}

void				*realloc(void *ptr, size_t size)
{
	void			*ret;
	t_malloc_env	env;

	env = *(get_malloc_env(NULL));
	if (!env.is_set)
		init_malloc_env(&env);
	if (pthread_mutex_lock(get_mutex()))
	{
		if (env.opt_flags & MA_ABORT)
			abort_msg("Error while locking mutex, abort.");
		return (NULL);
	}
	ret = call_realloc(ptr, size);
	if (env.opt_flags & MA_HIST)
		push_ma_hist(ret, size, ptr, REALLOC_TYPE);
	if (pthread_mutex_unlock(get_mutex()) && env.opt_flags & MA_ABORT)
		abort_msg("Error while unlocking mutex, abort.");
	return (ret);
}
