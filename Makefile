# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgleason <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/14 22:43:19 by cgleason          #+#    #+#              #
#    Updated: 2018/08/18 20:28:13 by cgleason         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

CC = @gcc

CFLAGS = -Wall -Wextra -Werror -o $(NAME)

SRC = main.c fdata_comparators.c dirdata_comparators.c helpers.c vec_heap.c \
	parsers.c shape_directories.c freers.c

OBJS = $(SRC:.c=.o)

LIB = libft/libft.a

$(NAME): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIB)

$(LIB):
	@make -C libft

.PHONY: clean fclean all re

clean:
	@rm -f $(OBJS)
	@make clean -C libft

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft

all: $(NAME)

re: fclean all
