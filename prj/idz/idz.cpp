////#include <opencv2/opencv.hpp>
////
////using namespace cv;
////
////int main()
////{
////
////   Mat image(Mat::zeros(800, 600, CV_8U));
////   int fontFace(FONT_HERSHEY_PLAIN);
////   double fontScale(2.0);
////   int thickness(3);  
////   Point textOrg(50, 50);
////   putText(image, "Hello, word!", textOrg, fontFace, fontScale, Scalar::all(255), thickness, 8);
////   imshow("Hello, word! Press any key...", image);
////   waitKey(0);
////   return 0;
////}
//
////
//// пример нахождения контуров с помощью функции cvFindContours()
////
//// http://robocraft.ru
////
//
//#include <cv.h>
//#include <highgui.h>
//#include <stdlib.h>
//#include <stdio.h>
//
//IplImage* image = 0;
//IplImage* gray = 0;
//IplImage* bin = 0;
//IplImage* dst = 0;
//
//int main(int argc, char* argv[])
//{
//        // имя картинки задаётся первым параметром
//        char* filename = argc >= 2 ? argv[1] : "Image0.jpg";
//        // получаем картинку
//        image = cvLoadImage(filename,1);
//
//        printf("[i] image: %s\n", filename);
//        assert( image != 0 );
//
//        // создаём одноканальные картинки
//        gray = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 1 );
//        bin = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 1 );
//        // клонируем
//        dst = cvCloneImage(image);
//        // окно для отображения картинки
//        cvNamedWindow("original",CV_WINDOW_AUTOSIZE);
//        cvNamedWindow("binary",CV_WINDOW_AUTOSIZE);
//        cvNamedWindow("contours",CV_WINDOW_AUTOSIZE);
//
//        // преобразуем в градации серого
//        cvCvtColor(image, gray, CV_RGB2GRAY);
//
//        // преобразуем в двоичное
//        cvInRangeS(gray, cvScalar(40), cvScalar(150), bin); // atoi(argv[2])
//
//        CvMemStorage* storage = cvCreateMemStorage(0);
//        CvSeq* contours=0;
//
//        // находим контуры
//        int contoursCont = cvFindContours( bin, storage,&contours,sizeof(CvContour),CV_RETR_LIST,CV_CHAIN_APPROX_SIMPLE,cvPoint(0,0));
//
//        // нарисуем контуры
//        for(CvSeq* seq0 = contours;seq0!=0;seq0 = seq0->h_next){
//                cvDrawContours(dst, seq0, CV_RGB(255,216,0), CV_RGB(0,0,250), 0, 1, 8); // рисуем контур
//        }
//
//        // показываем картинки
//        cvShowImage("original",image);
//        cvShowImage("binary", bin);
//        cvShowImage("contours", dst);
//
//        // ждём нажатия клавиши
//        cvWaitKey(0);
//
//        // освобождаем ресурсы
//        cvReleaseImage(&image);
//        cvReleaseImage(&gray);
//        cvReleaseImage(&bin);
//        cvReleaseImage(&dst);
//        // удаляем окна
//        cvDestroyAllWindows();
//        return 0;
//}

/**
 * @function findContours_Demo.cpp
 * @brief Demo code to find contours in an image
 * @author OpenCV team
 */






