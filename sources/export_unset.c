/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftuncer <ftuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 12:29:02 by ftuncer           #+#    #+#             */
/*   Updated: 2022/09/22 16:03:41 by ftuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	*ft_realloc(void *ptr, size_t size)
{
	char	*new_ptr;

	if (!ptr)
		return (malloc(size));
	new_ptr = malloc(size);
	ft_memmove(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr);
}

void	ft_export_one(char *arg)
{
	char	**temp;
	int		i;

	i = -1;
	temp = ft_split(arg, '=');
	while (environ[++i])
	{
		if (!ft_strncmp(environ[i], temp[0], ft_strlen(temp[0])))
		{
			environ = ft_realloc(environ, (i + 2) * 8);
			environ[i] = ft_strdup(arg);
			free_array(temp);
			return ;
		}
	}
	environ = ft_realloc(environ, (i + 2) * 8);
	environ[i] = ft_strdup(arg);
	environ[i + 1] = NULL;
	free_array(temp);
}

void	ft_export(char **args)
{
	int		i;

	i = 0;
	while (args[++i])
	{
		if (!ft_strchr(args[i], '=') || ft_isdigit(args[i][0]))
		{
			printf("Not a valid identifier\n");
			update_status(1, 0, NULL);
			return ;
		}
		ft_export_one(args[i]);
	}
	update_status(0, 0, NULL);
}

void	clear_env_node(char *arg)
{
	int		i;
	int		j;
	char	**temp;

	i = 0;
	j = 0;
	while (environ[i])
	{
		temp = ft_split(environ[i], '=');
		if (!ft_strncmp(temp[0], arg, ft_strlen(arg)))
		{
			free(environ[j]);
			j++;
		}
		environ[i] = environ[j];
		i++;
		j++;
		free_array(temp);
	}
}

void	ft_unset(char **args)
{
	int	i;

	i = 0;
	while (args[++i])
		clear_env_node(args[i]);
}
