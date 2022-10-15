# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bfiguet <bfiguet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/22 16:26:53 by bfiguet           #+#    #+#              #
#    Updated: 2022/10/06 15:32:58 by bfiguet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL = /bin/bash

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
CFLAGS += -Iinc/
#ifeq ($(DEBUG_), 1)
#CFLAGS += -g3 -fsanitize=address
#else \
ifeq ($(DEBUG), 2)
CFLAGS += -g -fsanitize=thread
#endif

RM = rm -rf
OBJ_DIR = obj/

SRCS = $(addsuffix .c, \
			$(addprefix src/,	\
			actions \
			init \
			main \
			utils \
			))	\

OBJS = $(SRCS:src/%.c=obj/%.o)

all: $(NAME)

obj/%.o:src/%.c Makefile
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

norm:
	-norminette $(SRCS)
	-norminette inc

.PHONY: all clean fclean re norm
