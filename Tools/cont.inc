#if WIN32 
#pragma warning(disable:4002)
#endif
//按钮标识,
//         X,Y,W,H,UP图片ID,DOWN图片ID,OVER图片ID,
//         OnPointerPressed函数,OnPointerDragged函数,OnPointerReleased函数,
//         OnKeyPressed函数,OnKeyReleased函数

#define CONT
RES(test, 8, 1, 2, 0, 0, ID_red, ID_blue, ID_green, click, click, NP, NK, NK)
#undef CONT