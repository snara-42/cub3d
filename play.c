#include "cub3d.h"
#include "vec.h"

#include <mlx.h>
#include <X11/keysym.h>
#include <X11/X.h>

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <limits.h>
#include <sys/param.h>
#include <math.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#if 0
# define printf (void)
#endif

t_vec	try_move(const t_map map, t_vec pos, t_vec dir);
int		map_at_i(const t_map map, t_ivec pos);

int		f_exit(t_ctx *ctx);

void	put_pixel(const t_img *img, int x, int y, t_color color);
t_color	get_pixel(const t_img *img, int x, int y);

void	draw_background(const t_ctx *ctx);

int	draw(const t_ctx *ctx)
{
	const t_mlx *const	mlx = &ctx->mlx;
	const t_img *const	img = &mlx->img;
	const t_vec *const	pos = &ctx->player.pos;
	const t_vec *const	dir = &ctx->player.dir;
	const t_ivec		size = mlx->img.size;

	draw_background(ctx);
	for (int x = 0; x < size.x; ++x)
	{
		int		side;
		t_ivec	map_pos = ivec(pos->x, pos->y);
		t_vec	ray_dir;
		double	wall_dist;
		{
			const t_vec	camera = vec(x / (double)size.x * 2.0 - 1.0, 0);
			const t_vec	plane = vec_sca(vec_rot(*dir, -M_PI_2), 0.75);
			ray_dir = vec_add(*dir, vec_sca(plane, camera.x));
			const t_vec	delta_dist = vec(fabs(1.0 / ray_dir.x), fabs(1.0 / ray_dir.y));
			const t_ivec	step = ivec(copysign(1.0, ray_dir.x), copysign(1.0, ray_dir.y));

			t_vec	side_dist = vec_mul(vec(fabs(map_pos.x + (ray_dir.x >= 0) - pos->x), fabs(map_pos.y + (ray_dir.y >= 0) - pos->y)), delta_dist);
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
				if (map_at_i(ctx->map, map_pos) != MAP_EMPTY)
					break ;
			}
			wall_dist = (side % 2 == 1) ? side_dist.x - delta_dist.x : side_dist.y - delta_dist.y;
		}
		{
			const t_img	*img = &mlx->texture[side - 1];
			int		line_h = (int)(size.y / wall_dist);
			t_ivec	start = ivec(x, MAX(0, size.y / 2 - line_h / 2));
			t_ivec	end = ivec(x, MIN(size.y - 1, size.y / 2 + line_h / 2));

			double	wall_x = (side % 2 == 0) ? pos->x + wall_dist * ray_dir.x : pos->y + wall_dist * ray_dir.y;
			wall_x -= floor(wall_x);
			t_ivec	tex = ivec((int)(wall_x * img->size.x), 0);
			if ((side == 3) || (side == 4))
				tex.x = img->size.x - tex.x - 1;

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

double	key_to_rad(int key)
{
	if (key == XK_w || key == XK_Up)
		return (0.0);
	else if (key == XK_a)
		return (M_PI_2);
	else if (key == XK_s || key == XK_Down)
		return (M_PI);
	else if (key == XK_d)
		return (-M_PI_2);
	return (0.0);
}

int	f_key_hook(int key, t_ctx *ctx)
{
	t_vec *const	pos = &ctx->player.pos;
	t_vec *const	dir = &ctx->player.dir;

	if (key == XK_q || key == XK_Q || key == XK_Escape)
		f_exit(ctx);
	else if (key == XK_Left || key == XK_Right)
	{
		*dir = vec_rot(*dir, (double []){-M_PI_4, M_PI_4}[key == XK_Left]);
	}
	else if (key == XK_w || key == XK_a || key == XK_s || key == XK_d
			|| key == XK_Up || key == XK_Down)
	{
		ctx->player.pos = try_move(ctx->map, *pos,
				vec_sca(vec_rot(*dir, key_to_rad(key)), 0.5));
	}
	printf("k=%d p=(%f,%f)(%f,%f)\n", key, dir->x, dir->y, pos->x, pos->y);
	draw(ctx);
	return (0);
}

#if 0

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
		mlx_put_image_to_window(mlx->mlx, mlx->win, img->ptr, img->size.x * i, 0);
	}
	return (0);
}

int	init(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, SCREEN_W, SCREEN_H, "cub3d");
	t_img	*img = &mlx->img;
	img->size = ivec(SCREEN_W, SCREEN_H);
	img->ptr = mlx_new_image(mlx->mlx, img->size.x, img->size.y);
	img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->size_line, &img->endian);
	init_img(mlx);

	mlx_do_key_autorepeaton(mlx->mlx);
	//mlx_loop_hook(mlx->mlx, draw, mlx);
	mlx_key_hook(mlx->win, f_key_hook, mlx);
	mlx_hook(mlx->win, DestroyNotify, StructureNotifyMask, f_exit, mlx);
	return (0);
}

int	main()
{
	t_mlx	mlx = {};
	init(&mlx);
	loop(&mlx);
}
#endif

#if 0

__attribute__((destructor))
void	end(void)
{
	system("leaks -q a.out");
}

#endif
