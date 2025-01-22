/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:16:11 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/01/22 14:16:28 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSIN_H
# define PARSIN_H

# include <stdio.h>
# include <stdlib.h>
# include <../readline/readline.h>
# include <../readline/history.h>
# include "../lib/libft/libft.h"

extern int	g_exit_status;

typedef struct s_token {
	char			*value;
	struct s_token	*next;
}	t_token;

char	*get_env_value(const char *var);
char	*expand_var(const char *input, int *i);
char	*expand_tokens(const char *token);

int		is_whitespace(char c);
int		handle_quotes(const char *input, int *i, t_token **tokens);
char	*copy_substr(const char *input, int start, int length);
void	add_token(t_token **tokens, const char *value);
void	hand_spc_chars(const char *input, int *i, int *start, t_token **tokens);
void	handle_word(const char *input, int *i, int *start, t_token **tokens);
t_token	*tokenize(const char *input);

#endif