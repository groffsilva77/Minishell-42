/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:49:08 by ytavares          #+#    #+#             */
/*   Updated: 2025/01/22 18:45:28 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//parser = implementar funçoes que transforma a lista de tokens (t_token) em comandos estruturados (t_command)

#include "parsing.h"


/*parse_tokens = recebe uma lista encadeada de tokens como entrada e retorna uma lista encadeada de comandos*/


t_command *parse_tokens(t_token *tokens)
{
	t_command *commands = NULL; //ponteiro para o inicio da lista encadeada de comandos que será retornada
	t_command *atl_cmd = NULL; //ponteiro para o comando atual qu está sendo construido
	
	char **args = NULL;
	int		arg_count = 0;
	char	*input_file = NULL;
	char	*output_file = NULL;
	t_cmd_type cmd_type = CMD_SIMPLE;
	
	while(tokens) //percorre toda a lista de tokens
		if (ft_strncmp(tokens->value, "|", 1) == 0) //compara o primeiro caractere com um |
			add_command(&commands, atl_cmd); //adiciona o comado á lista encadeada de comandos
			atl_cmd = NULL; //reseta o ponteiro (indica que um novo comando será criado)
		else if (ft_strchr("<>", tokens->value[0])) //caso aucontrario, verifica de o primeiro caractere do token está entre os simbolos <>
		if (atl_cmd)
			{
				parse_redirections(atl_cmd, &tokens) //processa o redirecionamento, configurando os campos (input_file ou output_file) da estrutura
			tokens = tokens->next; //proximo token
			} //verifica se há um comando atual para associar o redicionamento
			
		
		
	
}