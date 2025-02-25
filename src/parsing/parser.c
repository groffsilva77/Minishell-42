/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2025/02/25 14:26:49 by ytavares          #+#    #+#             */
/*   Updated: 2025/02/25 14:26:52 by ytavares         ###   ########.fr       */
=======
/*   Created: 2025/01/22 17:49:08 by ytavares          #+#    #+#             */
/*   Updated: 2025/02/19 19:07:05 by ggroff-d         ###   ########.fr       */
>>>>>>> 61e53790d7d686fd655c7b05c5e64901fb0963bc
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*creat_or_get_command(t_command *atl_cmd)
{
	if (!atl_cmd)
		atl_cmd = create_command();
	return (atl_cmd);
}

t_command	*handle_pipe(t_command *commands, t_command **atl_cmd)
{
	add_command(&commands, *atl_cmd);
	*atl_cmd = NULL;
	return (commands);
}

int	handle_arg(t_command **atl_cmd, t_token *tokens, t_shell *shell)
{
	char	**temp;

	*atl_cmd = creat_or_get_command(*atl_cmd);
	temp = ft_realloc_array((*atl_cmd)->args, (*atl_cmd)->argument_count + 1,
			tokens->value, shell);
	if (!temp)
	{
		ft_putstr_fd("Error: Memory allocation failed in realloc array\n", 2);
		free((*atl_cmd)->args);
		(*atl_cmd)->args = NULL;
		return (-1);
	}
	(*atl_cmd)->args = temp;
	(*atl_cmd)->args[(*atl_cmd)->argument_count] = ft_strdup(tokens->value);
	if (!(*atl_cmd)->args[(*atl_cmd)->argument_count])
		return (free ((*atl_cmd)->args), 0);
	(*atl_cmd)->argument_count++;
	(*atl_cmd)->args[(*atl_cmd)->argument_count] = NULL;
	return (0);
}
t_command	*parse_tokens(t_token *tokens, t_shell *shell)
{
	t_command	*commands;
	t_command	*atl_cmd;

	commands = NULL;
	atl_cmd = NULL;
	while (tokens)
	{
		if (ft_strncmp(tokens->value, "|", 1) == 0)
			commands = handle_pipe(commands, &atl_cmd);
		else if (ft_strchr("<>", tokens->value[0]))
		{
			if (!tokens->next)
				return (commands);
			if (!atl_cmd)
				atl_cmd = create_command();
			parse_redirections(atl_cmd, &tokens);
		}
		else if (handle_arg(&atl_cmd, tokens, shell) == -1)
			return (NULL);
		tokens = tokens->next;
	}
	if (atl_cmd)
		add_command(&commands, atl_cmd);
	return (commands);
}
