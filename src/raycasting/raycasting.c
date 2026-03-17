/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 21:34:46 by vpoelman          #+#    #+#             */
/*   Updated: 2026/03/16 21:34:46 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static void	fill_background_section(t_game *game, int start_y, int end_y,
		int color)
{
	int	x;
	int	y;

	y = start_y;
	while (y < end_y)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			put_pixel(&game->img, x, y, color);
			x++;
		}
		y++;
	}
}

static void	draw_ceiling_floor(t_game *game)
{
	fill_background_section(game, 0, WINDOW_HEIGHT / 2, game->ceiling_color);
	fill_background_section(game, WINDOW_HEIGHT / 2, WINDOW_HEIGHT,
		game->floor_color);
}

void	raycasting(t_game *game)
{
	t_ray	ray;
	int		x;

	draw_ceiling_floor(game);
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		calculate_ray(game, &ray, x);
		perform_dda(game, &ray);
		draw_vertical_line(game, &ray, x);
		x++;
	}
}
