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
using namespace std;

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

Mat FireDetectionHSV(Mat& image)	//利用HSV划分阈值进行火焰检测
{
	Mat imageHSV;
	cvtColor(image, imageHSV, COLOR_BGR2HSV);
	Mat BinaryImage = Mat::zeros(image.rows, image.cols, CV_8UC1);
	for (int i = 0; i < imageHSV.rows; i++)
	{
		for (int j = 0; j < imageHSV.cols; j++)
		{
			int value_h = imageHSV.at<cv::Vec3b>(i, j)[0];
			int value_s = imageHSV.at<cv::Vec3b>(i, j)[1];
			int value_v = imageHSV.at<cv::Vec3b>(i, j)[2];
			if ((value_h >= 0 && value_h <= 60) && (value_s <= 255 && value_s >= 160) && (value_v <= 255 && value_v >= 160))
			{
				BinaryImage.at<uchar>(i, j) = 255;
				image.at<cv::Vec3b>(i, j)[0] = 0;
				image.at<cv::Vec3b>(i, j)[1] = 255;
				image.at<cv::Vec3b>(i, j)[2] = 0;
			}
		}
	}

	return BinaryImage;

}


int cameraTest() {

	// 创建VideoCapture对象，参数为0表示打开默认摄像头
	VideoCapture cap(1);

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

		//frame = FireDetectionHSV(frame);

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

int faceClassifierTest() {


	// 加载人脸检测器
	CascadeClassifier Classifier;
	string Path = "D:/tools/opencv/build/etc/haarcascades/haarcascade_frontalface_default.xml";
	Classifier.load(Path);
	if (!Classifier.load(Path))   //加载xml文件  
	{
		cout << "xml文件加载失败" << endl;
		return -1;
	}

	// 创建VideoCapture对象，参数为0表示打开默认摄像头
	VideoCapture cap(1);
	vector<Rect> faces;

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
		cv::putTextZH(frame, "Hello, 很赞", cv::Point(20, 20), CV_RGB(255, 255, 255), 20);

		Classifier.detectMultiScale(frame, faces, 1.1, 3, 0, Size(30, 30));

		for (size_t t = 0; t < faces.size(); t++)
		{
			rectangle(frame, faces[t], Scalar(0, 255, 0), 2, 8);//画个绿框
		}
		imshow("Camera", frame);
		waitKey(10);//延时10ms


					// 按下q键退出循环
		if (waitKey(3) == 'q')
			break;
	}

	// 释放摄像头资源和所有窗口
	cap.release();
	destroyAllWindows();

}

int main()
{
	//显示图像
	imgTest();
	//显示摄像头
	int ret = cameraTest();

	faceClassifierTest();

	return 0;
}
