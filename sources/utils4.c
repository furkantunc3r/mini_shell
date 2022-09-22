/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftuncer <ftuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:06:36 by ftuncer           #+#    #+#             */
/*   Updated: 2022/09/22 13:48:57 by ftuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	duplicate_fds(int **fd, t_cmd cmd, int i, int j)
{
	if (i > 0)
		dup2(fd[j - 1][0], STDIN_FILENO);
	if (cmd.cmds[i + 1] != NULL)
		dup2(fd[j][1], STDOUT_FILENO);
}

void	dist_pipe(t_cmd cmd, int **fd, int *pid)
{
	int		j;
	int		i;
	t_cmd	holder;

	i = -1;
	j = 0;
	while (cmd.cmds[++i])
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			duplicate_fds(fd, cmd, i, j);
			close_fds(fd);
			if (!check_for_redir(cmd.cmds[i]))
				parse_cmd(cmd.cmds[i]);
			else
			{
				holder.cmds = ft_split(cmd.cmds[i], ' ');
				run_wout_pipe(holder);
			}
			exit(0);
		}
		j++;
	}	
}

char	**idx_redir(char const *s)
{
	char	**redirs;

	redirs = malloc(sizeof(char *) * red_count((char *)s));
	if (!redirs)
		return (0);
	redirs = make_redir(redirs, s);
	return (redirs);
}
