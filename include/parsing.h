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
	char	**args; //matrix de argumentos
	int		argument_count; //contador de argumentos
	char	*input_file; //arquivo de entrada
	char	*output_file; //arquivo de saída 
	t_cmd_type	type; //tipos do comando
	struct	s_command *next;  //proximo comando da lista
} t_command;

//environment variable and expansion
char	*get_env_value(const char *var);
char	*expand_var(const char *input, int *i);
char	*expand_tokens(const char *token);

//tokenizer and utils for tokenizer
int		is_whitespace(char c);
int		handle_quotes(const char *input, int *i, t_token **tokens);
char	*copy_substr(const char *input, int start, int length);
void	add_token(t_token **tokens, const char *value);
void	hand_spc_chars(const char *input, int *i, int *start, t_token **tokens);
void	handle_word(const char *input, int *i, int *start, t_token **tokens);
t_token	*tokenize(const char *input);

//parser 
t_command	*create_command(void);
void		parse_redirections(t_command **t_command, t_command *new_cmd);
void		add_command(t_command **commands, t_command *new_cmd);
t_command	*parser_tokens(t_token *token);


#endif