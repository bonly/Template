/**
 *  @file Configure.cpp
 *
 *  @date 2012-2-27
 *  @author Bonly
 */
#include "pre.h"
//#include <stdlib.h>
//#include <aeestdlib.h>
#include "Configure.h"

static Configure* conf = 0;

void destory_conf()
{
  if(conf)
    SafeFree ((Configure*)conf);
}


Configure* instance_conf()
{
  if(0 == conf)
  {
    conf = (Configure*)SafeMalloc(sizeof(Configure));
    return conf;
  }
  return conf;
}

