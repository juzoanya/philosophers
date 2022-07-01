# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juzoanya <juzoanya@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/03 23:18:02 by juzoanya          #+#    #+#              #
#    Updated: 2022/07/01 19:13:58 by juzoanya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -lpthread -ggdb3 $(INC)

PATH_SRC = ./src/
PATH_INC = ./inc/
PATH_OBJS = ./objs/
INC = -I ./inc

SRC = 	$(PATH_SRC)philo.c \
		$(PATH_SRC)errors.c \
		$(PATH_SRC)tasks.c \
		$(PATH_SRC)utils.c \
		$(PATH_SRC)init.c \


OBJS = $(patsubst $(PATH_SRC)%.c, $(PATH_OBJS)%.o, $(SRC))

VAL			:= valgrind
VAL_FLAGS	:= --leak-check=full --show-leak-kinds=all --tool=memcheck --track-origins=yes --log-file=valgrind-out.txt

ARGS =	5 310 200 100 1

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(SRC) -o $(NAME) $(CFLAGS)
	@echo "$(NAME) created"

$(PATH_OBJS)%.o:	$(PATH_SRC)%.c
	@mkdir -p $(PATH_OBJS)
	$(CC) $(CFLAGS) $(INC). -c $< -o $@

clean:
	@rm -rf $(PATH_OBJS)
	@echo "OBJ Deleted!"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(NAME) is Deleted!"

re:	fclean all

memcheck:	clean all
	clear
	$(VAL) $(VAL_FLAGS) ./$(NAME) $(ARGS)

.PHONY:	all clean fclean re