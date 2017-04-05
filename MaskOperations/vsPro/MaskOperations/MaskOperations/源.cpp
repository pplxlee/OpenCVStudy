// file:///G:/%E7%A7%91%E7%A0%94/%E5%BC%80%E5%8F%91%E6%96%87%E6%A1%A3/OpenCV/3.2.0/3.2.0/d7/d37/tutorial_mat_mask_operations.html
#include <iostream> // for standard I/O
#include <string>   // for strings
#include <iomanip>  // for controlling float print precision
#include <sstream>  // string to number conversion
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

#define TEST_MAT UMat
//#define TEST_MAT Mat

int main()
{
	const string imageName = "G:/MyCenter/MyCode/OpenCV学习/TestImage/magazineResize/420.jpg";
	Mat image;
	image = imread(imageName, 1);

	if (image.empty())                      // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	Mat image_kernel;
	image.copyTo(image_kernel);
	Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0,
		-1, 5, -1,
		0, -1, 0);

	/* 
	 This is a code block for handling mask operation with using UMat.
	 Before using getUMat to handl, you should set the Mat to right size and channal.
	 Note that UMat can locked with Mat, and vice versa.
	*/
	{
		UMat imageUM = image.getUMat(ACCESS_READ);
		UMat image_kernelUM = image_kernel.getUMat(ACCESS_WRITE);
		UMat kernelUM = kernel.getUMat(ACCESS_MASK);
		filter2D(imageUM, image_kernelUM, imageUM.depth(), kernelUM);
	}

	imwrite("G:/MyCenter/MyCode/OpenCV学习/TestImage/magazineResize/420_kernel.jpg", image_kernel);

	Mat image_gray;
	cvtColor(image, image_gray, COLOR_BGR2GRAY);
	imwrite("G:/MyCenter/MyCode/OpenCV学习/TestImage/magazineResize/420_gray.jpg", image_gray);
	
	namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Display window", image);                // Show our image inside it.
	waitKey(0); // Wait for a keystroke in the window
	imshow("Display window", image_kernel);                // Show our image inside it.
	waitKey(0); // Wait for a keystroke in the window
	imshow("Display window", image_gray);                // Show our image inside it.
	waitKey(0); // Wait for a keystroke in the window
	return 0;
}