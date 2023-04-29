#include "vec.h"

#include <mlx.h>
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
#define MAP_EMPTY XK_0

#if 0
#define printf (void)
#endif

typedef char	t_world[MAP_X][MAP_Y];
t_world	world =
{
  "111111111111111111111111",
  "100000000000000000000001",
  "100000000000000000000001",
  "100000000000000000000001",
  "100000222220000303030001",
  "100000200020000000000001",
  "100000200020000300030001",
  "100000200020000000000001",
  "100000220220000303030001",
  "100000000000000000000001",
  "100000000000000000000001",
  "100000000000000000000001",
  "100000000000000000000001",
  "100000000000000000000001",
  "100000000000000000000001",
  "100000000000000000000001",
  "144444444000000000000001",
  "140400004000000000000001",
  "140000504000000000000001",
  "140400004000000000000001",
  "140444444000000000000001",
  "140000000000000000000001",
  "144444444000000000000001",
  "111111111111111111111111",
};

	t_vec	player = {22,12};
	t_vec	dir = {-1,0};

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

t_color	get_pixel(const t_img *img, int x, int y)
{
	const t_ivec	size = img->size;

	if (ivec_in(ivec(x, y), size))
		return (*(t_color *)&img->addr[y * img->size_line + x * (img->bpp / CHAR_BIT)]);
	return (-1);
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
		printf("!%s[%06x](%d,%d)->(%d,%d)\n", __func__, color, a.x,a.y, b.x,b.y);
}

int	world_ati(const t_world world, t_ivec pos)
{
	const t_ivec	size = ivec(MAP_X, MAP_Y);
	if (ivec_in(pos, size))
		return (world[pos.y][pos.x]);
	printf("!%s(%d,%d)\n", __func__, pos.x, pos.y);
	return (-1);
}

int	world_at(const t_world world, t_vec pos)
{
	return (world_ati(world, ivec(pos.x, pos.y)));
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
			const t_vec	plane = vec_sca(vec_rot(dir, -M_PI_2), 0.75);
			const t_vec	ray_dir = vec_add(dir, vec_sca(plane, camera.x));
			const t_vec	delta_dist = vec(fabs(1.0 / ray_dir.x), fabs(1.0 / ray_dir.y));
			const t_ivec	step = ivec(copysign(1.0, ray_dir.x), copysign(1.0, ray_dir.y));

			t_ivec	map_pos = ivec(player.x, player.y);
			t_vec	side_dist = vec_mul(vec(fabs(map_pos.x + (ray_dir.x >= 0) - player.x), fabs(map_pos.y + (ray_dir.y >= 0) - player.y)), delta_dist);
			int		hit = 0;
			while (!hit)
			{
				int		side = 0;//TODO enum
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
				if (world_ati(world, map_pos) != MAP_EMPTY)
				{
					hit = side;
				}
			}
			double	wall_dist = (hit == 1 || hit == 3) ? side_dist.x - delta_dist.x : side_dist.y - delta_dist.y;
			int	line_y = MIN(size.y, size.y / wall_dist);

			draw_vline(&mlx->img,\
					ivec(x, MAX(0, size.y / 2 - line_y / 2)),\
					ivec(x, MIN(size.y - 1, size.y / 2 + line_y / 2)),\
					(int[]){0x00ffffff,0x00ffff00,0x00ff00ff,0x0000ffff,0x0000ff00}[hit]); //TODO
		}
	}

	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.ptr, 0, 0);
	return (0);
}


int	f_key_hook(int key, t_mlx *mlx)
{
	if (key == 'q' || key == XK_Escape)
		exit(0);
	else if (key == XK_Up || key == XK_Down || key == XK_Left || key == XK_Right)
	{
		t_vec	d = vec_rot(dir, M_PI_2 * (-(key % 4) + 2));//TODO enum
		d = vec_sca(d, 0.25);
		if (world_at(world, vec_add(player, vec(d.x, 0))) == MAP_EMPTY)
			player = vec_add(player, vec(d.x, 0));
		if (world_at(world, vec_add(player, vec(0, d.y))) == MAP_EMPTY)
			player = vec_add(player, vec(0, d.y));
	}
	else if (key == XK_a || key == XK_d)
	{
		double	speed = (double []){-M_PI, M_PI}[key == XK_a] / 8;
		dir = vec_rot(dir, speed);
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
