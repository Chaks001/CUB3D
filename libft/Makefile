# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: your_login <your_login@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/01 12:00:00 by your_login       #+#    #+#              #
#    Updated: 2024/01/01 12:00:00 by your_login      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = ft_strlen.c ft_strdup.c ft_strcmp.c ft_strncmp.c \
       ft_split.c ft_atoi.c ft_isspace.c ft_isdigit.c \
       ft_memset.c ft_memcpy.c ft_putstr_fd.c ft_putnbr_fd.c \
       ft_strchr.c ft_strjoin.c ft_putchar_fd.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re