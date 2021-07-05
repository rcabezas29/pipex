/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 20:37:16 by rcabezas          #+#    #+#             */
/*   Updated: 2021/07/05 17:34:57 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

char    *cmd_path(t_pipex *ps, char *cmd, char *envp[])
{
    char    *path;
    char    *tmp;
    int     i;

    path = NULL;
    i = 0;
    while (ps->paths[i])
    {
        tmp = ft_strjoin(ft_strjoin(ps->paths[i], "/"), cmd);
        if (execve(path, NULL, envp) == 127)
            i++;
        else
            path = tmp;
    }
    if (!tmp)
    {
        ft_putstr(ft_strjoin(cmd, ": command not found"));
        exit(EXIT_SUCCESS);
    }
    return (path);
}

void    exec_cmd1(t_pipex *ps, int fd[2], char *envp[])
{
    ps->file1 = open(ps->archive_one, O_RDONLY);
    if (!ps->file1)
    {
        ft_putstr("Error al abrir archivo\n");
        exit(EXIT_SUCCESS);
    }
    close(fd[0]);
    dup2(fd[0], STDOUT_FILENO);
    close(fd[1]);
    execve(cmd_path(ps, ps->cmd_one, envp), NULL, envp);
}

void    exec_cmd2(t_pipex *ps, int fd[2], char **envp)
{
    close(fd[1]);
    ps->file2 = open(ps->archive_two, O_WRONLY);
    if (!ps->file2)
    {
        ft_putstr("Error al abrir archivo\n");
        exit(EXIT_SUCCESS);
    }
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(ps->file2, STDOUT_FILENO);
    execve(cmd_path(ps, ps->cmd_two, envp), NULL, envp);
}

void    take_paths(t_pipex *ps, char *envp[])
{
    int i;

    i = 0;
    while (envp[i])
    {
        if (ft_strncmp("PATH=", envp[i], 5) == 0)
            ps->paths = ft_split(ft_strchr(envp[i], '/'), ':');
        i++;
    }
}

void    arguments(t_pipex *ps, int argc, char **argv)
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

int	    main(int argc, char **argv, char *envp[])
{
    t_pipex *ps;
    int     fd[2];
    int     pid;

    ps = ft_calloc(4, sizeof(t_pipex));
    pipe(fd);
    arguments(ps, argc, argv);
    take_paths(ps, envp);
    pid = fork();
    if (pid == 0)
        exec_cmd1(ps, fd, envp);
    else
    {
        pid = fork();
        if (pid == 0)
            exec_cmd2(ps, fd, envp);
        else
            close(fd[0]);
    }
    close(ps->file1);
    close(ps->file2);
    return (0);
}