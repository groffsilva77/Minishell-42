/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:56:05 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/01/21 15:56:53 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	char	*dest_end;

	dest_end = dest;
	while (*dest_end != '\0')
	{
		dest_end++;
	}
	while (nb-- && *src != '\0')
	{
		*dest_end++ = *src++;
	}
	*dest_end = '\0';
	return (dest);
}
