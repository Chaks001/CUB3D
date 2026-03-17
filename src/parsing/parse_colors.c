/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoelman <vpoelman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 21:34:46 by vpoelman          #+#    #+#             */
/*   Updated: 2026/03/16 21:34:46 by vpoelman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && !ft_isspace(str[i]))
			return (0);
		if (ft_isspace(str[i]))
		{
			while (str[i] && ft_isspace(str[i]))
				i++;
			if (str[i])
				return (0);
			break ;
		}
		i++;
	}
	return (1);
}

static int	set_color(t_game *game, int type, char **rgb)
{
	int	r;
	int	g;
	int	b;

	if (!is_valid_number(rgb[0]) || !is_valid_number(rgb[1])
		|| !is_valid_number(rgb[2]))
		return (print_error("Color values must be between 0 and 255", game));
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (print_error("Color values must be between 0 and 255", game));
	if (type == 0)
		game->floor_color = create_rgb(r, g, b);
	else
		game->ceiling_color = create_rgb(r, g, b);
	return (0);
}

static int	check_duplicate(t_game *game, int type)
{
	if (type == 0 && game->floor_color != -1)
		return (print_error("Duplicate color definition", game));
	if (type == 1 && game->ceiling_color != -1)
		return (print_error("Duplicate color definition", game));
	return (0);
}

int	parse_color(char *line, t_game *game, int type)
{
	char	**rgb;
	int		i;
	int		ret;

	if (check_duplicate(game, type))
		return (1);
	i = 0;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!line[i])
		return (print_error("Missing color values", game));
	rgb = ft_split(&line[i], ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		free_lines(rgb);
		return (print_error("Invalid color format (R,G,B)", game));
	}
	ret = set_color(game, type, rgb);
	free_lines(rgb);
	return (ret);
}
