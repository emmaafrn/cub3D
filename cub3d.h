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
#define screenWidth 800
#define screenHeight 600
#define RAD M_PI / 180

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
	double				rs;
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

typedef		struct	s_eastnwest
{
	double			t2;
	int				text2;
}					t_eastnwest;

typedef		struct	s_state
{ 
	t_struct		parse;
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
	double			angle_temp;
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
	int				pxl_color;
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
void			ft_intersections(t_state *state);
int				key_hook(int keycode, t_state *state);
void			d_or_a_key(t_state *state);
void			w_or_s_key(t_state *state);
int				release_key(int keycode, t_state *state);
void			ft_mem_sprite_tab(t_state *state);
void			ft_coord_sprites(t_state *state);
void			ft_planes_sprites(t_state *state);
int				ft_find_sprite(t_vector dir, t_state *state, int sprite_num);
t_wall_text		ft_texture(double t1, double t2, int text1, int text2);
t_wall_text		ft_find_texture(t_state *state, int i, int j);
t_eastnwest		check_east_n_west(t_state *state, int j, int i, t_eastnwest res);
int				mlx_get_texture_first(t_state *state);
int				mlx_get_texture(t_state *state);
double			get_vector_norm(t_vector U);
double			get_sprite_text(t_state *state, t_coord I, int k);
void			ft_sort_sprites(t_state *state);
void			ft_smaller_dist(t_state *state, int i, int j, double dist_min);
int				ft_is_sprite_printed(t_state *state, int sprite_num, int i, int j);
int				ft_print_sprite(t_state *state, int i, int j, int result);
void			ft_print_the_right_pixel(t_state *state, int i, int j);
double			calc_dividend(t_plane p, double rs, t_coord pos);
void			distance_dividend_wall(t_coord pos, t_plane *plane, int limit);
void			distance_dividend_sprites(t_state *state);
t_coord			scaling_pixel_color(int i, int j, t_state *state, int scale);

#endif
