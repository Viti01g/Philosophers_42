/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vruiz-go <vruiz-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:56:27 by vruiz-go          #+#    #+#             */
/*   Updated: 2023/10/10 18:21:23 by vruiz-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_variable(t_gen *gen, char **argv, int argc)
{
	if (check_num(argv))
		msg_err("Invalid Arguments\n", gen);
	gen->num_philos = ft_atoi_philo(argv[1]);
	gen->ml_die_gn = ft_atoi_philo(argv[2]);
	gen->ml_eat_gn = ft_atoi_philo(argv[3]);
	gen->ml_thk_gn = ft_atoi_philo(argv[4]);
	if (argc == 6)
		gen->num_eats = ft_atoi_philo(argv[5]);
	else
		gen->num_eats = -1;
	if ((gen->num_eats == 0) || gen->ml_die_gn <= 0 || gen->ml_eat_gn <= 0
		|| gen->ml_thk_gn <= 0)
		msg_err("Todos los argumentos tienen que estar por encima de 0.\n", gen);
	gen->flag = TRUE;
	init_data(gen);
	//printf("num filos: %ld\ntiempo muerte: %ld\ntiempo comida: %ld\ntiempo dormir: %ld\n", gen->num_philos, gen->ml_die_gn, gen->ml_eat_gn, gen->ml_thk_gn);
}

void	init_mutex(t_gen *gen, int i)
{
	pthread_mutex_init(&gen->forks[i], NULL);
	pthread_mutex_init(&gen->mu_print[i], NULL);
	pthread_mutex_init(&gen->mu_data[i], NULL);
}

void	dta_philos(t_gen *gen, int i)
{
	gen->philo[i].data = gen;
	gen->philo[i].id = i + 1;
	gen->philo[i].tenedo_izq = i;
	gen->philo[i].tenedo_drch = (i + 1) % (gen->num_philos);
	gen->philo[i].life = &(gen->flag);
	gen->philo[i].num_eats_philo = 0;
	gen->philo[i].mls_eat_ph = gen->ml_eat_gn;
	gen->philo[i].mls_die_ph = gen->ml_die_gn;
	gen->philo[i].mls_thk_ph = gen->ml_thk_gn;
	gen->philo[i].start_time_philo = gen->start_time;
	gen->philo[i].mu_data_ph = gen->mu_data;
	gen->philo[i].mu_print_ph = gen->mu_print;
	gen->philo[i].num_eats_philo_max = gen->num_eats;
}

void	init_data(t_gen *gen)
{
	gen->philo = malloc(sizeof(t_philo) * gen->num_philos);
	if (!gen->philo)
		msg_err("failed to alloc memory.\n", gen);
	gen->forks = malloc(sizeof(pthread_mutex_t) * gen->num_philos);
	if (!gen->forks)
		msg_err("failed to alloc memory.\n", gen);
	gen->mu_data = malloc(sizeof(pthread_mutex_t) * gen->num_philos);
	if (!gen->mu_data)
		msg_err("failed to alloc memory.\n", gen);
	gen->mu_print = malloc(sizeof(pthread_mutex_t) * 1);
	if (!gen->mu_print)
		msg_err("failed to alloc memory.\n", gen);
	gen->philo_id = malloc(sizeof(pthread_t) * gen->num_philos);
	if (!gen->philo_id)
		msg_err("failed to alloc memory.\n", gen);
	gen->start_time = get_time();
/* 	while (1)
	{
		printf("tempo: %ld\n", (get_time() - gen->start_time));
	} */
}
