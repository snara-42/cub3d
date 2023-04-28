#include "mlx.h"
#include <X11/keysym.h>

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <limits.h>
#include <sys/param.h>

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

//#include <libc.h>

#define MAP_X 24
#define MAP_Y 24
#define SCREEN_X 640
#define SCREEN_Y 480

#if 0
#define printf (void)
#endif

typedef int	t_world[MAP_X][MAP_Y];
t_world	world =
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

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

	t_vec	player = {22,12};
	t_vec	dir = {-1,0};
	t_vec	plane = {0,.66};

typedef uint32_t	t_color;
struct	s_img
{
	void	*ptr;
	char	*addr;
	t_ivec	size;
	int		bpp;
	int		size_line;
	int		endian;
};
typedef struct s_img	t_img;

struct	s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img;
};
typedef struct s_mlx	t_mlx;

int	draw();
int	f_key_hook();

int	init(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, SCREEN_X, SCREEN_Y, "cub3d");
	{
	t_img	*img = &mlx->img;
	img->size = ivec(SCREEN_X, SCREEN_Y);
	img->ptr = mlx_new_image(mlx->mlx, img->size.x, img->size.y);
	img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->size_line, &img->endian);
	}
	mlx_do_key_autorepeaton(mlx->mlx);
	//mlx_loop_hook(mlx->mlx, draw, mlx);
	mlx_key_hook(mlx->win, f_key_hook, mlx);
	return (0);
}

void	put_pixel(t_img *img, int x, int y, t_color color)
{
	const t_ivec	size = img->size;

	if (ivec_in(ivec(x, y), size))
		*(t_color *)&img->addr[y * img->size_line + x * (img->bpp / CHAR_BIT)] = color;
}

void	draw_vline(t_img *img, t_ivec a, t_ivec b, t_color color)
{
	const t_ivec	size = img->size;

	//printf("vline[%06x](%d,%d)->(%d,%d)\n", color, a.x,a.y, b.x,b.y);
	if (ivec_in(a, size) && ivec_in(b, size))
		for (int y = a.y; y != b.y; y += a.y < b.y ? 1 : -1)
		{
			put_pixel(img, a.x, y, color);
		}
	else
		printf("!vline[%06x](%d,%d)->(%d,%d)\n", color, a.x,a.y, b.x,b.y);
}

int	draw(t_mlx *mlx)
{
	t_img	*img = &mlx->img;
	printf("[%d,%d %d %d %d]\n", img->size.x, img->size.y, img->bpp, img->size_line, img->endian);

	const t_ivec	size = mlx->img.size;
	for (int y = 0; y < size.y; ++y)
		for (int x = 0; x < size.x; ++x)
		{
			put_pixel(&mlx->img, x, y, 0x00424242);
		}

	{
		for (int x = 0; x < size.x; ++x)
		{
			const t_vec	camera = vec(x / (double)size.x * 2.0 - 1.0, 0);
			const t_vec	ray_dir = vec_add(dir, vec_sca(plane, camera.x));
			const t_vec	delta_dist = vec(fabs(1.0 / ray_dir.x), fabs(1.0 / ray_dir.y));
			const t_ivec	step = ivec(copysign(1.0, ray_dir.x), copysign(1.0, ray_dir.y));

			t_ivec	map_pos = ivec(player.x, player.y);
			t_vec	side_dist = vec_mul(vec(fabs(map_pos.x + (ray_dir.x >= 0) - player.x), fabs(map_pos.y + (ray_dir.y >= 0) - player.y)), delta_dist);
			int		hit = 0;
			while (!hit)
			{
				int		side = 0;
				if (side_dist.x < side_dist.y)
				{
					side_dist.x += delta_dist.x;
					map_pos.x += step.x;
					side = 2 + step.x;
				}
				else
				{
					side_dist.y += delta_dist.y;
					map_pos.y += step.y;
					side = 3 + step.y;
				}
				if (world[map_pos.y][map_pos.x] > 0)
				{
					hit = side;
				}
			}
			double	wall_dist = (hit == 1 || hit == 3) ? side_dist.x - delta_dist.x : side_dist.y - delta_dist.y;
			int	line_y = (size.y / wall_dist);

			draw_vline(&mlx->img,\
					ivec(x, MAX(0, size.y / 2 - line_y / 2)),\
					ivec(x, MIN(size.y - 1, size.y / 2 + line_y / 2)),\
					(int[]){0x00ffffff,0x00ffff00,0x00ff00ff,0x0000ffff,0x0000ff00}[hit]);
		}
	}

	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.ptr, 0, 0);
	return (0);
}

int	world_at(const t_world world, t_vec pos)
{
	return (world[(int)pos.y][(int)pos.x]);
}

int	f_key_hook(int key, t_mlx *mlx)
{
	if (key == 'q' || key == XK_Escape)
		exit(0);
	else if (key == XK_Up || key == XK_Down || key == XK_Left || key == XK_Right)
	{
		t_vec	d = vec_sca(vec_rot(dir, M_PI_2 * (-(key % 4) + 2)), 0.25);
		if (world_at(world, vec_add(player, vec(d.x, 0))) == 0)
			player = vec_add(player, vec(d.x, 0));
		if (world_at(world, vec_add(player, vec(0, d.y))) == 0)
			player = vec_add(player, vec(0, d.y));
	}
	else if (key == XK_a || key == XK_d)
	{
		double	speed = (double []){-M_PI, M_PI}[key == XK_a] / 8;
		dir = vec_rot(dir, speed);
		plane = vec_rot(plane, speed);
	}
	printf("d=(%f,%f) pl=(%f,%f)\n", dir.x,dir.y, player.x,player.y);
	draw(mlx);
	return (0);
}

void	loop(t_mlx *mlx)
{
	mlx_loop(mlx->mlx);
}

int	main()
{
	t_mlx	mlx = {};
#define mlx (&mlx)
	init(mlx);
	loop(mlx);
}
