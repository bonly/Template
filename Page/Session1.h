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
        static int  init(); ///< ��ʼ������ָ��
        static void onPaint(); ///< ��Ⱦ����ָ��
        static void running(); ///< ������Ϸ�߼��ĺ���ָ��

    public:
        Page  _page;
};

//extern "C"{ 
Page* createSession1(); ///< ����ҳ�溯��
void onDestory(); ///< �ͷ���Դ����ָ��
//}
#endif /* SESSION1_H_ */
