# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eerika <eerika@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/17 16:22:18 by eerika            #+#    #+#              #
#    Updated: 2021/08/17 16:22:19 by eerika           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc -g

HEADDIR	=	includes

CFLAGS	=	-I$(HEADDIR) -Wall -Wextra -Werror

SRC		=	philo.c \
			ft_atoi.c \
			init.c \
			threads.c \
			utils.c

OBJ 	= $(SRC:.c=.o)

NAME	=	philo

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $^

$(LIBDIR)/%.o:$(HEADDIR)/%.h

$(LIBDIR)/%.o:	%.c
	$(CC) -o $@ -c $<

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean