/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 20:37:16 by rcabezas          #+#    #+#             */
/*   Updated: 2021/06/30 18:38:25 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void    exec_cmd1(t_pipex *ps, int fd[2], char **envp)
{
    close(fd[0]);
    dup2(fd[0], STDOUT_FILENO);
    close(fd[1]);
    execve();
}

void    exec_cmd2(t_pipex *ps, int fd[2], char **envp)
{
    close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	//dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
    execve();
}

void    take_paths(t_pipex *ps, char **envp)
{
    int i;

    i = 0;
    while (envp[i])
    {
        if (ft_strcmp("PATH=", envp[i]))
            ps->paths = ft_split(ft_strchr(envp[i], '='), ':');
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

int	    main(int argc, char **argv, char **envp)
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
    }
    return (0);
}