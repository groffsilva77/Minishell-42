#ifndef PARSING_H
# define PARSING_H

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

typedef enum e_cmd_type { //tipos de comando
	CMD_SIMPLE,
	CMD_PIPE,
	CMD_REDIR_IN,
	CMD_REDIR_OUT,
	CMD_APPEND
} t_cmd_type;

typedef struct s_command { //armazena informações do comando
	char	**args;
	int		argument_count;
	char	*input_file;
	char	*output_file;
	t_cmd_type	type;
	struct	s_command *next;  //proximo comando
} t_command;

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