/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 20:31:01 by rcabezas          #+#    #+#             */
/*   Updated: 2021/06/07 20:46:39 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/includes/libft.h"

typedef struct  s_pipex
{
    char    *archive_one;
    char    *archive_two;
    char    *cmd_one;
    char    *cmd_two;
}               t_pipex;

#endif