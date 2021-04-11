#ifndef CUB3D_H
# define CUB3D_H

# include "parsing/parsing.h"
# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <string.h>
# include <stdarg.h>
# include <stdio.h>
# include <limits.h>
# include <fcntl.h>

#define KEY_D 2
#define KEY_S 1 
#define KEY_A 0
#define KEY_W 13
#define KEY_LEFT 123
#define KEY_RIGHT 124
#define KEY_ESC 53
#define mapWidth 24
#define mapHeight 8
#define screenWidth 300
#define screenHeight 300

extern int	worldMap[mapHeight][mapWidth];

typedef		struct	s_vector
{
	double			x;
	double			y;
	double			z;
}					t_vector;

typedef		struct	s_coord
{
	double			x;
	double			y;
	double			z;
}					t_coord;

typedef		struct	s_planes
{
	double				a;
	double				b;
	double				c;
	double				d;
}					t_plane;

typedef		struct	s_inter
{
	double			t;
	t_coord			coord;
}					t_inter;

typedef		struct	s_sprite
{
	t_coord			coord;
	t_plane			plane;
	t_inter			inter;
}					t_sprite;

typedef		struct	s_textures
{
	void	*img;
	char	*data;
	int		width;
	int		height;
	int		line_length;
	int		endian;
	int		bits_per_pixel;
	char	*addr;
}					t_textures;

typedef		struct	s_wall_text
{
	double			t;
	int				result;
}					t_wall_text;

typedef		struct	s_state
{
	t_struct		map;
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	t_coord			player_pos;
	t_vector		**dir_ray;
	t_plane			*x_plane;
	t_plane			*y_plane;
	double			angle;
	int				k;
	int				i_plane;
	t_plane			*plane;
	t_coord			inter1_wall;
	t_coord			inter2_wall;
	t_wall_text		wall_text;
	int				W_key;
	int				A_key;
	int				D_key;
	int				S_key;
	int				left_key;
	int				right_key;
	t_textures		*text;
	int				nb_sprites;
	t_sprite		*sprite_tab;
}					t_state;

void			my_mlx_pixel_put(t_state *state, int x, int y, int color);
char			*get_pixel(t_textures *text, int x, int y);
void			ft_planes(t_state *state);
void			ft_ray_dir(t_state *state);
int				ft_loop(t_state *state);
int				ft_init_game(t_state *state);
t_vector		create_vector(double x, double y, double z);
t_vector		rotate_vector_z(t_vector vector, double angle);
double			ft_distance(t_state *state, t_plane plane, t_vector dir);
t_inter			ft_get_coord(t_vector dir, t_state *state, int i, int j);
double			check_north(t_state *state, int i, int j);
double			check_south(t_state *state, int i, int j);
double			check_east(t_state *state, int i, int j);
double			check_west(t_state *state, int i, int j);
double			ft_fmax(double a, double b);
double			ft_fmin(double a, double b);
t_coord			rectif_pos(t_state *state, t_plane plane, t_coord inter);
void			ft_orientation(t_state *state, int i, int j);
void			ft_intersections(t_state *state);
int				key_hook(int keycode, t_state *state);
void			d_or_a_key(t_state *state);
void			w_or_s_key(t_state *state);
int				release_key(int keycode, t_state *state);
void			ft_mem_sprite_tab(t_state *state);
void			ft_coord_sprites(t_state *state);
void			ft_planes_sprites(t_state *state);
int				ft_find_sprite(t_vector dir, t_state *state, int i, int j);
t_wall_text		ft_texture(double t1, double t2, int text1, int text2);
t_wall_text		ft_find_texture(t_state *state, int i, int j);
void			mlx_get_texture(t_state *state);

#endif
