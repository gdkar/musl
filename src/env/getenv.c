#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "libc.h"

char *getenv(const char *name)
{
  if(!__environ || !name[0] ) return NULL;
  if(!__environ || !name[0] ) return NULL;
  if(!name[1])
  {
    uint16_t name_start = ('='<<8)|name[0];
    for(uint16_t **ep = (uint16_t**)__environ;*ep;++ep)
    {
        uint16_t ep_start = **ep;
        memmove(&ep_start,ep,sizeof(ep_start));
        if ( name_start == ep_start ) return (char*)&(*ep)[1];
    }
  }
  else
  {
    uint16_t name_start = *(uint16_t*)name;
    name = &name[2];
    size_t len = strlen(name);
    for(char **ep = __environ; *ep; ++ep)
    {
      if ( !(*ep)[2] ) continue;
      uint16_t ep_start = *(uint16_t*)(*ep);
      if ( ep_start == name_start && !strncmp ( &(*ep)[2],name,len)
                                  && (*ep)[len + 2] == '=')
        return &(*ep)[len+3];
    }
  }
  return NULL;
}
