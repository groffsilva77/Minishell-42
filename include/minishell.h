/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:14:26 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/02/20 14:05:36 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <errno.h>
# include <../readline/readline.h>
# include <../readline/history.h>
# include "../lib/libft/libft.h"

// # include "memory.h"
// # include "builtins.h"
// # include "parsing.h"
// # include "utils.h"
// # include "signals.h"
// # include "execution.h"
// # include "main_utils.h"

extern int	g_exit_status;

typedef enum e_cmd_type {
	CMD_SIMPLE,
	CMD_PIPE,
	CMD_REDIR_IN,
	CMD_REDIR_OUT,
	CMD_APPEND,
	CMD_HEREDOC
}	t_cmd_type;

typedef struct s_command {
	char				**args;
	char				*input_file;
	char				*output_file;
	char				*heredoc_delim;
	int					heredoc_pipe[2];
	int					append_output;
	int					is_heredoc;
	int					heredoc_fd;
	int					argument_count;
	int					is_builtin;
	t_cmd_type			type;
	struct s_command	*next;
}	t_command;

typedef struct s_token {
	char			*value;
	struct s_token	*next;
	t_command		*cmd;
}	t_token;

typedef struct s_memory
{
	void				*ptr_for_memory_block;
	struct s_memory		*next_ptr;
}	t_memory;

typedef struct s_shell
{
	t_memory	*memory;
	char		**env_copy;
	int			exit_status;
}	t_shell;

typedef struct s_exec_context
{
	int		prev_fd;
	int		pipe_fds[2];
	__pid_t	pid;
}	t_exec_context;

typedef struct s_expand_vars
{
	size_t	i;
	size_t	j;
	int		in_squotes;
	int		in_dquotes;
}	t_expand_vars;

void		handle_sigint(int sig);
void		setup_signal_handlers(void);

void		ft_free_all(t_shell *shell);
void		free_tokens(t_token *tokens);
void		ft_free_array(char **array);
void		*fts_malloc(t_shell *shell, size_t size);
void		ft_free(t_shell *shell, void *ptr);

void		shell_loop(t_shell *shell);

int			is_operator(const char *token);
int			validate_syntax(t_token *tokens);

char		*get_env_value(const char *var);
int			handle_quotes_state(char c, int	*in_squotes, int *in_dquotes);
char		*expand_var(const char *input, size_t *i);
int			expand_variable(const char *token, size_t *i, char *expanded,
				int j);
char		*process_expansion(const char *token, char *expanded,
				size_t max_len, int allow_expansion);
char		*expand_tokens(const char *token, int allow_expansion);

int			process_single_quote(const char *input, int *i, t_token **tokens,
				char *sbstr);
int			process_double_quote(const char *input, int *i, t_token **tokens,
				char *sbstr);
int			is_whitespace(char c);
void		add_token(t_token **tokens, const char *value);
char		*copy_substr(const char *input, int start, int length);

int			handle_quotes(const char *input, int *i, t_token **tokens);
void		hand_pipe(const char *input, int *i, t_token **tokens);
void		handle_redirects(const char *input, int *i, t_token **tokens);
void		hand_spc_chars(const char *input, int *i, int *start,
				t_token **tokens);

void		finzalize_token(const char *input, int *i, int *start,
				t_token **tokens);
int			process_quotes(const char *input, int *i, t_token **tokens);
void		process_special_chars(const char *input, int *i, int *start,
				t_token **tokens);
void		handle_word(const char *input, int *i, int *start,
				t_token **tokens);
void		process_word(const char *input, int *i, int *start,
				t_token **tokens);

t_token		*tokenize(const char *input);
void		process_whitespace(const char *input, int *i, int *start,
				t_token **tokens);

t_command	*create_command(void);
void		parse_redirections(t_command *cmd, t_token **tokens);
void		add_command(t_command **commands, t_command *new_cmd);

t_command	*creat_or_get_command(t_command *atl_cmd);
t_command	*handle_pipe(t_command *commands, t_command **atl_cmd);
t_command	*parse_tokens(t_token *tokens, t_shell *shell);
void		handle_redirection(t_command **atl_cmd, t_token **tokens);
int			handle_arg(t_command **atl_cmd, t_token *tokens, t_shell *shell);

void		execute_command(t_command *cmd, t_shell *shell);
void		create_process(t_command *cmd, t_exec_context *ctx, t_shell *shell);
void		execute_pipeline(t_command *commands, t_shell *shell);
void		execute_single_command(t_command *cmd, t_shell *shell);

int			handle_input_redirection(t_command *cmd);
int			handle_output_redirection(t_command *cmd);
int			setup_redirections(t_command *cmd);
int			handle_redirections(t_command *cmd);

char		*resolve_absolute_path(const char *command);
char		*search_in_path(const char *command, char *path);
char		*find_command_path(const char *command, char **envp);

void		free_commands(t_command *commands, t_shell *shell);

char		*fts_strdup(t_shell *shell, const char *s1);
char		*fts_strjoin(t_shell *shell, char const *s1, char const *s2);
char		**ft_realloc_array(char **array, int new_size, char *new_value,
				t_shell *shell);
char		*ft_strcat(char *dest, const char *src);
char		*ft_strcpy(char *dest, char *src);
char		*fts_strtrim(const char *str);

int			the_cd(char **args, t_shell *shell);
int			the_echo(char **args, t_shell *shell);
int			the_exit(char **args, t_shell *shell);
int			the_env(t_shell *shell);
int			the_export(char **args, t_shell *shell);
int			the_pwd(t_shell *shell);
int			the_unset(char **args, t_shell *shell);

int			is_builtin(char *cmd);
int			execute_builtin(t_command *cmd, t_shell *shell);

#endif