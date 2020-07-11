/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 04:12:19 by tsedigi           #+#    #+#             */
/*   Updated: 2017/12/14 04:12:20 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void			add_l_p(void *to_add)
{
	t_malloc_env	env;
	t_alloc_page	*p;

	env = *(get_malloc_env(NULL));
	p = env.larges;
	if (!p)
	{
		env.larges = (t_alloc_page *)to_add;
		get_malloc_env(&env);
	}
	else
	{
		while (p && p->next)
			p = p->next;
		p->next = to_add;
		((t_alloc_page *)to_add)->prev = p;
	}
}

static int			check_large_size(t_malloc_env *env, size_t size)
{
	if (!env || !size)
		return (0);
	if (env->max.rlim_cur != 0 && env->max.rlim_max != 0)
	{
		if (size < env->max.rlim_max)
		{
			if (size > env->max.rlim_cur)
			{
				if (get_malloc_env(NULL)->opt_flags & MA_SOFTLIM)
					abort_msg("Size is ahead of soft limit, abort.");
				return (1);
			}
			return (1);
		}
		if (get_malloc_env(NULL)->opt_flags & MA_HARDLIM)
			abort_msg("Size is ahead of hard limit, abort.");
		return (0);
	}
	return (1);
}

void				*call_malloc(size_t size)
{
	t_malloc_env	env;
	void			*ret;
	t_alloc_page	*p;

	env = *(get_malloc_env(NULL));
	ret = NULL;
	if (!size)
		return (NULL);
	if (size <= env.max_tiny)
		ret = tiny_malloc(size);
	else if (size <= env.max_small)
		ret = small_malloc(size);
	else if (check_large_size(&env, size))
	{
		ret = create_page(LARGE_P, size);
		if (ret)
			add_l_p(ret);
		p = (t_alloc_page *)ret;
		ret = p->mem;
	}
	if (ret && env.opt_flags & MA_SCRIB)
		ma_fillmem(ret, size, MA_FILL);
	return (ret);
}

void				*malloc(size_t size)
{
	void			*ret;
	t_malloc_env	env;

	env = *(get_malloc_env(NULL));
	ret = NULL;
	if (!size)
		return (NULL);
	if (!env.is_set)
		init_malloc_env(&env);
	if (pthread_mutex_lock(get_mutex()))
	{
		if (env.opt_flags & MA_ABORT)
			abort_msg("Error while locking mutex, abort.");
		return (NULL);
	}
	ret = call_malloc(size);
	if (env.opt_flags & MA_HIST)
		push_ma_hist(ret, size, NULL, MALLOC_TYPE);
	if (pthread_mutex_unlock(get_mutex()) && env.opt_flags & MA_ABORT)
		abort_msg("Error while unlocking mutex, abort.");
	return (ret);
}
