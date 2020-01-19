#pragma once
void createbutton(int l, int r, int u, int d, int size, LPCTSTR lpszFace);
void setheadline(int x, int y, int size, LPCTSTR lpszFace);
void drawAlpha(IMAGE* picture, int  picture_x, int picture_y);
void loadAlpha(IMAGE* img, LPCTSTR pImgFile, int nWidth, int nHeight, bool bResize);
void transparentimage(IMAGE *dstimg, int x, int y, IMAGE *srcimg, UINT transparentcolor);
void puttextxy(int x, int y, int num);