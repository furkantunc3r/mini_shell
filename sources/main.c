/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftuncer <ftuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:34:02 by ftuncer           #+#    #+#             */
/*   Updated: 2022/09/23 09:59:28 by ftuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	run_wout_pipe(t_cmd cmd)
{
	if (*cmd.cmds)
	{
		if (ft_strstr(cmd.cmds[0], "echo"))
			ft_echo(cmd.cmds);
		else if (ft_strstr(cmd.cmds[0], "cd"))
			ft_cd(cmd.cmds[1]);
		else if (ft_strstr(cmd.cmds[0], "pwd"))
			ft_pwd();
		else if (ft_strstr(cmd.cmds[0], "env"))
			ft_env(environ);
		else if (ft_strstr(cmd.cmds[0], "export") && cmd.cmds[1] != NULL)
			ft_export(cmd.cmds);
		else if (ft_strstr(cmd.cmds[0], "unset") && cmd.cmds[1] != NULL)
			ft_unset(cmd.cmds);
		else if (ft_strstr(cmd.cmds[0], "exit"))
			exit(0);
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

void	shell_process(char *history, char *prompt, t_cmd cmd)
{
	while (42)
	{
		history = readline(prompt);
		if (!history)
			exit(0);
		if (!check_syntax(history))
		{
			add_history(history);
			if (history)
			{
				if (!history)
					continue ;
				run_shell(cmd, history);
				free(history);
			}
		}
	}
}

int	main(void)
{
	t_cmd	cmd;
	char	*history;
	char	*prompt;

	cmd.cmds = NULL;
	prompt = ft_strdup(getenv("LOGNAME"));
	prompt = ft_strjoin(prompt, "$ ");
	history = NULL;
	shell_process(history, prompt, cmd);
	return (0);
}
