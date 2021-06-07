/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 20:37:16 by rcabezas          #+#    #+#             */
/*   Updated: 2021/06/07 21:29:23 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

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

int	    main(int argc, char **argv)
{
    t_pipex *ps;
    
    ps = ft_calloc(4, sizeof(t_pipex));
    arguments(ps, argc, argv);
    return (0);
}