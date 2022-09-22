/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_determine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftuncer <ftuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 13:11:27 by mhaksal           #+#    #+#             */
/*   Updated: 2022/09/22 16:03:08 by ftuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

int	determine_syntax(char *str, int i)
{
	if (str[i] == '<')
	{
		if (!check_right_r(i, str))
			return (update_status(258 * 256, 1,
					"syntax error near unexpected token '<'\n"));
	}
	else if (str[i] == '>')
	{
		if (!check_right(i, str))
			return (update_status(258 * 256, 1,
					"syntax error near unexpected token '>'\n"));
	}
	return (0);
}

int	char_count(char *str, char c)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == c)
			j++;
	}
	return (j);
}
