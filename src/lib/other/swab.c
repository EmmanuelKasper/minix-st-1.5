#include <lib.h>
/*  swab(3)
 *
 *  Author: Terrence W. Holm          Sep. 1988
 */

void swab(from, to, count)
char *from;
char *to;
int count;
{
  register char temp;

  count >>= 1;

  while (--count >= 0) {
	temp = *from++;
	*to++ = *from++;
	*to++ = temp;
  }
}
