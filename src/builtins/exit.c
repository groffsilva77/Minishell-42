/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:22:31 by ytavares          #+#    #+#             */
/*   Updated: 2025/03/19 13:14:48 by ggroff-d         ###   ########.fr       */
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
	long	the_final_status;

	printf("exit\n");
	if (args[1])
	{
		if (!validate_exit_arg(args[1]))
		{
			shell->exit_status = 2;
			return (1);
		}
		if (args[2])
		{
			printf("exit: too many arguments\n");
			shell->exit_status = 1;
			return (1);
		}
		exit_code = ft_atoi(args[1]);
		shell->exit_status = exit_code % 256;
	}
	the_final_status = shell->exit_status;
	rl_clear_history();
	cleanup_shell(shell);
	exit(the_final_status);
}
