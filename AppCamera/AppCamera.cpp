// AppCamera.cpp: 定义控制台应用程序的入口点。
//
//读取图片并显示

#include "stdafx.h"
#include "stdio.h"
#include<iostream> 
#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2\imgproc.hpp>
#include "cv_puttextzh.h"

using namespace cv;

void imgTest() {

	Mat img = imread("D:/xcy.jpg");
	cv::putTextZH(
		img,
		"Hello, opencv很赞",
		cv::Point(1100, 600),
		CV_RGB(255, 255, 255),
		20
	);
	namedWindow("测试opencv", WINDOW_AUTOSIZE);
	imshow("测试opencv", img);
	waitKey(3000);
	cv::destroyWindow("测试opencv");
}

int cameraTest() {

	// 创建VideoCapture对象，参数为0表示打开默认摄像头
	VideoCapture cap(0);

	// 检查摄像头是否成功打开
	if (!cap.isOpened())
	{
		std::cout << "Failed to open camera!" << std::endl;
		return -1;
	}

	// 创建窗口
	namedWindow("Camera", WINDOW_NORMAL);

	// 循环读取摄像头捕捉到的帧并显示
	while (true)
	{
		// 读取一帧图像
		Mat frame;
		cap.read(frame);

		// 检查是否成功读取到一帧图像
		if (frame.empty())
		{
			std::cout << "Failed to read frame from camera!" << std::endl;
			break;
		}

		// 显示图像
		cv::putTextZH(
			frame,
			"Hello, 很赞",
			cv::Point(20, 20),
			CV_RGB(255, 255, 255),
			20
		);
		imshow("Camera", frame);

		// 按下q键退出循环
		if (waitKey(1) == 'q')
			break;
	}

	// 释放摄像头资源和所有窗口
	cap.release();
	destroyAllWindows();

	return 0;
}

int main()
{
	//显示图像
	imgTest();
	//显示摄像头
	int ret = cameraTest();

	return ret;
}
