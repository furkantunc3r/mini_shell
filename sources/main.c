/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftuncer <ftuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:34:02 by ftuncer           #+#    #+#             */
/*   Updated: 2022/09/22 12:10:06 by ftuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	run_wout_pipe(t_cmd cmd)
{
	if (*cmd.cmds)
	{
		if (!ft_strncmp(cmd.cmds[0], "echo", 4))
			ft_echo(cmd.cmds);
		else if (!ft_strncmp(cmd.cmds[0], "cd", 2))
			ft_cd(cmd.cmds[1]);
		else if (!ft_strncmp(cmd.cmds[0], "pwd", 3))
			ft_pwd();
		else if (!ft_strncmp(cmd.cmds[0], "env", 3))
			ft_env(environ);
		else if (!ft_strncmp(cmd.cmds[0], "export", 6) && cmd.cmds[1] != NULL)
			ft_export(cmd.cmds);
		else if (!ft_strncmp(cmd.cmds[0], "unset", 5) && cmd.cmds[1] != NULL)
			ft_unset(cmd.cmds);
		else if (!ft_strncmp(cmd.cmds[0], "exit", 4))
			exit(0);
		else if (!ft_strncmp(cmd.cmds[0], "$?", 2))
			update_status(1, 1);
		else
			run_with_execve(cmd);
	}
	free_array(cmd.cmds);
}

void	dist_redirs(t_cmd command)
{
	int	i;

	i = -1;
	file_creator(command);
	while (command.redirs[++i])
	{
		if (ft_strstr(command.redirs[i], ">"))
			g_than(command.cmds[i + 1]);
		else if (ft_strstr(command.redirs[i], ">>"))
			gg_than(command.cmds[i + 1]);
		else if (ft_strstr(command.redirs[i], "<"))
			l_than(command.cmds[i + 1]);
		else if (ft_strstr(command.redirs[i], "<<"))
			l_than("heredoc");
	}
	free_array(command.cmds);
}

int	main(void)
{
	t_cmd	cmd;
	char	*history;
	char	*prompt;

	signal(SIGINT, shandler);
	signal(SIGQUIT, shandler);
	cmd.cmds = NULL;
	prompt = ft_strdup(getenv("LOGNAME"));
	prompt = ft_strjoin(prompt, "$ ");
	while (42)
	{
		history = readline(prompt);
		if (!history)
			exit(0);
		run_shell(cmd, history);
		add_history(history);
		free(history);
	}
	return (0);
}
