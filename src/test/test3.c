/* test 3 */

#include <signal.h>
#include <stdio.h>

int is, array[4];
int parsigs, parpid, parcum;
int sigct, cumsig, errct;

main()
{
  int i;

  printf("Test  3 ");
  fflush(stdout);		/* have to flush for child's benefit */

  for (i = 0; i < 9; i++) {
	test91();
	test92();
  }
  if (cumsig != 9) e(3);
  if (errct == 0)
	printf("ok\n");
  else
	printf("%d errors\n", errct);
}


test90()
{
  extern catch();

  int n, pid;

  parpid = getpid();
  signal(10, catch);

  if (pid = fork()) {
	while (parsigs == 0);
	if (kill(pid, 9) < 0) e(1);
	wait(&n);
	if (n != 9) e(2);
  } else {
	kill(parpid, 10);
	pause();
  }
}


catch()
{
  parsigs++;
  parcum++;
}

e(n)
int n;
{
  printf("Error %d  ", n);
  errct++;
  perror("");
}


test91()
{
  int fd[2], n, sigpip();
  char buf[4];

  sigct = 0;
  signal(SIGPIPE, sigpip);
  pipe(fd);
  if (fork()) {
	/* Parent */
	close(fd[0]);
	while (sigct == 0) {
		write(fd[1], buf, 1);
	}
	wait(&n);
  } else {
	/* Child */
	close(fd[0]);
	close(fd[1]);
	exit(0);
  }
}

sigpip()
{
  sigct++;
  cumsig++;
}


test92()
{
  int pid, n;

  signal(SIGINT, SIG_DFL);
  is = 0;
  if ((array[is++] = fork()) > 0) {
	if ((array[is++] = fork()) > 0) {
		if ((array[is++] = fork()) > 0) {
			if ((array[is++] = fork()) > 0) {
				signal(SIGINT, SIG_IGN);
				kill(array[0], SIGINT);
				kill(array[1], SIGINT);
				kill(array[2], SIGINT);
				kill(array[3], SIGINT);
				wait(&n);
				wait(&n);
				wait(&n);
				wait(&n);
			} else {
				pause();
			}
		} else {
			pause();
		}
	} else {
		pause();
	}
  } else {
	pause();
  }
}
