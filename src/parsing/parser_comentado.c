/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_comentado.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:49:08 by ytavares          #+#    #+#             */
/*   Updated: 2025/01/23 17:55:00 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//parser = implementar funçoes que transforma a lista de tokens (t_token) em comandos estruturados (t_command)

#include "parsing.h"

/*create_commad = Criará uma estrutura de comando sempre que necessário. */

/*parse_redirections = Atualizará os campos de redirecionamento (<, >, >>) do comando atual.*/

/*add_command  = add_command: Garantirá que os comandos sejam adicionados à lista encadeada.*/

/*parse_tokens = recebe uma lista encadeada de tokens como entrada e retorna uma lista encadeada de comandos*/


t_command	*create_commad(void)
{
	t_command *cmd; //ponteiro para a uma nova estrutura de comando
	
	cmd = malloc(sizeof(t_command)); //aloca memória para essa nova estrutura
	if (!cmd) //verifica se deu bom na alocação
		return (NULL);
	//aqui, agente inicia todos os campos da estrutura t_command
	cmd->args = NULL; 
	cmd->argument_count = 0;
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->type = CMD_SIMPLE;
	cmd->next = NULL;

	return(cmd); //retorna a nova estrutura de comandos

}

void	parse_redirections(t_command *cmd, t_token **tokens)
{
	if (ft_strncmp((*tokens)->value, "<", 1) == 0) //verifica se o token atual é entrada redirecioada
		cmd->input_file = ft_strdup((*tokens)->next->value); //se for, copia o nome do arquivo de entrada
	else if (ft_strncmp((*tokens)->value, ">", 1) == 0) //mesma coisa, mas agora é com a saida redirecionada
		cmd->output_file = ft_strdup((*tokens)->next->value); //se for copia o nome do arquivo de saída
	else if (ft_strncmp((*tokens)->value, ">>", 2) == 0) //verifica se o token atual é adição de arquivo
		cmd->output_file = ft_strdup((*tokens)->next->value); //se for, copia o nome do arquivo de saída para append
	*tokens = (*tokens)->next; //vai para o proximo token
}

void	add_command(t_command **commands, t_command *new_cmd)
{
	t_command	*atl; //ponteiro para percorrer a lista do comandos
	
	if (!*commands) //se a lista de comandos estiver vaia, adiciona o novo comando
		*commands = new_cmd;
	else //se nã estiver vazia
	{
		atl = *commands; //o ponteiro atl mostra o primeiro elemento da lista
		while (atl->next) //percorre a lista encadeada, movento atl para o proximo, até que chegue ao último nó da lista
			atl = atl->next; 
		atl->next = new_cmd; //após encontrar o último nó, o new_cmd será o final da lista
	}
}

t_command	*parse_tokens(t_token *tokens)
{
	t_command *commands = NULL; //lista de comandos a ser retornada
	t_command *atl_cmd = NULL; //comando atual sendo processado

	while (tokens) //percorre todos os tokens
	{
		if (ft_strncmp(tokens->value, "|", 1) == 0) //se encontrar um pipe, adiciona o comando atual á lista
		{
			add_command(&commands, atl_cmd);
			atl_cmd = NULL;
		}
		else if (ft_strchr("<>", tokens->value[0])) //se encontrar redirecionamento
		{
			if (!atl_cmd) // cria um novo comando se não existir
				atl_cmd = create_commad();
			parse_redirections(atl_cmd, &tokens); //processa redicionamentos (o primeiro token é processado aqui)
			tokens = tokens->next; //pula para o proximo token (pois o primeiro token já foi tratado na função parse__redictions)
		}
		else
		{
			if (!atl_cmd) //cria um  novo comando se não existir 
				atl_cmd = create_commad();
			atl_cmd->args = ft_realloc_array(
				atl_cmd->args, atl_cmd->argument_count + 1, token->value) //adiciona o novo comando (tokens->value) a listá de argumentos atl_cmd->args
			atl_cmd->argument_count++; //incrementa o contaodr de argumentos
		}
		tokens = tokens->next; //vai para o proximo token
	}
	if (atl_cmd) //verifica se existe atl_cmd (pois o ultimo comando do input não é seguido de um |, então é necessario adicionar esse comando no final)
		add_command(&commands, atl_cmd); //adiciona atl_cmd á lista encadeada de comandos
		return (commands); //retorna a lista de comandos, qie agora contém todos os comandos processados apartir os tokens
}

/*resumo 

Percorre a lista de tokens
Cria comandos conforme encontra tokens
Trata pipes, redirecionamentos e argumentos
Monta uma lista encadeada de comandos*/