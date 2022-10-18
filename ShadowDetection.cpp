// ShadowDetection.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;
//形态学闭运算 先膨胀后腐蚀
Mat Closure(const Mat& img){
    Mat dst;
	//设置卷积核大小
    int element_size = 1;
    int s = element_size * 2 + 1;
	//闭运算
    Mat structureElement = getStructuringElement(MORPH_RECT, Size(s, s), Point(-1, -1));
    dilate(img, dst, structureElement, Point(-1, -1), 1);//先膨胀
    erode(dst, dst, structureElement, Point(-1, -1));//再腐蚀
    return dst;
}
//基于HSV彩色空间的阴影检测///////////////////////////////////////////
Mat HSV(const Mat& img) {
	int width = img.cols;
	int height = img.rows;
	Mat dst,img_hsv;
	img_hsv.create(img.size(), img.type());
	dst.create(img.size(), CV_8UC3);
	//BGR转换到HSV空间
	cvtColor(img, img_hsv, COLOR_BGR2HSV);//H色调 S饱和度 V明度
	double h, s, v, m;
	//计算指数m(-1~1)并进行阈值分割
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) {
			h = img_hsv.at<Vec3b>(i, j)[0];
			s = img_hsv.at<Vec3b>(i, j)[1];
			v = img_hsv.at<Vec3b>(i, j)[2];
			m = (((s - v) / (h + s + v)));
			if (m > 0.3)//分割阈值设为0.3
				dst.at<Vec3b>(i, j) = { 0,255,255 };
			else
				dst.at<Vec3b>(i, j) = { 100,0,100 };
		}
    //执行闭运算
    dst = Closure(dst);
	imshow("阴影检测-HSV", dst);
	imwrite("HSV.jpg", dst);
	return dst;
}
//基于C1C2C3彩色空间的阴影检测////////////////////////////////////////
Mat C1C2C3(const Mat& img) {
	int width = img.cols;
	int height = img.rows;
	Mat dst,temp;
    dst.create(img.size(), CV_8UC3);
    double C3;
    //计算C3指数，并进行双阈值分割
    for (int i = 0; i < height; i++) 
        for (int j = 0; j < width; j++) {
            double R = img.at<Vec3b>(i, j)[2];
            double G = img.at<Vec3b>(i, j)[1];
            double B = img.at<Vec3b>(i, j)[0];
            C3 = atan(B / MAX(R,G));
            if (C3 > 0.4 && B < 34) //阈值设为C3>0.4和Blue<34
                dst.at<Vec3b>(i, j) = { 0,255,255 };
            else
                dst.at<Vec3b>(i, j) = { 100,0,100 };
        }
    //执行闭运算
    dst = Closure(dst);
    imshow("阴影检测-C1C2C3", dst);
	imwrite("C1C2C3.jpg", dst);
	return dst;
}
int main()
{
	Mat srcImg = imread("第三部分 阴影检测/Color.bmp", 4);//保持原通道数原深度
	HSV(srcImg);
	C1C2C3(srcImg);
	waitKey(0);
	imshow("test", srcImg);

}


