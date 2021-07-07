/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 20:37:16 by rcabezas          #+#    #+#             */
/*   Updated: 2021/07/07 21:20:24 by rcabezas         ###   ########.fr       */
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
		tmp = ft_strjoin(ft_strjoin(ps->paths[i], "/"), cmd);
		check_path = open(tmp, O_RDONLY);
		if (check_path < 0)
			i++;
		else
		{
			path = tmp;
			break ;
		}
	}
	if (!tmp)
	{
		ft_putstr(ft_strjoin(cmd, ": command not found"));
		exit(EXIT_SUCCESS);
	}
	return (path);
}

void	exec_cmd1(t_pipex *ps, int fd[2], char *envp[])
{
	ps->file1 = open(ps->archive_one, O_RDONLY);
	if (ps->file1 == -1)
	{
		ft_putstr("Error al abrir archivo\n");
		exit(EXIT_SUCCESS);
	}
	close(fd[READ_END]);
	dup2(ps->file1, STDIN_FILENO);
	dup2(fd[WRITE_END], STDOUT_FILENO);
	close(fd[WRITE_END]);
	execve(cmd_path(ps, ps->cmd_one), ft_split(ps->cmd_one, ' '), envp);
}

void	exec_cmd2(t_pipex *ps, int fd[2], char **envp)
{
	ps->file2 = open(ps->archive_two, O_WRONLY);
	if (ps->file2 == -1)
	{
		ft_putstr("Error al abrir archivo\n");
		exit(EXIT_SUCCESS);
	}
	dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);
	dup2(ps->file2, STDOUT_FILENO);
	execve(cmd_path(ps, ps->cmd_two), ft_split(ps->cmd_two, ' '), envp);
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

void	arguments(t_pipex *ps, int argc, char **argv)
{
	if (argc != 5)
	{
		ft_putstr("Error\n");
		exit(EXIT_SUCCESS);
	}
	ps->archive_one = ft_strdup(argv[1]);
	ps->cmd_one = ft_strdup(argv[2]);
	ps->cmd_two = ft_strdup(argv[3]);
	ps->archive_two = ft_strdup(argv[4]);
}

int	main(int argc, char **argv, char *envp[])
{
	t_pipex	*ps;
	int		fd[2];
	int		pid;
	int		status;

	ps = ft_calloc(4, sizeof(t_pipex));
	pipe(fd);
	arguments(ps, argc, argv);
	take_paths(ps, envp);
	pid = fork();
	if (pid == 0)
		exec_cmd1(ps, fd, envp);
	else
	{
		close(fd[WRITE_END]);
		pid = fork();
		if (pid == 0)
			exec_cmd2(ps, fd, envp);
		else
			close(fd[READ_END]);
	}
	waitpid(pid, &status, WNOHANG);
	close(ps->file1);
	close(ps->file2);
	return (0);
}
