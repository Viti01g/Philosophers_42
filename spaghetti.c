/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaghetti.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vruiz-go <vruiz-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:41:11 by vruiz-go          #+#    #+#             */
/*   Updated: 2023/10/16 19:14:28 by vruiz-go         ###   ########.fr       */
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
	if (philo->num_eats_philo >= 0)
		philo->num_eats_philo++;
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
	while (*(cheese->life) == FALSE)
	{
		pthread_mutex_unlock(cheese->mu_print_ph);
		ft_provolonne(cheese);
		pthread_mutex_lock(cheese->mu_print_ph);
	}
	pthread_mutex_unlock(cheese->mu_print_ph);
	return (NULL);
}

void	ft_start_party(t_gen *gen)
{
	int	i;

	i = 0;
	gen->flag_mtex = TRUE;
	while (i < gen->num_philos)
	{
		init_mutex(gen, i);
		dta_philos(gen, i);
		pthread_create(&(gen->philo_id[i]), NULL, &ft_spaghetti, &(gen->philo[i]));
		i++;
	}
}

int	ft_caducado(t_gen *gen, int i)
{
	gen->actual_time = get_time() - gen->philo->start_time_philo;
	if ((gen->actual_time - gen->philo[i].last_eat) > gen->ml_die_gn)
	{
		ft_print_msgs(&(gen->philo[i]), DEAD);
		pthread_mutex_lock(gen->mu_print);
		gen->flag = TRUE;
		pthread_mutex_unlock(gen->mu_print);
		return(0);
	}
	if (gen->philo[i].num_eats_philo == gen->philo[i].num_eats_philo_max && gen->philo[i].finish_eat == FALSE)
	{
		gen->philo[i].finish_eat = TRUE;
		gen->num_eats_counter++;
		if (gen->num_eats_counter == gen->num_philos)
		{
			pthread_mutex_lock(gen->mu_print);
			gen->flag = TRUE;
			pthread_mutex_unlock(gen->mu_print);
			return (0);
		}
	}
	return(1);
}
