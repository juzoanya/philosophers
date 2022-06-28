/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juzoanya <juzoanya@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 23:19:39 by juzoanya          #+#    #+#             */
/*   Updated: 2022/06/28 19:34:38 by juzoanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>

typedef enum e_state
{
	sleeping,
	thinking,
	eating,
	dead
}	t_state;

typedef struct s_args
{
	int		tt_eat;
	int		tt_sleep;
	int		tt_die;
	int		nbr_meal;
	int		nbr;
}			t_args;

typedef struct s_info
{
	int				id;
	long			std_eat;
	long			std_sleep;
	long			start;
	int				eat_cnt;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*print;
	pthread_mutex_t	*time;
	int				r_sw;
	int				l_sw;
}					t_info;

typedef struct s_philo
{
	struct s_philo	*philo;
	pthread_t		th;
	t_state			state;
	t_args			args;
	t_info			info;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*print;
	pthread_mutex_t	*time;
	int				nbr;
}					t_philo;

void	*routine(void *content);
void	ft_eating(t_philo *philo);
void	ft_thinking(t_philo *philo);
void	death_action(t_philo *philo);
void	lock_left(t_philo *philo);
void	lock_right(t_philo *philo);
void	free_philo(t_philo *philo);

//initialization functions
int		init_args(t_philo *philo, char **argv);
int		init_mutex(t_philo *philo);
void	init_philo(t_philo *philo);
void	init_thread(t_philo *philo);

//error checking & handling
int		check_args(char **argv);
void	err_handler(int n);

//helpers
int		ft_atoi(const char *nptr);
long	gettime(void);

#endif