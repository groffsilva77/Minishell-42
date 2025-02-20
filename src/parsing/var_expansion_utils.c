/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:59:29 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/02/20 13:12:04 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_exit_status = 0;

char	*get_env_value(t_shell *shell, const char *var)
{
	int			i;
	const char	*key;
	size_t		var_len;

	if (!shell || !shell->env_copy || !var)
		return (ft_strdup(""));
	var_len = ft_strlen(var);
	i =0;
	while(shell->env_copy[i])
	{
		key = shell->env_copy[i];
		if (!ft_strncmp(key, var, var_len) && key[var_len] == '=')
		{
			printf("get_env_value: Variável '%s' encontrada, valor: '%s'\n", var, key + var_len + 1);
			return (ft_strdup(key + var_len + 1));
		}
		i++;
	}
	printf("get_env_value: Nenhum valor encontrado para a variável '%s'\n", var);
	return(ft_strdup(""));
}

/* char	*get_env_value(const char *var)
{
	char	*value;

	printf("get_env_value: Buscando a variável '%s' no ambiente\n", var);
	if (!var)
		return (ft_strdup(""));
	value = getenv(var);
	if (value)
		printf("get_env_value: Valor encontrado '%s' para a variável '%s'\n", value, var);
	else
		printf("get_env_value: Nenhum valor encontrado para a variável '%s'\n", var);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
} */

int	handle_quotes_state(char c, int	*in_squotes, int *in_dquotes)
{
	if (c == '\'' && !(*in_dquotes))
	{
		*in_squotes = !(*in_squotes);
		return (1);
	}
	else if (c == '"' && !(*in_squotes))
	{
		*in_dquotes = !(*in_dquotes);
		return (1);
	}
	return (0);
}

char	*expand_var(t_shell *shell, const char *input, size_t *i)
{
	size_t	start;
	size_t	len;
	char	*var_name;
	char	*value;

	start = *i + 1;
	len = 0;
	
	printf("expand_var: Recebido token '%s', índice inicial %zu\n", input, *i);
	if (input[start] == '?')
	{
		*i += 2;
		return (ft_itoa(g_exit_status));
	}
	while (input[start + len] && (ft_isalnum(input[start + len])
			|| input[start + len] == '_'))
			len++;
	if (len == 0)
		return ((*i)++, ft_strdup("$"));
	var_name = malloc(len + 1);
	if (!var_name)
		return (NULL);
	ft_strlcpy(var_name, &input[start], len + 1);
	printf("expand_var: start=%zu, len=%zu, var_name='%s'\n", start, len, var_name);
	value = get_env_value(shell, var_name);
	if (value)
		printf("expand_var: Variável '%s' -> Valor '%s'\n", var_name, value);
	else
		printf("expand_var: variável '%s' valor NULL\n", var_name);
	free(var_name);
	*i = start + len;
	return (value);
}

int	expand_variable(t_shell *shell, const char *token, size_t *i, char *expanded, int j)
{
	char	*value;
	int		k;
	
	 printf("expand_variable: Token recebido '%s', índice atual %zu\n", token, *i);
	value = expand_var(shell, token, i);
	if (!value)
		return (j);
	k = 0;
	while (value[k])
		expanded[j++] = value[k++];
	free(value);
	return (j);
}

char	*process_expansion(t_shell *shell, const char *token, char *expanded,
			size_t max_len, int allow_expansion)
{
	size_t	i;
	size_t	j;
	int		in_squotes;
	int		in_dquotes;

	if (!token || !expanded)
	{
		printf("process_expansion: Erro! token ou expanded são NULL\n");
		return(NULL);
	}
	i = 0;
	j = 0;
	in_squotes = 0;
	in_dquotes = 0;

	printf("process_expansion: Processando token '%s'\n", token);
	while (token[i] && j < max_len - 1)
	{
		if (handle_quotes_state(token[i], &in_squotes, &in_dquotes))
			i++;
		else if (token[i] == '$' && allow_expansion && !in_squotes)
			j = expand_variable(shell, token, &i, expanded, j);
		else
			expanded[j++] = token[i++];
	}
	expanded[j] = '\0';
	printf("process_expansion: Token expandido para '%s'\n", expanded);
	return (expanded);
}
