/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: VR <VR@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:39:20 by vruiz-go          #+#    #+#             */
/*   Updated: 2023/10/12 12:49:14 by VR               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>

# define TRUE 1
# define FALSE 0

# define LFT_FRK "take left fork 🍴."
# define RGH_FRK "take right fork 🍴."
# define EATING "is eating 🌭."
# define SLEEP "is sleeping 🛌."
# define THNK "is thinking ⏳"
# define DEAD "is dead 💀."

typedef struct philo
{
	int				id;
	int				*life;
	long			start_time_philo;
	long			num_eats_philo;
	long			num_eats_philo_max;
	long			finish_eat;
	long			mls_eat_ph;
	long			mls_die_ph;
	long			mls_thk_ph;
	long			last_eat;
	int				tenedo_izq;
	int				tenedo_drch;
	pthread_mutex_t	*mu_print_ph;
	pthread_mutex_t	*mu_data_ph;
	pthread_t		*hilo_philo;
	struct gen		*data;
}	t_philo;

typedef struct gen
{
	int				flag;
	long			start_time;
	long			actual_time;
	long			num_philos;
	long			ml_eat_gn;
	long			ml_thk_gn;
	long			ml_die_gn;
	long			num_eats;
	long			num_eats_counter;
	t_philo			*philo;
	pthread_t		*philo_id;
	pthread_mutex_t	*mu_print;
	pthread_mutex_t	*mu_data;
	pthread_mutex_t	*forks;
}	t_gen;

void	msg_err(char *msg, t_gen *gen);
void	init_variable(t_gen *gen, char **argv, int argc);
int		ft_atoi_philo(char *str);
void	freeall(t_gen *data);
int		check_num(char **str);
void	init_data(t_gen *gen);
long	get_time(void);
int		ft_usleep(unsigned int time);
void	ft_start_party(t_gen *gen);
void	init_mutex(t_gen *gen, int i);
void	ft_print_msgs(t_philo *philo, char *msg);
void	dta_philos(t_gen *gen, int i);
int		ft_caducado(t_gen *gen, int i);

#endif
