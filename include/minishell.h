#ifndef MINISHELL_H
# define MINISHELL_H

//library
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "memory.h"
# include "builtins.h"
# include "parsin.h"
# include "execution.h"

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


//functions we will use to manage memory (prototype)
void	*ft_malloc(t_shell *shell, size_t size);
void	ft_free(t_shell *shell, void *ptr);
void	ft_free_all(t_shell *shell);
