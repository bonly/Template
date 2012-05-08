/**
 *  @file Configure.h
 *
 *  @date 2012-2-27
 *  @author Bonly
 */

#ifndef CONFIGURE_H_
#define CONFIGURE_H_

typedef struct _Configure Configure;
enum {PTM=50}; //<������
struct _Configure
{
    int X; //<��Ļ�ֱ���X
    int Y; //<��Ļ�ֱ���Y
    int ShiftX;//< Xƫ��
    int ShiftY;//< Yƫ��
};

void destory_conf(); //< �͹�

Configure* instance_conf();

#define CONF instance_conf()
#define DELCONF() destory_conf()

#endif /* CONFIGURE_H_ */
