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
#define screenWidth 400
#define screenHeight 400

typedef		struct	s_vector
{
	float			x;
	float			y;
	float			z;
}					t_vector;

typedef		struct	s_coord
{
	float			x;
	float			y;
	float			z;
}					t_coord;

typedef		struct	s_planes
{
	float				a;
	float				b;
	float				c;
	float				d;
}					t_plane;

typedef		struct	s_inter
{
	double			t;
	t_coord			inter;
	int				i;
	int				j;
}					t_inter;

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
	t_vector		**dir_ray;
	t_plane			*x_plane;
	t_plane			*y_plane;
	float			angle;
	int				k;
	int				i_plane;
	t_plane			*plane;
	t_inter			interr;
}					t_state;

t_vector	create_vector(float x, float y, float z);
t_vector	rotate_vector_z(t_vector vector, float angle);
float		ft_distance(t_state *state, t_plane plane, t_vector dir);
void		ft_lol(t_vector dir, t_state *state, int i, int j);
void		check_north(t_state *state, int i, int j);
void		check_south(t_state *state, int i, int j);
void		check_east(t_state *state, int i, int j);
void		check_west(t_state *state, int i, int j);
float		ft_fmax(float a, float b);
float		ft_fmin(float a, float b);
t_coord		rectif_pos(t_state *state, t_plane plane, t_coord inter);

#endif