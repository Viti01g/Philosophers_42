/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vruiz-go <vruiz-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:28:06 by vruiz-go          #+#    #+#             */
/*   Updated: 2023/10/05 16:42:29 by vruiz-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	freeall(t_gen *data)
{
	int	i;

	i = -1;
	/* while (++i < data->num_philos)
	{
		pthread_mutex_destroy(data->philo[i].tenedo_izq);
		pthread_mutex_destroy(data->philo[i].tenedo_drch);
	} */
	free(data->philo);
	pthread_mutex_destroy(data->mu_print);
}
void	msg_err(char *msg, t_gen *gen)
{
	if (gen->flag >= 1)
		gen->flag = 1;
	//freeall(gen);
	printf("%s\n", msg);
	exit(EXIT_FAILURE);

}

void	ft_print_msgs(t_philo *philo, char *msg)
{
	long	time_aux;

	pthread_mutex_lock(philo->mu_print_ph);
	time_aux = get_time() - philo->start_time_philo;
	if (philo->life != FALSE)
		printf("%ld ms -- philo %d %s\n", time_aux, philo->id, msg);
	pthread_mutex_unlock(philo->mu_print_ph);
}
