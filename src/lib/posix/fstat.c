#include <lib.h>
#include <sys/types.h>
#include <sys/stat.h>

PUBLIC int fstat(fd, buffer)
int fd;
struct stat *buffer;
{
  return(callm1(FS, FSTAT, fd, 0, 0, (char *)buffer, NIL_PTR, NIL_PTR));
}
