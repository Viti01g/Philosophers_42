# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: VR <VR@student.42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/11 13:01:34 by vruiz-go          #+#    #+#              #
#    Updated: 2023/10/14 19:53:53 by VR               ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc
CFLAGS = -Wall -Werror -Wextra #-g3 -fsanitize=thread

SRCS = main.c \
			error.c \
			utils.c \
			parse.c \
			spaghetti.c

OBJS = $(SRCS:.c=.o)

RM = rm -f

all: $(NAME)
	
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo $(NAME)": ready to be executed"

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
