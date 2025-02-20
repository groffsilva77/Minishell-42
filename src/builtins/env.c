/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:23:11 by ytavares          #+#    #+#             */
/*   Updated: 2025/02/20 12:05:30 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//env: exibe todas as variáveis armazenadas na cópia do ambiente(env_copy)

#include "minishell.h"

int	the_env(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell->env_copy || !shell->env_copy[0])
	{
		shell->exit_status = 1;
		return (1);
	}
	while (shell->env_copy[i])
	{
		printf("%s\n", shell->env_copy[i]);
		i++;
	}
	shell->exit_status = 0;
	return (0);
}

/*
resumão

1- cria um iterador para printar as variaveis de ambiente;
2- verifica se há variáveis de ambiente (se não tiver: atualiza os status de saída e retorna 1, se tiver: segue o fluxo)
3- percorre toda a matriz de env_copy até chegar no nulo
4- printa a variavél
5- vai para aproxima
6- atualiza a saída e retorna 0
*/