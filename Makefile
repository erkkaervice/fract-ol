# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/03 15:04:01 by eala-lah          #+#    #+#              #
#    Updated: 2024/10/07 11:50:01 by eala-lah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = fractol

INCS        = -I ./inc/ -I ./libft/inc/
LIBFT_DIR   = libft/
LIBFT       = $(LIBFT_DIR)/libft.a
MLX_DIR     = mlx42/
MLX         = $(MLX_DIR)/libmlx42.a

SRC_DIR     = src/
SRC         = \
    main.c \

SRCS        = $(addprefix $(SRC_DIR), $(SRC))
OBJ_DIR     = obj/
OBJS        = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -fPIC
GIT_FLAGS   = git clone --depth 1

all: $(LIBFT) $(MLX) $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "Created object directory."

$(OBJ_DIR)%.o: $(SRC_DIR)%.c inc/fractol.h
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@ 2> /dev/stderr > /dev/null
	@echo "Compiled $< into $@."

$(MLX):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		$(GIT_FLAGS) https://github.com/codam-coding-college/MLX42.git $(MLX_DIR) > /dev/null 2>&1 || exit 1; \
	fi
	@cmake -B $(MLX_DIR)/build $(MLX_DIR) 2> /dev/stderr > /dev/null
	@$(MAKE) -C $(MLX_DIR)/build 2> /dev/stderr > /dev/null
	@echo "MLX library built."

$(LIBFT):
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		$(GIT_FLAGS) https://github.com/erkkaervice/libft.git $(LIBFT_DIR) > /dev/null 2>&1 || exit 1; \
	fi
	@make -C $(LIBFT_DIR) CFLAGS="-Wall -Wextra -Werror -fPIC -I ./inc/" 2> /dev/stderr > /dev/null
	@echo "Libft library built."

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L $(MLX_DIR)/build -lmlx42 -L $(LIBFT_DIR) -lft -lm -lXext -lX11 2> /dev/stderr > /dev/null
	@echo "Executable $(NAME) created."

bonus: all

clean:
	@rm -rf $(OBJ_DIR) 2> /dev/stderr > /dev/null
	@rm -rf $(MLX_DIR)/build 2> /dev/stderr > /dev/null
	@make -C $(MLX_DIR)/build clean 2> /dev/stderr > /dev/null
	@make -C $(LIBFT_DIR) clean 2> /dev/stderr > /dev/null
	@echo "Cleaned up $(OBJ_DIR) and libraries."

fclean: clean
	@rm -f $(MLX) 2> /dev/stderr > /dev/null
	@rm -f $(LIBFT) 2> /dev/stderr > /dev/null
	@rm -rf $(LIBFT_DIR) 2> /dev/stderr > /dev/null
	@rm -rf $(MLX_DIR) 2> /dev/stderr > /dev/null
	@rm -f $(NAME) 2> /dev/stderr > /dev/null
	@echo "Fully cleaned up all generated files."

re: fclean all

.PHONY: all clean fclean re bonus
