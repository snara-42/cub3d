/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 03:20:41 by subaru            #+#    #+#             */
/*   Updated: 2023/09/25 03:22:42 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	init_ray(t_ray *r, const t_ctx *ctx, int x)
{
	const t_player	p = ctx->player;

	*r = (t_ray){};
	r->camera = vec(x / (double)ctx->mlx.img.size.x * 2.0 - 1.0, 0);
	r->plane = vec_sca(vec_rot(p.dir, -M_PI_2), 0.75);
	r->dir = vec_add(p.dir, vec_sca(r->plane, r->camera.x));
	r->delta_dist = vec(fabs(1.0 / r->dir.x), fabs(1.0 / r->dir.y));
	r->step = ivec(copysign(1.0, r->dir.x), copysign(1.0, r->dir.y));
	r->map_pos = ivec(p.pos.x, p.pos.y);
	r->side_dist = vec_mul(vec(fabs(r->map_pos.x + (r->dir.x >= 0) - p.pos.x),
				fabs(r->map_pos.y + (r->dir.y >= 0) - p.pos.y)), r->delta_dist);
}

void	simulate_ray(t_ray *r, const t_ctx *ctx)
{
	while (map_at_i(ctx->map, r->map_pos) != MAP_WALL)
	{
		if (r->side_dist.x < r->side_dist.y)
		{
			r->side_dist.x += r->delta_dist.x;
			r->map_pos.x += r->step.x;
			r->side = (int []){E_EA, E_WE}[r->dir.x < 0];
		}
		else
		{
			r->side_dist.y += r->delta_dist.y;
			r->map_pos.y += r->step.y;
			r->side = (int []){E_NO, E_SO}[r->dir.y < 0];
		}
	}
	if (r->side == E_WE || r->side == E_EA)
		r->wall_dist = r->side_dist.x - r->delta_dist.x;
	else
		r->wall_dist = r->side_dist.y - r->delta_dist.y;
	if (r->side == E_WE || r->side == E_EA)
		r->wall_x = ctx->player.pos.y + r->wall_dist * r->dir.y;
	else
		r->wall_x = ctx->player.pos.x + r->wall_dist * r->dir.x;
	r->wall_x -= floor(r->wall_x);
}

void	draw_line(t_ray *r, const t_ctx *ctx, int x)
{
	const t_ivec	size = ctx->mlx.img.size;
	const t_img		*img = &ctx->mlx.texture[r->side];
	t_draw			d;
	int				y;

	d.line_h = (int)(size.y / r->wall_dist);
	d.start = ivec(x, MAX(0, size.y / 2 - d.line_h / 2));
	d.end = ivec(x, MIN(size.y - 1, size.y / 2 + d.line_h / 2));
	d.step = (double)img->size.y / d.line_h;
	d.tex_pos = (d.start.y - SCREEN_H / 2. + d.line_h / 2.) * d.step;
	d.tex = ivec((int)(r->wall_x * img->size.x), 0);
	if ((r->side == E_EA) || (r->side == E_SO))
		d.tex.x = img->size.x - d.tex.x - 1;
	y = d.start.y;
	while (y < d.end.y)
	{
		d.tex.y = (int)round(d.tex_pos);
		put_pixel(&ctx->mlx.img, x, y, get_pixel(img, d.tex.x, d.tex.y));
		d.tex_pos += d.step;
		++y;
	}
}

int	f_draw(const t_ctx *ctx)
{
	const t_mlx	*mlx = &ctx->mlx;
	t_ray		r;
	int			x;

	draw_background(ctx);
	x = 0;
	while (x < mlx->img.size.x)
	{
		init_ray(&r, ctx, x);
		simulate_ray(&r, ctx);
		draw_line(&r, ctx, x);
		++x;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.ptr, 0, 0);
	return (0);
}
