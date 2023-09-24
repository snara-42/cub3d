/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:35:04 by subaru            #+#    #+#             */
/*   Updated: 2023/09/25 03:22:49 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "vec.h"

#include <stdio.h>
#include <sys/param.h>

void	put_pixel(const t_img *img, int x, int y, t_color color)
{
	const t_ivec	size = img->size;

	if (ivec_in(ivec(x, y), size))
		*(t_color *)&img->addr
			[y * img->size_line + x * (img->bpp / CHAR_BIT)] = color;
}

t_color	get_pixel(const t_img *img, int x, int y)
{
	const t_ivec	size = img->size;

	if (ivec_in(ivec(x, y), size))
		return (*(t_color *)&img->addr
			[y * img->size_line + x * (img->bpp / CHAR_BIT)]);
	return (~0);
}

void	draw_vline(const t_img *img, t_ivec a, t_ivec b, t_color color)
{
	const t_ivec	size = img->size;
	int				y;
	int				end;

	if (!(ivec_in(a, size) && ivec_in(b, size)))
		return ((void)printf("!%s[%06x](%d,%d)->(%d,%d)\n",
				__func__, color, a.x, a.y, b.x, b.y));
	y = MIN(a.y, b.y);
	end = MAX(a.y, b.y);
	while (y < end)
	{
		put_pixel(img, a.x, y++, color);
	}
}

void	draw_hline(const t_img *img, t_ivec a, t_ivec b, t_color color)
{
	const t_ivec	size = img->size;
	int				x;
	int				end;

	if (!(ivec_in(a, size) && ivec_in(b, size)))
		return ((void)printf("!%s[%06x](%d,%d)->(%d,%d)\n",
				__func__, color, a.x, a.y, b.x, b.y));
	x = MIN(a.x, b.x);
	end = MAX(a.x, b.x);
	while (x < end)
	{
		put_pixel(img, x++, a.y, color);
	}
}

void	draw_background(const t_ctx *ctx)
{
	const t_ivec	size = ctx->mlx.img.size;
	int				y;

	y = -1;
	while (++y < size.y / 2)
	{
		draw_hline(&ctx->mlx.img, ivec(0, y), ivec(SCREEN_W - 1, y),
			ctx->color[E_CEIL]);
	}
	while (++y < size.y)
	{
		draw_hline(&ctx->mlx.img, ivec(0, y), ivec(SCREEN_W - 1, y),
			ctx->color[E_FLOOR]);
	}
}
