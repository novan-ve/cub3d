# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: novan-ve <novan-ve@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/02/08 17:12:54 by novan-ve       #+#    #+#                 #
#    Updated: 2020/02/08 17:40:17 by novan-ve      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRCS = ft_bmp.c \
		ft_fill.c \
		ft_free.c \
		ft_map.c \
		ft_move.c \
		ft_parser.c \
		ft_raycast.c \
		ft_run.c \
		ft_sprite_init.c \
		ft_sprite.c \
		ft_texture.c \
		ft_utils.c \
		ft_cub.c \
		get_next_line.c \
		get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Werror -Wextra

LIBS = -Lmlx/ -lmlx -Lft_printf/ -lftprintf -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME):
		make -C mlx
		make -C ft_printf
		cp mlx/libmlx.dylib .
		gcc $(FLAGS) -c $(SRCS)
		gcc $(FLAGS) $(LIBS) -o $(NAME) $(OBJS)

clean:
		make -C mlx clean
		make -C ft_printf clean
		rm -f $(OBJS)

fclean:	clean
		rm -f $(NAME) libmlx.dylib mlx/libmlx.dylib ft_printf/libftprintf.a

re:		fclean $(NAME)

.PHONY:	all clean fclean re
