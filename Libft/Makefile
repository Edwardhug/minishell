# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/30 11:46:37 by lgabet            #+#    #+#              #
#    Updated: 2023/05/03 16:04:31 by lgabet           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

SRCS	= libft/srcs/ft_isascii.c\
libft/srcs/ft_memset.c\
libft/srcs/ft_strnstr.c\
libft/srcs/ft_isdigit.c\
libft/srcs/ft_strchr.c\
libft/srcs/ft_strrchr.c\
libft/srcs/ft_atoi.c\
libft/srcs/ft_isprint.c\
libft/srcs/ft_strdup.c\
libft/srcs/ft_tolower.c\
libft/srcs/ft_bzero.c\
libft/srcs/ft_memchr.c\
libft/srcs/ft_strlcat.c\
libft/srcs/ft_toupper.c\
libft/srcs/ft_calloc.c\
libft/srcs/ft_memcmp.c\
libft/srcs/ft_strlcpy.c\
libft/srcs/ft_isalnum.c\
libft/srcs/ft_memcpy.c\
libft/srcs/ft_strlen.c\
libft/srcs/ft_isalpha.c\
libft/srcs/ft_memmove.c\
libft/srcs/ft_strncmp.c\
libft/srcs/ft_substr.c\
libft/srcs/ft_strjoin.c\
libft/srcs/ft_strtrim.c\
libft/srcs/ft_split.c\
libft/srcs/ft_itoa.c\
libft/srcs/ft_strmapi.c\
libft/srcs/ft_striteri.c\
libft/srcs/ft_putchar_fd.c\
libft/srcs/ft_putstr_fd.c\
libft/srcs/ft_putendl_fd.c\
libft/srcs/ft_putnbr_fd.c\
libft/srcs/ft_lstnew.c\
libft/srcs/ft_lstadd_front.c\
libft/srcs/ft_lstsize.c\
libft/srcs/ft_lstlast.c\
libft/srcs/ft_lstadd_back.c\
libft/srcs/ft_lstdelone.c\
libft/srcs/ft_lstclear.c\
libft/srcs/ft_lstiter.c\
libft/srcs/ft_lstmap.c\
get_next_line/srcs/get_next_line.c\
get_next_line/srcs/get_next_line_utils.c\
printf/srcs/ft_printchar.c\
printf/srcs/ft_printstr.c\
printf/srcs/ft_printf.c\
printf/srcs/ft_printaddress.c\
printf/srcs/ft_printnbr.c\
printf/srcs/ft_print_unsigned.c\
printf/srcs/ft_print_hexa.c\
printf/srcs/ft_itoa.c\
printf/srcs/ft_unsigned_itoa.c\
printf/srcs/ft_itoa_x.c

HEADERS = libft/includes/libft.h\
get_next_line/includes/get_next_line.h\
printf/includes/ft_printf.h
OBJS= ${SRCS:.c=.o}

all: $(NAME)

%.o : %.c $(HEADERS)
		$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}
	
$(NAME) : $(OBJS) $(HEADERS)
	ar -rcs $(NAME) $(OBJS) $(HEADERS)

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all re bonus clean fclean