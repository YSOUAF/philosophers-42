/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:20:12 by ysouaf            #+#    #+#             */
/*   Updated: 2025/07/14 13:41:08 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

# define THINKING "is thinking" 
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define FORK "has taken a fork"
# define DIED "died"

typedef struct s_data	t_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	long			last_meal_t;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	lock;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				nbr_philo;
	int				n_mutexc;
	int				n_philoc;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				must_eat;
	long			start_time;
	int				one_die;
	int				finished;
	pthread_mutex_t	*forks;
	pthread_mutex_t	message;
	pthread_mutex_t	death;
	t_philo			*philos;
}	t_data;

int		ft_atoi(const char *str);
int		check_parse(int ac, char **av, t_data *data);
int		ft_error(char *str, t_data *data);
void	ft_exit(t_data *data);
long	get_time_in_ms(void);
void	smart_sleep(long duration_ms, t_philo *philo);
void	*routine(void *philo_ptr);
void	*monitor(void *data_ptr);
int		init(t_data *data, int ac, char **av);
int		case_one(t_data *data);
int		thread_init(t_data *data);
void	eat(t_philo *philo);
void	messages(const char *str, t_philo *philo);
int		ft_atoi_check(char *str);
int		is_valid_args(char **argv);
int		check_death1(t_philo *philo);

#endif