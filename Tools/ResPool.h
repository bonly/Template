/**
 *  @file ResPool.h
 *
 *  @date 2012-2-27
 *  @author Bonly
 */

#ifndef RESPOOL_H_
#define RESPOOL_H_

#ifdef __cplusplus
extern "C"{
#endif

typedef struct _Obj Obj;

/**
 * 定义创建实例的函数格式
 * @param void* 不指定类型的指针,可NULL
 */
typedef int(*Tcreate)(void*);

/**
 * 对象结构体
 */
struct _Obj
{
    int ID;  ///< 与列表中的序号一一对应,从0开始
    void *obj; ///< 对象实例指针
    Tcreate create;  ///< 创建实例的函数指针
};

/**
 * 资源访问接口
 */
typedef struct _ResPool
{
   Obj* (*getObj)(int ID);  ///< 取得对象
   void (*delObj)(int idx); ///< 删除对象
   void (*fix_relation)();  ///< 补完整结构数据
   int  res_max;  ///< 最大资源数
   Obj** List;    ///< 指向存储数组
}ResPool;

/**
 * 取ResPool实例
 * @return ResPool实例
 */
typedef int (*pinit)(ResPool*); ///< 初始化对象的函数指针
ResPool* instance_ResPool(ResPool* *resp, pinit child_init);  ///< 获取对象

/** 
 * 销毁对象池
 */
void destory_resp(ResPool* resp);

/**
 * 方便外部访问的宏 
 */
#define RESP(X,Y) instance_ResPool(X,Y) ///< @def RESP   X: ResPool* Y: pinit
#define DELRESP(X) destory_resp(X) ///< @def DELRESP     X: ResPool*

#ifdef __cplusplus
}
#endif


#endif /* RESPOOL_H_ */