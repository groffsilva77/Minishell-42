/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:35:38 by ytavares          #+#    #+#             */
/*   Updated: 2025/01/31 17:50:32 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_arguments(char **args, int i)
{
	char	*expand_result;

	while (args[i])
	{
		expand_result = expand_tokens(args[i]);
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

	i = 1;
	newline = 1;
	if (args[1] && ft_strncmp(args[1], "-n", 3) == 0)
	{
		newline = 0;
		i++;
	}
	print_arguments(args, i);
	if (newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	shell->exit_status = 0;
	return (0);
}
/*
Inicializa variáveis:

i = 1 (começa no primeiro argumento)
newline = 1 (por padrão, imprime nova linha)
Verifica a flag -n:

Se o primeiro argumento for "-n", define newline = 0 e incrementa i para ignorá-lo.
Itera pelos argumentos:

Expande cada argumento (expand_tokens).
Imprime o argumento expandido.
Adiciona um espaço se houver um próximo argumento.
Imprime nova linha, se necessário:

Se newline == 1, imprime \n.
Define o código de saída:

shell->exit_status = 0 (indica sucesso).
Retorna 0 para indicar execução bem-sucedida.
*/