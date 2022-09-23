/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd_env_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftuncer <ftuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 15:04:23 by ftuncer           #+#    #+#             */
/*   Updated: 2022/09/23 11:07:58 by ftuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	ft_cd(char *path)
{
	if (chdir(path) < 0)
		perror("");
	update_status(chdir(path), 0, NULL);
}

void	ft_pwd(void)
{
	char	*path;

	path = NULL;
	path = getcwd(path, sizeof(path));
	if (!path)
	{
		update_status(1, 0, NULL);
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
		update_status(0, 0, NULL);
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
	update_status(0, 0, NULL);
}

int	update_status(int new_val, int x, char *str)
{
	static int	exit_status;

	if (x != -10)
		exit_status = new_val % 255;
	if (x == 1 && str)
		printf("%s", str);
	return (exit_status);
}
