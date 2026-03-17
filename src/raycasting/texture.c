/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 21:34:46 by vpoelman          #+#    #+#             */
/*   Updated: 2026/03/16 21:34:46 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static int	**allocate_texture_array(int width, int height)
{
	int	**texture;
	int	i;

	texture = malloc(sizeof(int *) * height);
	if (!texture)
		return (NULL);
	i = 0;
	while (i < height)
	{
		texture[i] = malloc(sizeof(int) * width);
		if (!texture[i])
		{
			while (--i >= 0)
				free(texture[i]);
			free(texture);
			return (NULL);
		}
		i++;
	}
	return (texture);
}

static void	copy_texture_data(t_texture *texture)
{
	int	x;
	int	y;

	y = 0;
	while (y < texture->img.height)
	{
		x = 0;
		while (x < texture->img.width)
		{
			texture->texture[y][x] = get_pixel_color(&texture->img, x, y);
			x++;
		}
		y++;
	}
}

int	load_texture_from_file(t_game *game, t_texture *texture, char *path)
{
	texture->img.img = mlx_xpm_file_to_image(game->mlx, path,
			&texture->img.width, &texture->img.height);
	if (!texture->img.img)
		return (print_error("Could not load texture", game));
	texture->img.addr = mlx_get_data_addr(texture->img.img,
			&texture->img.bits_per_pixel, &texture->img.line_length,
			&texture->img.endian);
	texture->texture = allocate_texture_array(texture->img.width,
			texture->img.height);
	if (!texture->texture)
		return (print_error("Memory allocation failed for texture", game));
	copy_texture_data(texture);
	return (0);
}

int	load_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!game->textures[i].img.img || !game->textures[i].texture)
			return (print_error("Texture not properly loaded", game));
		i++;
	}
	return (0);
}

void	free_texture(t_game *game, t_texture *texture)
{
	int	i;

	if (texture->img.img)
	{
		mlx_destroy_image(game->mlx, texture->img.img);
		texture->img.img = NULL;
	}
	if (texture->texture)
	{
		i = 0;
		while (i < texture->img.height)
		{
			free(texture->texture[i]);
			i++;
		}
		free(texture->texture);
		texture->texture = NULL;
	}
}
