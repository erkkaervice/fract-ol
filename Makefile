# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/03 15:04:01 by eala-lah          #+#    #+#              #
#    Updated: 2024/12/05 17:20:27 by eala-lah         ###   ########.fr        #
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
    fractal.c \
    fractals.c \
    input.c \
    main.c \

OBJ_DIR     = obj/
OBJS        = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

CC          = gcc
CFLAGS      = -Wall -Wextra -Werror $(INCS) -fPIC
GIT_FLAGS   = git clone --depth 1
MLX_FLAGS   = -L $(MLX_DIR)/build -lmlx42 -lglfw -lGL -lm -lpthread -ldl

all: $(LIBFT) $(MLX) $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) 2> /dev/null || { echo "Failed to create object directory." >&2; exit 1; }

$(MLX):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		$(GIT_FLAGS) https://github.com/codam-coding-college/MLX42.git $(MLX_DIR) > /dev/null 2>&1 || { echo "Failed to clone MLX42 repository." >&2; exit 1; }; \
	fi
	@cmake -B $(MLX_DIR)/build $(MLX_DIR) > /dev/null 2>&1 || { echo "Failed to configure MLX library." >&2; exit 1; }
	@$(MAKE) -C $(MLX_DIR)/build > /dev/null 2>&1 || { echo "Failed to build MLX library." >&2; exit 1; }

$(LIBFT):
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		$(GIT_FLAGS) https://github.com/erkkaervice/libft.git $(LIBFT_DIR) > /dev/null 2>&1 || { echo "Failed to clone libft repository." >&2; exit 1; }; \
	fi
	@make -C $(LIBFT_DIR) CFLAGS="-Wall -Wextra -Werror -fPIC -I ./inc/" > /dev/null 2>&1 || { echo "Failed to build libft library." >&2; exit 1; }
	@rm -f $(LIBFT_DIR)/README.md > /dev/null 2>&1 || { echo "Failed to remove README.md." >&2; exit 1; }

$(OBJ_DIR)%.o: $(SRC_DIR)%.c inc/fractol.h
	@$(CC) $(CFLAGS) -c $< -o $@ 2> /dev/stderr || { echo "Failed to compile $<." >&2; exit 1; }

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS) -L $(LIBFT_DIR) -lft 2> /dev/stderr || { echo "Failed to create executable $(NAME)." >&2; exit 1; }

bonus: all

clean:
	@rm -rf $(OBJ_DIR) 2> /dev/null || { echo "Failed to clean object files." >&2; exit 1; }
	@make -C $(LIBFT_DIR) clean > /dev/null 2>&1 || { if [ -d "$(LIBFT_DIR)" ]; then echo "Failed to clean libft." >&2; exit 1; fi; }
	@rm -rf $(MLX_DIR)/build 2> /dev/null || { if [ -d "$(MLX_DIR)" ]; then echo "Failed to remove MLX build directory." >&2; exit 1; fi; }

fclean: clean
	@rm -f $(LIBFT) $(NAME) 2> /dev/stderr || { echo "Failed to remove generated files." >&2; exit 1; }
	@rm -rf $(LIBFT_DIR) 2> /dev/stderr || { if [ -d "$(LIBFT_DIR)" ]; then echo "Failed to remove libft directory." >&2; exit 1; fi; }
	@rm -rf $(MLX_DIR) 2> /dev/stderr || { if [ -d "$(MLX_DIR)" ]; then echo "Failed to remove MLX library." >&2; exit 1; fi; }

re: fclean all

.PHONY: all clean fclean re bonus
