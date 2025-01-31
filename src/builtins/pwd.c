/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:40:49 by ytavares          #+#    #+#             */
/*   Updated: 2025/01/31 17:27:45 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//pwd: mostra o caminho/diretório atual que você está
#include "minishell.h"

int	the_pwd(t_shell *shell)
{
	char	atl_dir[1024];

	if (getcwd(atl_dir, sizeof(atl_dir)) != NULL)
	{
		printf("%s\n", atl_dir);
		shell->exit_status = 0;
		return (0);
	}
	perror("pwd");
	shell->exit_status = 1;
	return (1);
}

/*
t_shell: um ponteiro para a struct de dados

resumão:

1- declara um buffer estatico para armazanar o diretório atual
2- utiliza a função getcwd para pagar o caminho completo e o diretório atual e armazena em atl_dir
3- se der certo: printa o diretório atual, atualiza os status de saida e retorna 0.
se der ruim: imprime uma menssagem de erro com perror, atualiza os status de saída, e retona 1
*/