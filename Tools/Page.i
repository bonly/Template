#line 1 ".\\Page.cpp"







#line 1 "f:\\home\\bonly\\my documents\\visual studio 2005\\projects\\template\\tools\\Page.h"










typedef struct _Page Page;
struct _Page
{
    int  (*init)(); 
    void (*onPaint)(); 
    void (*onDestory)(); 
    void (*running)(); 
};

#line 21 "f:\\home\\bonly\\my documents\\visual studio 2005\\projects\\template\\tools\\Page.h"
#line 9 ".\\Page.cpp"



