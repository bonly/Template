/**
 *  @file Tasks.cpp
 *
 *  @date 2012-2-27
 *  @author Bonly
 */
#include "pre.h"
//#include <stdlib.h>
#include <aeestdlib.h>
#include "Tasks.h"
#include "Page.h"

extern Page* createSession1();
extern Page* createPreLoad();

///预定义本地函数
static bool OnPointerPressed(int x, int y);

/**
 * 页面列表
 */
static PageEntry list[] = {
  { 0, 0, createPreLoad},
  { 1, 0, createSession1},
  { 2, 0, 0 }
};

/**
 * 文件静态变量tasks
 */
static Tasks *tasks = 0;

/**
 * 销毁task列表
 * @return void
 */
static void destory_tasks()
{
    int i = 0;
    for (i = 0; i < tasks->page_count; ++i)
    {
        if (list[i].page != 0)
        {
            list[i].page->onDestory();
            list[i].page = 0;
        }
    }
    if (tasks !=0)
    {
        SafeFree(tasks);
        tasks = 0;
    }
}

/**
 * 销毁单个task
 * @param idx 要销毁的页面索引
 * @return void
 */
static void destory_task(const int idx)
{
    if (list[idx].page != 0)
    {
        list[idx].page->onDestory();
        list[idx].page = 0;
    }
}

/**
 * 取得指定的页面
  * @param idx 要获取的页面序号
 * @return PageEntry* 指定页面的指针 0为失败
 */
static PageEntry* get_page(int idx)
{
    if(idx >= TASKS->page_count || idx < 0 )
        return 0;
    return &list[idx];
}

/**
 * 运行处理逻辑
 * @param p
 */
static void run(void *p)
{
    if (TASKS->page_count < 1)///只有一个页面(也就是页面列表为空),则退出
      return;
    switch(TASKS->operation)
    {
      case NEXT_PAGE:
      {
        if (CURPAGE->page != 0)///先删除旧页
        {
            DELPAGE(TASKS->current_page);
            CURPAGE->page = 0;
        }
        if (TASKS->next_page == -1) ///获取下一页索引,-1表示退出
        {
            EXIT(false);
        }
        TASKS->current_page = TASKS->next_page; ///下一页面切为当前页面
        TASKS->operation = CURRENT_PAGE;
      }
      case CURRENT_PAGE:
      {
        if (CURPAGE->creatFcn != 0)
        {
          if (CURPAGE->page == 0)
          {
            //firstEnterFlag = 2;///加载等待蒙层
            ///创建并初始化页面
            CURPAGE->page = CURPAGE->creatFcn();
            CURPAGE->page->init();
            TASKS->current_page = CURPAGE->idx;
          }
          CURPAGE->page->running();
        }
        break;
      }
    }
    return;
}

/**
 * 渲染
 * @param p
 */
static void onPaint(void *p)
{
  if (TASKS->page_count < 1) ///只有一个页面(也就是页面列表为空),则退出
        return;
  if (CURPAGE->page != 0)
  {
    CURPAGE->page->onPaint();
  }
  return ;
}

/**
 * 初始化任务
 * @return -1:失败 0:成功
 */
static int init()
{
    if (tasks == 0)
        return -1;
    tasks->current_page = 0;
    tasks->page_count = 0;
    tasks->next_page = 0;
    tasks->operation = CURRENT_PAGE;
    while (list[tasks->page_count].creatFcn != 0)
    {
        list[tasks->page_count].idx = tasks->page_count;///设置表列中每项对应的ID
        ++tasks->page_count;
    }

    tasks->destory_task = destory_task;
    tasks->destory_tasks = destory_tasks;
    tasks->get_page = get_page;
    tasks->run = run;
    tasks->onPaint = onPaint;
    tasks->OnPointerPressed = &OnPointerPressed;
    return 0;
}

/**
 * 取得tasks实例
 * @return Tasks& 返回实例
 */
Tasks* get_tasks()
{
    if (0==tasks)
    {
        tasks = (Tasks*)SafeMalloc(sizeof(Tasks));
        if(-1 == init())
        {
            SafeFree(tasks);
            return 0;
        }
    }
    return tasks;
}

static bool OnPointerPressed(int x, int y)
{
  if (TASKS->page_count < 1) ///只有一个页面(也就是页面列表为空),则退出
        return false;
  if (CURPAGE->page != 0)
  {
    CURPAGE->page->OnPointerPressed(x, y);
  }
  return true;
}
