/*
 FILE: background.h/cpp
 FUNCTION: some functions used for graphics
 COPYRIGHT: Evergrow Hook
*/
#include "pch.h"

//create a button
void createbutton(int l, int r, int u, int d, int size, LPCTSTR lpszFace) {
	setfillcolor(WHITE);
	solidroundrect(l, u, r, d, 0, 0);
	settextcolor(BLACK);
	settextstyle(size, 0, _T("宋体"));
	RECT rect = { l,u,r,d };
	drawtext(lpszFace, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

//create a headline
void setheadline(int x,int y,int size, LPCTSTR lpszFace) {
	settextcolor(YELLOW);
	settextstyle(size, 0, _T("黑体"));
	outtextxy(x, y, lpszFace);
}

// load a .png picture and remove the transparent part
//notice: this function is copied from the Internet
void drawAlpha(IMAGE* picture, int  picture_x, int picture_y) //x为载入图片的X坐标，y为Y坐标
{

	// 变量初始化
	DWORD *dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
	DWORD *draw = GetImageBuffer();
	DWORD *src = GetImageBuffer(picture); //获取picture的显存指针
	int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
	int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
	int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
	int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
	int dstX = 0;    //在显存里像素的角标

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //在显存里像素的角标
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
			int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //在显存里像素的角标
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
			}
		}
	}
}

//load an image in a clear way
void loadAlpha(IMAGE* img, LPCTSTR pImgFile, int nWidth = 0, int nHeight = 0, bool bResize = false) {
	IMAGE tp;
	loadimage(&tp, _T("img\\transparent.png"), 0, 0, true);
	*img = tp;
	loadimage(img, pImgFile, nWidth, nHeight, bResize);
}

//another way of showing a transparent image
//notice: this function is copied from the Internet
void transparentimage(IMAGE *dstimg, int x, int y, IMAGE *srcimg, UINT transparentcolor)
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();
	// 使用 Windows GDI 函数实现透明位图
	TransparentBlt(dstDC, x, y, w, h, srcDC, 0, 0, w, h, transparentcolor);
}

//show a number
void puttextxy(int x, int y, int num) {
	TCHAR ss[20];
	swprintf_s(ss, _T("%d"), num);
	outtextxy(x, y, ss);
}
