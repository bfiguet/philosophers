/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiguet <bfiguet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:18:56 by bfiguet           #+#    #+#             */
/*   Updated: 2022/11/02 13:08:56 by bfiguet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define MALLOC_ERR "malloc error"
# define UNLOCK_ERR "mutex unlock error"
# define LOCK_ERR "mutex lock error"
# define MUTEX_ERR "mutex error"
# define THREAD_ERR "thread error"

# define DIED "\033[7;31mis dead\033[m\n"
# define FORK "\033[0;32mhas taken a fork\033[m\n"
# define EAT "\033[0;31mis eating\033[m\n"
# define SLEEP "\033[0;34mis sleeping\033[m\n"
# define THINK "\033[0;33mis thinking\033[m\n"

typedef struct s_data	t_data;

typedef enum e_print
{
	ERROR,
	PHILO
}				t_print;

typedef struct s_fork
{
	pthread_mutex_t		*mutex_fork;
	size_t				last_philo;
}				t_fork;

typedef struct s_philo
{
	size_t				id;
	size_t				last_meal;
	size_t				already_eat;
	int					alive;
	pthread_mutex_t		*mutex_meal;
	t_fork				*left_f;
	t_fork				*right_f;
	t_data				*data;
}				t_philo;

typedef struct s_data
{
	size_t				nb_philo;
	size_t				t_die;
	size_t				t_eat;
	size_t				t_sleep;
	size_t				start_time;
	size_t				nb_meals;
	int					end;
	size_t				process;
	t_philo				*philos;
	t_fork				*forks;
	pthread_t			**threads;
	pthread_mutex_t		*mutex_msg;
	pthread_mutex_t		*mutex_end;
}				t_data;

//main.c
int		ft_life(t_data *data, size_t id, int *flag, int *print);
void	*dinner(void *ph);
int		ft_philo(t_data *data);
int		ft_start(t_data *data);

//init.c
size_t	ft_time(void);
int		ft_parse(t_data *data, int ac, char **av);
int		ft_mutex(pthread_mutex_t **mtx, t_data *data);
int		ft_data(t_data *data);
int		ft_check_arg(t_data *data);

//actions.c
int		ft_is_dead(t_philo *philo);
int		ft_eat(t_philo *philo);
t_fork	*ft_take_fork(t_philo *philo);
int		ft_end_fork(t_philo *philo, t_fork *fork);
int		ft_forks(t_philo *philo, t_fork *fork);

//exit.c
int		ft_is_end(t_philo *philo, int after_eat);
void	ft_clean_mtx(pthread_mutex_t *mtx);
void	ft_exit(t_data *data);

//utils.c
int		ft_error(char *s, t_data *data);
int		ft_print(t_philo *philo, int i, char *s);
int		ft_wait(size_t i, size_t die);
int		ft_atoi(char *av, size_t *res);
int		ft_strlen(char *str);

#endif
