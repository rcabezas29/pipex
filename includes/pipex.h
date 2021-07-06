/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 20:31:01 by rcabezas          #+#    #+#             */
/*   Updated: 2021/07/06 15:21:37 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/includes/libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <signal.h>

#define READ_END    0
#define WRITE_END   1

typedef struct  s_pipex
{
    char    *archive_one;
    char    *archive_two;
    char    *cmd_one;
    char    *cmd_two;
    char    **paths;
    int     file1;
    int     file2;
}               t_pipex;

int	    main(int argc, char **argv, char **envp);
void    arguments(t_pipex *ps, int argc, char **argv);
void    take_paths(t_pipex *ps, char **envp);
void    exec_cmd1(t_pipex *ps, int fd[2], char **envp);
void    exec_cmd2(t_pipex *ps, int fd[2], char **envp);
char    *cmd_path(t_pipex *ps, char *cmd, char **envp);
#endif