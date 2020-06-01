#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "iostream"
#include "fstream"
#include "stdint.h"

using namespace cv;
using namespace std;

void pic_to_rgb(Mat const& img);

int main()
{
	setlocale(0, "");

	Mat pic_inp;
	char file_name[256];

	cout << "Введите название файла - ";
	cin >> file_name;
	getchar();

	pic_inp = imread(file_name, CV_LOAD_IMAGE_COLOR);
//	namedWindow("Input image", CV_WINDOW_AUTOSIZE);
//	imshow("Input image", pic_inp);

	Mat gray, edge, pic_out;
	cvtColor(pic_inp, gray, CV_BGR2GRAY);

	Canny(gray, edge, 50, 150, 3);

	edge.convertTo(pic_out, CV_8U);
//	namedWindow("Output image", CV_WINDOW_AUTOSIZE);
//	imshow("Canny", pic_out);

	Mat pic_inv = ~pic_out;
//	imshow("Output.jpg", pic_inv);

	imwrite("Output.jpg", pic_inv);

	waitKey(0);

	Mat pic_rgb;
	pic_rgb = imread("Output.jpg", CV_LOAD_IMAGE_COLOR);

	cout << "Нажмите на любую клавишу для записи данных в файл. " << endl;
	getchar();
	cout << "Подождите, идёт запись в файл..." << endl;

	pic_to_rgb(pic_rgb);

	cout << "Запись окончена, нажмите на любую клавшу для завершения программы.";
	getchar();
	return 0;
}

void pic_to_rgb(Mat const& img)
{
	int rd, gn, bl, r, c;
	ofstream outf_rgb;

	outf_rgb.open("RGB.txt");

	for (r = 0; r < img.rows; r++)
	{
		for (c = 0; c < img.cols; c++)
		{
			rd = img.at<Vec3b>(r, c)[2];
			outf_rgb << rd << ' ';
			gn = img.at<Vec3b>(r, c)[1];
			outf_rgb << gn << ' ';
			bl = img.at<Vec3b>(r, c)[0];
			outf_rgb << bl << endl;
		}
	}
	outf_rgb << "Размер картинки: " << c << "x" << r;
	outf_rgb.close();
}