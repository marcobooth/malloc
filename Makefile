#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbooth <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/03 15:16:31 by mbooth            #+#    #+#              #
#    Updated: 2017/12/03 15:21:54 by mbooth           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

INC = -I include -I libft/
LIB = -L $(LIBFT) -lft
LIBFT = 			libft

SRCS = srcs/malloc.c \
			 srcs/free.c \
			 srcs/utilities.c \
			 srcs/realloc.c \
			 srcs/show_alloc_mem.c \
			 srcs/bonus.c

OBJ = $(SRCS:.c=.o)

CC = gcc -Wall -Wextra -Werror -g

%.o: %.c
	$(CC) -o $@ -c $< $(INC)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT)
	$(CC) -shared -o $@ $(OBJ) $(LIB)
	@ln -sf $(NAME) libft_malloc.so

clean:
	make clean -C libft/
	@-/bin/rm -f $(OBJ)
	@echo "cleaned" $(NAME)

fclean: clean
	make fclean -C libft/
	@-/bin/rm -f $(NAME)
	@rm -f libft_malloc.so
	@echo "fcleaned" $(NAME)

re: fclean all
