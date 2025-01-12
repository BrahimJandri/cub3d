/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<<< HEAD:library/Libft/ft_strcmp.c
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:34:04 by bjandri           #+#    #+#             */
/*   Updated: 2024/08/23 16:01:08 by bjandri          ###   ########.fr       */
========
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reddamss <damssi.art@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 23:25:27 by reddamss          #+#    #+#             */
/*   Updated: 2023/11/17 03:39:09 by reddamss         ###   ########.fr       */
>>>>>>>> Damssi:library/Libft/library/Libft/ft_strdup.c
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

<<<<<<<< HEAD:library/Libft/ft_strcmp.c
int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] || s2[i])
========
char	*ft_strdup(const char *s1)
{
	int		len;
	char	*p;

	len = ft_strlen((char *)s1);
	p = malloc((len * sizeof(char)) + 1);
	if (!p)
		return (0);
	len = 0;
	while (s1[len])
>>>>>>>> Damssi:library/Libft/library/Libft/ft_strdup.c
	{
		if (s1[i] && s1[i] == s2[i])
			i++;
		else
			return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
	}
<<<<<<<< HEAD:library/Libft/ft_strcmp.c
	return (0);
========
	p[len] = '\0';
	return (p);
>>>>>>>> Damssi:library/Libft/library/Libft/ft_strdup.c
}
