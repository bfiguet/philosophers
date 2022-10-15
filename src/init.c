/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiguet <bfiguet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:20:53 by bfiguet           #+#    #+#             */
/*   Updated: 2022/10/15 15:31:40 by bfiguet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long long	ft_get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int	ft_init(t_data *data)
{
	int	i;

	i = data->nb_philo;
	data->is_dead = 0;
	data->all_ate = 0;
	if (data->nb_philo > 200)
		ft_error("You can't use more than 250 philosophers");
	if (pthread_mutex_init(&(data->mutex_msg), NULL))
		return (1);
	if (pthread_mutex_init(&(data->mutex_meal), NULL))
		return (1);
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(data->mutex_forks[i]), NULL))
			return (1);
		data->philo[i].id = i + 1;
		data->philo[i].nb_meal = 0;
		data->philo[i].left_f = i;
		data->philo[i].right_f = (i + 1) % data->nb_philo;
		data->philo[i].last_eat = 0;
		data->philo[i].philo_data = data;
	}
	return (0);
}

/*int ft_init(t_data *data)
{
    int i;

    i = data->nb_philo;
    data->is_dead = 0;
    data->all_ate = 0;
    if (data->nb_philo > 200)
        ft_error("You can't use more than 200 philosophers");
    if (pthread_mutex_init(&(data->mutex_msg), NULL))
        return (1);
    if (pthread_mutex_init(&(data->mutex_meal), NULL))
        return (1);
    while (--i >= 0)
    {
        if (pthread_mutex_init(&(data->mutex_forks[i]), NULL))
            return (1);
        data->philo[i].id = i + 1;
        data->philo[i].nb_meal = 0;
        data->philo[i].left_f = i;
        data->philo[i].right_f = (i + 1) & data->nb_philo;
        data->philo[i].last_eat = 0;
        data->philo[i].philo_data = data;
    }
    return (0);
}*/

void    ft_check_arg(int ac, char **av)
{
    if (ac > 5 || ac > 6)
        ft_error("./philo need at least 5 args and 6 max");
    if (ft_isdigit(ac, av) == -1)
        ft_error("Please enter only digits in arguments");
    if (ft_atoi(av[1]) == 0 || ft_atoi(av[2]) == 0 || ft_atoi(av[3]) == 0
        || ft_atoi(av[4]) == 0)
        ft_error("A argument must be positive");
}

void    ft_stock_arg(int ac, char **av, t_data *data)
{
    data->nb_philo = ft_atoi(av[1]);
    data->t_die = ft_atoi(av[2]);
    data->t_eat = ft_atoi(av[3]);
    data->t_sleep = ft_atoi(av[4]);
    if (ac == 6)
        data->t_must_eat = ft_atoi(av[5]);
    else
        data->t_must_eat = -1;
    if (ft_init(data) == 1)
        ft_error("Initialisation fail");
}