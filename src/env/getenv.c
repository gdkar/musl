#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "libc.h"

char *getenv(const char *name)
{
  if(!__environ || !name[0] ) return NULL;
  uint16_t  * name_16 = (uint16_t*)name;
  uint16_t ** environ_16 = (uint16_t**)__environ;
  if(!name[1])
  {
    uint16_t name_start = ('='<<8)|name[0];
    for(uint16_t **ep = environ_16;*ep;++ep)
    {
        uint16_t ep_start = **ep;
        memmove(&ep_start,ep,sizeof(ep_start));
        if ( name_start == ep_start )
          return (char*)&(*ep)[1];
    }
  }
  else
  {
    uint16_t name_start = name_16[0];
    name = (const char *)&name_16[1];
    size_t len = strlen(name);
    for(uint16_t **ep = environ_16; *ep; ++ep)
    {
      uint16_t ep_start = **ep;
      if ( ep_start == name_start && !strncmp ( (const char*)&(*ep)[1],name,len)
                                  && (*ep)[len + 2] == '=')
        return &((char*)*ep)[len+3];
    }
  }
  return NULL;
/*	int i;
	size_t l = strlen(name);
	if (!__environ || !*name || strchr(name, '=')) return NULL;
	for (i=0; __environ[i] && (strncmp(name, __environ[i], l)
		|| __environ[i][l] != '='); i++);
	if (__environ[i]) return __environ[i] + l+1;
	return NULL;*/
}
