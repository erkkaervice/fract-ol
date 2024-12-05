# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/03 15:04:01 by eala-lah          #+#    #+#              #
#    Updated: 2024/12/05 14:47:24 by eala-lah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Project Name and Libraries ---
# Specifies the project name, library directories, and required libraries.
NAME        = fractol
INCS        = -I ./inc/ -I ./libft/inc/
LIBFT_DIR   = libft/
LIBFT       = $(LIBFT_DIR)/libft.a
MLX_DIR     = mlx42/
MLX         = $(MLX_DIR)/libmlx42.a

# --- Source and Object Directories ---
# Defines directories for source code and object files.
SRC_DIR     = src/
SRC         = \
    fractal.c \
    fractals.c \
    input.c \
    main.c \

OBJ_DIR     = obj/
OBJS        = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

# --- Compiler and Flags ---
# Specifies the compiler, compilation flags, and necessary library flags.
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror $(INCS) -fPIC
GIT_FLAGS   = git clone --depth 1
MLX_FLAGS   = -L $(MLX_DIR)/build -lmlx42 -lglfw -lGL -lm -lpthread -ldl

# --- Default Target ---
# Builds all dependencies and final executable
all: $(LIBFT) $(MLX) $(OBJ_DIR) $(NAME)

# --- Directory Setup ---
# Creates the object directory if it doesn't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) 2> /dev/null || { echo "Failed to create object directory." >&2; exit 1; }

# --- MLX Library Setup ---
# Installs and builds the MLX library, cloning the repository if not already present.
$(MLX):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		$(GIT_FLAGS) https://github.com/codam-coding-college/MLX42.git $(MLX_DIR) > /dev/null 2>&1 || { echo "Failed to clone MLX42 repository." >&2; exit 1; }; \
	fi
	@cmake -B $(MLX_DIR)/build $(MLX_DIR) > /dev/null 2>&1 || { echo "Failed to configure MLX library." >&2; exit 1; }
	@$(MAKE) -C $(MLX_DIR)/build > /dev/null 2>&1 || { echo "Failed to build MLX library." >&2; exit 1; }

# --- libft Library Setup ---
# Installs and builds the libft library, cloning the repository if not already present.
$(LIBFT):
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		$(GIT_FLAGS) https://github.com/erkkaervice/libft.git $(LIBFT_DIR) > /dev/null 2>&1 || { echo "Failed to clone libft repository." >&2; exit 1; }; \
	fi
	@make -C $(LIBFT_DIR) CFLAGS="-Wall -Wextra -Werror -fPIC -I ./inc/" > /dev/null 2>&1 || { echo "Failed to build libft library." >&2; exit 1; }
	@rm -f $(LIBFT_DIR)/README.md > /dev/null 2>&1 || { echo "Failed to remove README.md." >&2; exit 1; }

# --- Compilation ---
# Compiles source files into object files.
$(OBJ_DIR)%.o: $(SRC_DIR)%.c inc/fractol.h
	@$(CC) $(CFLAGS) -c $< -o $@ 2> /dev/stderr || { echo "Failed to compile $<." >&2; exit 1; }

# --- Linking ---
# Links object files and creates the final executable.
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS) -L $(LIBFT_DIR) -lft 2> /dev/stderr || { echo "Failed to create executable $(NAME)." >&2; exit 1; }

# --- Bonus Target ---
# Bonus target to build everything (equivalent to the 'all' target)
bonus: all

# --- Cleaning ---
# Removes object files and cleans the libraries
clean:
	@rm -rf $(OBJ_DIR) 2> /dev/null || { echo "Failed to clean object files." >&2; exit 1; }
	@make -C $(LIBFT_DIR) clean > /dev/null 2>&1 || { if [ -d "$(LIBFT_DIR)" ]; then echo "Failed to clean libft." >&2; exit 1; fi; }
	@rm -rf $(MLX_DIR)/build 2> /dev/null || { if [ -d "$(MLX_DIR)" ]; then echo "Failed to remove MLX build directory." >&2; exit 1; fi; }

# --- Full Clean ---
# Full clean target to remove everything including the executable and libraries.
fclean: clean
	@rm -f $(LIBFT) $(NAME) 2> /dev/stderr || { echo "Failed to remove generated files." >&2; exit 1; }
	@rm -rf $(LIBFT_DIR) 2> /dev/stderr || { if [ -d "$(LIBFT_DIR)" ]; then echo "Failed to remove libft directory." >&2; exit 1; fi; }
	@rm -rf $(MLX_DIR) 2> /dev/stderr || { if [ -d "$(MLX_DIR)" ]; then echo "Failed to remove MLX library." >&2; exit 1; fi; }

# --- Rebuild ---
# Rebuilds everything by cleaning and running all again
re: fclean all

# --- Phony Targets ---
# Declares all targets as phony to avoid conflicts with files of the same name
.PHONY: all clean fclean re bonus
