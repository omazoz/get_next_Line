/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omazoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 18:53:46 by omazoz            #+#    #+#             */
/*   Updated: 2021/12/19 21:36:49 by omazoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

static char	*ft_get_line(char *str, char *store, int k)
{
	char	*tmp;

	if (k == -1 || str[0] == '\0')
	{
		free(str);
		return (NULL);
	}
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
	static char	store[10240][BUFFER_SIZE + 1];
	char		*tmp;
	char		*str;
	char		buf[BUFFER_SIZE + 1];
	int			k;

	if (fd < 0 || fd >= 10240)
		return (NULL);
	str = ft_strdup(store[fd]);
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
	str = ft_get_line(str, store[fd], k);
	return (str);
}
