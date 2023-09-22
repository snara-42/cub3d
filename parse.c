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
	parse_config(ctx, fd);
	parse_map(ctx, fd);
	close(fd);
	return (0);
}

#if 1

static void	print_ctx(const t_ctx *ctx)
{
	const t_player	p = ctx->player;

	for (int i = 0; i < 4; i++)
	{
		const t_img img = ctx->mlx.texture[i];
		printf("texture [%p](%u*%u)\n", img.addr, img.size.x, img.size.y);
	}
	printf("C=%#06x F=%#06x\n", ctx->color[0], ctx->color[1]);
	printf("player = (%f,%f),(%f,%f)\n", p.pos.x, p.pos.y, p.dir.x, p.dir.y);
	for (int y = 0; y < MAP_H; y++)
		printf("%s%s", ctx->map[y], &"\n"[!ctx->map[y][0]]);
}

static int	init_mlx(t_mlx *mlx)
{
	t_img	* const img = &mlx->img;

	mlx->mlx = or_exit(mlx_init(), __func__);
	mlx->win = or_exit(mlx_new_window(mlx->mlx, SCREEN_W, SCREEN_H, "cub3d"), __func__);
	img->size = ivec(SCREEN_W, SCREEN_H);
	img->ptr = or_exit(mlx_new_image(mlx->mlx, img->size.x, img->size.y), __func__);
	img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->size_line, &img->endian);
	return (0);
}

int	main(int ac, char *av[])
{
	t_ctx	ctx = {{}, .color = {COLOR_DFL, COLOR_DFL},};
	t_mlx	*mlx = &ctx.mlx;

	if (ac != 2)
		or_exit(NULL, "usage: ./cub3d cubfile");
	init_mlx(&ctx.mlx);
	parse_file(&ctx, av[1]);
	print_ctx(&ctx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->texture[0].ptr, 10, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->texture[1].ptr, 100, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->texture[2].ptr, 200, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->texture[3].ptr, 300, 0);
	sleep(1);
}

#endif
