/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiguet <bfiguet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:50:30 by bfiguet           #+#    #+#             */
/*   Updated: 2022/11/02 13:19:14 by bfiguet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_error(char *s, t_data *data)
{
	if (s)
		printf("Error: %s\n", s);
	if (data)
		ft_exit(data);
	return (1);
}

int	ft_print(t_philo *philo, int flag, char *s)
{
	if (pthread_mutex_lock(philo->data->mutex_msg))
		return (ft_error(LOCK_ERR, NULL));
	if (flag == ERROR)
		ft_error(s, NULL);
	else
	{
		if (pthread_mutex_lock(philo->data->mutex_end))
			return (ft_error(LOCK_ERR, NULL));
		if (!philo->data->end)
			printf("\033[0;35m%zu ms \033[m \033[1;36m%zu \033[m%s", \
				ft_time() - philo->data->start_time, philo->id, s);
		if (pthread_mutex_unlock(philo->data->mutex_end))
			return (ft_error(UNLOCK_ERR, NULL));
	}
	if (pthread_mutex_unlock(philo->data->mutex_msg))
		return (ft_error(UNLOCK_ERR, NULL));
	if (flag == ERROR)
		return (1);
	return (0);
}

int	ft_wait(size_t i, size_t die)
{
	size_t	begin;
	size_t	now;
	size_t	end;

	end = ft_time() + i;
	now = ft_time();
	begin = now;
	while (now < end)
	{
		usleep(100);
		now = ft_time();
		if (now - begin > die)
			return (1);
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;
	
	i = 0;
	while(str && str[i])
		i++;
	return (i);
}

int	ft_atoi(char *av, size_t *res)
{
	*res = 0;
	if (ft_strlen(av) == 0)
		return (1);
	while (*av >= '0' && *av <= '9')
		*res = *res * 10 + (*av++ - 48);
	if (*av)
		return (1);
	return (0);
}


