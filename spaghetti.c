/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaghetti.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vruiz-go <vruiz-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:41:11 by vruiz-go          #+#    #+#             */
/*   Updated: 2023/10/09 18:41:29 by vruiz-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_provolonne(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->forks[philo->tenedo_izq]));
	ft_print_msgs(philo, LFT_FRK);
	pthread_mutex_lock(&(philo->data->forks[philo->tenedo_drch]));
	ft_print_msgs(philo, RGH_FRK);
	philo->last_eat = get_time() - philo->start_time_philo;
	ft_print_msgs(philo, EATING);
	ft_usleep(philo->mls_eat_ph);
	pthread_mutex_unlock(&(philo->data->forks[philo->tenedo_izq]));
	pthread_mutex_unlock(&(philo->data->forks[philo->tenedo_drch]));
	ft_print_msgs(philo, SLEEP);
	ft_usleep(philo->mls_thk_ph);
	ft_print_msgs(philo, THNK);
}

void	*ft_spaghetti(void *tomato_y_peperoni)
{
	t_philo	*cheese;

	cheese = tomato_y_peperoni;
	pthread_mutex_lock(cheese->mu_print_ph);
	pthread_mutex_unlock(cheese->mu_print_ph);
	if (cheese->id % 2 == 0)
		ft_usleep(50);
	pthread_mutex_lock(cheese->mu_print_ph);
	while (1)
	{
		pthread_mutex_unlock(cheese->mu_print_ph);
		ft_provolonne(cheese);
		pthread_mutex_lock(cheese->mu_print_ph);
	}
	pthread_mutex_unlock(cheese->mu_print_ph);
}

void	ft_start_party(t_gen *gen, int argc)
{
	int	i;
	int j;

	i = 0;
	while (i < gen->num_philos)
	{
		init_mutex(gen, i);
		dta_philos(gen, argc, i);
		j = pthread_create(&(gen->philo_id[i]), NULL, &ft_spaghetti, &(gen->philo[i]));
		i++;
	}
}

int	ft_caducado(t_gen *gen, int i)
{
	gen->actual_time = get_time() - gen->philo[i].start_time_philo;
	if ((gen->actual_time - gen->philo[i].last_eat) > gen->ml_die_gn)
	{
		ft_print_msgs(&(gen->philo[i]), DEAD);
		pthread_mutex_lock(gen->mu_print);
		gen->flag++;
		pthread_mutex_unlock(gen->mu_print);
		return(0);
	}
	return(1);
}
