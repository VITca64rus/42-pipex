/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazelda <sazelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:32:11 by sazelda           #+#    #+#             */
/*   Updated: 2022/01/12 17:40:20 by sazelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void	child_process(int f1, int f2, char **env, int end[2])
{
	int	code;

	dup2(f1, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	close(end[0]);
	close(f1);
	char * const command[] = {"ls", "-l", NULL};
	code = execve("/bin/ls", command, env);
}

void	parent_process(int f1, int f2, char **env, int end[2])
{
	int status;
	int	code;
	waitpid(-1, &status, 0);
	dup2(f2, STDOUT_FILENO); // f2 is the stdout
	dup2(end[0], STDIN_FILENO); // end[0] is the stdin
	close(end[1]);
	close(f2);
	char * const command[] = {"wc", "-l", NULL};
	code = execve("/usr/bin/wc", command, env);
}

int	main(int argc, char **argv, char **env)
{
	int	f1;
	int	f2;

	f1 = open(argv[1], O_RDONLY);
	f2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (f1 < 0 || f2 < 0)
		return (-1);
	int   end[2];
    pid_t parent;
    pipe(end);
    parent = fork();
    if (parent < 0)
         return (perror("Fork: "));
    if (!parent) // if fork() returns 0, we are in the child process
        child_process(f1,f2, env, end);
    else
        parent_process(f1,f2, env, end);

}
