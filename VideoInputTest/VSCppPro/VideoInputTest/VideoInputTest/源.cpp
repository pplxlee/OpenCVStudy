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

int main()
{
	const string sourceTestVideo = "G:/MyCenter/MyCode/OpenCV学习/TestVideo/VID_20170403_101811.mp4";
	VideoCapture captTestVideo(sourceTestVideo);
	if (!captTestVideo.isOpened())
	{
		cout << "Could not open reference " << sourceTestVideo << endl;
		return -1;
	}
	cout << "Open reference" << sourceTestVideo << "successfully!" << endl;

	Size testVideoS = Size((int)captTestVideo.get(CAP_PROP_FRAME_WIDTH),
		(int)captTestVideo.get(CAP_PROP_FRAME_HEIGHT));

	const char* WIN_TV = "Under Test";
	// Windows
	namedWindow(WIN_TV, WINDOW_AUTOSIZE);
	moveWindow(WIN_TV, 400, 100);         //750,  2 (bernat =0)

	cout << "TestVideo frame resolution: Width=" << testVideoS.width << "  Height=" << testVideoS.height
		<< " of nr#: " << captTestVideo.get(CAP_PROP_FRAME_COUNT) << "  FPS=" << captTestVideo.get(CV_CAP_PROP_FPS) << endl;

	Size frameTestVideoResizeS = testVideoS / 2;
	Mat frameTestVideo;
	Mat frameTestVideoResize;
	for (;;) {
		captTestVideo >> frameTestVideo;
		if (frameTestVideo.empty()) {
			cout << "The video is over!" << endl;
			break;
		}
		frameTestVideoResize = Mat(frameTestVideo);
		resize(frameTestVideo, frameTestVideoResize, frameTestVideoResizeS);
		imshow(WIN_TV, frameTestVideoResize);
		char c = (char)waitKey();
		if (c == 27) break;
	}

	return 0;
}
