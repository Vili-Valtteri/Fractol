# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/04 18:25:17 by raho              #+#    #+#              #
#    Updated: 2022/06/15 09:53:21 by vlaine           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
CC = gcc
LIB = libft/libft.a
DSYM = fractol.dSYM
INCLUDE = libft/
LIBMLX = libmlx.dylib
CFLAGS = -I $(INCLUDE) -Wall -Wextra -Werror
SRCS = main.c handle_file.c exit_program.c open_window.c inputs.c\
mlx_window_loop.c fractol.c fractals.c fractol_helper.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIB) $(LIBMLX) $(OBJS)
	$(CC) $(LIB) $(LIBMLX) $(OBJS) -o $(NAME) $(CFLAGS) -pthread

$(LIB):
	make -C libft

$(LIBMLX):
	make -C  minilibx
	mv minilibx/libmlx.dylib libmlx.dylib

clean:
	make -C libft clean
	make -C minilibx clean
	rm -rf $(DSYM)
	rm -f $(OBJS)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)
	rm -f $(LIBMLX)

re: fclean all

.PHONY: all clean fclean re
