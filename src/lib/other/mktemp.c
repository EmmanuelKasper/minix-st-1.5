#include <lib.h>
/* mktemp - make a name for a temporary file */
#include <sys/types.h>
#include <unistd.h>

char *mktemp(template)
char *template;
{
  int pid;
  char *p;

  pid = getpid();		/* get process id as semi-unique number */
  p = template;
  while (*p++);			/* find end of string */
  p--;				/* backup to last character */

  /* Replace XXXXXX at end of template with pid. */
  while (*--p == 'X') {
	*p = '0' + (pid % 10);
	pid = pid / 10;
  }
  return(template);
}
