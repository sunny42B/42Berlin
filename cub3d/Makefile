# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/11 09:45:00 by fhassoun          #+#    #+#              #
#    Updated: 2023/09/19 09:56:12 by fhassoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME = cub3d
SRC_DIR = sources
OBJ_DIR = objects

SOURCES = 	$(SRC_DIR)/main.c 					\
			$(SRC_DIR)/textures.c 				\
			$(SRC_DIR)/routine.c 				\
			$(SRC_DIR)/error_checks.c			\
			$(SRC_DIR)/error_handling.c			\
			$(SRC_DIR)/error_handling2.c		\
			$(SRC_DIR)/free_and_error.c			\
			$(SRC_DIR)/free_and_error2.c		\
			$(SRC_DIR)/parse_config.c			\
			$(SRC_DIR)/parse_map.c				\
			$(SRC_DIR)/print_funcs.c			\
			$(SRC_DIR)/wall_check.c				\
			$(SRC_DIR)/movement.c				\
			$(SRC_DIR)/movement_utils.c			\
			$(SRC_DIR)/floor_casting.c			\
			$(SRC_DIR)/wall_casting.c			\
			$(SRC_DIR)/wall_casting_utils.c			\

OBJECTS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SOURCES))

LIBFT_PATH = ./libft
LIBFT_NAME = ft
LIBFT = $(LIBFT_PATH)/lib$(LIBFT_NAME).a

MLX_PATH = ./MLX42/build
MLX_NAME = mlx42
MLX = $(MLX_PATH)/lib$(MLX_NAME).a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INC = -I./includes -I./libft -I./MLX42
#LDFLAGS for linux
#LDFLAGS = -L$(LIBFT_PATH) -l$(LIBFT_NAME) -L$(MLX_PATH) -l$(MLX_NAME) -lglfw -ldl -lm -pthread
#LDFLAGS for MacOS
#LDFLAGS = -L$(LIBFT_PATH) -l$(LIBFT_NAME) -L$(MLX_PATH) -l$(MLX_NAME) -lglfw -ldl -lm -pthread -L"/opt/homebrew/Cellar/glfw/3.3.8/lib/"

ifeq ($(shell uname), Linux)
	LDFLAGS = -L$(LIBFT_PATH) -l$(LIBFT_NAME) -L$(MLX_PATH) -l$(MLX_NAME) -lglfw -ldl -lm -pthread
else
	LDFLAGS = -L$(LIBFT_PATH) -l$(LIBFT_NAME) -L$(MLX_PATH) -l$(MLX_NAME) -lglfw -ldl -lm -pthread -L"/opt/homebrew/Cellar/glfw/3.3.8/lib/"
endif


#all: libmlx $(NAME)
all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJECTS)
#	$(CC) $(OBJECTS) $(LDFLAGS)  -o $@ $(LIBFT) $(MLX)
	@$(CC) $(OBJECTS) $(INC) $(CFLAGS) $(LDFLAGS) -o $(NAME)

$(LIBFT): $(LIBFT_PATH)/*.c
	@make -C $(LIBFT_PATH)

$(MLX): 
	@make -C $(MLX_PATH)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@echo "\033[0;32m[OK]\033[0m    \033[0;38;5;199mCompiling\033[0m $(<F)"

libmlx:
#	@if git submodule status | egrep -q '^[-]|^[+]' ; then \
#            echo "INFO: Need to reinitialize git submodules"; \
#            git submodule update --init; \
#    fi
	@if [ ! -d "./MLX42/" ]; then \
        git clone https://github.com/codam-coding-college/MLX42.git; \
    fi
	@if [ ! -d "./MLX42/build" ]; then \
		cmake ./MLX42 -B ./MLX42/build ; \
	fi


clean:
	@rm -f $(OBJECTS)
	@make -C $(LIBFT_PATH) clean
	@make -C $(MLX_PATH) clean
	@echo "\033[0;32m[OK]\033[0m    \033[0;38;5;44mRemoving objects\033[0m"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(MLX)
	@make -C $(LIBFT_PATH) fclean
	
	@echo "\033[0;32m[OK]\033[0m    \033[0;38;5;44mRemoving executable\033[0m"
#	@make -C $(LIBFT_PATH) fclean

re: fclean all 

.PHONY: all clean fclean re libmlx
