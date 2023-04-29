#ifndef VEC_H
# define VEC_H
# include <stdbool.h>

struct s_vec
{
	double	x;
	double	y;
};
typedef struct s_vec	t_vec;
struct s_ivec
{
	int	x;
	int	y;
};
typedef struct s_ivec	t_ivec;

t_ivec	ivec(int x, int y);
bool	ivec_in(t_ivec v, t_ivec size);

t_vec	vec(double x, double y);
t_vec	vec_add(t_vec a, t_vec b);
t_vec	vec_sub(t_vec a, t_vec b);
t_vec	vec_mul(t_vec a, t_vec b);
t_vec	vec_sca(t_vec a, double n);
t_vec	vec_div(t_vec a, t_vec b);
t_vec	vec_rot(t_vec v, double angle);

#endif
