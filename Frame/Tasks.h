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
 * ��ں���,���𴴽�ҳ��ṹ��
 * @return Page* ������ҳ��ָ��,0Ϊʧ��
 */
typedef Page* PageCreateFcn();

/**
 * ҳ����ڴ洢��
 */
struct _PageEntry
{
        int idx;
        Page* page;
        PageCreateFcn* creatFcn;
};

/**
 * �������,����ҳ��
 */
struct _Tasks
{
        int page_count; ///< ҳ������
        int current_page; ///< ��ǰҳ��
        int next_page; ///< �¸�ҳ��
        int operation; ///< ������ʶ
        PageEntry* (*get_page)(int idx); ///< ȡ��ָ����ҳ��
        void (*destory_tasks)(); ///< ����task�б�
        void (*destory_task)(const int idx); ///< ���ٵ���task
        void (*run)(void*); ///< ����ҳ�洦���߼�
        void (*onPaint)(void*); ///< ��Ⱦ
};
/**
 * @enum ������ʶ
 */
enum {CURRENT_PAGE,NEXT_PAGE};

/**
 * ȡ��tasksʵ��
 * @return Tasks& ����ʵ��
 */
Tasks* get_tasks();

/**
 * �����ⲿ����Tasksʵ���ķ�װ
 */
#define TASKS get_tasks() ///< ��ȡ���������
#define CURPAGE TASKS->get_page(TASKS->current_page)  ///< ȡ��ǰҳ��
#define NEXTPAGE TASKS->get_page(TASKS->next_page)  ///< ȡ��һ��ҳ��
#define DELPAGE(X) TASKS->destory_task(X)  ///< ɾ��ָ��ҳ��
#define DELTASK() TASKS->destory_tasks() ///< ɾ�����������������ҳ���б�
#endif /* TASKS_H_ */
