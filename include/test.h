/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:17:58 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/01/19 15:44:20 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include <stdio.h>
# include <stdlib.h>
# include <../readline/readline.h>
# include <../readline/history.h>
# include "../lib/libft/libft.h"

typedef struct s_token {
	char			*value;
	struct s_token	*next;
}	t_token;

char	*get_env_value(const char *var);
char	*expand_var(const char *input, int *i);
char	*expand_tokens(const char *token);
void	add_token(t_token **tokens, const char *value);
int		is_whitespace(char c);
char	*copy_substr(const char *input, int start, int length);
int		handle_quotes(const char *input, int *i, t_token **tokens);
void	hand_spc_chars(const char *input, int *i, int *start, t_token **tokens);
void	handle_word(const char *input, int *i, int *start, t_token **tokens);
t_token	*tokenize(const char *input);

#endif