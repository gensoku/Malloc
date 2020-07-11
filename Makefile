# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/25 07:23:30 by tsedigi           #+#    #+#              #
#    Updated: 2018/05/25 07:23:32 by tsedigi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif
#	Program output
NAME = libft_malloc_$(HOSTTYPE).so
LINK = libft_malloc.so

CC = gcc

CFLAGS = -Wall -Wextra -Werror 

LIB_OPTS = -shared -fPIC

ALL_CFLAGS = $(CFLAGS)

#	Ojects/Sources directories
INC_MALLOC = includes/
SRC_MALLOC = $(shell find src | grep "\.c$$" | sed "s/\.c$$//g")
INCLUDES += $(addprefix -iquote , $(INC_MALLOC))
INC_CHECK = $(shell find includes | grep "\.h$$")
SRCS += $(addsuffix .c, $(SRC_MALLOC))

#	Final OBJS
OBJS = $(SRCS:.c=.o)

#	Layout
VERBOSE = true

all: header $(NAME) footer

header:
	@echo "\033[33m[\033[4m$(NAME)\033[0m\033[33m] Compile\033[0m"

footer:
	@echo "\033[33m[\033[4m$(NAME)\033[0m\033[33m] Finished\033[0m"

$(NAME): $(INC_CHECK) $(OBJS)
ifeq ($(VERBOSE),true)
	@echo "\033[34m. Compile Final .\033[0m $(NAME)"
else
	@printf"\033[34m.\033[0m\n"
endif
	@$(CC) -shared -fPIC $(OBJS) -o $(NAME)

link:
	@$(RM) $(NAME) $(LINK)
	@ln -s $(NAME) $(LINK)		

%.o: %.c
ifeq ($(VERBOSE),true)
	@echo "\033[34m. Compile .\033[0m $<"
else
	@printf"\033[34m.\033[0m"
endif
	@$(CC) -c -fPIC $(ALL_CFLAGS) $(INCLUDES) -c $< -o $@
	@make link

clean:
	@echo -e "\033[33m[\033[4m$(NAME)\033[0m\033[33m] >>\033[0m \033[31mCLEAN all object files (*.o)\033[0m"
	@$(RM) $(OBJS) 

fclean: clean
	@echo -e "\033[33m[\033[4m$(NAME)\033[0m\033[33m] >>\033[0m \033[31mFCLEAN project binary ($(NAME))\033[0m"
	@$(RM) $(NAME) $(LINK)

re: fclean all
