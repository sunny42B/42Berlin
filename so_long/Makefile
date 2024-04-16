# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sung-hle <sung-hle@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/11 15:46:45 by sung-hle          #+#    #+#              #
#    Updated: 2023/05/29 16:34:10 by sung-hle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    := so_long
CFLAGS  := -Wextra -Wall -Werror
LIBMLX  := ./MLX42/build
HEADERS := -I ./include -I $(LIBMLX)/include
LIBS    := $(LIBMLX)/libmlx42.a -ldl -lglfw -pthread -lm
LIBFT   := libft/libft.a
SRCS    :=	main.c 					\
			error_checks.c			\
			functions.c				\
			functions_two.c			\
			mlx_func.c				\
			mlx_func_two.c			\
			print.c					\
			pics.c					\
			some_utils.c			\
			sl_bonus.c
SRCS_BONUS 	:=	main_bonus.c 				\
			error_checks_bonus.c			\
			functions_bonus.c				\
			functions_two_bonus.c			\
			mlx_func_bonus.c				\
			mlx_func_two_bonus.c			\
			print_bonus.c					\
			pics_bonus.c					\
			some_utils_bonus.c				\
			sl_bonus_bonus.c
OBJS    := ${SRCS:.c=.o}
OBJS_BONUS    := ${SRCS_BONUS:.c=.o}

all: $(NAME)

compile: $(NAME)

libmlx:
	make -C libft
	@if [ ! -d "./MLX42/" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git; \
	fi
	@if [ ! -d "./MLX42/build" ]; then \
		cd ./MLX42 && cmake -B build && cmake --build build -j4; \
	fi

%.o: %.c
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(LIBFT) -o $(NAME)

bonus: $(NAME)_bonus

$(NAME)_bonus: $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBS) $(LIBFT) -o $(NAME)_bonus

clean:
	make clean -C libft
	rm -f $(OBJS) ${OBJS_BONUS}

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME)_bonus
	rm -f $(LIBMLX)/libmlx42.a
	rm -rf MLX42

re: fclean all

.PHONY: clean fclean re
