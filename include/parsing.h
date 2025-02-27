/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:19:31 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/02/26 17:00:58 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

int			is_operator(const char *token);
int			validate_syntax(t_token *tokens);

char		*get_env_value(t_shell *shell, const char *var);
char		*expand_var(t_shell *shell, const char *input, size_t *i);
char		*expand_tokens(t_shell *shell, const char *token,
					int allow_expansion);

//tokenizer and utils for tokenizer
int			is_whitespace(char c);
int			handle_quotes(t_shell *shell, const char *input, int *i,
					t_token **tokens);
char		*copy_substr(const char *input, int start, int length);
void		add_token(t_token **tokens, const char *value, int in_squotes,
					int in_dquotes);
void		hand_spc_chars(const char *input, int *i, int *start,
				t_token **tokens);
void		handle_word(const char *input, int *i, int *start,
				t_token **tokens);
t_token		*tokenize(t_shell *shell, const char *input);

t_command	*create_command(void);
t_command	*parse_tokens(t_token *tokens, t_shell *shell);
void		parse_redirections(t_command *cmd, t_token **tokens);
void		add_command(t_command **commands, t_command *new_cmd);

#endif