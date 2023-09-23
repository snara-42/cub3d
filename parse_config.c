/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 09:05:51 by subaru            #+#    #+#             */
/*   Updated: 2023/09/23 19:42:18 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <mlx.h>

#include <stdlib.h>

static t_color	rgb_to_color(t_color rgb[3])
{
	const uint8_t	r = rgb[0];
	const uint8_t	g = rgb[1];
	const uint8_t	b = rgb[2];

	return (r << 16 | g << 8 | b << 0);
}

t_color	parse_color(t_color *p, const char *s)
{
	t_color	rgb[3];

	if (*p != COLOR_DFL)
		or_exit(NULL, "duplicate color configuration");
	if (ft_sscanf(s, "%u,%u,%u", &rgb[0], &rgb[1], &rgb[2]) != 3)
		or_exit(NULL, "invalid color configuration");
	if (!(in_range(rgb[0], 0, 256) && in_range(rgb[1], 0, 256)
			&& in_range(rgb[2], 0, 256)))
		or_exit(NULL, "color out of range");
	*p = rgb_to_color(rgb);
	return (*p);
}

bool	is_valid_config(t_ctx *ctx)
{
	if (!(ctx->mlx.texture[0].ptr && ctx->mlx.texture[1].ptr
			&& ctx->mlx.texture[2].ptr && ctx->mlx.texture[3].ptr))
		return (false);
	if (ctx->color[0] == COLOR_DFL || ctx->color[1] == COLOR_DFL)
		return (false);
	return (true);
}

bool	init_img(t_mlx *mlx, t_img *img, const char *path)
{
	if (img->ptr)
		or_exit(NULL, "duplicate texture configuration");
	img->ptr = or_exit(mlx_xpm_file_to_image(mlx->mlx, (char *)path,
				&img->size.x, &img->size.y), "failed to load xpm file");
	img->addr = or_exit(mlx_get_data_addr(img->ptr, &img->bpp, &img->size_line,
				&img->endian), "failed to get_data_addr");
	return (!!img->ptr);
}

bool	parse_config(t_ctx *ctx, int fd)
{
	char		*s;

	while (!is_valid_config(ctx))
	{
		s = get_next_line(fd);
		if (!s)
			or_exit(NULL, "missing configuration");
		else if (!ft_strncmp("WE ", s, 3))
			init_img(&ctx->mlx, &ctx->mlx.texture[E_WE], str_skip(&s[3], ' '));
		else if (!ft_strncmp("NO ", s, 3))
			init_img(&ctx->mlx, &ctx->mlx.texture[E_NO], str_skip(&s[3], ' '));
		else if (!ft_strncmp("EA ", s, 3))
			init_img(&ctx->mlx, &ctx->mlx.texture[E_EA], str_skip(&s[3], ' '));
		else if (!ft_strncmp("SO ", s, 3))
			init_img(&ctx->mlx, &ctx->mlx.texture[E_SO], str_skip(&s[3], ' '));
		else if (!ft_strncmp("C ", s, 2))
			parse_color(&ctx->color[E_CEIL], &s[2]);
		else if (!ft_strncmp("F ", s, 2))
			parse_color(&ctx->color[E_FLOOR], &s[2]);
		else if (!!ft_strncmp("", s, 1))
			or_exit(NULL, "unknown element");
		free(s);
	}
	return (true);
}
