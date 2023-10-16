/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vruiz-go <vruiz-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:28:06 by vruiz-go          #+#    #+#             */
/*   Updated: 2023/10/16 19:17:49 by vruiz-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	ft_free_mllc(t_gen *gen)
{
	if (gen->philo)
		free(gen->philo);
	if (gen->forks)
		free(gen->forks);
	if (gen->mu_data)
		free(gen->mu_data);
	if (gen->mu_print)
		free(gen->mu_print);
	if (gen->philo_id)
		free(gen->philo_id);
}

void	ft_free_mtx(t_gen *gen)
{
	int	i;

	i = -1;
	while (++i < gen->num_philos)
		pthread_mutex_destroy(&(gen->forks[i])); 
	free(gen->philo);
	pthread_mutex_destroy(gen->mu_print);
}
void	msg_err(char *msg, t_gen *gen)
{
	if (gen->flag_mllc == TRUE)
		ft_free_mllc(gen);
	if (gen->flag_mtex == TRUE)
		ft_free_mtx(gen);
	printf("%s\n", msg);
	exit(EXIT_FAILURE);

}

void	ft_print_msgs(t_philo *philo, char *msg)
{
	long	time_aux;

	pthread_mutex_lock(philo->mu_print_ph);
	time_aux = get_time() - philo->start_time_philo;
	if (*(philo->life) == FALSE)
		printf("%ld ms -- philo %d %s\n", time_aux, philo->id, msg);
	pthread_mutex_unlock(philo->mu_print_ph);
}

void	end_philos(t_gen *gen)
{
	int	i;

	i = 0;
	if (gen->num_philos == 1)
		pthread_detach(gen->philo_id[0]);
	else
	{
		while (i < gen->num_philos)
		{
			pthread_mutex_unlock(gen->philo[i].mu_data_ph);
			pthread_join(gen->philo_id[i], NULL);
			i++;
		}
	}
	i = -1;
	while (++i < gen->num_philos)
	{
		pthread_mutex_destroy(&(gen->forks[i]));
		pthread_mutex_destroy(gen->mu_print);
		pthread_mutex_destroy(&(gen->mu_data[i]));
	}
	ft_free_mllc(gen);
}
