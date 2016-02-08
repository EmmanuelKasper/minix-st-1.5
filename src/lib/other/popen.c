#include <lib.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

PRIVATE int pids[20];

FILE *popen(command, type)
char *command, *type;
{
  int piped[2];
  int Xtype = *type == 'r' ? 0 : *type == 'w' ? 1 : 2;
  int pid;
  extern FILE *fdopen();

  if (Xtype == 2 ||
      pipe(piped) < 0 ||
      (pid = fork()) < 0)
	return((FILE *)NULL);

  if (pid == 0) {
	/* Child */
	register int *p;

	for (p = pids; p < &pids[20]; p++) {
		if (*p) close(p - pids);
	}
	close(piped[Xtype]);
	dup2(piped[!Xtype], !Xtype);
	close(piped[!Xtype]);
	execl("/bin/sh", "sh", "-c", command, (char *) 0);
	exit(-1);		/* like system() ??? */
  }
  pids[piped[Xtype]] = pid;
  close(piped[!Xtype]);
  return(fdopen(piped[Xtype], type));
}

int pclose(iop)
FILE *iop;
{
  int fd = fileno(iop);
  int status, wret;
  void (*intsave) () = signal(SIGINT, SIG_IGN);
  void (*quitsave) () = signal(SIGQUIT, SIG_IGN);
  void (*hupsave) () = signal(SIGHUP, SIG_IGN);

  fclose(iop);
  while ((wret = wait(&status)) != -1) {
	if (wret == pids[fd]) break;
  }
  if (wret == -1) status = -1;
  signal(SIGINT, intsave);
  signal(SIGQUIT, quitsave);
  signal(SIGHUP, hupsave);
  pids[fd] = 0;
  return(status);
}
