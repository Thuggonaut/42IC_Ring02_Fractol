#Program name
NAME				=	fractol

# Compiler and CFlags
CC					=	gcc
CFLAGS				=	-Wall -Werror -Wextra
LIBS      			=	-lXext -lX11 -lm
RM					=	rm -f

# Directories
LIBFT				=	./libft/libft.a
MLX					=	./minilibx-linux/libmlx.a
INC					=	inc/
SRC_DIR				=	src/
OBJ_DIR				=	obj/

# Source Files
SRC					=	fractol.c \
						init.c \
						render.c \
						events.c \
						utils.c \
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
						@make -sC ./minilibx-linux

# Compile object files from source files
$(OBJ_DIR)%.o:			$(SRC_DIR)%.c 
						@mkdir -p $(@D)
						@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
						@$(RM) -r $(OBJ_DIR)
						@make clean -C ./minilibx-linux
						@make clean -C ./libft

fclean: 				clean
						@$(RM) $(NAME)
						@$(RM) $(MLX)
						@$(RM) $(LIBFT)

re: 					fclean all

# Phony targets represent actions not files
.PHONY: 				all clean fclean re