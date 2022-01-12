/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazelda <sazelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:32:11 by sazelda           #+#    #+#             */
/*   Updated: 2022/01/12 19:40:05 by sazelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "ft_pipex.h"

void	child_process(int f1, int f2, char **env, int end[2], char *comand)
{
	int		code;
	char	**comands;

	comands = ft_split(comand, ' ');
	dup2(f1, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	close(end[0]);
	close(f1);
	code = execve("/bin/ls", comands, env);
	free(comands);
}

void	parent_process(int f1, int f2, char **env, int end[2], char *comand, char *path)
{
	int		status;
	int		code;
	char	**comands;
	char	**paths;
	int		i;
	char	*pat;

	paths = ft_split(path, ':');
	comands = ft_split(comand, ' ');
	waitpid(-1, &status, 0);
	dup2(f2, STDOUT_FILENO);
	dup2(end[0], STDIN_FILENO);
	close(end[1]);
	close(f2);
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		paths[i] = ft_strjoin(paths[i], comands[0]);
		code = execve(paths[i], comands, env);
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	int		f1;
	int		f2;
	int		end[2];
	pid_t	parent;

	f1 = open(argv[1], O_RDONLY);
	f2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (f1 < 0 || f2 < 0)
		return (-1);
	pipe(end);
	parent = fork();
	if (parent < 0)
		return (perror("Fork: "));
	if (!parent)
		child_process(f1, f2, env, end, argv[2]);
	else
		parent_process(f1, f2, env, end, argv[3], env[7]);
}
