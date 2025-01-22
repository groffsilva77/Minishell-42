#include "parsin.h"

int			g_exit_status = 0; // Variável global para armazenar o status de saída

// Função que busca o valor de uma variável de ambiente
char	*get_env_value(const char *var)
{
	char	*value;

	// Obtém o valor da variável de ambiente
	value = getenv(var);
	if (!value) // Caso não exista, retorna uma string vazia
		return (ft_strdup(""));
	return (ft_strdup(value)); // Retorna uma cópia do valor da variável
}

// Função para expandir variáveis no input
char	*expand_var(const char *input, int *i)
{
	int		start;   // Início do nome da variável
	int		len;     // Comprimento do nome da variável
	char	*var_name; // Nome da variável
	char	*value;   // Valor da variável

	start = *i + 1; // Começa logo após o caractere '$'
	len = 0;
	
	// Tratamento especial para a variável "$?"
	if (input[start] == '?')
	{
		(*i) += 2; // Avança o índice para pular "$?"
		value = malloc(12); // Aloca memória para armazenar o número
		if (!value)
			return (NULL); // Retorna NULL caso a alocação falhe
	    printf("%d", g_exit_status); // Converte o status de saída para string
		return (value); // Retorna o valor expandido
	}
	
	// Calcula o comprimento do nome da variável (válido para alfanuméricos e '_')
	while (input[start + len] && (ft_isalnum(input[start + len])
			|| input[start + len] == '_'))
			len++;
	
	// Se nenhum nome válido for encontrado, retorna apenas o caractere '$'
	if (len == 0)
	{
		(*i)++;
		return (ft_strdup("$"));
	}

	// Copia o nome da variável para var_name
	var_name = ft_strndup(&input[start], len);

	// Obtém o valor da variável usando get_env_value
	value = get_env_value(var_name);

	// Libera a memória de var_name
	free(var_name);

	// Atualiza o índice para continuar após o nome da variável
	*i = start + len;
	return (value); // Retorna o valor da variável
}

// Função para expandir todas as variáveis em um token
char	*expand_tokens(const char *token)
{
	char	*expanded; // String resultante com as variáveis expandidas
	char	*value;    // Valor expandido de uma variável
	int		i;         // Índice do token original
	int		j;         // Índice da string expandida
	int		k;         // Índice para copiar o valor expandido

	k = 0;
	i = 0;
	j = 0;

	if (!token) // Caso o token seja NULL, retorna NULL
		return (NULL);

	// Aloca memória para a string expandida
	expanded = malloc(1024); // Limite arbitrário
	if (!expanded)
		return (NULL); // Retorna NULL se a alocação falhar

	// Percorre o token original
	while (token[i])
	{
		// Caso encontre o caractere '$', tenta expandir a variável
		if (token[i] == '$')
		{
			value = expand_var(token, &i); // Expande a variável
			if (value) // Caso o valor expandido seja válido
			{
				// Copia o valor expandido para a string final
				while (value[k])
					expanded[j++] = value[k++];
				free(value); // Libera a memória do valor expandido
				k = 0; // Reinicia o índice para o próximo valor
			}
		}
		else
			// Copia caracteres normais diretamente para a string expandida
			expanded[j++] = token[i++];
	}
	
	// Finaliza a string expandida com '\0'
	expanded[j] = '\0';
	return (expanded); // Retorna a string expandida
}
