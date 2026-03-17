/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 21:34:46 by vpoelman          #+#    #+#             */
/*   Updated: 2026/03/16 21:34:46 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static void	calculate_texture_coords(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_x = game->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = game->player.x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x
			* (double)game->textures[ray->tex_num].img.width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = game->textures[ray->tex_num].img.width - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = game->textures[ray->tex_num].img.width - ray->tex_x - 1;
	ray->step = 1.0 * game->textures[ray->tex_num].img.height
		/ ray->line_height;
	ray->tex_pos = (ray->draw_start - WINDOW_HEIGHT / 2 + ray->line_height / 2)
		* ray->step;
}

static int	get_texture_number(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x < 0)
			return (WEST);
		else
			return (EAST);
	}
	else
	{
		if (ray->ray_dir_y < 0)
			return (NORTH);
		else
			return (SOUTH);
	}
}

static void	draw_wall_pixels(t_game *game, t_ray *ray, int x, int y)
{
	int	tex_y;
	int	color;
	int	tex_h;
	int	tex_w;

	tex_h = game->textures[ray->tex_num].img.height;
	tex_w = game->textures[ray->tex_num].img.width;
	while (y < ray->draw_end)
	{
		tex_y = (int)ray->tex_pos % tex_h;
		ray->tex_pos += ray->step;
		if (tex_y < tex_h && ray->tex_x < tex_w)
			color = game->textures[ray->tex_num].texture[tex_y][ray->tex_x];
		else
			color = 0;
		if (ray->side == 1)
			color = (color >> 1) & DARK_MASK;
		put_pixel(&game->img, x, y, color);
		y++;
	}
}

void	draw_vertical_line(t_game *game, t_ray *ray, int x)
{
	ray->tex_num = get_texture_number(ray);
	calculate_texture_coords(game, ray);
	draw_wall_pixels(game, ray, x, ray->draw_start);
}
