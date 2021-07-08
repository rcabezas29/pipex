/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 11:06:01 by rcabezas          #+#    #+#             */
/*   Updated: 2021/07/08 13:45:17 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

char	*cmd_path(t_pipex *ps, char *cmd)
{
	char	*path;
	char	*tmp;
	int		i;
	int		check_path;

	path = NULL;
	i = 0;
	while (ps->paths[i])
	{
		tmp = ft_strjoin(ft_strjoin(ps->paths[i], "/"), ft_split(cmd, ' ')[0]);
		check_path = open(tmp, O_RDONLY);
		if (check_path < 0)
			i++;
		else
		{
			path = tmp;
			break ;
		}
	}
	if (!path)
	{
		ft_putstr(ft_strjoin(cmd, ": command not found"));
		exit(EXIT_SUCCESS);
	}
	return (path);
}

void	take_paths(t_pipex *ps, char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			ps->paths = ft_split(ft_strchr(envp[i], '/'), ':');
		i++;
	}
}