//
//#include "opencv2/imgcodecs.hpp"
//#include "opencv2/highgui.hpp"
//#include "opencv2/imgproc.hpp"
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//Mat src_gray;
//int thresh = 100;
//RNG rng(12345);
//
///// Function header
//void thresh_callback(int, void*);
//
///**
// * @function main
// */
//int main(int argc, char** argv)
//{
//	/// Load source image
//	CommandLineParser parser(argc, argv, "{@input | C:/Users/julno/Desktop/sample/data/Jenna.jpg | input image}");
//	Mat src = imread(parser.get<String>("@input"));
//	if (src.empty())
//	{
//		cout << "Could not open or find the image!\n" << endl;
//		cout << "Usage: " << argv[0] << " <Input image>" << endl;
//		return -1;
//	}
//
//	/// Convert image to gray and blur it
//	cvtColor(src, src_gray, COLOR_BGR2GRAY);
//	blur(src_gray, src_gray, Size(3, 3));
//
//	/// Create Window
//	const char* source_window = "Source";
//	namedWindow(source_window);
//	imshow(source_window, src);
//
//	const int max_thresh = 255;
//	createTrackbar("Canny thresh:", source_window, &thresh, max_thresh, thresh_callback);
//	thresh_callback(0, 0);
//
//	waitKey();
//	return 0;
//}
//
///**
// * @function thresh_callback
// */
//void thresh_callback(int, void*)
//{
//	/// Detect edges using Canny
//	Mat canny_output;
//	Canny(src_gray, canny_output, thresh, thresh * 2);
//
//	/// Find contours
//	vector<vector<Point> > contours;
//	vector<Vec4i> hierarchy;
//	findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
//
//	/// Draw contours
//	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
//	for (size_t i = 0; i < contours.size(); i++)
//	{
//		Scalar color = Scalar(0.0, 128.0, 0.0);
//		drawContours(drawing, contours, (int)i, color, 1, LINE_4, hierarchy, 0);
//	}
//
//	/// Show in a window
//	imshow("Contours", drawing);
//}




//
//#include "opencv2/objdetect/objdetect.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//
//using namespace cv;
//using namespace std;
//
//int main()
//{
//	Mat image = imread("C:/Users/julno/Desktop/sample/data/Jenna.jpg");
//	Mat binary = imread("C:/Users/julno/Desktop/sample/data/Jenna.png", 0);
//
//	// Eliminate noise and smaller objects
//	Mat fg;
//	erode(binary, fg, Mat(), Point(-1, -1), 2);
//
//	// Identify image pixels without objects
//	Mat bg;
//	dilate(binary, bg, Mat(), Point(-1, -1), 3);
//	threshold(bg, bg, 1, 128, THRESH_BINARY_INV);
//
//	// Create markers image
//	Mat markers(binary.size(), CV_8U, Scalar(0));
//	markers = fg + bg;
//
//	markers.convertTo(markers, CV_32S);
//	watershed(image, markers);
//
//	markers.convertTo(markers, CV_8U);
//	imshow("a", markers);
//	waitKey(0);
//}

//#include <opencv2/core/core.hpp> 
//#include <opencv2/highgui/highgui.hpp>
//#include <string>
//#include <iostream>
//using namespace cv;
//using namespace std;
//
//int main(int argc, char** argv)
//{
//	// Read original image 
//	Mat src;
//	Mat src1 = imread("C:/Users/julno/Desktop/iV1qavzzp_4.jpg");
//	src = src1;
//
//	//if fail to read the image
//	if (!src.data)
//	{
//		cout << "Error loading the image" << endl;
//		return -1;
//	}
//
//	// Create a window
//	namedWindow("My Window", 1);
//
//	//Create trackbar to change brightness
//	int iSliderValue1 = 50;
//	createTrackbar("Brightness", "My Window", &iSliderValue1, 100);
//
//	//Create trackbar to change contrast
//	int iSliderValue2 = 50;
//	createTrackbar("Contrast", "My Window", &iSliderValue2, 100);
//
//	while (true)
//	{
//		//Change the brightness and contrast of the image
//		Mat dst;
//		int iBrightness = iSliderValue1 - 50;
//		double dContrast = iSliderValue2 / 50.0;
//		src.convertTo(dst, -1, dContrast, iBrightness);
//
//		//show the brightness and contrast adjusted image
//		int width = 2 * src1.cols; // width of 2 images next to each other
//		int height = src1.rows;
//
//		cv::Mat inputAll = cv::Mat(height, width, src1.type());
//
//		cv::Rect subImageROI = cv::Rect(0, 0, src1.cols, src1.rows);
//
//		// copy to subimage:
//		src1.copyTo(inputAll(subImageROI));
//
//		// move to 2nd image ROI position:
//		subImageROI.x = src1.cols;
//		dst.copyTo(inputAll(subImageROI));
//
//		imshow("My Window", inputAll);
//		/*imshow("My Window", src1);*/
//
//		// Wait until user press some key for 50ms
//		int iKey = waitKey(50);
//
//		//if user press 'ESC' key
//		if (iKey == 27)
//		{
//			break;
//		}
//	}
//
//	return 0;
//}