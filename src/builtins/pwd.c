/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:40:49 by ytavares          #+#    #+#             */
/*   Updated: 2025/02/25 14:08:18 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
