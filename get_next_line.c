/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omazoz <omazoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 18:51:44 by omazoz            #+#    #+#             */
/*   Updated: 2021/12/20 20:24:44 by omazoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_hasendl(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

static char	*ft_get_line(char *str, char *store)
{
	int		k;
	char	*tmp;

	k = ft_hasendl(str);
	if (k == 0)
		store[0] = '\0';
	else
	{
		tmp = str;
		str = (char *) malloc(sizeof(char) * (k + 1));
		ft_strlcpy(str, tmp, k + 1);
		ft_strlcpy(store, tmp + k, BUFFER_SIZE + 1);
		free(tmp);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	store[BUFFER_SIZE + 1];
	char		*tmp;
	char		*str;
	char		buf[BUFFER_SIZE + 1];
	int			k;

	str = ft_strdup(store);
	while (!ft_hasendl(str))
	{
		k = read(fd, buf, BUFFER_SIZE);
		if (k == 0 || k == -1)
			break ;
		buf[k] = '\0';
		tmp = str;
		str = ft_strjoin(str, buf);
		free(tmp);
	}
	if (k == -1 || str[0] == '\0')
	{
		free(str);
		return (NULL);
	}
	str = ft_get_line(str, store);
	return (str);
}
