#include <iostream>
#include "MeanShift.h"

Mat src_gray;
int thresh = 255;
// Загрузка изображения


Mat Dst;

void thresh_callback(int, void*)
{
	/// Нахождение границ, используя детектор Канни
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
	Mat Img;
	string filename;
	cin >> filename;
	cout << filename;
	Img = imread(filename);


	//namedWindow("The Original Picture before resize");
	//imshow("The Original Picture before resize", Img);

	int y_size = 400;
	int x_size;
	if (Img.rows >= y_size) {
		x_size = (int)(Img.cols / ((double)Img.rows / y_size));
	}
	else
	{
		x_size = (int)(Img.cols * ((double)y_size / Img.rows));
	}
	resize(Img, Img, Size(x_size, y_size));

	// Вывод оригинала
	namedWindow("The Original Picture");
	imshow("The Original Picture", Img);

	// Конвертирование из RGB в Lab
	cvtColor(Img, Img, COLOR_RGB2Lab);

	// Вывод после конвертирования из RGB в Lab
	//namedWindow("After Converting");
	//imshow("After Converting", Img);

	// Инициализация с пространственной и цветовой пропускной способностью
	MeanShift MSProc(16, 4);
	// Процесс фильтрации
	MSProc.MSFiltering(Img);

	// Вывод после Mean Shift Filtering
	//namedWindow("After Filtering");
	//imshow("After Filtering", Img);

	// Процесс сегментации, включающий процесс фильтрации 
	MSProc.MSSegmentation(Img);

	// Вывод результата MS
	//namedWindow("After Segmentation");
	//imshow("After Segmentation", Img);
	

	// Вывод пропускной способности
	cout<<"the Spatial Bandwith is "<<MSProc.hs<<endl;
	cout<<"the Color Bandwith is "<<MSProc.hr<<endl;

	// Конвертирование из Lab в RGB
	cvtColor(Img, Img, COLOR_Lab2RGB);

	// Вывод результата MS
	//namedWindow("MS Picture");
	//imshow("MS Picture", Img);

	// Преобразование изображения в серый и размытие
	cvtColor(Img, src_gray, COLOR_BGR2GRAY);

	// Вывод результата MS
	//namedWindow("Gray");
	//imshow("Gray", src_gray);

	blur(src_gray, src_gray, Size(3, 3));

	// Вывод результата MS
	//namedWindow("Blur");
	//imshow("Blur", src_gray);

	namedWindow("Posterize Picture");

	const int max_thresh = 255;
	createTrackbar("Canny thresh:", "Posterize Picture", &thresh, max_thresh, thresh_callback);

	Dst = Img;
	thresh_callback(0, 0);

	waitKey();
	return 1;
}

