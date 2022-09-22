/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd_env_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftuncer <ftuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 15:04:23 by ftuncer           #+#    #+#             */
/*   Updated: 2022/09/22 10:24:21 by ftuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	ft_cd(char *path)
{
	if (chdir(path) < 0)
		perror("");
	update_status(chdir(path), 0);
}

void	ft_pwd(void)
{
	char	*path;

	path = NULL;
	path = getcwd(path, sizeof(path));
	if (!path)
	{
		update_status(1, 0);
		return ;
	}
	printf("%s\n", path);
}

void	ft_env(char **environ)
{
	int	i;

	i = -1;
	while (environ[++i])
		printf("%s\n", environ[i]);
}

void	ft_echo(char **args)
{
	int		i;

	i = 0;
	if (args[1] == NULL)
	{
		printf("\n");
		return ;
	}
	if (!ft_strncmp(args[1], "-n", 2))
		i = 1;
	while (args[++i])
	{
		printf("%s", args[i]);
		if (args[i + 1] != NULL)
			printf(" ");
	}
	if (ft_strncmp(args[1], "-n", 2))
		printf("\n");
	update_status(0, 0);
}

void	update_status(int new_val, int x)
{
	static int	exit_status;

	if (x == 0)
		exit_status = new_val % 255;
	else if (x == 1)
	{
		printf("%d", exit_status);
		exit_status = 0;
	}
}
