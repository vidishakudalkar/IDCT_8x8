#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


Mat IDCT(Mat dct) {
	int height = dct.rows - (dct.rows % 8);
	int width = dct.cols - (dct.cols % 8);
	float temp;
	double alphai, alphaj;


	Mat image_idct_dc(dct.rows, dct.cols, dct.type());
	for (int currentrow = 0; currentrow < height; currentrow += 8)
	{
		for (int currentcolumn = 0; currentcolumn < width; currentcolumn += 8)
		{
			for (int i = currentrow; i < currentrow + 8; i++)
			{
				for (int j = currentcolumn; j < currentcolumn + 8; j++)
				{

					temp = 0.0;
					if (i == 0) alphai = 1.0 / sqrt(2.0); else alphai = 1.0;
					if (j == 0) alphaj = 1.0 / sqrt(2.0); else alphaj = 1.0;
					for (int x = currentrow; x < currentrow + 8; x++)
					{
						for (int y = currentcolumn; y < currentcolumn + 8; y++)
						{

							temp += (dct.at<Vec3b>(x, y)[2])
								*(cos((((2 * i) + 1)) * ((x * 3.14159)) / (2 * 8)))
								*(cos((((2 * j) + 1)) * ((y * 3.14159)) / (2 * 8)))
								*(alphai*alphaj);
						}
					}
					temp *= ((2 / sqrt(8 * 8)));
					image_idct_dc.at<Vec3b>(i, j)[2] = int(temp);
				}
			}
		}
	}


	return image_idct_dc;
}

void showoutput(string windowname, Mat image) {
	namedWindow(windowname, CV_WINDOW_AUTOSIZE);
	imshow(windowname, image);
	waitKey();
	cvDestroyAllWindows();
}

int main()

{
	Mat image;
	image = imread("basel3.bmp", CV_LOAD_IMAGE_COLOR);
	if (image.empty())
		cerr << "Error: Loading image" << endl;

	Mat image_idct_dc(image.rows, image.cols, image.type());
	Mat image_idct_dc_9components(image.rows, image.cols, image.type());

	image_idct_dc = IDCT(image);
	showoutput("IDCT OF DC IMAGE", image_idct_dc);
	

	waitKey(0);
	return 0;
}
