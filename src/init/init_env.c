/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_malloc_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 04:13:57 by tsedigi           #+#    #+#             */
/*   Updated: 2017/12/14 04:13:58 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void			check_for_hist_file(t_malloc_env *env,
	char **environ, char *chr, size_t i)
{
	int				fd;

	while (environ[i])
	{
		chr = ma_strchr(environ[i], '=');
		if (chr)
		{
			chr[0] = 0;
			if (!ma_strcmp(environ[i], "MallocHistFile"))
			{
				if (ma_strlen(&chr[1]))
				{
					fd = open(&chr[1], O_CREAT | O_TRUNC | O_WRONLY,
						ma_get_rights());
					env->hist_fd = fd != -1 ? fd : 1;
					chr[0] = '=';
					break ;
				}
			}
			chr[0] = '=';
		}
		i++;
	}
}

static void			check_for_file_log(t_malloc_env *env,
	char **environ, char *chr, size_t i)
{
	int				fd;

	while (environ[i])
	{
		chr = ma_strchr(environ[i], '=');
		if (chr)
		{
			chr[0] = 0;
			if (!ma_strcmp(environ[i], "MallocFile"))
			{
				if (ma_strlen(&chr[1]))
				{
					fd = open(&chr[1],
						O_CREAT | O_APPEND | O_WRONLY, ma_get_rights());
					env->fd = fd != -1 ? fd : 1;
					chr[0] = '=';
					break ;
				}
			}
			chr[0] = '=';
		}
		i++;
	}
}

static void			set_env_vars(t_malloc_env *env, char **environ)
{
	if (env_var_is_set("MallocGuards", environ))
	{
		if (!(env_var_is_set("MallocNoGuardPre", environ)))
			env->opt_flags |= PRE_GUARD;
		if (!(env_var_is_set("MallocNoGuardPos", environ)))
			env->opt_flags |= POST_GUARD;
	}
	if (env_var_is_set("MallocFile", environ))
		check_for_file_log(env, environ, NULL, 0);
	if (env_var_is_set("MallocScrib", environ))
		env->opt_flags |= MA_SCRIB;
	if (env_var_is_set("MallocErrAbort", environ))
	{
		env->opt_flags |= MA_ABORT;
		if (env_var_is_set("MallocSoftLimAbrt", environ))
			env->opt_flags |= MA_SOFTLIM;
		if (env_var_is_set("MallocHardLimAbrt", environ))
			env->opt_flags |= MA_HARDLIM;
	}
	if (env_var_is_set("MallocHist", environ))
	{
		env->opt_flags |= MA_HIST;
		if (env_var_is_set("MallocHistFile", environ))
			check_for_hist_file(env, environ, NULL, 0);
	}
}

static void			init_malloc_env_pages(t_malloc_env *env)
{
	get_malloc_env(env);
	env->tinys = create_page(TINY_P, 0);
	env->smalls = create_page(SMALL_P, 0);
	env->larges = NULL;
	env->history = NULL;
	env->last_hist = NULL;
	get_malloc_env(env);
}

void				init_malloc_env(t_malloc_env *env)
{
	extern char		**environ;

	env->is_set = 1;
	env->max_tiny = MAX_TINY;
	env->min_small = env->max_tiny * 2;
	env->max_small = env->min_small * S_ALLOC_BLK;
	env->opt_flags = 0;
	env->fd = 1;
	env->hist_fd = 1;
	set_env_vars(env, environ);
	if (getrlimit(RLIMIT_DATA, &env->max))
	{
		if (env->opt_flags & MA_ABORT)
			abort_msg("getrlimit() failed cannot specifie max limit");
		env->max.rlim_cur = 0;
		env->max.rlim_max = 0;
	}
	else
	{
		env->max.rlim_cur -= (SZ_LHD + GD_LG_PR + GD_LG_PO);
		env->max.rlim_max -= (SZ_LHD + GD_LG_PO + GD_LG_PR);
	}
	init_malloc_env_pages(env);
}
