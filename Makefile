# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kgolda <kgolda@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/11 21:15:13 by kgolda            #+#    #+#              #
#    Updated: 2022/01/28 19:13:11 by kgolda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS =	philo_main.c\
		philo_inits.c\
		philo_simulations.c\
		philo_utils.c\
		philo_watcher.c\
		destroy_thread_mutex.c

OBJ = $(SRCS:.c=.o)

HEADER = philo.h

CC = gcc

CFLAGS = -Wall -Werror -Wextra

RM = rm -f

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

rebonus: fclean

.PHONY: all clean fclean re
