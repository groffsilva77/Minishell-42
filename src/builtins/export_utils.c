/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:14:46 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/03/19 17:15:10 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_export_error(char *name, char *arg, t_shell *shell)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	free(name);
	shell->exit_status = 1;
	return (1);
}

int	process_export(char *arg, t_shell *shell)
{
	const char	*eq_position;
	char		*name;
	char		*value_ex;
	size_t		name_len;

	eq_position = ft_strchr(arg, '=');
	if (!eq_position)
		return (0);
	name_len = eq_position - arg;
	name = malloc(name_len + 1);
	if (!name)
		return (1);
	ft_memcpy(name, arg, name_len);
	name[name_len] = '\0';
	if (!is_valid_var_name(name))
		return (handle_export_error(name, arg, shell));
	value_ex = ft_strdup(eq_position + 1);
	if (!value_ex)
		return (free(name), 1);
	if (update_existing_var(name, value_ex, shell) != 0)
	{
		if (add_new_var(name, value_ex, shell) != 0)
			return (free(name), free(value_ex), 1);
	}
	return (free(name), free(value_ex), 0);
}
