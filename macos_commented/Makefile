#Program name
NAME				=	fractol

# Compiler and CFlags
CC					=	gcc
CFLAGS				=	-Wall -Werror -Wextra
RM					=	rm -f

# Determine the platform
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	LIBS = -lXext -lX11 -lm
	MLX = ./minilibx-linux/libmlx.a
	INC = inc/ libft/ minilibx-linux/
else ifeq ($(UNAME_S), Darwin)
	LIBS = -Lminilibx-macos -lmlx -framework OpenGL -framework AppKit -lm
	MLX = ./minilibx-macos/libmlx.a
	INC = inc/ libft/ minilibx-macos/
endif

# Directories
LIBFT				=	./libft/libft.a
SRC_DIR				=	src/
OBJ_DIR				=	obj/

# Source Files
SRC					=	fractol.c \
						init.c \
						render.c \
						events.c \
						utils1.c \
						utils2.c \
						colours.c

SRCS				=	$(addprefix $(SRC_DIR), $(SRC))

# Object files
OBJ 				= 	$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

# Build rules

all: 					$(MLX) $(LIBFT) $(NAME)

$(NAME): 				$(OBJ) $(MLX) $(LIBFT)
						@$(CC) $(CFLAGS) $(OBJ) $(MLX) $(LIBFT) $(LIBS) -o $(NAME)

$(LIBFT):
						@make -sC ./libft

$(MLX):
						@if [ "$(UNAME_S)" = "Linux" ]; then \
							make -sC ./minilibx-linux; \
						else \
							make -sC ./minilibx-macos; \
						fi

						

# Compile object files from source files
$(OBJ_DIR)%.o:			$(SRC_DIR)%.c 
						@mkdir -p $(@D)
						@$(CC) $(CFLAGS) -c $< -o $@

clean:
						@$(RM) -r $(OBJ_DIR)
						@make clean -C $(dir $(MLX))
						@make clean -C ./libft

fclean: 				clean
						@$(RM) $(NAME)
						@$(RM) $(MLX)
						@$(RM) $(LIBFT)

re: 					fclean all

# Phony targets represent actions not files
.PHONY: 				all clean fclean re