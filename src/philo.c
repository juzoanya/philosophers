/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juzoanya <juzoanya@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 23:35:13 by juzoanya          #+#    #+#             */
/*   Updated: 2022/06/28 19:36:57 by juzoanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philo(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->nbr)
		pthread_mutex_destroy(&philo->fork[i]);
	free(philo->fork);
	free(philo->print);
	free(philo->time);
	free(philo);
	exit(0);
}

void	*routine(void *content)
{
	t_philo	*philo;

	philo = (t_philo *)content;
	if (philo->info.id % 2 == 0)
		usleep(philo->args.tt_eat / 2);
	while (philo->state != dead && philo->info.eat_cnt != philo->args.nbr_meal)
	{
		lock_left(philo);
		lock_right(philo);
		if (philo->info.l_sw && philo->info.r_sw)
			ft_eating(philo);
		else
		{
			if (pthread_mutex_unlock(philo->info.fork_l) == 0)
				philo->info.l_sw = 0;
			ft_thinking(philo);
		}
		if ((gettime() - philo->info.start >= philo->args.tt_die
				&& philo->info.eat_cnt == 0)
			|| gettime() - philo->info.std_eat >= philo->args.tt_die)
			death_action(philo);
	}
	return (NULL);
}

int	check_args(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= 0 || argv[i][j] <= 9))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_philo	*philo;

	if (argc == 5 || argc == 6)
	{
		philo = (t_philo *)malloc(sizeof(t_philo) * (ft_atoi(argv[1])));
		if (!philo)
			err_handler(2);
		if (!init_args(philo, argv))
			err_handler(0);
		init_mutex(philo);
		init_philo(philo);
		init_thread(philo);
		free_philo(philo);
	}
	else
		printf("ERROR: Number of arguments require to run program!\n");
	return (0);
}
