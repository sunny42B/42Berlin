# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/19 11:11:36 by fhassoun          #+#    #+#              #
#    Updated: 2023/08/02 15:43:01 by fhassoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC_DIR = sources
OBJ_DIR = objects

SOURCES =	$(SRC_DIR)/main.c				\
			$(SRC_DIR)/main_utils.c				\
			$(SRC_DIR)/handling_envp.c		\
			$(SRC_DIR)/some_funcs.c			\
			$(SRC_DIR)/some_funcs_two.c			\
			$(SRC_DIR)/signals.c			\
			$(SRC_DIR)/signal_utils.c			\
			$(SRC_DIR)/minishell_utils.c	\
			$(SRC_DIR)/lexer_helper.c	\
			$(SRC_DIR)/lexer_helper2.c	\
			$(SRC_DIR)/parser1.c	\
			$(SRC_DIR)/parser2.c	\
			$(SRC_DIR)/parser3.c	\
			$(SRC_DIR)/lexer1.c	\
			$(SRC_DIR)/lexer2.c	\
			$(SRC_DIR)/lexer3.c	\
			$(SRC_DIR)/redirect.c	\
			$(SRC_DIR)/redirect_utils.c	\
			$(SRC_DIR)/executer.c	\
			$(SRC_DIR)/executer_utils.c	\
			$(SRC_DIR)/executer_helper_one.c	\
			$(SRC_DIR)/executer_helper_two.c	\
			$(SRC_DIR)/executer_helper_three.c	\
			$(SRC_DIR)/dollar.c	\
			$(SRC_DIR)/dollar_utils.c	\
			$(SRC_DIR)/expander.c	\
			
			
			

OBJECTS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SOURCES))

LIBFT_PATH = ./libft
LIBFT_NAME = ft
LIBFT = $(LIBFT_PATH)/lib$(LIBFT_NAME).a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
INC = -I./includes
LDFLAGS = -L$(LIBFT_PATH) -l$(LIBFT_NAME) -pthread -lreadline

all:  $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
		@$(CC) $(OBJECTS) $(INC) $(CFLAGS) $(LDFLAGS) -o $(NAME) 
		@echo "\033[0;32m[OK]\033[0m    \033[0;38;5;199mCompiling\033[0m $(NAME) executable"
		
$(LIBFT): $(LIBFT_PATH)/*.c
	@make -C $(LIBFT_PATH)
		
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@echo "\033[0;32m[OK]\033[0m    \033[0;38;5;199mCompiling\033[0m $(<F)"

clean:
	@rm -f $(OBJECTS)
	@make -C $(LIBFT_PATH) clean
	@echo "\033[0;32m[OK]\033[0m    \033[0;38;5;44mRemoving objects\033[0m"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean
	@echo "\033[0;32m[OK]\033[0m    \033[0;38;5;44mRemoving executable\033[0m"

re: fclean all 

.PHONY: all clean fclean re 