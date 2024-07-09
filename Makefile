NAME = cub3d
CC = cc
CFLAGS = #-Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

LIBFT = libft
LIBFT_LIB = $(LIBFT)/libft.a

SRC_DIR = srcs
SRC_FILES = main.c error.c parse.c checks.c drawing.c \
			screen_matrix_utils.c raycasting.c \
			player_utils.c movement.c
SRC_PATHS = $(addprefix $(SRC_DIR)/,$(SRC_FILES))
OBJ_DIR = obj
OBJ_FILES = $(SRC_PATHS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Update these lines for GLFW and other required libraries
GLFW_LIB = -lglfw
GLFW_PATH = /usr/lib/x86_64-linux-gnu
OPENGL_LIB = -lGL
MATH_LIB = -lm
DL_LIB = -ldl
PTHREAD_LIB = -pthread

# Add this line for X11 library
X11_LIB = -lX11

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(LIBFT_LIB) $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES) \
		-L$(LIBFT) -lft \
		MLX42/libmlx42.a \
		-L$(GLFW_PATH) $(GLFW_LIB) \
		$(OPENGL_LIB) $(DL_LIB) $(PTHREAD_LIB) $(MATH_LIB) $(X11_LIB) \
		-I$(LIBFT) -Iinclude -IMLX42

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c cub3d.h
	$(CC) $(CFLAGS) -I$(LIBFT) -Iinclude -IMLX42 -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)
	$(MAKE) clean -C $(LIBFT)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re