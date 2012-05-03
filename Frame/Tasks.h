/**
 *  @file Tasks.h
 *
 *  @date 2012-2-27
 *  @author Bonly
 */

#ifndef TASKS_H_
#define TASKS_H_

typedef struct _Tasks Tasks;
typedef struct _Page Page;
typedef struct _PageEntry PageEntry;

/**
 * 入口函数,负责创建页面结构体
 * @return Page* 创建的页面指针,0为失败
 */
typedef Page* PageCreateFcn();

/**
 * 页面入口存储器
 */
struct _PageEntry
{
        int idx;
        Page* page;
        PageCreateFcn* creatFcn;
};

/**
 * 任务管理,控制页面
 */
struct _Tasks
{
        int page_count; ///< 页面总数
        int current_page; ///< 当前页面
        int next_page; ///< 下个页面
        int operation; ///< 操作标识
        PageEntry* (*get_page)(int idx); ///< 取得指定的页面
        void (*destory_tasks)(); ///< 销毁task列表
        void (*destory_task)(const int idx); ///< 销毁单个task
        void (*run)(void*); ///< 运算页面处理逻辑
        void (*onPaint)(void*); ///< 渲染
};
/**
 * @enum 操作标识
 */
enum {CURRENT_PAGE,NEXT_PAGE};

/**
 * 取得tasks实例
 * @return Tasks& 返回实例
 */
Tasks* get_tasks();

/**
 * 方便外部操作Tasks实例的封装
 */
#define TASKS get_tasks() ///< 获取任务管理器
#define CURPAGE TASKS->get_page(TASKS->current_page)  ///< 取当前页面
#define NEXTPAGE TASKS->get_page(TASKS->next_page)  ///< 取下一个页面
#define DELPAGE(X) TASKS->destory_task(X)  ///< 删除指定页面
#define DELTASK() TASKS->destory_tasks() ///< 删除整个任务管理器及页面列表
#endif /* TASKS_H_ */
