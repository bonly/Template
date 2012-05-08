/**
 *  @file Session1.h
 *
 *  @date 2012-3-22
 *  @author Bonly
 */

#ifndef SESSION1_H_
#define SESSION1_H_
#include "../Tools/Page.h"

class Session1
{
    public:
        Session1();
        virtual ~Session1();
        static int  init(); ///< 初始化函数指针
        static void onPaint(); ///< 渲染函数指针
        static void running(); ///< 处理游戏逻辑的函数指针

    public:
        Page  _page;
};

//extern "C"{ 
Page* createSession1(); ///< 创建页面函数
void onDestory(); ///< 释放资源函数指针
//}
#endif /* SESSION1_H_ */
