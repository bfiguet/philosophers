/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiguet <bfiguet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:07:13 by bfiguet           #+#    #+#             */
/*   Updated: 2022/10/16 19:10:25 by bfiguet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

struct	s_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				nb_meal;
	int				left_f;
	int				right_f;
	long long		last_eat;
	struct s_data	*philo_data;
}				t_philo;

typedef struct s_data
{
	pthread_mutex_t	mutex_meal;
	pthread_mutex_t	mutex_forks[200];
	pthread_mutex_t	mutex_msg;
	long long		start_time;
	int				is_dead;
	int				nb_philo;
	int				all_ate;
	int				t_must_eat;
	long int		t_die;
	long int		t_eat;
	long int		t_sleep;
	t_philo			philo[200];
}				t_data;

//main.c
void		ft_exit(t_data *data);
void		ft_philo(t_data *data);

//init.c
long long	ft_get_time(void);
int			ft_init(t_data *data);
void		ft_check_arg(int ac, char **av);
void		ft_stock_arg(int ac, char **av, t_data *data);

//utils.c
void		ft_print(t_data *data, int nb, char *s);
void		ft_error(char *s);
int			ft_strlen(char *str);
int			ft_atoi(char *str);
int			ft_isdigit(int argc, char **argv);

//actions.c
void		ft_eat(t_philo *philo);
void		ft_sleep(long long time, t_data *data);
void		*dinner(void *dinner);
void		ft_check_death(int i, t_data *data, t_philo *philo);
void		ft_is_dead(t_data *data, t_philo *philo);

#endif
