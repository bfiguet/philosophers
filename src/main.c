/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiguet <bfiguet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:13:00 by bfiguet           #+#    #+#             */
/*   Updated: 2022/10/15 15:18:04 by bfiguet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void    ft_exit(t_data *data)
{
    t_philo *philo;
    int     i;

    i = 0;
    philo = data->philo;
    if (data->nb_philo == 1)
        pthread_mutex_unlock(&(data->mutex_forks[philo[0].left_f]));
    while (i < data->nb_philo)
    {
        pthread_join(philo[i].thread, NULL);
        i++;
    }
    i = 0;
    while (++i < data->nb_philo)
        pthread_mutex_destroy(&(data->mutex_forks[i]));
    pthread_mutex_destroy(&(data->mutex_msg));
    pthread_mutex_destroy(&(data->mutex_msg));
    exit (0);
}

void	ft_philo(t_data *data)
{
	int		i;
	t_philo	*ph;

	i = 0;
	ph = data->philo;
	data->start_time = ft_get_time();
	while (i < data->nb_philo)
	{
		if (pthread_create(&(ph[i].thread), NULL, dinner, &(ph[i])))
			ft_error("Unable to create a thread");
		pthread_mutex_lock(&(data->mutex_meal));
		ph[i].last_eat = ft_get_time();
		pthread_mutex_unlock(&(data->mutex_meal));
		i++;
	}
	ft_is_dead(data, ph);
	ft_exit(data);
}

/*
void    ft_philo(t_data *data)
{
    int     i;
    t_philo *philo;

    i = 0;
    philo = data->philo;
    data->start_time = ft_get_time();
    while (i < data->nb_philo)
    {
        if (pthread_create(&(philo[i].thread), NULL, dinner, &(philo[i])))
            ft_error("Unable to create a thread");
        pthread_mutex_lock(&(data->mutex_meal));
        philo[i].last_eat = ft_get_time();
        //ft_print(data, philo->id, "test last_eat");
        pthread_mutex_unlock(&(data->mutex_meal));
        i++;
    }
    ft_is_dead(data, philo);
    ft_exit(data);
}*/

int main(int ac, char **av)
{
    t_data  data;

    ft_check_arg(ac, av);
    ft_stock_arg(ac, av, &data);
    ft_philo(&data);
    return (0);
}