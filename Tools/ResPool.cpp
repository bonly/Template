/**
 *  @file ResPool.cpp
 *
 *  @date 2012-2-27
 *  @author Bonly
 */
#include "pre.h"
#include "ResPool.h"
#include <aeestdlib.h>

static ResPool* pool = 0; ///< ָ�򱻲�����
static Obj* getObj(int ID);

static int init(ResPool* resp)
{
  resp->getObj = getObj;
  return 0;
}

/**
 * �͹�,�������ʱɾ����Դ��
 */
void destory_resp(ResPool* resp)
{
    if (resp)
    {
        int i = 0;
        for ( i=0; i<resp->res_max; ++i)
        {
             resp->delObj(i);
        }
        SafeDelete(resp);
        resp = 0;
    }
}

/**
 * ȡ����
 * @param ID �����ID
 * @return  ����ʵ��ָ��
 */
static Obj* getObj(int ID)
{
    if (ID < 0 || ID > pool->res_max)
        return 0;
    if (pool->List[ID]->obj == 0)
        pool->List[ID]->create(0);
    return pool->List[ID];
}

/**
 * ��ȡ��Դʵ��
 */
ResPool* instance_ResPool(ResPool* *resp, pinit child_init)
{
    if(0 == *resp)
    {
        if (0 == child_init)
          return 0;

        *resp = SafeNew ResPool;
        (*resp)->List = 0;
        
        if ((0 != init(*resp)) || (0 != child_init(*resp)))
        {
          SafeDelete(*resp);
          return 0;
        }
        (*resp)->fix_relation();
    }
    pool = *resp;
    
    return pool;
}
