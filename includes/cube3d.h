/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 21:34:46 by vpoelman          #+#    #+#             */
/*   Updated: 2026/03/16 21:34:46 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

# ifdef __linux__
#  include <X11/X.h>
#  include <X11/keysym.h>
# endif

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720
# define FOV 66
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03
# define DARK_MASK 0x7F7F7F

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

# ifdef __linux__
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_ESC 65307
# else
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_ESC 53
# endif

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct s_texture
{
	t_img		img;
	int			**texture;
}				t_texture;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct s_ray
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			tex_num;
	double		wall_x;
	int			tex_x;
	double		step;
	double		tex_pos;
}				t_ray;

typedef struct s_keys
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			left;
	int			right;
}				t_keys;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	char		**map;
	int			map_width;
	int			map_height;
	t_player	player;
	t_keys		keys;
	t_texture	textures[4];
	int			floor_color;
	int			ceiling_color;
	int			has_moved;
}				t_game;

/* parsing/parse_file.c */
int				parse_file(char *filename, t_game *game);

/* parsing/parse_map.c */
int				parse_map(char **lines, t_game *game, int start);
int				find_max_width(char **lines, int start);

/* parsing/parse_elements.c */
int				parse_elements(char **lines, t_game *game);

/* parsing/validate_map.c */
int				validate_map(t_game *game);

/* parsing/map_alloc.c */
char			**allocate_map(int height, int width);
char			**create_visited_map(t_game *game);
void			free_visited_map(char **visited, int height);

/* parsing/utils.c */
char			**read_file_lines(char *filename);
int				count_lines(char **lines);
void			free_lines(char **lines);
int				is_valid_extension(char *filename, char *extension);

/* parsing/parse_colors.c */
int				parse_color(char *line, t_game *game, int is_ceiling);

/* parsing/gnl.c */
char			*get_next_line(int fd);

/* game/game.c */
int				init_game(t_game *game);
int				game_loop(t_game *game);
void			init_player_direction(t_game *game, char dir);

/* game/hooks.c */
int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_game *game);

/* game/movement.c */
void			handle_movement(t_game *game);

/* raycasting/raycasting.c */
void			raycasting(t_game *game);

/* raycasting/dda.c */
void			calculate_ray(t_game *game, t_ray *ray, int x);
void			perform_dda(t_game *game, t_ray *ray);

/* raycasting/render.c */
void			draw_vertical_line(t_game *game, t_ray *ray, int x);

/* raycasting/texture.c */
int				load_textures(t_game *game);
int				load_texture_from_file(t_game *game, t_texture *texture,
					char *path);
void			free_texture(t_game *game, t_texture *texture);

/* utils/graphics.c */
int				create_rgb(int r, int g, int b);
int				get_pixel_color(t_img *img, int x, int y);
void			put_pixel(t_img *img, int x, int y, int color);

/* utils/error.c */
int				print_error(char *message, t_game *game);

/* utils/cleanup.c */
void			cleanup_game(t_game *game);
void			free_map(char **map);
int				close_game(t_game *game);

#endif