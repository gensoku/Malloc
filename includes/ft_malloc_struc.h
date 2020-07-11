/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_struc.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 03:58:44 by tsedigi           #+#    #+#             */
/*   Updated: 2017/12/13 03:58:45 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_STRUC_H
# define FT_MALLOC_STRUC_H

# include <stdio.h>
# include <sys/mman.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/resource.h>
# include <fcntl.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct		s_ma_stack
{
	void			*rien;
}					t_ma_stack;

typedef struct		s_ma_hist
{
	char				type;
	void				*ret;
	size_t				size;
	void				*ptr;
	struct s_ma_hist	*next;
}					t_ma_hist;

typedef struct		s_tiny_head
{
	unsigned int	heads;
	unsigned int	mem;
	unsigned short	size[32];
	unsigned short	max_empty;
}					t_tiny_head;

typedef	struct		s_small_head
{
	unsigned char	heads;
	unsigned char	mem;
	unsigned short	size[8];
	unsigned short	max_empty;
}					t_small_head;

typedef	struct		s_large_head
{
	size_t			size;
}					t_large_head;

typedef	struct		s_alloc_page
{
	void			*prev;
	void			*next;
	char			type;
	void			*headers;
	void			*mem;
}					t_alloc_page;

typedef struct		s_rea_s
{
	char			found;
	char			type;
	char			blok;
	char			frag;
	char			err;
	t_alloc_page	*page;
}					t_rea_s;

typedef	struct		s_malloc_env
{
	t_alloc_page	*tinys;
	t_alloc_page	*smalls;
	t_alloc_page	*larges;
	size_t			min_small;
	size_t			max_tiny;
	size_t			max_small;
	char			opt_flags;
	struct rlimit	max;
	char			is_set;
	int				fd;
	int				hist_fd;
	t_ma_hist		*history;
	t_ma_hist		*last_hist;
}					t_malloc_env;

#endif
