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

#define MAP_W 24
#define MAP_H 24
#define TEX_W 128
#define TEX_H 128
#define SCREEN_W 640
#define SCREEN_H 480
#define MAP_EMPTY '0'

#if 0
#define printf (void)
#endif

typedef char	t_world[MAP_W][MAP_H];
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

enum	e_dir
{
	E_NONE = 0,
	E_LEFT = 1,
	E_UP = 2,
	E_RIGHT = 3,
	E_DOWN = 4,
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
	t_img	texture[4];
};
typedef struct s_mlx	t_mlx;

int	draw();
int	f_key_hook();

void	put_pixel(t_img *img, int x, int y, t_color color);

int	init_img(t_mlx *mlx)
{
	for (int i=0; i<4; i++)
	{
		t_img	*img = &mlx->texture[i];
#if 1
		img->ptr = mlx_xpm_file_to_image(mlx->mlx,
			(char*[]){"cubfiles/xpm/p_ji_w_1.xpm","cubfiles/xpm/p_ji_n_1.xpm","cubfiles/xpm/p_ji_e_1.xpm","cubfiles/xpm/p_ji_s_1.xpm"}[i],
				&img->size.x, &img->size.y);
		img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->size_line, &img->endian);
#else
		img->size = ivec(TEX_W, TEX_H);
		img->ptr = mlx_new_image(mlx->mlx, img->size.x, img->size.y);
		img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->size_line, &img->endian);
	}
	for(int y = 0; y < TEX_H; y++)
		for(int x = 0; x < TEX_W; x++)
		{
			int xorcolor = (x * 256 / TEX_W) ^ (y * 256 / TEX_H);
			int ycolor = (y * 32) % 256;
			int xycolor = y * 128 / TEX_H + x * 128 / TEX_W;
			put_pixel(&mlx->texture[0], x, y, 65536 * 192 * (x % 16 && y % 16)); //red bricks
			put_pixel(&mlx->texture[1], x, y, 256 * xorcolor); //xor green
			put_pixel(&mlx->texture[2], x, y, 0x100 * xycolor + 0x10000 * ycolor); //sloped yellow gradient
			put_pixel(&mlx->texture[3], x, y, xorcolor + 256 * xorcolor + 65536 * xorcolor); //xor greyscale
#endif
		}
	for (int i=0; i<4; i++)
	{
		t_img	*img = &mlx->texture[i];
		mlx_put_image_to_window(mlx->mlx, mlx->win, img->ptr, TEX_W*i, 0);
	}
	return (0);
}

int	init(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, SCREEN_W, SCREEN_H, "cub3d");
	{
		t_img	*img = &mlx->img;
		img->size = ivec(SCREEN_W, SCREEN_H);
		img->ptr = mlx_new_image(mlx->mlx, img->size.x, img->size.y);
		img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->size_line, &img->endian);
	}
	init_img(mlx);
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
	const t_ivec	size = ivec(MAP_W, MAP_H);
	if (ivec_in(pos, size))
		return (world[pos.y][pos.x]);
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

	for (int x = 0; x < size.x; ++x)
	{
		int		side = E_NONE;
		t_ivec	map_pos = ivec(player.x, player.y);
		t_vec	ray_dir;
		double	wall_dist;
		{
			const t_vec	camera = vec(x / (double)size.x * 2.0 - 1.0, 0);
			const t_vec	plane = vec_sca(vec_rot(dir, -M_PI_2), 0.75);
			ray_dir = vec_add(dir, vec_sca(plane, camera.x));
			const t_vec	delta_dist = vec(fabs(1.0 / ray_dir.x), fabs(1.0 / ray_dir.y));
			const t_ivec	step = ivec(copysign(1.0, ray_dir.x), copysign(1.0, ray_dir.y));

			t_vec	side_dist = vec_mul(vec(fabs(map_pos.x + (ray_dir.x >= 0) - player.x), fabs(map_pos.y + (ray_dir.y >= 0) - player.y)), delta_dist);
			while (1)
			{
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
					side = 3 - step.y;
				}
				if (world_ati(world, map_pos) != MAP_EMPTY)
					break ;
			}
			wall_dist = (side % 2 == 1) ? side_dist.x - delta_dist.x : side_dist.y - delta_dist.y;
		}
		{
			t_img	*img = &mlx->texture[side - 1];
			int		line_h = (int)(size.y / wall_dist);
			t_ivec	start = ivec(x, MAX(0, size.y / 2 - line_h / 2));
			t_ivec	end = ivec(x, MIN(size.y - 1, size.y / 2 + line_h / 2));

			double	wall_x = (side % 2 == 0) ? player.x + wall_dist * ray_dir.x : player.y + wall_dist * ray_dir.y;
			wall_x -= floor(wall_x);
			t_ivec	tex = ivec((int)(wall_x * img->size.x), 0);
			if ((side == 3) || (side == 4)) tex.x = img->size.x - tex.x - 1;

			double	step = (double)img->size.y / line_h;
			double	tex_pos = (start.y - SCREEN_H / 2. + line_h / 2.) * step;
			for (int y = start.y; y < end.y; ++y)
			{
				tex.y = (int)round(tex_pos);
				tex_pos += step;
				t_color	color = get_pixel(img, tex.x, tex.y);
				put_pixel(&mlx->img, x, y, color);
			}
		}
	}

	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.ptr, 0, 0);
	return (0);
}

t_vec	try_move(t_vec player, t_vec dir)
{
	if (world_at(world, vec_add(player, vec(dir.x, 0))) == MAP_EMPTY)
		player = vec_add(player, vec(dir.x, 0));
	if (world_at(world, vec_add(player, vec(0, dir.y))) == MAP_EMPTY)
		player = vec_add(player, vec(0, dir.y));
	return (player);
}

double	key_to_rad(int key)
{
	if (key == 'w')
		return (0.0);
	else if (key == 'a')
		return (M_PI_2);
	else if (key == 's')
		return (M_PI);
	else if (key == 'd')
		return (-M_PI_2);
	else if (key == XK_Up)
		return (0.0);
	else if (key == XK_Down)
		return (M_PI);
	return (0.0);
}

int	f_key_hook(int key, t_mlx *mlx)
{
	if (key == 'q' || key == XK_Escape)
		exit(0);
	else if (key == XK_Left || key == XK_Right)
	{
		double	speed = (double []){-M_PI, M_PI}[key == XK_Left] / 8;
		dir = vec_rot(dir, speed);
	}
	else if (key == XK_w || key == XK_a || key == XK_s || key == XK_d || key == XK_Up || key == XK_Down)
	{
		t_vec	d = vec_rot(dir, key_to_rad(key));
		d = vec_sca(d, 0.25);
		player = try_move(player, d);
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
	init(&mlx);
	loop(&mlx);
}

#if 0
__attribute__((destructor))
void	end(void)
{
	system("leaks -q a.out");
}
#endif
