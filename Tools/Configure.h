/**
 *  @file Configure.h
 *
 *  @date 2012-2-27
 *  @author Bonly
 */

#ifndef CONFIGURE_H_
#define CONFIGURE_H_

typedef struct _Configure Configure;
enum {PTM=50}; //<Ëõ·ÅÂÊ
struct _Configure
{
    int X; //<ÆÁÄ»·Ö±æÂÊX
    int Y; //<ÆÁÄ»·Ö±æÂÊY
    int ShiftX;//< XÆ«ÒÆ
    int ShiftY;//< YÆ«ÒÆ
};

void destory_conf(); //< ÊÍ¹¹

Configure* instance_conf();

#define CONF instance_conf()
#define DELCONF() destory_conf()

#endif /* CONFIGURE_H_ */
