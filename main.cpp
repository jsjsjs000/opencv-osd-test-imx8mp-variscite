#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/video/tracking.hpp>
#include "opencv_test.hpp"

#define CAMERA     "/dev/video2"
#define WIDTH      1280
#define HEIGHT     720
#define FORMAT     "YUY2"
#define FRAMERATE  50

// #define FACE_DETECT

int main(int argc, char *argv[])
{
	cv::VideoCapture cap;
	OpenCVTest *openCV = new OpenCVTest();
	if (!openCV->initializeCamera(cap, CAMERA, FORMAT, WIDTH, HEIGHT, FRAMERATE))
		return 1;
	
#ifdef FACE_DETECT
	cv::CascadeClassifier face_cascade;
	if (!face_cascade.load("haarcascade_frontalface_default.xml"))
	{
		std::cerr << "Nie można załadować klasyfikatora twarzy\n";
		return -1;
	}
#endif

	cv::Mat frame;
	cap >> frame;

	openCV->printInformation(frame);

	std::string pipeline =
			"appsrc is-live=true do-timestamp=true format=time ! "
			"video/x-raw,format=BGR,width=" + std::to_string(frame.cols) +
					",height=" + std::to_string(frame.rows) + " ! " +
			"videoconvert ! " +
			// "waylandsink sync=false window-width=" +
			// 		std::to_string(frame.cols) + " window-height=" + std::to_string(frame.rows);
			"fpsdisplaysink sync=false video-sink=\"waylandsink sync=false window-width=" +
					std::to_string(frame.cols) + " window-height=" + std::to_string(frame.rows) + "\"";

	cv::VideoWriter out(pipeline, cv::CAP_GSTREAMER, 0, FRAMERATE, frame.size(), true);

	if (!out.isOpened())
	{
		std::cout << "gstreamer error\n";
		return -1;
	}

	struct timespec last_ts;
	while (true)
	{
		// struct tm *tm_info = localtime(&ts.tv_sec);

		struct timespec ts;
		clock_gettime(CLOCK_REALTIME, &ts);
		int us = ts.tv_nsec / 1000;
		int diff_us = (ts.tv_nsec - last_ts.tv_nsec) / 1000;
		if (diff_us < 0)
			diff_us += 1000000;
		memcpy(&last_ts, &ts, sizeof(ts));

		printf("%2ld.%03d s (+%2d ms)\n", ts.tv_sec % 60, us / 1000, diff_us / 1000);

		cap >> frame;
		if (frame.empty())
			break;

#ifdef FACE_DETECT
		cv::Mat gray, edges;
			/* konwersja do grayscale */
		// cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
		cv::cvtColor(frame, gray, cv::COLOR_YUV2GRAY_YUY2);

			/* wykrywanie krawędzi */
		cv::Canny(gray, edges, 80, 150);

			/* wykrywanie twarzy */
		std::vector<cv::Rect> faces;
		face_cascade.detectMultiScale(gray, faces);

		for (const auto &f : faces)
			cv::rectangle(frame, f, cv::Scalar(0,255,0), 2);
#endif

		cv::Mat bgr;
		cv::cvtColor(frame, bgr, cv::COLOR_YUV2BGR_YUY2);
		out.write(bgr);

		if (cv::waitKey(1) == 27) // ESC
			break;
	}

	return 0;
}
