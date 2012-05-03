/**
 *  @file ResPool.h
 *
 *  @date 2012-2-27
 *  @author Bonly
 */

#ifndef RESPOOL_H_
#define RESPOOL_H_

typedef struct _Obj Obj;

/**
 * ���崴��ʵ���ĺ�����ʽ
 * @param void* ��ָ�����͵�ָ��,��NULL
 */
typedef int(*Tcreate)(void*);

/**
 * ����ṹ��
 */
struct _Obj
{
    int ID;  ///< ���б��е����һһ��Ӧ,��0��ʼ
    void *obj; ///< ����ʵ��ָ��
    Tcreate create;  ///< ����ʵ���ĺ���ָ��
};

/**
 * ��Դ���ʽӿ�
 */
struct ResPool
{
   Obj* (*getObj)(int ID);  ///< ȡ�ö���
   void (*delObj)(int idx); ///< ɾ������
   void (*fix_relation)();  ///< �������ṹ����
   int  res_max;  ///< �����Դ��
   Obj** List;    ///< ָ��洢����
};

/**
 * ȡResPoolʵ��
 * @return ResPoolʵ��
 */
typedef int (*pinit)(ResPool*); ///< ��ʼ������ĺ���ָ��
ResPool* instance_ResPool(ResPool *&resp, pinit child_init=0);  ///< ��ȡ����

/** 
 * ���ٶ����
 */
void destory_resp(ResPool* resp);

/**
 * �����ⲿ���ʵĺ� 
 */
#define RESP(X,Y) instance_ResPool(X,Y) ///< @def RESP   X: ResPool* Y: pinit
#define DELRESP(X) destory_resp(X) ///< @def DELRESP     X: ResPool*
#endif /* RESPOOL_H_ */