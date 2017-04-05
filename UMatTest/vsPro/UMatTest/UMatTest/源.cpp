#include <iostream> // for standard I/O
#include <string>   // for strings
#include <iomanip>  // for controlling float print precision
#include <sstream>  // string to number conversion
#include <opencv2/core.hpp>     // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/imgproc.hpp>  // Gaussian Blur
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>  // OpenCV window I/O

using namespace std;
using namespace cv;

#define TEST_MAT UMat
//#define TEST_MAT Mat

int main()
{
	const string sourceTestVideo = "G:/MyCenter/MyCode/OpenCVѧϰ/TestVideo/VID_20170403_101811.mp4";
	VideoCapture captTestVideo(sourceTestVideo);
	if (!captTestVideo.isOpened())
	{
		cout << "Could not open reference " << sourceTestVideo << endl;
		return -1;
	}
	cout << "Open reference" << sourceTestVideo << "successfully!" << endl;

	Size testVideoS = Size((int)captTestVideo.get(CAP_PROP_FRAME_WIDTH),
		(int)captTestVideo.get(CAP_PROP_FRAME_HEIGHT));

	//const char* WIN_TV = "Under Test";
	//// Windows
	//namedWindow(WIN_TV, WINDOW_AUTOSIZE);
	//moveWindow(WIN_TV, 400, 100);         //750,  2 (bernat =0)

	cout << "TestVideo frame resolution: Width=" << testVideoS.width << "  Height=" << testVideoS.height
		<< " of nr#: " << captTestVideo.get(CAP_PROP_FRAME_COUNT) << "  FPS=" << captTestVideo.get(CV_CAP_PROP_FPS) << endl;

	Size frameTestVideoResizeS = testVideoS / 2;
	TEST_MAT frameTestVideo;
	TEST_MAT frameTestVideoResize;
	TEST_MAT frameP = TEST_MAT();
	TEST_MAT frameShow;

	TEST_MAT gray,grad;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;

	for (;;) {
		frameP = TEST_MAT(frameTestVideoResize);
		captTestVideo >> frameTestVideo;
		if (frameTestVideo.empty()) {
			cout << "The video is over!" << endl;
			break;
		}
		frameTestVideoResize = TEST_MAT(frameTestVideo);
		resize(frameTestVideo, frameTestVideoResize, frameTestVideoResizeS);

		if (frameP.empty()) {
			frameTestVideoResize.copyTo(frameP);
		}
		else {
			subtract(frameTestVideoResize, frameP, frameP);
		}
		if (frameShow.empty()) {
			frameP.copyTo(frameShow);
		}
		else {
			add(frameShow, frameP, frameShow);
		}
		frameTestVideoResize.copyTo(frameP);

		GaussianBlur(frameTestVideoResize, frameTestVideoResize, Size(3, 3), 0, 0, BORDER_DEFAULT);
		cvtColor(frameTestVideoResize, gray, COLOR_BGR2GRAY);
		TEST_MAT grad_x, grad_y;
		TEST_MAT abs_grad_x, abs_grad_y;
		Sobel(gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
		Sobel(gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
		convertScaleAbs(grad_x, abs_grad_x);
		convertScaleAbs(grad_y, abs_grad_y);
		addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
	}
	const char* WIN_TV = "Under Test";
	// Windows
	namedWindow(WIN_TV, WINDOW_AUTOSIZE);
	moveWindow(WIN_TV, 400, 100);         //750,  2 (bernat =0)
	imshow(WIN_TV, frameShow);
	char c = (char)waitKey();
	return 0;
}
