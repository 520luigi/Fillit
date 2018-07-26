# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: szheng <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/20 15:21:44 by szheng            #+#    #+#              #
#    Updated: 2018/07/23 19:10:44 by szheng           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

CC = gcc

FLAGS = -Wall -Werror -Wextra

SRC_PATH = ./srcs/
INC_PATH = ./includes/
OBJ_PATH = ./obj/
LFT_PATH = ./libft/

SRC_NAME = main.c solve.c

INC_NAME = fillit.h

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
INC = $(addprefix -I,$(INC_PATH))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LFT_PATH)
	@$(CC) -o $(NAME) $(OBJ) -L $(LFT_PATH) -lft
	@echo "Fillit is READY!"


$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(FLAGS) $(INC) -o $@ -c $<

clean:
	@make -C $(LFT_PATH) clean
	@rm -rf $(OBJ_PATH)
	@echo "Object files cleared!"

fclean: clean
	@make -C $(LFT_PATH) fclean
	@rm -f $(NAME)
	@echo "All clean!"

re: fclean all

.PHONY: clean $(NAME) fclean all re
