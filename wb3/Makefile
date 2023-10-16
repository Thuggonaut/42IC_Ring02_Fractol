#Program name
NAME			=	fractol

# Compiler
CC				=	gcc
CFLAGS			=	-Werror -Wextra -Wall

# Minilibx
MLX_PATH		=	minilibx-linux/
MLX_NAME		=	libmlx.a
MLX				=	$(MLX_PATH)$(MLX_NAME)

# Libft
LIBFT_PATH		=	libft/
LIBFT_NAME		=	libft.a
LIBFT			=	$(LIBFT_PATH)$(LIBFT_NAME)

# Includes
INC				=	-I ./inc/\
					-I ./libft/\
					-I ./minilibx-linux/

# Sources
SRC_PATH		=	src/
SRC				=	fractol.c \
					init.c \
					render.c \
					events.c \
					handle_error.c \
					utils.c \

SRCS			=	$(addprefix $(SRC_PATH), $(SRC))

# Objects
OBJ_PATH		=	obj/
OBJ				=	$(SRC:.c=.o)
OBJS			=	$(addprefix $(OBJ_PATH), $(OBJ))

all: 				$(MLX) $(LIBFT) $(NAME)

$(OBJ_PATH)%.o: 	$(SRC_PATH)%.c
					@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJS): 			$(OBJ_PATH)

$(OBJ_PATH):
					@mkdir $(OBJ_PATH)

$(MLX):
					@make -sC $(MLX_PATH)

$(LIBFT):
					@make -sC $(LIBFT_PATH)

$(NAME): 			$(OBJS)
					@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX) $(LIBFT) $(INC) -lXext -lX11 -lm

bonus: 				all

clean:
					@rm -rf $(OBJ_PATH)
					@make clean -C $(MLX_PATH)
					@make clean -C $(LIBFT_PATH)

fclean: 			clean
					@rm -f $(NAME)
					@rm -f $(LIBFT_PATH)$(LIBFT_NAME)

re: 				fclean all

.PHONY: 			all re clean fclean