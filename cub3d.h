#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
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
#define screenWidth 1000
#define screenHeight 1000

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

typedef		struct	s_state
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	t_coord			player_pos;
	t_vector		player_dir;
	t_vector		**dir_ray;
	t_plane			*x_plane;
	t_plane			*y_plane;
	double			angle;
	int				k;
	int				i_plane;
	t_plane			*plane;
	t_coord			inter1_wall;
	t_coord			inter2_wall;
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

t_vector		create_vector(double x, double y, double z);
t_vector		rotate_vector_z(t_vector vector, double angle);
double			ft_distance(t_state *state, t_plane plane, t_vector dir);
t_inter			ft_lol(t_vector dir, t_state *state, int i, int j);
double			check_north(t_state *state, int i, int j);
double			check_south(t_state *state, int i, int j);
double			check_east(t_state *state, int i, int j);
double			check_west(t_state *state, int i, int j);
double			ft_fmax(double a, double b);
double			ft_fmin(double a, double b);
t_coord			rectif_pos(t_state *state, t_plane plane, t_coord inter);
void			ft_orientation(t_state *state, int i, int j);
int				ft_texture(double t1, double t2, int text1, int text2);
int				key_hook(int keycode, t_state *state);
void			ft_mem_sprite_tab(t_state *state);
void			ft_coord_sprites(t_state *state);
void			ft_planes_sprites(t_state *state);
int				ft_find_sprite(t_vector dir, t_state *state, int i, int j);

#endif