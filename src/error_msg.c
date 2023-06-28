/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:47:18 by gsmereka          #+#    #+#             */
/*   Updated: 2023/06/28 16:03:53 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/miniRT.h"

int	error_msg(int error)
{
	if (error == COUNT_ERROR)
	{
		ft_printf("Error\nOnly one file allowed\n");
	}
	if (error == FILE_EXTENSION_ERROR)
	{
		ft_printf("Error\nOnly files with the '.rt' extension allowed\n");
	}
	return (0);
}