# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 12:44:40 by fhassoun          #+#    #+#              #
#    Updated: 2023/07/13 18:25:52 by fhassoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= 	ft_strcmp.c			\
			ft_strchr.c			\
			ft_strrchr.c		\
			ft_strlcpy.c		\
			ft_strlcat.c		\
			ft_strlen.c			\
			ft_memset.c			\
			ft_strncmp.c		\
			ft_putchar_fd.c		\
			ft_putstr_fd.c		\
			ft_putnbr_fd.c		\
			ft_substr.c			\
			ft_putendl_fd.c		\
			ft_tolower.c		\
			ft_toupper.c		\
			ft_atoi.c			\
			ft_itoa.c			\
			ft_bzero.c			\
			ft_strdup.c			\
			ft_isalpha.c		\
			ft_isdigit.c		\
			ft_isalnum.c		\
			ft_isprint.c		\
			ft_isascii.c		\
			ft_memcpy.c			\
			ft_memmove.c		\
			ft_memchr.c			\
			ft_memcmp.c			\
			ft_strjoin.c		\
			ft_strnstr.c		\
			ft_strmapi.c		\
			ft_striteri.c		\
			ft_strtrim.c		\
			ft_split.c			\
			ft_calloc.c			\
			ft_lstnew.c			\
			ft_lstadd_front.c 	\
			ft_lstsize.c		\
			ft_lstlast.c		\
			ft_lstadd_back.c	\
			ft_lstdelone.c		\
			ft_lstclear.c		\
			ft_lstiter.c		\
			ft_lstmap.c			\
			ft_printf_convert.c	\
			ft_printf_utils.c	\
			ft_printf.c			\
			ft_gnl.c			\
			ft_gnl_utils.c		\
			ft_strisspace.c		\
			ft_isspace.c
			
OBJS		= ${SRCS:.c=.o}

NAME		= libft.a

CC			= cc -Wall -Wextra -Werror

%.o: %.c libft.h ft_printf.h ft_gnl.h
			@${CC} -I. -c $< -o ${<:.c=.o}

all:		${NAME}

${NAME}:	${OBJS} libft.h
			@ar rcs ${NAME} ${OBJS}

clean:
			@rm -f ${OBJS} ${OBJS_BONUS}

fclean:		clean
			@rm -f ${NAME}

re:			fclean all


.PHONY:		all clean fclean re

