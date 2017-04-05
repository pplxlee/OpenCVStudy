#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdio>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

const int MAX_CORNERS = 500;

int main() {
	const string sourceTestVideo = "G:/MyCenter/MyCode/OpenCVÑ§Ï°/TestVideo/VID_20170403_101811.mp4";
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
		captTestVideo >> frameTestVideo;
		captTestVideo >> frameTestVideo;
		if (frameTestVideo.empty()) {
			cout << "The video is over!" << endl;
			break;
		}
		frameTestVideoResize = Mat(frameTestVideo);
		resize(frameTestVideo, frameTestVideoResize, frameTestVideoResizeS);

		imgNow.copyTo(imgPrev);
		cvtColor(frameTestVideoResize, imgNow, COLOR_BGR2GRAY);

		vector<Point2f> prepoint, nextpoint;
		vector<uchar> state;
		vector<float>err;
		vector<Point2f> flowpoint(MAX_CORNERS);
		vector<float> pointdistance(MAX_CORNERS);
	//	Mat mReRgb;


		if (!imgPrev.empty())
		{
			//LK¹âÁ÷
			goodFeaturesToTrack(imgPrev, prepoint, 50, 0.01, 8, Mat(), 5, false, 0.04);
			//cvfindCornerSubPix(imgPrev, prepoint, MAX_CORNERS, )
			calcOpticalFlowPyrLK(imgPrev, imgNow, prepoint, nextpoint, state, err, Size(10, 10), 3);

			Point2f avepoint(0, 0);
			double avedistance = 0, addistance = 0;
			double thdistance;
			int cnt = 0;
			for (int i = 0; i<state.size(); i++)
			{
				if (state[i] != 0)
				{
					flowpoint[i].x = nextpoint[i].x - prepoint[i].x;
					flowpoint[i].y = nextpoint[i].y - prepoint[i].y;
				}
				avepoint.x += flowpoint[i].x;
				avepoint.y += flowpoint[i].y;
				cnt++;
			}
			avepoint.x /= cnt;
			avepoint.y /= cnt;

			for (int i = 0; i < state.size(); i++)
			{
				if (state[i] != 0)
				{
					pointdistance[i] = sqrt((flowpoint[i].x - avepoint.x)*(flowpoint[i].x - avepoint.x) + (flowpoint[i].y - avepoint.y)*(flowpoint[i].y - avepoint.y));
					avedistance += pointdistance[i];
				}
			}
			avedistance /= cnt;

			for (int i = 0; i < state.size(); i++)
			{
				if (state[i] != 0)
				{
					addistance += (avedistance - pointdistance[i])*(avedistance - pointdistance[i]);
				}
			}
			addistance /= cnt; addistance = sqrt(addistance);
			thdistance = 2 * addistance;

			cnt = 0;
			avepoint.x = 0;
			avepoint.y = 0;
			for (int i = 0; i<state.size(); i++)
			{
				if (state[i] != 0 && fabs(avedistance - pointdistance[i]) < thdistance)
				{
					cnt++;
					avepoint.x += flowpoint[i].x;
					avepoint.y += flowpoint[i].y;
					line(frameTestVideoResize, Point((int)prepoint[i].x, (int)prepoint[i].y), Point((int)nextpoint[i].x, (int)nextpoint[i].y), Scalar(0, 0, 255), 1, 8);
				}
			}
			avepoint.x /= cnt;
			avepoint.y /= cnt;


		//	resize(frameTestVideoResize, mRgb, mRgb.size());


		}

		imshow(WIN_TV, frameTestVideoResize);
		char c = (char)waitKey();
		if (c == 27) break;
	}


}