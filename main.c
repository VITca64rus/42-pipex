#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "libft/libft.h"

void child_process(int pipefd[2], int fd1, char **path, char *cmd, char **env)
{
	int i = 0;
	char *ptr;
	char **comands;

	printf("cmd = %s\n", cmd);
	comands = ft_split(cmd, ' ');

    printf("child\n");
    dup2(fd1, 0);
    dup2(pipefd[1],1);
   	close(pipefd[0]);
    close(fd1);
	i = 0;
	while (path[i])
	{
		ptr = path[i];
		path[i] = ft_strjoin(path[i], "/");
		free(ptr);
		ptr = path[i];
		path[i] = ft_strjoin(path[i], comands[0]);
		free(ptr);
		execve(path[i], comands, env);
		free(path[i]);
		i++;
	}
}

void parent_process(int pipefd[2], int fd2, char **path, char *cmd, char **env)
{
    int *status;
    char *buf;
	char **comands;
	char *ptr;
	int i;

	comands = ft_split(cmd, ' ');
    buf = malloc(10000);

    waitpid(-1, status, 0);
    printf("parent\n");
    dup2(fd2, 1);
	dup2(pipefd[0], 0);
    close(pipefd[1]);
	i = 0;
	while (path[i])
	{
		ptr = path[i];
		path[i] = ft_strjoin(path[i], "/");
		free(ptr);
		ptr = path[i];
		path[i] = ft_strjoin(path[i], comands[0]);
		free(ptr);
		execve(path[i], comands, env);
		free(path[i]);
		i++;
	}
}

char **ft_find_path(char **env)
{
    int i = 0;
    char **paths;
    char *path = NULL;

    while (env[i])
    {
        if (env[i][0] == 'P' && env[i][1] == 'A')
		{
			path = &env[i][5];
            break;
		}
        i++;
    }
	if (path != NULL)
	{
    	paths = ft_split(path, ':');
    	return (paths);
	}
	return (NULL);
}

int main(int argc, char **argv, char **env)
{
    int pipefd[2];
    pid_t pid;
    int     f1, f2;
    char **paths = NULL;

	paths = ft_find_path(env);
    if (argc != 5 || paths == NULL)
		return (1);

	f1 = open(argv[1], O_RDONLY);
	f2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (f1 < 0 || f2 < 0)
	{
		dup2(1, STDOUT_FILENO);
		perror("pipex");
	}
    pipe(pipefd);
    pid = fork();
    if (!pid)
        child_process(pipefd, f1, paths, argv[2], env);
    else
        parent_process(pipefd, f2, paths, argv[3], env);
}