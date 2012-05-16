/**
 *  @file Page.h
 *
 *  @date 2012-2-27
 *  @author Bonly
 */

#ifndef PAGE_H_
#define PAGE_H_

typedef struct _Page Page;
struct _Page
{
    int  (*init)(); ///< ��ʼ������ָ��
    void (*onPaint)(); ///< ��Ⱦ����ָ��
    void (*onDestory)(); ///< �ͷ���Դ����ָ��
    void (*running)(); ///< ������Ϸ�߼��ĺ���ָ��
    
    bool (*OnPointerPressed)(int x, int y);
    bool (*OnPointerDragged)(int x, int y);
    bool (*OnPointerReleased)(int x, int y);
    bool (*OnKeyReleased)(int keyCode);
    bool (*OnKeyPressed)(int keyCode);
};

#endif /* PAGE_H_ */
