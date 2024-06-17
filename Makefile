NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

LIBFT = libft
LIBFT_LIB = $(LIBFT)/libft.a

# Updated source and object files for executable to reflect /src folder
SRC_DIR = srcs
SRC_FILES = main.c error.c parse.c
SRC_PATHS = $(addprefix $(SRC_DIR)/,$(SRC_FILES))
OBJ_DIR = obj
OBJ_FILES = $(SRC_PATHS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Rule to make everything
all: $(OBJ_DIR) $(NAME)

# Creating the obj directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Compiling the project and linking with libft and mlx_linux to create the executable
$(NAME): $(LIBFT_LIB) $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES) -L$(LIBFT) -lft MLX42/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm

# Rule for making libft
$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT)

# Rule for making object files, now looks in src directory and includes header
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c cub3d.h
	$(CC) $(CFLAGS) -I$(LIBFT) -c $< -o $@

# Cleaning up the object files
clean:
	$(RM) -r $(OBJ_DIR)
	$(MAKE) clean -C $(LIBFT)

# Full clean (includes the libraries and executable)
fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFT)

# Re-make everything
re: fclean all

# Prevents issues with make and filenames
.PHONY: all clean fclean re
