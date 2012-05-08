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

///Ԥ���屾�غ���
static bool OnPointerPressed(int x, int y);

/**
 * ҳ���б�
 */
static PageEntry list[] = {
  { 0, 0, createPreLoad},
  { 1, 0, createSession1},
  { 2, 0, 0 }
};

/**
 * �ļ���̬����tasks
 */
static Tasks *tasks = 0;

/**
 * ����task�б�
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
 * ���ٵ���task
 * @param idx Ҫ���ٵ�ҳ������
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
 * ȡ��ָ����ҳ��
  * @param idx Ҫ��ȡ��ҳ�����
 * @return PageEntry* ָ��ҳ���ָ�� 0Ϊʧ��
 */
static PageEntry* get_page(int idx)
{
    if(idx >= TASKS->page_count || idx < 0 )
        return 0;
    return &list[idx];
}

/**
 * ���д����߼�
 * @param p
 */
static void run(void *p)
{
    if (TASKS->page_count < 1)///ֻ��һ��ҳ��(Ҳ����ҳ���б�Ϊ��),���˳�
      return;
    switch(TASKS->operation)
    {
      case NEXT_PAGE:
      {
        if (CURPAGE->page != 0)///��ɾ����ҳ
        {
            DELPAGE(TASKS->current_page);
            CURPAGE->page = 0;
        }
        if (TASKS->next_page == -1) ///��ȡ��һҳ����,-1��ʾ�˳�
        {
            EXIT(false);
        }
        TASKS->current_page = TASKS->next_page; ///��һҳ����Ϊ��ǰҳ��
        TASKS->operation = CURRENT_PAGE;
      }
      case CURRENT_PAGE:
      {
        if (CURPAGE->creatFcn != 0)
        {
          if (CURPAGE->page == 0)
          {
            //firstEnterFlag = 2;///���صȴ��ɲ�
            ///��������ʼ��ҳ��
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
 * ��Ⱦ
 * @param p
 */
static void onPaint(void *p)
{
  if (TASKS->page_count < 1) ///ֻ��һ��ҳ��(Ҳ����ҳ���б�Ϊ��),���˳�
        return;
  if (CURPAGE->page != 0)
  {
    CURPAGE->page->onPaint();
  }
  return ;
}

/**
 * ��ʼ������
 * @return -1:ʧ�� 0:�ɹ�
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
        list[tasks->page_count].idx = tasks->page_count;///���ñ�����ÿ���Ӧ��ID
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
 * ȡ��tasksʵ��
 * @return Tasks& ����ʵ��
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
  if (TASKS->page_count < 1) ///ֻ��һ��ҳ��(Ҳ����ҳ���б�Ϊ��),���˳�
        return false;
  if (CURPAGE->page != 0)
  {
    CURPAGE->page->OnPointerPressed(x, y);
  }
  return true;
}
