/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vruiz-go <vruiz-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:27:15 by vruiz-go          #+#    #+#             */
/*   Updated: 2023/10/10 15:35:45 by vruiz-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_pedir_cuenta(t_gen *gen)
{
	int	i;

	gen->num_eats = 0;
	while (1)
	{
		i = 0;
		while (i < gen->num_philos)
		{
			pthread_mutex_lock(gen->mu_data);
			if (ft_caducado(gen, i) == 0)
				return ;
			pthread_mutex_unlock(gen->mu_data);
			i++;
		}
	}
}

int	main(int argc, char **argv)
{
	char **argf;
	argf = argv;
	t_gen	gen;

	if (argc == 5 || argc == 6)
	{
		init_variable(&gen, argv, argc);
		ft_start_party(&gen);
		ft_pedir_cuenta(&gen);
	}
	else
		msg_err("Invalid number of arguments.", &gen);
	return (0);
}
