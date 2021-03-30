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

typedef		struct	s_vector
{
	double			x;
	double			y;
	double			z;
}					t_vector;

typedef		struct	s_planes
{
	int				a;
	int				b;
	int				c;
	double			d;
}					t_planes;

typedef		struct	s_state
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	t_vector		player_pos;
	t_vector		**dir_ray;
	t_planes		*x_plane;
	t_planes		*y_plane;
	double			angle;
}					t_state;

t_vector	create_vector(float x, float y, float z);
t_vector	rotate_vector_z(t_vector vector, double angle);
void		ft_lol(int i, int j, t_state *state);

#endif