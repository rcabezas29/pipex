/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 20:37:16 by rcabezas          #+#    #+#             */
/*   Updated: 2021/07/08 13:50:16 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	exec_cmd1(t_pipex *ps, int fd[2], char *envp[])
{
	char	*path;
	char	**splitted_cmd;

	path = cmd_path(ps, ps->cmd_one);
	splitted_cmd = ft_split(ps->cmd_one, ' ');
	close(fd[READ_END]);
	ps->file1 = open(ps->archive_one, O_RDONLY);
	if (ps->file1 == -1)
	{
		ft_putstr("Error al abrir archivo\n");
		exit(EXIT_SUCCESS);
	}
	dup2(ps->file1, STDIN_FILENO);
	close(ps->file1);
	dup2(fd[WRITE_END], STDOUT_FILENO);
	close(fd[WRITE_END]);
	execve(path, splitted_cmd, envp);
}

void	exec_cmd2(t_pipex *ps, int fd[2], char **envp)
{
	char	*path;
	char	**splitted_cmd;

	path = cmd_path(ps, ps->cmd_two);
	splitted_cmd = ft_split(ps->cmd_two, ' ');
	ps->file2 = open(ps->archive_two, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND);
	if (ps->file2 == -1)
	{
		ft_putstr("Error al abrir archivo\n");
		exit(EXIT_SUCCESS);
	}
	dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);
	dup2(ps->file2, STDOUT_FILENO);
	close(ps->file2);
	execve(path, splitted_cmd, envp);
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
	wait(&status);
	wait(&status);
	return (0);
}
