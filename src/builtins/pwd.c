/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:40:49 by ytavares          #+#    #+#             */
/*   Updated: 2025/02/21 15:41:07 by ggroff-d         ###   ########.fr       */
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
