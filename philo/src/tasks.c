/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juzoanya <juzoanya@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 19:29:48 by juzoanya          #+#    #+#             */
/*   Updated: 2022/06/28 19:33:54 by juzoanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_left(t_philo *philo)
{
	if (pthread_mutex_lock(philo->info.fork_l) == 0)
	{
		philo->info.l_sw = 1;
		pthread_mutex_lock(philo->info.print);
		printf("%ld %d has taken (left) a fork\n", gettime(), philo->info.id);
	}
	pthread_mutex_unlock(philo->info.print);
}

void	lock_right(t_philo *philo)
{
	if (pthread_mutex_lock(philo->info.fork_r) == 0)
	{
		philo->info.r_sw = 1;
		pthread_mutex_lock(philo->info.print);
		printf("%ld %d has taken (right) a fork\n", gettime(), philo->info.id);
	}
	pthread_mutex_unlock(philo->info.print);
}

void	death_action(t_philo *philo)
{
	philo->state = dead;
	pthread_mutex_lock(philo->info.print);
	printf("%ld %d is dead\n", gettime(), philo->info.id);
	free_philo(philo);
}

void	ft_thinking(t_philo *philo)
{
	philo->state = thinking;
	pthread_mutex_lock(philo->info.print);
	printf("%ld %d is thinking\n", gettime(), philo->info.id);
	pthread_mutex_unlock(philo->info.print);
}

void	ft_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->info.time);
	philo->info.std_eat = gettime();
	pthread_mutex_unlock(philo->info.time);
	philo->state = eating;
	pthread_mutex_lock(philo->info.print);
	printf("%ld %d is eating\n", philo->info.std_eat, philo->info.id);
	pthread_mutex_unlock(philo->info.print);
	usleep(philo->args.tt_eat);
	if (pthread_mutex_unlock(philo->info.fork_r) == 0)
		philo->info.r_sw = 0;
	if (pthread_mutex_unlock(philo->info.fork_l) == 0)
		philo->info.l_sw = 0;
	philo->info.eat_cnt++;
	philo->state = sleeping;
	pthread_mutex_lock(philo->info.print);
	printf("%ld %d is sleeping\n", gettime(), philo->info.id);
	pthread_mutex_unlock(philo->info.print);
	usleep(philo->args.tt_sleep);
	ft_thinking(philo);
}
