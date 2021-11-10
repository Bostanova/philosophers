/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerika <eerika@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 16:21:55 by eerika            #+#    #+#             */
/*   Updated: 2021/08/17 16:21:57 by eerika           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_input
{
	int					count_of_phils;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	int					count_of_meal;
	int					full_phills;
	unsigned long long	start_time;
	int					need_to_stop;
}	t_input;

typedef struct s_philo
{
	int					id;
	unsigned long long	last_meal;
	int					count_meal;
	pthread_mutex_t		*fork_left;
	pthread_mutex_t		*fork_right;
	t_input				*input;
}	t_philo;

int					ft_atoi(const char *str);
void				ft_exit(char *err);
void				init(char **argv, t_input *input);
unsigned long long	get_time(void);
pthread_mutex_t		**alloc_forks(int len);
t_philo				*alloc_philo(int count, pthread_mutex_t **forks,
						t_input *input);
void				*start(void *philo);
void				is_dead(t_philo *philo);
void				free_memory(t_input *input, pthread_t *thread,
						pthread_mutex_t **forks, t_philo *philo);

#endif