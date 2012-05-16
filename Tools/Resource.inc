#if WIN32 
#pragma warning(disable:4002)
#endif
/*
斯凯: ID, 忽略, 文件名, 显示类型(透明) , 宽, 高
悠米: ID, 路径, 文件名, 显示类型(透明) , 宽, 高
*/

#ifdef IMGSEG
#ifdef __MTK__
RES(background, res/backgroud/, 2_bg.png, BM_COPY, 240, 400)
RES(se1, res/backgroud/, 1_bg.png, BM_COPY,240, 400)
RES(red, ./, book_red.dat, BM_TRANSPARENT,50, 50)
RES(blue, ./, book_blue.dat, BM_TRANSPARENT, 50, 50)
RES(green, ./, book_green.dat, BM_TRANSPARENT, 50, 50)
#endif

#ifdef __SKY__
RES(background, res/backgroud/, 2_bg.bmp, BM_COPY, 240, 400)
RES(se1, res/backgroud/, 1_bg.bmp, BM_COPY,240, 400)
RES(red, ./, book_red.bmp, BM_TRANSPARENT,50, 50)
RES(blue, ./, book_blue.bmp, BM_TRANSPARENT, 50, 50)
RES(green, ./, book_green.bmp, BM_TRANSPARENT, 50, 50)
RES(bk, ./, bk.bmp, BM_COPY, 240, 44)
RES(plane, ./, plane.bmp, BM_TRANSPARENT, 41, 26)
#endif
#endif