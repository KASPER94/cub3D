# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/12 16:23:30 by peanut            #+#    #+#              #
#    Updated: 2024/08/15 11:22:48 by cdeville         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=cub3d

CC=cc

CFLAGS= -Wall -Werror -Wextra -D BUFFER_SIZE=100

DEBUG = -g

MLX_DIR= minilibx/
MLX_NAME= libmlx.a
MLX_PATH= $(MLX_DIR)
MLX= $(MLX_PATH)$(MLX_NAME)

LIBFT_DIR= libft/
LIBFT_NAME= libft.a
LIBFT_PATH= $(LIBFT_DIR)
LBFT= $(LIBFT_PATH)$(LIBFT_NAME)

SRC_DIR = ./sources/
SRC =	check_map.c \
		color.c \
		error.c \
		events.c \
		init.c \
		main.c \
		movements.c \
		movements_rot.c \
		parse_get_info.c \
		parse_get_map.c \
		parse.c \
		path_checker.c \
		raycasting.c \
		textures.c \

SRCS = $(addprefix $(SRC_DIR), $(SRC))

INCLUDES_DIR= ./includes/
INCLUDES_FILES= cub3d

OBJ_DIR= ./objects/
OBJ= $(SRC:.c=.o)
OBJS= $(addprefix $(OBJ_DIR), $(OBJ))

INCLUDES= $(addprefix $(INCLUDES_DIR), $(addsuffix .h, $(INCLUDES_FILES)))

.PHONY: all clean fclean re norminette

all: $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	echo "Compiling $< to $@"
	$(CC) $(CFLAGS) $(DEBUG) -I $(LIBFT_PATH) -I $(INCLUDES_DIR) -c $< -o $@

$(NAME): $(OBJS)
	@echo "\e[0;32m\nGenerating libft...\n\e[0m"
	make -C $(LIBFT_PATH)
	@echo "\e[0;32m\nGenerating minilibx...\n\e[0m"
	make -C $(MLX_DIR)
	@echo "\e[0;32m\nLinking executable:\n\e[0m"
	$(CC) $(CFLAGS) $(OBJS) -o $@ -lft -L$(LIBFT_DIR) $(MLX) -lXext -lX11 -lm
	@echo "\e[0;32m\nMandatory part compiled !\n\e[0m"

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

clean:
	@echo "\e[0;31m\nDeleting objects\n\e[0m"
	rm -rf $(OBJ_DIR)
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)

fclean: clean
	@echo "\e[0;31m\nDeleting executable\n\e[0m"
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)
	make fclean -C $(LIBFT_DIR)

re: fclean all

norminette:
	@echo "\e[0;32m\nChecking .c norme:\n\e[0m"
	norminette ./src
	@echo "\e[0;32m\nChecking .h norme:\n\e[0m"
	norminette ./include
