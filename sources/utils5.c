/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftuncer <ftuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:50:33 by ftuncer           #+#    #+#             */
/*   Updated: 2022/09/23 10:02:02 by ftuncer          ###   ########.fr       */
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

// int	is_quote(char c)
// {
// 	if (c == 34 || c == 39)
// 		return (1);
// 	return (0);
// }

// char	**ft_split2(char *str, char sep)
// {
// 	char	**new;
// 	int		i;
// 	int		j;
// 	int		flag;

// 	i = 0;
// 	j = 0;
// 	flag = -1;
// 	new = (char **)malloc(5 * 8);
// 	while (str[i])
// 	{
// 		while (str[i] && str[i] != sep)
// 		{
// 			flag += is_quote(str[i]);
// 			if (str[i] != sep)
// 				new[j] = append_char(new[j], str[i]);
// 			else if ((is_quote(str[i]) && str[i + 1] == 32))
// 				break ;
// 			if (flag % 2 == 0)
// 				sep = 0;
// 			else
// 				sep = 32;
// 			i++;
// 		}
// 		while (str[i] == 32)
// 			i++;
// 		j++;
// 	}
// 	new[j] = NULL;
// 	return (new);
// }
