/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiguet <bfiguet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:13:49 by bfiguet           #+#    #+#             */
/*   Updated: 2022/10/15 15:59:01 by bfiguet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void    ft_print(t_data *data, int nb, char *s)
{
    pthread_mutex_lock(&(data->mutex_msg));
    if (!(data->is_dead))
        printf("\033[0;35m%4lli ms \033[m \033[1;36m%i \033[m%s\n", ft_get_time() - data->start_time, nb, s);
    pthread_mutex_unlock(&(data->mutex_msg));
}

void    ft_error(char *s)
{
    write(1, "Error\n", 6);
    write(1, s, ft_strlen(s));
    write(1, "\n", 1);
    exit(0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(char *str)
{
	int	num;
	int	i;

	i = 0;
	num = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num);
}

int	ft_isdigit(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < argc)
	{
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (-1);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}