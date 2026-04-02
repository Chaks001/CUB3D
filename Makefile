# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/02 16:28:11 by vpoelman          #+#    #+#              #
#    Updated: 2026/04/02 16:28:11 by vpoelman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -I$(MLX_DIR) -I$(LIBFT_DIR)

LIBFT_DIR = libft
MLX_DIR = mlx

LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a

SRCS = src/main.c \
       src/game/game.c \
       src/game/hooks.c \
       src/game/movement.c \
       src/parsing/gnl.c \
       src/parsing/map_alloc.c \
       src/parsing/parse_colors.c \
       src/parsing/parse_elements.c \
       src/parsing/parse_file.c \
       src/parsing/parse_map.c \
       src/parsing/lines_utils.c \
       src/parsing/utils.c \
       src/parsing/validate_map.c \
       src/raycasting/dda.c \
       src/raycasting/raycasting.c \
       src/raycasting/render.c \
       src/raycasting/texture.c \
       src/utils/cleanup.c \
       src/utils/error.c \
       src/utils/graphics.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@$(CC) $(OBJS) -L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -lft -lXext -lX11 -lm -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(MLX):
	@make -C $(MLX_DIR)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@if [ -d "$(MLX_DIR)" ]; then make -C $(MLX_DIR) clean; fi

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
