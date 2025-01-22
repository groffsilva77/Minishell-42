#ifndef MINISHELL_H
# define MINISHELL_H

//library
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "memory.h"
# include "builtins.h"
# include "parsing.h"
# include "execution.h"
# include "utils.h"
# include "lib/libft/libft.h"


//structs
typedef struct s_memory
{
	void				*ptr_for_memory_block;
	struct s_memory		*next_ptr;
}t_memory;

typedef struct s_shell
{
	t_memory	*memory;
	char		**env_copy;
	int			exit_status;
}t_shell;


