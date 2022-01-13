/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazelda <sazelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:32:11 by sazelda           #+#    #+#             */
/*   Updated: 2022/01/13 12:06:34 by sazelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ft_pipex.h"

void	ft_loop(char **paths, char **comands, char **env)
{
	int		i;
	char	*ptr;

	i = 0;
	while (paths[i])
	{
		ptr = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(ptr);
		ptr = paths[i];
		paths[i] = ft_strjoin(paths[i], comands[0]);
		free(ptr);
		execve(paths[i], comands, env);
		free(paths[i]);
		i++;
	}
	free(paths[i]);
}

void	child_process(int f1, char **env, int end[2], char *comand)
{
	char	**comands;
	char	**paths;
	int		i;

	paths = ft_split(&env[7][5], ':');
	comands = ft_split(comand, ' ');
	i = dup2(f1, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	close(end[0]);
	close(f1);
	if (i < 0)
		exit(0);
	ft_loop(paths, comands, env);
	free(comands);
	free(paths);
}

void	parent_process(int f2, char **env, int end[2], char *comand)
{
	int		status;
	char	**comands;
	char	**paths;

	paths = ft_split(&env[7][5], ':');
	comands = ft_split(comand, ' ');
	waitpid(-1, &status, 0);
	dup2(f2, STDOUT_FILENO);
	dup2(end[0], STDIN_FILENO);
	close(end[1]);
	close(f2);
	ft_loop(paths, comands, env);
	free(comands);
	free(paths);
}

int	main(int argc, char **argv, char **env)
{
	int		f1;
	int		f2;
	int		end[2];
	pid_t	parent;

	if (argc != 5)
		return (1);
	f1 = open(argv[1], O_RDONLY);
	f2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (f1 < 0 || f2 < 0)
	{
		dup2(1, STDOUT_FILENO);
		perror("pipex");
	}
	pipe(end);
	parent = fork();
	if (parent < 0)
		perror("Fork: ");
	if (!parent)
		child_process(f1, env, end, argv[2]);
	else
		parent_process(f2, env, end, argv[3]);
	return (0);
}
