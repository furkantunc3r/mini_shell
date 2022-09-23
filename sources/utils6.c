/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merkol <merkol@42kocaeli.com.tr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:04:54 by merkol            #+#    #+#             */
/*   Updated: 2022/09/23 17:04:56 by merkol           ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

int	quote_state(char *str, int pos)
{
	int	ret;
	int	i;
	int	quote;

	ret = 0;
	i = 0;
	quote = 0;
	while (str[i] && i < pos)
	{
		if (!quote && (str[i] == 34 || str[i] == 39))
			quote = str[i];
		if (quote == str[i] && ret == 0)
			ret = 1;
		else if (quote == str[i] && ret == 1)
			ret = 0;
		i++;
	}
	return (ret);
}

int	char_count(char *str, char c)
{
	int	i;
	int	ret;

	if (!str)
		return (0);
	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i] == c && !quote_state(str, i))
			ret++;
		i++;
	}
	return (ret);
}
