/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juzoanya <juzoanya@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 19:19:54 by juzoanya          #+#    #+#             */
/*   Updated: 2022/06/28 19:27:02 by juzoanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_args(t_philo *philo, char **argv)
{
	if (!check_args(argv))
		return (0);
	philo->nbr = ft_atoi(argv[1]);
	philo->args.tt_die = ft_atoi(argv[2]) * 1000;
	philo->args.tt_eat = ft_atoi(argv[3]) * 1000;
	philo->args.tt_sleep = ft_atoi(argv[4]) * 1000;
	philo->args.nbr = philo->nbr;
	if (argv[5])
		philo->args.nbr_meal = ft_atoi(argv[5]);
	else
		philo->args.nbr_meal = -1;
	if (philo->nbr < 2)
		return (0);
	return (1);
}

int	init_mutex(t_philo *philo)
{
	int		i;

	i = -1;
	philo->fork
		= (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * philo->nbr);
	if (!philo->fork)
		return (1);
	while (++i < philo->nbr)
		pthread_mutex_init(&philo->fork[i], NULL);
	philo->print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philo->print, NULL);
	philo->time = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philo->time, NULL);
	return (0);
}

void	init_philo(t_philo *philo)
{
	int		i;

	i = -1;
	while (++i < philo->nbr)
	{
		philo[i].info.id = i + 1;
		philo[i].info.std_eat = 0;
		philo[i].info.eat_cnt = 0;
		philo[i].info.std_sleep = 0;
		philo[i].info.l_sw = 0;
		philo[i].info.r_sw = 0;
		philo[i].args = philo->args;
		philo[i].state = philo->state;
		philo[i].info.fork_l = &philo->fork[i];
		philo[i].info.fork_r = &philo->fork[(i + 1) % philo->nbr];
		philo[i].info.print = philo->print;
		philo[i].info.time = philo->time;
	}
}

void	init_thread(t_philo *philo)
{
	int			i;

	i = -1;
	philo->info.start = gettime();
	while (++i < philo->nbr)
	{
		if (pthread_create(&philo[i].th, NULL, &routine, &philo[i]) != 0)
			err_handler(3);
	}
	i = -1;
	while (++i < philo->nbr)
		pthread_join(philo[i].th, NULL);
}
