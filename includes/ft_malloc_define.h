/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_define.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 03:58:53 by tsedigi           #+#    #+#             */
/*   Updated: 2017/12/13 03:58:57 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_DEFINE_H
# define FT_MALLOC_DEFINE_H

# include "ft_malloc_func.h"

/*
** Environement variables used for malloc
**
** MallocGuards 		;
**		If set add a guard page before and after each large block.
**		size of the guard can be modified with GD_LG_PR and GD_LG_PO.
** MallocNoGuardPre 	;
**		If set, do not add a guard page before large blocks,
** 		even if the MallocGuards environment variable is set.
** MallocNoGuardPos 	;
** 		If set, do not add a guard page after large blocks,
** 		even if the MallocGuards environment variable is set.
** MallocFile= ...		;
**		Create/append messages to the given file path '...' instead of writing
** 		to the standard error.
** MallocScrib			;
**		If set, fill memory that has been allocated with 0xaa bytes.
**		Also if set, fill memory that has been deallocated with 0x55 bytes.
**		Value can be modified with MA_FILL and FREE_FILL.
** MallocErrAbort		;
**		If set, causes abort(3) to be called if an error was encountered in
**		malloc(3) or free(3).
** MallocSoftLimAbrt	;
**		If MallocErrAbort is set, cause any allocation size ahead of
**		soft limit defined by getrlimit() to abort.
** MallocHardLimAbrt	;
**		If MallocErrAbort is set, cause any allocation size ahead of
**		hard limit defined by getrlimit() to abort.
** MallocHist			;
**		If set every call off malloc free or realloc will be saved,
**		a call of show_alloc_mem_ex(types, SHOW_HIST | ...) will print it.
** MallocHistFile= ...	;
**		If MallocHist is set, will create a file with the O_TRUNC flag
**		to print the current history to the path '...' on a
** 		show_alloc_mem_ex() with SHOW_HIST call.
*/

# define BLKS_PAGE				100
# define MA_FILL				0xaa
# define FREE_FILL				0x55
# define GD_LG_PR				(getpagesize())
# define GD_LG_PO				(getpagesize())
/*
**	MIN_TINY_SIZE can be modified, must be a multiple of 8 and <= 64
*/
# define MIN_TINY_SIZE			16

/*
** Show_alloc_mem_ex(type, options)
**			Types
*/
# define TINY_TYPE				1
# define SMALL_TYPE				2
# define LARGE_TYPE				4
# define ALL_TYPE				8
/*
**			Options
*/
# define SHOW_HIST				1
/*
** This option will print an history off every malloc free and realloc calls
** Works only if the MallocHist environ var is set.
*/
# define SHOW_MEM 				2
/*
** This option will print the state off memory,
** for any page types specified.
*/
# define DUMP_MEM				16
/*
** This option is only available with SHOW_MEM,
** it Dump the memory in hex form, and human readable form.
*/
# define SHOW_COLOR				8
/*
** Simply color for better visualisation.
*/
# define SHOW_FRAG				4
/*
** Self debug option.
*/

# define T_ALLOC_BLK			32
# define S_ALLOC_BLK			8
# define DEFAULT_FD				get_malloc_env(NULL)->fd
# define MIN_SMALL_SZ			get_malloc_env(NULL)->min_small
# define MAX_TINY				MIN_TINY_SIZE * T_ALLOC_BLK
# define MAX_SMALL				MIN_SMALL_SZ * S_ALLOC_BLK
# define SZ_OF_TO_B(x)			(sizeof(x) * 8)
# define ASSIGN					1
# define SUPRESS				0
# define MEM_T_SZ				(BLKS_PAGE * MAX_TINY)
# define MEM_S_SZ				(BLKS_PAGE * MAX_SMALL)
# define PRE_GUARD				1
# define POST_GUARD				2
# define MA_SCRIB				4
# define MA_ABORT				8
# define MA_SOFTLIM				16
# define MA_HARDLIM				32
# define MA_HIST				64
# define ASSIGN_UBIT(x)			((1 << x))
# define TINY_P		1
# define SMALL_P	2
# define LARGE_P	3
# define MALLOC_TYPE			1
# define FREE_TYPE				2
# define REALLOC_TYPE			4
# define MMAP_F		(PROT_READ | PROT_WRITE)
# define MMAP_O		(MAP_ANONYMOUS | MAP_PRIVATE)

/*
** equal to void * 2 for prev and next, 8 for type (struct t_alloc_page)
*/
# define SZ_G_HD	((SZ_OF_TO_B(void *) * 2) + 8)

/*
** Size Tiny header
** Size tiny Page
*/
# define SZ_THD(x)	mod_pg(SZ_OF_TO_B(t_tiny_head) * BLKS_PAGE + SZ_G_HD, x)
# define SZ_T_P	mod_pg(MIN_TINY_SIZE * T_ALLOC_BLK * BLKS_PAGE, 0) + SZ_THD(0)

/*
** Size Small header
** Size Small page
*/
# define SZ_SHD(x)	mod_pg(SZ_OF_TO_B(t_small_head) * BLKS_PAGE + SZ_G_HD, x)
# define SZ_S_P	mod_pg(MIN_SMALL_SZ * S_ALLOC_BLK * BLKS_PAGE, 0) + SZ_SHD(0)

/*
** Size Large header
*/
# define SZ_LHD 		mod_pg(SZ_OF_TO_B(t_large_head) + SZ_G_HD, 0)

/*
** Memory address
*/
# define ADR_M_T(p)			(p + SZ_THD(0))
# define ADR_M_S(p)			(p + SZ_SHD(0))
# define CHECK_GUARD(opt)	(opt & PRE_GUARD ? GD_LG_PR : 0)
# define ADR_M_L(p, opt)	(p + SZ_LHD + CHECK_GUARD(opt))

/*
** Headers offset Tiny and Small
*/
# define HEAD_OFF_T(p, o) 	(p + (o * SZ_OF_TO_B(t_tiny_head)))
# define HEAD_OFF_S(p, o) 	(p + (o * SZ_OF_TO_B(t_small_head)))

/*
** Tiny memory addr, offset block, offset fragmentation
*/
# define TME_O_F(mem, off, fg)	(mem + (MAX_TINY * off) + fg * MIN_TINY_SIZE)
/*
** Small memory addr, offset block, offset fragmentation
*/
# define SME_O_F(mem, off, fg)	(mem + (MAX_SMALL * off) + fg * MIN_SMALL_SZ)

# define BG_YELLOW					"\e[43m"
# define BG_RED						"\e[41m"
# define BG_GREEN					"\e[42m"
# define BG_BLUE					"\e[44m"
# define BG_MAGENT					"\e[45m"
# define BG_CYAN					"\e[46m"
# define BG_WHITE					"\e[47m"
# define BG_BLACK					"\e[40m"
# define RESET						"\033[0m"

# define YELLOW_H					"\e[33m"
# define RED_H						"\e[31m"
# define GREEN_H					"\e[32m"
# define BLUE_H						"\e[34m"
# define MAGENT_H					"\e[35m"
# define CYAN_H						"\e[36m"
# define WHITE_H					"\e[37m"
# define BLACK_H					"\e[30m"

#endif
