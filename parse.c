#include "cub3d.h"

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

#define C_DFL ~0u

char	*get_next_line(int fd);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_sscanf(const char *s, const char *fmt, ...);

void	*or_exit(void *p, const char *msg)
{
	if (p != NULL)
		return (p);
	printf("Error\n%s\n", msg);
	if (errno != 0 && errno != EAGAIN)
		perror("");
	exit(1);
}

char	*str_skip(const char *s, char c)
{
	while (*s == c)
		s++;
	return ((char *)s);
}

char	*ft_strchr(const char *s, char c)
{
	while (*s && *s != c)
		s++;
	if (*s == c)
		return ((char *)s);
	return (NULL);
}

int		ft_strncmp(const char *s, const char *t, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s[i] && t[i] && s[i] == t[i])
		i++;
	if (i >= n)
		return (0);
	return (t[i] - s[i]);
}

int		ft_strrcmp(const char *s, const char *t, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	m;

	i = 0;
	while (s[i])
		i++;
	j = 0;
	while (t[j])
		j++;
	m = 0;
	while (m < n && m < i && m < j && s[i - m] == t[j - m])
		m++;
	if (m >= n)
		return (0);
	return (t[j - m] - s[i - m]);
}

static t_color	rgb_to_color(t_color rgb[3])
{
	const uint8_t	r = rgb[0];
	const uint8_t	g = rgb[1];
	const uint8_t	b = rgb[2];

	return (r << 16 | g << 8 | b << 0);
}

static bool	in_range(int n, int min, int max)
{
	return (min <= n && n < max);
}

t_color	parse_color(t_color *p, const char *s)
{
	t_color	rgb[3];

	if (*p != C_DFL)
		or_exit(NULL, "duplicate color configuration");
	if (ft_sscanf(s, "%u,%u,%u", &rgb[0], &rgb[1], &rgb[2]) != 3)
		or_exit(NULL, "invalid color configuration");
	if (!(in_range(rgb[0], 0, 256) && in_range(rgb[1], 0, 256) && in_range(rgb[2], 0, 256)))
		or_exit(NULL, "color out of range");
	*p = rgb_to_color(rgb);
	return (*p);
}

bool	is_valid_config(t_ctx *ctx)
{
	if (!(ctx->mlx.texture[0].ptr && ctx->mlx.texture[1].ptr
		&& ctx->mlx.texture[2].ptr && ctx->mlx.texture[3].ptr))
		return (false);
	if (ctx->color[0] == C_DFL || ctx->color[1] == C_DFL)
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

bool	read_config(t_ctx *ctx, int fd)
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

static t_player	get_start_pos(const t_map map)
{
	size_t	x;
	size_t	y;
	char	c;

	y = 0;
	while (y < MAP_H)
	{
		x = 0;
		while (x < MAP_W && map[y][x])
		{
			c = map[y][x];
			if (c == 'W')
				return ((t_player){vec(x + .5, y + .5), vec(-1, 0)});
			else if (c == 'N')
				return ((t_player){vec(x + .5, y + .5), vec(0, -1)});
			else if (c == 'E')
				return ((t_player){vec(x + .5, y + .5), vec(+1, 0)});
			else if (c == 'S')
				return ((t_player){vec(x + .5, y + .5), vec(0, +1)});
			x++;
		}
		y++;
	}
	or_exit(NULL, "missing start position");
	return ((t_player){});
}

static bool	floodfill(const t_map map, t_map filled, int x, int y)
{
	bool	is_surrounded;

	if (!(0 <= x && x < MAP_W && 0 <= y && y < MAP_H))
		return (false);
	if (filled[y][x] || map[y][x] == MAP_WALL)
		return (true);
	filled[y][x] = true;
	is_surrounded = 
		floodfill(map, filled, x - 1, y)
		&& floodfill(map, filled, x + 1, y)
		&& floodfill(map, filled, x, y - 1)
		&& floodfill(map, filled, x, y + 1);
	return (is_surrounded);
}

bool	is_map_surrounded(const t_map map)
{
	const t_player	start = get_start_pos(map);
	const bool		is_surrounded = floodfill(
			map, (t_map){}, start.pos.x, start.pos.y);

	return (is_surrounded);
}

bool	is_valid_map(const t_map map)
{
	size_t	x;
	size_t	y;
	char	c;
	size_t	configured;

	configured = 0;
	y = 0;
	while (y < MAP_H)
	{
		x = 0;
		while (x < MAP_W && map[y][x])
		{
			c = map[y][x];
			if (!ft_strchr("01 NSEW", c))
				or_exit(NULL, "invalid character in map");
			if (ft_strchr("NSEW", c) && configured++)
				or_exit(NULL, "duplicate start pos");
			x++;
		}
		y++;
	}
	if (!configured)
		or_exit(NULL, "missing start pos");
	if (!is_map_surrounded(map))
		or_exit(NULL, "map not surrounded by wall");
	return (true);
}

bool	read_map(t_ctx *ctx, int fd)
{
	size_t	y;
	char	*s;

	y = 0;
	while (1)
	{
		s = get_next_line(fd);
		if (!s)
			break ;
		if (ft_strlcpy(ctx->map[y], s, MAP_W) >= MAP_W)
			or_exit(NULL, "map too wide");
		if (++y >= MAP_H)
			or_exit(NULL, "map too long");
		free(s);
	}
	if (!is_valid_map(ctx->map))
		or_exit(NULL, "map invalid");
	ctx->player = get_start_pos(ctx->map);
	return (true);
}

int	parse_file(t_ctx *ctx, const char *path)
{
	int	fd;
	
	if (!!ft_strrcmp(path, ".cub", 4))
		or_exit(NULL, "file extension must be '.cub'");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		or_exit(NULL, "could not open file");
	read_config(ctx, fd);
	read_map(ctx, fd);
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

static int	init(t_mlx *mlx)
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
	t_ctx	ctx = {{}, .color = {C_DFL, C_DFL},};
	t_mlx	*mlx = &ctx.mlx;

	if (ac != 2)
		or_exit(NULL, "usage: ./cub3d cubfile");
	init(&ctx.mlx);
	parse_file(&ctx, av[1]);
	print_ctx(&ctx);
	//
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->texture[0].ptr, 10, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->texture[1].ptr, 100, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->texture[2].ptr, 200, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->texture[3].ptr, 300, 0);
	sleep(1);
	//mlx_loop(ctx.mlx.mlx);
}

#endif
