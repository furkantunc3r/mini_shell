/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merkol <merkol@42kocaeli.com.tr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:04:10 by merkol            #+#    #+#             */
/*   Updated: 2022/09/23 17:04:14 by merkol           ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	l_than(char *file)
{
	int	fd;

	fd = 0;
	if (access(file, F_OK) == -1)
	{
		perror("Access: ");
		return ;
	}
	else
		fd = open(file, O_RDWR);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	ll_than(char *file)
{
	char	*input;
	int		fd;
	int		pid;

	fd = open("heredoc", O_RDWR | O_TRUNC);
	pid = fork();
	if (pid == 0)
	{
		while (42)
		{
			input = readline("> ");
			if (ft_strstr(input, file))
				break ;
			ft_putstr_fd(input, fd);
			ft_putchar_fd('\n', fd);
			free(input);
		}
		free(input);
		close(fd);
		exit (0);
	}
	free(file);
	close (fd);
	wait(NULL);
}

void	g_than(char *file)
{
	int	fd;

	fd = 0;
	fd = open(file, O_RDWR | O_TRUNC);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	gg_than(char *file)
{
	int	fd;

	fd = 0;
	if (access(file, F_OK) == -1)
	{
		fd = open(file, O_CREAT, 0666);
		if (fd < 0)
			perror("Create: ");
	}
	else
		fd = open(file, O_RDWR | O_APPEND);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

int	check_for_redir(char *cmd)
{
	if (ft_strnstr(cmd, "<", ft_strlen(cmd))
		|| ft_strnstr(cmd, ">", ft_strlen(cmd))
		|| ft_strnstr(cmd, "<<", ft_strlen(cmd))
		|| ft_strnstr(cmd, ">>", ft_strlen(cmd)))
		return (0);
	return (1);
}
