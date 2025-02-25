/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:35:38 by ytavares          #+#    #+#             */
/*   Updated: 2025/02/25 14:03:13 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_arguments(t_shell *shell, char **args, int i)
{
	char	*expand_result;

	while (args[i])
	{
		expand_result = expand_tokens(shell, args[i], 1);
		if (expand_result)
		{
			ft_putstr_fd(expand_result, STDOUT_FILENO);
			free(expand_result);
		}
		if (args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
}

int	the_echo(char **args, t_shell *shell)
{
	int	i;
	int	newline;

	if (!shell || !args)
	{
		shell->exit_status = 1;
		return (1);
	}
	i = 1;
	newline = 1;
	if (args[1] && ft_strncmp(args[1], "-n", 3) == 0)
	{
		newline = 0;
		i++;
	}
	if (!args[i])
	{
		if (newline)
			ft_putstr_fd("\n", STDOUT_FILENO);
		return (shell->exit_status = 0, 0);
	}
	print_arguments(shell, args, i);
	if (newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (shell->exit_status = 0, 0);
}
