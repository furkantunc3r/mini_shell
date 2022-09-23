/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftuncer <ftuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:47:27 by ftuncer           #+#    #+#             */
/*   Updated: 2022/09/23 10:15:05 by ftuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	run_shell(t_cmd cmd, char *history)
{
	signal(SIGINT, shandler);
	signal(SIGQUIT, shandler);
	if (ft_strnstr(history, "<<", ft_strlen(history)))
		find_eof(history);
	if (ft_strchr(history, '|'))
	{
		cmd.cmds = ft_split(history, '|');
		run_with_pipe(cmd);
		free_array(cmd.cmds);
	}
	else if (!check_for_redir(history))
		parse_cmd(history);
	else
	{
		cmd.cmds = ft_split(history, ' ');
		run_wout_pipe(cmd);
	}
}

void	shandler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	find_eof(char *str)
{
	char	**temp;
	char	**temp2;
	char	**ret;
	int		i;

	i = -1;
	temp = ft_split_cmds(str);
	temp2 = idx_redir(str);
	while (temp2[++i])
	{
		if (ft_strstr(temp2[i], "<<"))
		{
			ret = ft_split(temp[i + 1], '|');
			ll_than(ft_strtrim(ret[0], " "));
			free_array(ret);
		}
	}
	free_array(temp);
	free_array(temp2);
}

void	file_creator(t_cmd command)
{
	int	i;

	i = -1;
	while (command.redirs[++i])
	{
		if (ft_strstr(command.redirs[i], ">"))
		{
			if (access(command.cmds[i + 1], F_OK) == -1)
			{
				if (!open(command.cmds[i + 1], O_CREAT, 0666))
					perror("Create: ");
			}
		}
	}
}

int	**open_fds(t_cmd cmd, int **fd)
{
	int	j;

	j = -1;
	while (++j < vector_len(cmd.cmds))
	{
		fd[j] = malloc(sizeof(int) * 2);
		if (pipe(fd[j]) == -1)
			perror("");
	}
	fd[j] = NULL;
	return (fd);
}
