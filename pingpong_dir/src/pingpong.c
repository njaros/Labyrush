#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

void	solver_fork(char *path, char **env, const char *fifo_out, const char *fifo_in)
{
	int	solver_return;
	char	*execve_null_strs[1];

	int	fd_fifo_in = open(fifo_in, O_RDONLY);
	int	fd_fifo_out = open(fifo_out, O_WRONLY);
	if (fd_fifo_in == -1 || fd_fifo_out == -1)
	{
		fprintf(stderr, "fifo open error : %d : %s\n", errno, strerror(errno));
		exit(1);
	}

	if (dup2(fd_fifo_in, STDIN_FILENO) == -1)
		write(2, "dup2 error\n", 12);
	if (dup2(fd_fifo_out, STDOUT_FILENO) == -1)
		write(2, "dup2 error\n", 12);
	execve_null_strs[0] = 0;
	fprintf(stderr, "pingpong : ping start\n");
	solver_return = execve(path, execve_null_strs, env);
	fprintf(stderr, "pingpong : ping end\n");
	exit(solver_return);
}

void	subject_fork(char **path, char **env, const char *fifo_out, const char *fifo_in)
{
	int	subject_return;

	int	fd_fifo_out = open(fifo_out, O_WRONLY);
	int	fd_fifo_in = open(fifo_in, O_RDONLY);
	if (fd_fifo_in == -1 || fd_fifo_out == -1)
	{
		fprintf(stderr, "fifo open error : %d : %s\n", errno, strerror(errno));
		exit(1);
	}
	if (dup2(fd_fifo_in, STDIN_FILENO) == -1)
		write(2, "dup2 error\n", 12);
	if (dup2(fd_fifo_out, STDOUT_FILENO) == -1)
		write(2, "dup2 error\n", 12);
	fprintf(stderr, "pingpong : pong start\n");
	subject_return = execve(path[0], path, env);
	fprintf(stderr, "pingpong : pong end\n");
	exit(subject_return);
}

int	pingpong(char *path1, char **path2, char **env)
{
	int	pid_fork1;
	int pid_fork2;
	system("rm -f /tmp/a_to_b /tmp/b_to_a");
	const char	*fifo1 = "/tmp/a_to_b";
	const char	*fifo2 = "/tmp/b_to_a";

	if (mkfifo(fifo1, 0666) == -1)
	{
		fprintf(stderr, "mkfifo1 error : %d : %s\n", errno, strerror(errno));
		return (-1);
	}
	if (mkfifo(fifo2, 0666) == -1)
	{
		fprintf(stderr, "mkfifo2 error : %d : %s\n", errno, strerror(errno));
		return (-1);
	}

	fprintf(stderr, "fifos created\n");

	if (access(path1, X_OK))
	{
		fprintf(stderr, "access path1 error : %d : %s\n", errno, strerror(errno));
		return (-1);
	}
	if (access(path2[0], X_OK))
	{
		fprintf(stderr, "access path2 error : %d : %s\n", errno, strerror(errno));
		return (-1);
	}
	pid_fork1 = fork();
	if (pid_fork1 == -1)
	{
		fprintf(stderr, "fork for binary1 error : %d : %s\n", errno, strerror(errno));
		return (-1);
	}
	if (pid_fork1 == 0)
		solver_fork(path1, env, fifo1, fifo2);
	else 
	{
		pid_fork2 = fork();
		if (pid_fork2 == -1)
		{
			fprintf(stderr, "fork for binary2 error : %d : %s\n", errno, strerror(errno));
			kill(pid_fork1, SIGINT);
			system("rm -f /tmp/a_to_b /tmp/b_to_a");
			return (-1);
		}
		if (pid_fork2 == 0)
			subject_fork(path2, env, fifo2, fifo1);
		else
		{
			if (waitpid(pid_fork2, NULL, 0) == -1)
				write(2, "subject crashed\n", 17);
			write(2, "end of sim\n", 12);
			kill(pid_fork1, SIGINT);
		}
	}
	system("rm -f /tmp/a_to_b /tmp/b_to_a");
	return (0);
}

int main(int ac, char **av, char **env)
{
	int	err;

	if (ac < 3)
	{
		write(2, "how to use : ./pingpong + ./solver + ./subject + [subjet-opt]\n", 63);
		exit(1);
	}
	err = pingpong(av[1], &av[2], env);
	return err;
}
