# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bfiguet <bfiguet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/22 16:26:53 by bfiguet           #+#    #+#              #
#    Updated: 2022/11/02 13:03:32 by bfiguet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#SHELL	= /bin/bash

NAME	= philo
HEADER	= inc/philo.h
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g -fsanitize=thread
LFLAGS	= -pthread
#CFLAGS += -Iinc/
#CFLAGS += -g3 -fsanitize=address
#valgrind --tool=helgrind

RM = rm -rf
OBJ_DIR = obj/

SRCS = $(addsuffix .c, \
			$(addprefix src/,	\
			actions \
			exit \
			main \
			init \
			utils \
			))	\

OBJS = $(SRCS:src/%.c=obj/%.o)

obj/%.o:src/%.c Makefile
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(LFLAGS) $(SRCS) -o $@
	@echo "\033[0;32mRUN :\033[0m \033[1;32m./philo number_of_philosophers time_to_die \
	time_to_eat time_to_sleep (number_of_times_each_philosophers_must_eat) \033[0m"

clean:
	$(RM) $(OBJ_DIR)
	@echo "\033[1;33m Object files deleted \033[0m"

fclean: clean
	$(RM) $(NAME)
	@echo "\033[1;33m Executable files deleted \033[0m"

re: fclean all

.PHONY: all clean fclean re
