#include "cub3d.h"

t_vector	create_vector(double x, double y, double z)
{
	t_vector	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_vector	addition_v(t_vector v1, t_vector v2)
{
	t_vector	new;

	new.x = v1.x + v2.x;
	new.y = v1.y + v2.y;
	new.z = v1.z + v2.z;
	return (new);
}

t_vector	multi_v(t_vector v1, t_vector v2)
{
	t_vector	new;

	new.x = v1.x * v2.x;
	new.y = v1.y * v2.y;
	new.z = v1.z * v2.z;
	return (new);
}

t_vector	rotate_vector_z(t_vector vector, double angle)
{
	double	new_x;
	double	new_y;

	new_x = cos(angle) * vector.x - sin(angle) * vector.y;
	new_y = sin(angle) * vector.x + cos(angle) * vector.y;
	return (create_vector(new_x, new_y, vector.z));
}
