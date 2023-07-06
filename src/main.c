/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 20:16:42 by gde-mora          #+#    #+#             */
/*   Updated: 2023/07/05 21:41:41 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/miniRT.h"

# include <signal.h>
t_data	*g_aux_data; //Enqunto fazemos os testes

static void	test_handler(int signal);

void	signals_handling(t_data *data)
{
	struct sigaction	test;

	g_aux_data = data;
	ft_bzero(&test, sizeof(struct sigaction));
	test.sa_handler = test_handler;
	sigaction(SIGTERM, &test, NULL);
}

static void	test_handler(int signal)
{
	(void)signal;
	g_aux_data->debug_exit = 1;
}

int	main(int argc, char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(data)); //
	signals_handling(&data); // Lidando com o sinal do tester.
	init_data(&data); //
	validate_scene_file(argc, argv, &data); //
	read_scene_file(argv[1], &data); //
	get_scene_info(&data);
	render(&data);
	return (0);
}
