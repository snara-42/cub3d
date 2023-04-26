#include "mlx.h"
#include <stdint.h>
#include <stddef.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <X11/keysym.h>

#define OO 1e30
#define MAP_X 24
#define MAP_Y 24
#define SCREEN_X 640
#define SCREEN_Y 480

int world[MAP_X][MAP_Y]=
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

t_vec	vec(double x, double y)
{
	return ((t_vec){x, y});
}

t_vec	vec_div(t_vec a, t_vec b)
{
	return (vec(a.x / b.x, a.y / b.y));
}

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
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.ptr, 0, 0);
	//mlx_loop_hook(mlx->mlx, draw, mlx);
	mlx_key_hook(mlx->win, f_key_hook, mlx);
	return (0);
}

int	f_key_hook(int key, t_mlx *mlx)
{
	if (key == 'q' || key == XK_Escape)
		exit(0);
	draw(mlx);
	return (0);
}

void	put_pixel(t_img *img, int x, int y, t_color color)
{
	*(t_color *)&img->addr[y * img->size_line + x * (img->bpp / CHAR_BIT)] = color;
}

void	draw_vline(t_img *img, t_ivec a, t_ivec b, t_color color)
{
	printf("vline[%06x](%d,%d)->(%d,%d)\n", color, a.x,a.y, b.x,b.y);
	for (int y = a.y; y != b.y; y += a.y < b.y ? 1 : -1)
		put_pixel(img, a.x, y, color);
}

int	draw(t_mlx *mlx)
{
	t_img	*img = &mlx->img;
	printf("[%d,%d %d %d %d]\n", img->size.x, img->size.y, img->bpp, img->size_line, img->endian);

	t_ivec	size = mlx->img.size;
	for (int y = 0; y < size.y; ++y)
		for (int x = 0; x < size.x; ++x)
		{
			put_pixel(&mlx->img, x, y, 0x00424242);
		}

	t_vec	player = {22,12};
	t_vec	dir = {-1,0};
	t_vec	plane = {0,.66};

	// while (!done)
	{
		for (int x = 0; x < size.x; ++x)
		{
			t_vec	camera = vec(2 * x / (double)SCREEN_X - 1, 0);
			t_vec	ray_dir = vec(dir.x + plane.x * camera.x, dir.y + plane.y * camera.x);
			t_ivec	map_pos = ivec(player.x, player.y);
			t_vec	delta_dist = vec(fmin(OO, fabs(1.0 / ray_dir.x)), fmin(OO, fabs(1.0 / ray_dir.y)));
			t_ivec	step = ivec(copysign(1.0, ray_dir.x), copysign(1.0, ray_dir.y));
			t_vec	side_dist = vec(fdim(player.x, map_pos.x) + (ray_dir.x >= 0), fdim(player.y, map_pos.y) + (ray_dir.y >= 0));
			t_vec	perp_dist = vec(0, 0);

			int		hit = 0;
			int		side = 0;
			while (!hit)
			{
				if (side_dist.x < side_dist.y)
				{
					side_dist.x += delta_dist.x;
					map_pos.x += step.x;
					side = 2 * step.x;
				}
				else
				{
					side_dist.y += delta_dist.y;
					map_pos.y += step.y;
					side = 1 * step.y;
				}
				if (world[map_pos.y][map_pos.x] > 0)
				{
					hit = side;
					printf("(%f,%f)->(%d,%d)\n", player.x,player.y, map_pos.x,map_pos.y);
				}
			}
			if (abs(side) == 2)
				perp_dist.x = side_dist.x - delta_dist.x;
			else
				perp_dist.y = side_dist.y - delta_dist.y;
			int	line_y = size.y / (perp_dist.x + perp_dist.y);
			printf("x:%d (%f,%f) h:%d\n", x, perp_dist.x,perp_dist.y, line_y);

			//draw_vline(&mlx->img,\
					ivec(x, fmax(0, size.y / 4)),\
					ivec(x, fmin(size.y - 1, size.y / 4 * 3)),\
					(int[]){0x00ff0000,0x00ffff00,0x00ffffff,0x000000ff,0x0000ff00}[side+2]);
			draw_vline(&mlx->img,\
					ivec(x, fmax(0, size.y / 2 - line_y / 2)),\
					ivec(x, fmin(size.y - 1, size.y / 2 + line_y / 2)),\
					(int[]){0x00ff0000,0x00ffff00,0x00ffffff,0x000000ff,0x0000ff00}[side+2]);
		}
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.ptr, 0, 0);
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
