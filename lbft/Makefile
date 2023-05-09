# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmassavi <cmassavi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/15 15:57:41 by lcorpora          #+#    #+#              #
#    Updated: 2023/02/22 18:17:19 by cmassavi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =ft_bzero.c \
ft_itoa.c \
ft_putendl_fd.c \
ft_strjoin.c \
ft_strrchr.c \
ft_calloc.c \
ft_putnbr_fd.c \
ft_strlcat.c \
ft_strtrim.c \
ft_isalnum.c \
ft_memcmp.c \
ft_putstr_fd.c \
ft_strlcpy.c \
ft_isalpha.c \
ft_memcpy.c \
ft_split.c \
ft_strlen.c \
ft_tolower.c \
ft_isascii.c \
ft_memmove.c \
ft_strchr.c \
ft_strmapi.c \
ft_toupper.c \
ft_isdigit.c \
ft_memset.c \
ft_strdup.c \
ft_strncmp.c \
ft_atoi.c \
ft_isprint.c \
ft_putchar_fd.c \
ft_striteri.c \
ft_strnstr.c

SRCB = ft_lstnew.c \
ft_lstadd_back.c \
ft_lstdelone.c \
ft_lstadd_front.c \
ft_lstlast.c \
ft_lstsize.c \
ft_lstclear.c \
ft_lstiter.c \
ft_lstmap.c

NAME = libft.a

CC = gcc -Wall -Werror -Wextra

.c.o :
	$(CC) -c $(SRC)

OBJS = $(SRC:.c=.o)

$(NAME) : $(OBJS)
	ar rc $(NAME) $(OBJS)

all : $(NAME)

bonus :
	$(CC) -c $(SRCB)
	ar rc $(NAME) $(SRCB:.c=.o)

clean :
	rm -rf $(OBJS)
	rm -rf $(SRCB:.c=.o)

fclean : clean
	rm -rf $(NAME)

re : fclean all
