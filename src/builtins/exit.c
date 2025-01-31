/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:22:31 by ytavares          #+#    #+#             */
/*   Updated: 2025/01/31 16:48:05 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//exit: encerra o programa (ou o shell) e retorna um código de saída para o sistema operacional.

/*
args: array de argumentos(string)

Se não há argumentos: Sai com exit(0).
Se há um argumento numérico: Sai com esse código.
Se o argumento não é numérico: Exibe erro e sai com exit(2).
Se há mais de um argumento: Exibe erro, mas não sai.

*/

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

/*

Imprime "exit".
Verifica se args[1] existe: //se temos algum argumento 

Não: Encerra com shell->exit_status.
Sim: Continua.

Valida args[1]: //se ele e um numero

Inválido:
Exibe mensagem de erro.
Encerra com status 2.

Válido: Continua.

Verifica se args[2] existe: //se possui mais de um argumento

Sim:
Exibe mensagem de erro.
Define shell->exit_status = 1.
Retorna 1 (não encerra).

Não: Continua.

Converte args[1] para número (exit_code).
Define shell->exit_status = exit_code % 256.
Encerra o programa com shell->exit_status

*/