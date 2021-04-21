NAME = cub3D

SRC =	parsing/checkelements.c parsing/cub.c parsing/ft_strtrim.c parsing/ft_substr.c parsing/get_next_line.c\
		parsing/getlenmax.c parsing/islinevalid.c parsing/libft.c parsing/libftstuff.c parsing/listes.c\
		parsing/skynfloorcolor.c parsing/spacenplayerpos.c parsing/structstuff.c parsing/whatsthemap.c parsing/ft_wrmalloc.c\
		cub3d.c vectors.c check_intersections.c rectif_pos.c sprites_stuff.c\
		hook_stuff.c textures_stuff.c text_sprite.c mlx_text.c print_pixel.c\
		sort_sprites.c intersections.c calc.c

OBJ = ${SRC:.c=.o}

CC  = gcc

RM  = rm -f

CFLAGS = -I. -O2 -g3 -fsanitize=address #-Wall -Wextra -Werror #-Ofast

all:		$(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) ${CFLAGS} -L. -lmlx $^ -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:		fclean all