/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftuncer <ftuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:50:33 by ftuncer           #+#    #+#             */
/*   Updated: 2022/09/22 16:52:24 by ftuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

int	is_alnum(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '+')
			return (0);
		i++;
	}
	return (1);
}

int	where_env(char *s2)
{
	int		i;
	char	**temp;
	char	**env;

	i = 0;
	temp = ft_split(s2, '=');
	while (environ[i])
	{
		env = ft_split(environ[i], '=');
		if (ft_strstr(env[0], temp[0]))
		{
			free_array(env);
			free_array(temp);
			return (i);
		}
		free_array(env);
		i++;
	}
	free_array(temp);
	return (-1);
}
