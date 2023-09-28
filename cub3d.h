/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 03:26:15 by subaru            #+#    #+#             */
/*   Updated: 2023/09/28 20:59:23 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdint.h>
# include <stdbool.h>
# include <stddef.h>
# include <limits.h>
# include "vec.h"

# define SCREEN_W 640
# define SCREEN_H 480

# define MAP_W 1024
# define MAP_H 1024

# define MAP_EMPTY '0'
# define MAP_WALL '1'

# define COLOR_DFL ~0u

typedef uint32_t		t_color;
typedef char			t_map[1024][1024];

enum	e_dir
{
	E_L = 0,
	E_U = 1,
	E_R = 2,
	E_D = 3,
	E_WE = 0,
	E_NO = 1,
	E_EA = 2,
	E_SO = 3,
};
typedef enum e_dir		t_e_dir;

enum	e_color
{
	E_CEIL = 0,
	E_FLOOR = 1,
};

struct s_ray
{
	t_vec	dir;
	t_e_dir	side;
	double	wall_dist;
	double	wall_x;
	t_vec	camera;
	t_vec	plane;
	t_vec	delta_dist;
	t_vec	side_dist;
	t_ivec	step;
	t_ivec	map_pos;
};
typedef struct s_ray	t_ray;

struct s_draw
{
	int		line_h;
	t_ivec	start;
	t_ivec	end;
	t_ivec	tex;
	double	step;
	double	tex_pos;
};
typedef struct s_draw	t_draw;

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

struct	s_player
{
	t_vec	pos;
	t_vec	dir;
};
typedef struct s_player	t_player;

struct	s_ctx
{
	t_mlx		mlx;
	t_color		color[2];
	t_map		map;
	t_player	player;
};
typedef struct s_ctx	t_ctx;

//////////////////////////////////////////

bool	parse_config(t_ctx *ctx, int fd);
bool	parse_map(t_ctx *ctx, int fd);
int		parse_file(t_ctx *ctx, const char *path);

void	print_map(const t_ctx *ctx);
void	print_ctx(const t_ctx *ctx);

t_vec	try_move(const t_map map, t_vec pos, t_vec dir);
int		map_at_i(const t_map map, t_ivec pos);

void	put_pixel(const t_img *img, int x, int y, t_color color);
t_color	get_pixel(const t_img *img, int x, int y);
void	draw_background(const t_ctx *ctx);

int		f_exit(t_ctx *ctx);
int		f_draw(const t_ctx *ctx);
int		f_key_hook(int key, t_ctx *ctx);
int		f_mouse_hook(int button, int x, int y, t_ctx *ctx);

#endif
