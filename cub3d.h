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

#define COLOR_DFL ~0u

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
enum	e_color
{
	E_CEIL = 0,
	E_FLOOR = 1,
};

typedef uint32_t	t_color;

typedef char	t_map[MAP_W][MAP_H];

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

#endif
