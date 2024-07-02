NAME = cub3d
LIBFTDIR = ./libft
MAKE = make
CC = cc
CFLAGS = #-Wall -Wextra -Werror 
HEAD = includes/so_long.h
LIBMLX = ./MLX42
SRCS = srcs/main.c
		
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME): $(OBJS)
		@$(MAKE) -C $(LIBFTDIR)
		@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4
		@$(CC) $(CFLAGS) $(OBJS) $(LIBMLX)/build/libmlx42.a -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" ./libft/libft.a -o $(NAME) 

clean:
		@rm -f $(OBJS)
		@$(MAKE) clean -C $(LIBFTDIR)
		@rm -rf $(LIBMLX)/build

fclean: clean
		@rm -f $(NAME)
		@rm -f libft.a
		@$(MAKE) fclean -C $(LIBFTDIR)

re: fclean all

.PHONY: all clean fclean re
