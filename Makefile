NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
AR = ar rcs
RM = rm -f

LIBFT = libft
LIBFT_LIB = $(LIBFT)/libft.a
LIBFT_HEADER = $(LIBFT)/libft.h

SRC_DIR = srcs
SRC_FILES = main.c error_free.c \
			checking/check_map.c checking/check_utils.c checking/check.c \
			parsing/parse.c parsing/parse_replace_spaces.c parsing/parse_populate_values.c  parsing/parse_utils.c \
			movement/mov_hook.c movement/mov_move.c movement/mov_rotate.c movement/mov_utils.c \
			init/init_player.c init/init_textures.c \
			raycasting/raycasting1.c raycasting/raycasting2.c \
			drawing/draw_line.c  drawing/draw_wall.c drawing/draw_utils.c
SRC_PATHS = $(addprefix $(SRC_DIR)/,$(SRC_FILES))
OBJ_DIR = obj
OBJ_FILES = $(SRC_FILES:%.c=$(OBJ_DIR)/%.o)

GLFW_LIB = -lglfw
GLFW_PATH = /usr/lib/x86_64-linux-gnu
OPENGL_LIB = -lGL
MATH_LIB = -lm
DL_LIB = -ldl
PTHREAD_LIB = -pthread
X11_LIB = -lX11

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/checking
	mkdir -p $(OBJ_DIR)/parsing
	mkdir -p $(OBJ_DIR)/init
	mkdir -p $(OBJ_DIR)/movement
	mkdir -p $(OBJ_DIR)/raycasting
	mkdir -p $(OBJ_DIR)/drawing

$(NAME): $(OBJ_FILES) $(LIBFT_LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES) \
		-L$(LIBFT) -lft \
		MLX42/libmlx42.a \
		-L$(GLFW_PATH) $(GLFW_LIB) \
		$(OPENGL_LIB) $(DL_LIB) $(PTHREAD_LIB) $(MATH_LIB) $(X11_LIB) \
		-I$(LIBFT) -Iinclude -IMLX42

$(LIBFT_LIB): $(LIBFT_HEADER)
	$(MAKE) -C $(LIBFT)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c cub3d.h $(LIBFT_HEADER)
	$(CC) $(CFLAGS) -I$(LIBFT) -Iinclude -IMLX42 -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)
	$(MAKE) clean -C $(LIBFT)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re