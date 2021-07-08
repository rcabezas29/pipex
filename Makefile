# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/07 20:22:18 by rcabezas          #+#    #+#              #
#    Updated: 2021/07/08 11:06:26 by rcabezas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = gcc
CFLAGS = -Werror -Wextra -Wall

SRCS_PIPX = pipex.c path.c

PIPX_SRCS = $(addprefix srcs/, $(SRCS_PIPX))

OBJS_PIPX = $(PIPX_SRCS:.c=.o)

INCLUDES = includes

RM = rm -rf

LIBFT = libft

all : $(NAME)

$(NAME) : $(OBJS_PIPX)
	@make -C $(LIBFT)
	@$(CC) $(CFLAGS) -I$(INCLUDES) $(LIBFT)/libft.a $(OBJS_PIPX) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -I$(INCLUDES) -o $@ -c $<

clean :
	@$(RM) $(OBJS_PIPX)
	@make clean -C $(LIBFT)

fclean : clean
	@$(RM) $(NAME)
	@make fclean -C $(LIBFT)

re:				fclean all

.PHONY: 		all fclean clean re