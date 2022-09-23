/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merkol <merkol@42kocaeli.com.tr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:02:30 by merkol            #+#    #+#             */
/*   Updated: 2022/09/23 17:02:34 by merkol           ###   ########.tr       */
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

int	is_quote(char c)
{
	if (c == 34 || c == 39)
		return (1);
	return (0);
}

char	**splitter(char *str, char sep, int i, int j)
{
	char	**new;
	int		flag;

	flag = -1;
	new = (char **)ft_calloc(20, 8);
	while (str[i])
	{
		while (str[i] && str[i] != sep)
		{
			flag += is_quote(str[i]);
			if (str[i] != sep)
				new[j] = append_char(new[j], str[i]);
			else if ((is_quote(str[i]) && str[i + 1] == 32))
				break ;
			if (flag % 2 == 0)
				sep = 0;
			else
				sep = 32;
			i++;
		}
		while (str[i] == 32)
			i++;
		j++;
	}
	return (new);
}

char	**shell_split(char *str, char sep)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = ft_strtrim(str, " ");
	new = splitter(str, sep, i, j);
	free(str);
	return (new);
}
