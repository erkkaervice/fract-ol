# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/03 15:04:01 by eala-lah          #+#    #+#              #
#    Updated: 2024/10/04 13:46:46 by eala-lah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fractol

INCS		= -I ./inc/
LIBFT_DIR	= libft/
LIBFT		= $(LIBFT_DIR)/libft.a
MLX_DIR		= mlx42/
MLX		= $(MLX_DIR)/libmlx42.a

SRC_DIR		= src/
SRCS		= $(addprefix $(SRC_DIR), $(SRC))
SRC		= \
	main.c \

OBJ_DIR		= obj/
OBJS		= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

CC		= gcc
CFLAGS		= -Wall -Wextra -Werror -fPIC

all: $(OBJ_DIR) $(MLX) $(LIBFT) $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(MLX):
	if [ ! -d "$(MLX_DIR)" ]; then \
		git clone https://github.com/codam-coding-college/MLX42 $(MLX_DIR); \
	fi
	cmake -B $(MLX_DIR)/build $(MLX_DIR)
	$(MAKE) -C $(MLX_DIR)/build
	
$(LIBFT):
	if [ ! -d "$(LIBFT_DIR)" ]; then \
		git clone git@github.com:erkkaervice/libft.git $(LIBFT_DIR); \
	fi
	make -C $(LIBFT_DIR) CFLAGS="-Wall -Wextra -Werror -fPIC"

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L $(MLX_DIR)/build -lmlx42 -L $(LIBFT_DIR) -lft -lm -lXext -lX11

bonus: all

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(MLX_DIR)/build
	make -C $(MLX_DIR)/build clean
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(MLX)
	rm -f $(LIBFT)
	rm -rf $(LIBFT_DIR)
	rm -rf $(MLX_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus

