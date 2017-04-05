#include <opencv2/features2d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
using namespace std;
using namespace cv;
const float inlier_threshold = 2.5f; // Distance threshold to identify inliers
const float nn_match_ratio = 0.8f;   // Nearest neighbor matching ratio
int main(void)
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
	Mat imgPrev, imgNow;
	for (;;) {
		captTestVideo >> frameTestVideo;
		if (frameTestVideo.empty()) {
			cout << "The video is over!" << endl;
			break;
		}
		frameTestVideoResize = Mat(frameTestVideo);
		resize(frameTestVideo, frameTestVideoResize, frameTestVideoResizeS);

		imgPrev.copyTo(imgNow);
		cvtColor(frameTestVideoResize, imgNow, COLOR_BGR2GRAY);
		if (!imgPrev.empty()) 
		{
			//首先对两幅图像进行特征点的检测  
			//先准备参数  
			vector<KeyPoint> keyPoint1;
			vector<KeyPoint> keyPoint2;
			SURF surf;
			surf.detect(srcImage1, keyPoint1);
			surf.detect(srcImage2, keyPoint2);

		}

		imshow(WIN_TV, frameTestVideoResize);
		char c = (char)waitKey();
		if (c == 27) break;
	}





}