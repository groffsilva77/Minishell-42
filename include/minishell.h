/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:14:26 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/03/19 17:16:59 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define MAX_FD_TRACKED 256

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <bits/sigaction.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <termios.h>
# include <asm-generic/signal-defs.h>
# include <../readline/readline.h>
# include <../readline/history.h>
# include "../lib/libft/libft.h"

typedef enum e_cmd_type {
	CMD_SIMPLE,
	CMD_PIPE,
	CMD_REDIR_IN,
	CMD_REDIR_OUT,
	CMD_APPEND,
	CMD_HEREDOC
}	t_cmd_type;

typedef struct s_fd_tracker
{
	int	fds[MAX_FD_TRACKED];
	int	count;
	int	initialized;
}	t_fd_tracker;

typedef struct s_tokenize_data
{
	int		i;
	int		word_start;
	int		in_word;
	char	quote;
}	t_tokenize_data;

typedef struct s_command {
	char				**args;
	char				*input_file;
	char				*output_file;
	char				**heredoc_delims;
	char				*heredoc_delim;
	int					heredoc_pipe[2];
	int					append_output;
	int					is_heredoc;
	int					heredoc_fd;
	int					input_fd;
	int					output_fd;
	int					argument_count;
	int					is_builtin;
	char				*command;
	t_cmd_type			type;
	struct s_command	*next;
}	t_command;

typedef struct s_memory
{
	void				*ptr_for_memory_block;
	struct s_memory		*next_ptr;
}	t_memory;

typedef struct s_shell
{
	t_memory		*memory;
	t_fd_tracker	fd_tracker;
	char			*sbstr;
	char			*expand;
	char			**env_copy;
	int				exit_status;
	int				signal_received;
	t_command		*commands;
}	t_shell;

typedef struct s_token {
	char			*value;
	int				in_single_quotes;
	int				in_double_quotes;
	int				flags;
	struct s_token	*next;
	t_cmd_type		*type;
	t_shell			*shell;
	t_command		*cmd;
}	t_token;

typedef struct s_word_data
{
	const char	*input;
	int			start;
	int			len;
	t_token		**tokens;
}	t_word_data;

void			close_all_unused_fds(t_shell *shell, t_command *cmd);
int				is_fd_tracked(t_shell *shell, int fd);
void			init_fd_tracker(t_shell *shell);
int				track_fd(t_shell *shell, int fd);
void			untrack_fd(t_shell *shell, int fd);
void			close_and_untrack_fd(t_shell *shell, int *fd);
void			close_all_tracked_fds(t_shell *shell);

void			setup_signal_handlers(void);
void			sigint_handler(int sig);
sig_atomic_t	get_signal_state(void);
void			set_signal_state(int sig);

void			child_process(t_command *cmd, int *fd_in, int *pipe_fd,
					t_shell *shell);
void			parent_process(int *fd_in, int *pipe_fd, t_shell *shell);

void			free_shell(t_shell *shell);
void			free_command_list(t_command *cmd_list);
void			free_token_list(t_token *tokens);
void			free_token(t_token *token);
void			ft_free_array(char **array);
void			*fts_malloc(t_shell *shell, size_t size);
void			ft_free(t_shell *shell);
void			cleanup_shell(t_shell *shell);
void			exit_process(t_shell *shell, int exit_code);

void			shell_loop(t_shell *shell);

int				validate_syntax(t_token *tokens, t_shell *shell);

char			*get_env_value(t_shell *shell, const char *var);
char			*expand_var(t_shell *shell, const char *input, size_t *i);
int				expand_variable(t_shell *shell, const char *token, size_t *i,
					int j);
char			*process_expansion(t_shell *shell, const char *token,
					size_t max_len, int allow_expansion);
char			*expand_tokens(t_shell *shell, const char *token,
					int allow_expansion);

int				is_whitespace(char c);
void			add_token(t_token **tokens, const char *value, int in_squotes,
					int in_dquotes);
char			*copy_substr(const char *input, int start, int length);

void			handle_word(const char *input, int *i, int *start,
					t_token **tokens);
void			process_quotes(char *word, int len, int *has_squotes,
					int *has_dquotes);
void			process_word(t_shell *shell, t_word_data *data);
void			handle_special_char(const char *input, int i, t_token **tokens);

t_token			*tokenize(t_shell *shell, const char *input);

t_command		*create_command(void);
void			parse_redirections(t_command *cmd, t_token **tokens);
void			add_command(t_command **commands, t_command *new_cmd);

t_command		*create_or_get_command(t_command *atl_cmd);
t_command		*handle_pipe(t_command *commands, t_command **atl_cmd);
int				handle_arg(t_command **atl_cmd, t_token *tokens,
					t_shell *shell);
t_command		*parse_tokens(t_token *tokens, t_shell *shell);
char			*remove_quotes(const char *str);

int				execute_command(t_command *cmd, t_shell *shell);
void			execute_pipeline(t_command *commands, t_shell *shell);
void			execute_single_command(t_command *cmd, t_shell *shell);

int				handle_heredoc(t_command *cmd, t_shell *shell);
int				process_heredoc_delimiter(char *delim);
void			process_heredoc_line(char *line, int pipe_write_fd,
					t_shell *shell, int expand_vars);
int				handle_redirections(t_command *cmd, t_shell *shell);

char			*resolve_absolute_path(const char *command);
char			*search_in_path(const char *command, char *path);
char			*find_command_path(const char *command, char **envp);

void			free_commands(t_command *commands);

char			*fts_strdup(t_shell *shell, const char *s1);
char			*fts_strjoin(t_shell *shell, char const *s1, char const *s2);
char			**ft_realloc_array(char **array, int new_size, char *new_value,
					t_shell *shell);
char			*ft_strcat(char *dest, const char *src);
char			*ft_strcpy(char *dest, char *src);
char			*fts_strtrim(const char *str);

int				the_cd(char **args, t_shell *shell);
int				the_echo(char **args, t_shell *shell);
int				the_exit(char **args, t_shell *shell);
int				the_env(t_shell *shell);
int				the_export(char **args, t_shell *shell);
int				is_valid_var_name(const char *name);
int				update_existing_var(char *name, char *value_ex, t_shell *shell);
int				add_new_var(char *name, char *value_ex, t_shell *shell);
int				process_export(char *arg, t_shell *shell);
int				the_pwd(t_shell *shell);
int				the_unset(char **args, t_shell *shell);

int				is_builtin(char *cmd);
int				execute_builtin(t_command *cmd, t_shell *shell);

char			**duplicate_env(char **env);
t_shell			*init_shell(char **env);

#endif