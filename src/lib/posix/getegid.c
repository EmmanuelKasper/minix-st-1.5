#include <lib.h>
#include <sys/types.h>

PUBLIC gid_t getegid()
{
  int k;
  k = callm1(MM, GETGID, 0, 0, 0, NIL_PTR, NIL_PTR, NIL_PTR);
  if (k < 0) return((gid_t) k);
  return((gid_t) _M.m2_i1);
}
