/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 04:09:40 by tsedigi           #+#    #+#             */
/*   Updated: 2017/12/20 04:09:41 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static char			check_free_large(void *ptr)
{
	t_alloc_page	*p;
	void			*mem;

	p = get_malloc_env(NULL)->larges;
	while (p)
	{
		mem = p->mem;
		if (ptr == mem)
			return (free_large(p));
		if (ptr >= mem && ptr <= mem + ((t_large_head *)p->headers)->size)
		{
			if (get_malloc_env(NULL)->opt_flags & MA_ABORT)
				abort_msg("Ptr beeing freed was not allocated, abort.");
			return (0);
		}
		if (ptr >= (void *)p && ptr <= mem + ((t_large_head *)p->headers)->size)
		{
			if (get_malloc_env(NULL)->opt_flags & MA_ABORT)
				abort_msg("Ptr beeing freed was not allocated, abort.");
		}
		p = p->next;
	}
	return (0);
}

static char			check_free_small(void *ptr)
{
	t_alloc_page	*p;
	void			*mem;

	p = get_malloc_env(NULL)->smalls;
	while (p)
	{
		mem = p->mem;
		if (ptr >= mem && ptr <= mem + MEM_S_SZ)
			return (free_small(ptr, p));
		if (ptr >= (void *)p && ptr <= mem + MEM_T_SZ)
		{
			if (get_malloc_env(NULL)->opt_flags & MA_ABORT)
				abort_msg("Ptr beeing freed was not allocated, abort.");
		}
		p = p->next;
	}
	return (0);
}

static char			check_free_tiny(void *ptr)
{
	t_alloc_page	*p;
	void			*mem;

	p = get_malloc_env(NULL)->tinys;
	while (p)
	{
		mem = p->mem;
		if (ptr >= mem && ptr <= mem + MEM_T_SZ)
			return (free_tiny(ptr, p));
		if (ptr >= (void *)p && ptr <= mem + MEM_T_SZ)
		{
			if (get_malloc_env(NULL)->opt_flags & MA_ABORT)
				abort_msg("Ptr beeing freed was not allocated, abort.");
		}
		p = p->next;
	}
	return (0);
}

void				call_free(void *ptr)
{
	if (!ptr)
		return ;
	if (check_free_tiny(ptr))
		return ;
	if (check_free_small(ptr))
		return ;
	check_free_large(ptr);
}

void				free(void *ptr)
{
	t_malloc_env	env;

	env = *(get_malloc_env(NULL));
	if (!env.is_set)
		init_malloc_env(&env);
	if (pthread_mutex_lock(get_mutex()))
	{
		if (env.opt_flags & MA_ABORT)
			abort_msg("Error while locking mutex, abort.");
		return ;
	}
	call_free(ptr);
	if (env.opt_flags & MA_HIST)
		push_ma_hist(NULL, 0, ptr, FREE_TYPE);
	if (pthread_mutex_unlock(get_mutex()) && env.opt_flags & MA_ABORT)
		abort_msg("Error while unlocking mutex, abort.");
}
