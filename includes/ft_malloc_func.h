/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_func.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 03:58:37 by tsedigi           #+#    #+#             */
/*   Updated: 2017/12/13 03:58:38 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_FUNC_H
# define FT_MALLOC_FUNC_H

# include "ft_malloc_struc.h"

void				free(void *ptr);
void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);
void				show_alloc_mem();

/*
** Manager
*/
void				*create_page(char type, size_t size);
size_t				mod_pg(size_t size, char ret_add);
size_t				size_large_page(size_t size, char opt_flags);

/*
**	Single
*/
t_malloc_env		*get_malloc_env(t_malloc_env *env);

/*
** Init
*/
void				init_malloc_env(t_malloc_env *env);

/*
** Lib tool
*/
void				ma_putendl(char *str);
void				ma_putstr(char *str);
void				ma_putchar(char c);
void				ma_putnbr(int n);
void				ma_putszt(size_t i);
size_t				ma_strlen(char *str);
void				ma_print_hex(int i);
void				ma_putaddr(void *addr, char *msg);
void				ma_print_u_bit(unsigned int c, char type, char opts);
void				ma_bzero(void *s1, size_t n);
void				ma_mem_cpy(void *src, void *dest, size_t size);
char				*ma_strchr(const char *s, int c);
int					ma_strcmp(const char *s1, const char *s2);
void				ma_fillmem(void *ptr, size_t size, char val);
void				ma_putcolor(char *color, char *msg, void *addr, size_t x);
void				ma_dump_mem(void *addr, size_t size, char opts);
mode_t				ma_get_rights(void);

/*
** Malloc
*/
void				*call_malloc(size_t size);
void				*tiny_malloc(size_t size);
void				*small_malloc(size_t size);
void				refresh_empty_t(t_tiny_head *h);
void				refresh_empty_s(t_small_head *h);
char				check_umem(unsigned long mem, char i, char scale);
void				assign_mem_s(unsigned char *mem,
	char i, char scale, char opt);
void				assign_mem_t(unsigned int *mem,
	char i, char scale, char opt);
char				get_scale(size_t size, char type);

/*
** Free
*/
void				call_free(void *ptr);
char				free_tiny(void *ptr, t_alloc_page *p);
void				mun_tiny(t_alloc_page *p);
char				free_small(void *ptr, t_alloc_page *p);
void				mun_small(t_alloc_page *p);
char				free_large(t_alloc_page *p);

/*
** Realloc
*/
void				*call_realloc(void *ptr, size_t size);
void				get_infos_rea_t(t_alloc_page *p, void *ptr, t_rea_s *ret);
void				*realloc_tinys(t_rea_s *rea, void *ptr, size_t size);
void				get_infos_rea_s(t_alloc_page *p, void *ptr, t_rea_s *ret);
void				*realloc_smalls(t_rea_s *rea, void *ptr, size_t size);
void				*realloc_larges(t_rea_s *rea, void *ptr, size_t size);

/*
** Environ
*/
char				env_var_is_set(char *value, char **array);

/*
** History
*/
void				push_ma_hist(void *ret, size_t size, void *ptr, char type);

/*
** Debug
*/
void				print_head_mem(unsigned int m,
	unsigned int h, char type, char opts);
void				abort_msg(char *msg);

/*
** Show_alloc
*/
void				show_larges(void *p);
void				show_alloc_mem_ex(char types, char opts);
void				ma_show_memory(char types, char opts);
void				show_ex_tiny(t_alloc_page *p, char opts);
void				show_ex_small(t_alloc_page *p, char opts);
void				show_ex_large(t_alloc_page *p, char opts);

/*
** Mutex
*/
pthread_mutex_t		*get_mutex(void);
#endif
