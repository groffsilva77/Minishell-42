/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:22:31 by ytavares          #+#    #+#             */
/*   Updated: 2025/02/25 14:04:56 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	validate_exit_arg(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
		{
			printf("exit: %s: numeric argument is required\n", arg);
			return (0);
		}
		i++;
	}
	return (1);
}

int	the_exit(char **args, t_shell *shell)
{
	long	exit_code;

	printf("exit\n");
	if (args[1])
	{
		if (!validate_exit_arg(args[1]))
		{
			shell->exit_status = 2;
			exit(2);
		}
		if (args[2])
		{
			printf("exit: too many arguments\n");
			shell->exit_status = 1;
			return (1);
		}
		exit_code = ft_atoi(args[1]);
		shell->exit_status = exit_code % 256;
		exit(shell->exit_status);
	}
	exit(shell->exit_status);
}
