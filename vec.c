#include "vec.h"
#include <math.h>
#include <stdbool.h>

t_ivec	ivec(int x, int y)
{
	return ((t_ivec){x, y});
}

bool	ivec_in(t_ivec v, t_ivec size)
{
	return (0 <= v.x && v.x < size.x && 0 <= v.y && v.y < size.y);
}

t_vec	vec(double x, double y)
{
	return ((t_vec){x, y});
}

t_vec	vec_add(t_vec a, t_vec b)
{
	return (vec(a.x + b.x, a.y + b.y));
}

t_vec	vec_sub(t_vec a, t_vec b)
{
	return (vec(a.x - b.x, a.y - b.y));
}

t_vec	vec_mul(t_vec a, t_vec b)
{
	return (vec(a.x * b.x, a.y * b.y));
}

t_vec	vec_sca(t_vec a, double n)
{
	return (vec(a.x * n, a.y * n));
}

t_vec	vec_div(t_vec a, t_vec b)
{
	return (vec(a.x / b.x, a.y / b.y));
}

t_vec	vec_rot(t_vec v, double angle)
{
	return (vec(v.x * cos(angle) - v.y * sin(angle),
			v.x * sin(angle) + v.y * cos(angle)));
}
