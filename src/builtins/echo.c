/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:35:38 by ytavares          #+#    #+#             */
/*   Updated: 2025/03/08 17:30:57 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_arguments(t_shell *shell, char **args, int i)
{
	(void)shell;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
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
