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
    int  (*init)(); ///< 初始化函数指针
    void (*onPaint)(); ///< 渲染函数指针
    void (*onDestory)(); ///< 释放资源函数指针
    void (*running)(); ///< 处理游戏逻辑的函数指针
    
    bool (*OnPointerPressed)(int x, int y);
    bool (*OnPointerDragged)(int x, int y);
    bool (*OnPointerReleased)(int x, int y);
    bool (*OnKeyReleased)(int keyCode);
    bool (*OnKeyPressed)(int keyCode);
};

#endif /* PAGE_H_ */
