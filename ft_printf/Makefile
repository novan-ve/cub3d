# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: novan-ve <novan-ve@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/12/20 14:11:17 by novan-ve       #+#    #+#                 #
#    Updated: 2019/12/27 16:18:09 by novan-ve      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

FLAGS = -Wall -Werror -Wextra libft/libft.h -c

SRCS = ft_printf.c \
		ft_printi.c \
		ft_printx.c \
		ft_printp.c \
		ft_prints.c \
		ft_printu.c \
		ft_calc.c

OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(SRCS) ft_printf.h
	make -C libft
	cp libft/libft.a .
	mv libft.a $(NAME)
	gcc $(FLAGS) $(SRCS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
	rm -rf $(OBJS)
	make -C libft/ clean

fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean

re: fclean all
