# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sung-hle <sung-hle@42student.berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/12 16:11:14 by sung-hle          #+#    #+#              #
#    Updated: 2022/12/23 17:02:01 by sung-hle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES = server.c client.c
OBJECTS = $(SOURCES:.c=.o)

CC = cc -Wall -Wextra -Werror
CC_FLAGS = -Llibft -lft

%.o:%.c
	$(CC) -c -o $@ $^
	
all:	libft server client

libft: 
	make -C libft
	
server: server.c libft/libft.a
	$(CC) -o $@ $< $(CC_FLAGS)

client: client.c libft/libft.a
	$(CC) -o $@ $< $(CC_FLAGS)

clean:
	rm -f $(OBJECTS)
	make -C libft clean
	
fclean: clean
	rm -f server client libft/libft.a
	make -C libft fclean

re:	fclean all

.PHONY: libft clean fclean re
