/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:55:50 by gsmereka          #+#    #+#             */
/*   Updated: 2023/08/08 18:38:25 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/miniRT.h"


void	criar_relogio(t_data *data)
{
	t_tuple	*relogio;
	t_tuple	*twelve;
	t_tuple	*three;
	t_matrix	*r;

	(void)data;
	// passo 2
	relogio = create_point(0, 0, 0);
	twelve = create_point(0, 0, 1);

	// passo 3
	r = rotation_y(data, (3 * M_PI) / 6);
	three = multiply_matrix_with_tuple(r, twelve);
	print_tuple(three);
	free(twelve);
	free(three);
	free_matrix(r);
	free(relogio);
}

// void	paint_matrix(t_matrix *matrix)
// {

// }

static int	handle_render(t_data *data)
{
	int		i;
	int		pos;

	i = 0;
	data->address_img = mlx_get_data_addr(data->img, &data->bits_per_pixel, \
		&data->size_line, &data->endian);
	pos = 50;
	while (i < 16)
	{
		paint_pixel(pos + i, pos, RED, data);
		paint_pixel(pos, pos + i, RED, data);
		paint_pixel(pos + i, pos + 15, BLUE, data);
		paint_pixel(pos + 15, pos + i, BLUE, data);
		i++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
	return (0);
}

int	test_render(t_data	*data)
{
	// criar_relogio(data);
	// exit_error("", 0, data);
	data->mlx_ptr = mlx_init();
	if (!(data->mlx_ptr))
		exit_error(INTERFACE_ERROR, 2, data);
	if (!data->win_width && !data->win_height)
	{
		data->win_width = 500;
		data->win_height = 500;
	}
	data->win_ptr = mlx_new_window(data->mlx_ptr, \
		data->win_width, data->win_height, "miniRT");
	data->img = mlx_new_image(data->mlx_ptr, data->win_width, data->win_height);
	mlx_expose_hook(data->win_ptr, &handle_render, data);
	mlx_key_hook(data->win_ptr, &handle_esc, data);
	mlx_hook(data->win_ptr, 17, 0, &handle_x, data);
	mlx_loop(data->mlx_ptr);
	return (1);
}
