.PHONY: all clean fclean re

SRC = 	main.c \
        color.c \
		debug.c \
		dll.c \
		dll2.c \
		image.c \
		init.c \
		input.c \
		keys.c \
		keys2.c \
		terminate.c \
		transform.c \
		transform2.c \
		projections.c


NAME = fdf

SRC_DIR = ./src

OBJ_DIR = ./obj

INC_DIR = ./inc

LIB = ftprintf

LIBFT_DIR = ./printf

LIBFT_INC_DIR = $(LIBFT_DIR)/inc

MINILIBX_DIR = ./minilibx

FLAGS = -Wall -Werror -Wextra

CC = gcc

INCLUDES = -I$(INC_DIR) -I$(LIBFT_INC_DIR) -I$(MINILIBX_DIR)

LIBRARIES = -L$(LIBFT_DIR) -L$(MINILIBX_DIR) \
			-l$(LIB) -lmlx -framework OpenGL -framework AppKit

OBJ = $(SRC:.c=.o)

OBJS = $(addprefix $(OBJ_DIR)/, $(OBJ))

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	@echo "Compiling library. Please wait..."
	@make -C $(LIBFT_DIR)/
	@echo "libft done"
	@echo "Compiling minilibx. Please wait..."
	@make -C minilibx/
	@echo "minilibx done"
	@echo "Compiling fdf..."
	@gcc -o $(NAME) $(OBJS) $(INCLUDES) $(LIBRARIES)
	@echo "We're ready to work"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<

clean:
	@echo "cleaninig"
	@make -C $(LIBFT_DIR) clean
	@make -C $(MINILIBX_DIR) clean
	@rm -rf $(OBJ_DIR)
	@echo "objects removed"

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -rf $(MINILIBX_LIB)/obj
	@rm -f $(NAME)
	@echo "Cleaning is done. Directory is ready"

re: fclean all
