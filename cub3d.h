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
#define screenWidth 1024
#define screenHeight 512

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
	int				a;
	int				b;
	int				c;
	float			d;
}					t_plane;

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
	t_plane			*plane;
}					t_state;

t_vector	create_vector(float x, float y, float z);
t_vector	rotate_vector_z(t_vector vector, float angle);
float		ft_distance(t_coord *pos, t_plane *plane);
void		ft_lol(t_vector dir, t_state *state);
void		check_north(t_state *state, int i, int j);

#endif