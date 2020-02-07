/*
 FILE: background.h/cpp
 FUNCTION: some functions used for graphics
 COPYRIGHT: Evergrow Hook
*/
#pragma once
void createbutton(int l, int r, int u, int d, int size, LPCTSTR lpszFace);//create a button
void setheadline(int x, int y, int size, LPCTSTR lpszFace);//create a headline
void drawAlpha(IMAGE* picture, int  picture_x, int picture_y);// load a .png picture and remove the transparent part
void loadAlpha(IMAGE* img, LPCTSTR pImgFile, int nWidth, int nHeight, bool bResize);//load an image in a clear way
void transparentimage(IMAGE *dstimg, int x, int y, IMAGE *srcimg, UINT transparentcolor);//another way of showing a transparent image
void puttextxy(int x, int y, int num);//show a number
