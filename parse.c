/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 09:04:01 by subaru            #+#    #+#             */
/*   Updated: 2023/09/23 19:45:50 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

#include <mlx.h>

#include <stdint.h>
#include <stddef.h>
#include <limits.h>
#include <stdbool.h>

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

bool	parse_config(t_ctx *ctx, int fd);
bool	parse_map(t_ctx *ctx, int fd);

int	parse_file(t_ctx *ctx, const char *path)
{
	int	fd;

	if (!!ft_strrcmp(path, ".cub", 4))
		or_exit(NULL, "file extension must be '.cub'");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		or_exit(NULL, "could not open file");
	*ctx = (t_ctx){.mlx = ctx->mlx, .color = {COLOR_DFL, COLOR_DFL}};
	parse_config(ctx, fd);
	parse_map(ctx, fd);
	close(fd);
	return (0);
}
