/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_key_hook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 03:21:14 by subaru            #+#    #+#             */
/*   Updated: 2023/09/25 03:21:21 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "vec.h"

#include <mlx.h>
#include <X11/keysym.h>
#include <X11/X.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int	f_exit(t_ctx *ctx)
{
	t_mlx *const	mlx = &ctx->mlx;

	if (mlx && mlx->win)
		mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
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
	printf("k=%d p=(%f,%f)(%f,%f)\n", key, pos->x, pos->y, dir->x, dir->y);
	f_draw(ctx);
	return (0);
}