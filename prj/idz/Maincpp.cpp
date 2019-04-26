#include <iostream>
#include "MeanShift.h"

Mat src_gray;
int thresh = 100;
// Загрузка изображения
Mat Img = imread("C:/Users/julno/Desktop/Vajd2qsDFkk.jpg");
Mat Dst;

void thresh_callback(int, void*)
{
	/// Detect edges using Canny
	Mat canny_output;
	Canny(src_gray, canny_output, thresh, thresh * 2);

	/// Нахождение контуров
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

	/// Отрисовка контуров
	for (size_t i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(0, 0, 0);
		drawContours(Dst, contours, (int)i, color, 1, LINE_8, hierarchy, 0);
	}

	/// Показ в окне
	imshow("Posterize Picture", Dst);
}

int main(){
	
	resize(Img, Img, Size(319, 540), 0, 0, 1);
	// Вывод оригинала
	namedWindow("The Original Picture");
	imshow("The Original Picture", Img);

	// Конвертирование из RGB в Lab
	cvtColor(Img, Img, COLOR_RGB2Lab);

	// Initilize Mean Shift with spatial bandwith and color bandwith
	MeanShift MSProc(16, 4);
	// Filtering Process
	MSProc.MSFiltering(Img);
	// Segmentation Process include Filtering Process (Region Growing)
	MSProc.MSSegmentation(Img);

	Dst = Img;
	// Print the bandwith
	cout<<"the Spatial Bandwith is "<<MSProc.hs<<endl;
	cout<<"the Color Bandwith is "<<MSProc.hr<<endl;

	// Convert color from Lab to RGB
	cvtColor(Img, Img, COLOR_Lab2RGB);

	/// Convert image to gray and blur it
	cvtColor(Img, src_gray, COLOR_BGR2GRAY);
	blur(src_gray, src_gray, Size(3, 3));

	// Show the result image
	namedWindow("MS Picture");
	imshow("MS Picture", Img);

	namedWindow("Posterize Picture");

	const int max_thresh = 255;
	createTrackbar("Canny thresh:", "Posterize Picture", &thresh, max_thresh, thresh_callback);


	thresh_callback(0, 0);

	waitKey();
	return 1;
}

