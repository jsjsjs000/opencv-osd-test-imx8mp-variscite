#include <iostream>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include "opencv_test.hpp"

bool OpenCVTest::initializeCamera(cv::VideoCapture& cap, const std::string& camera,
		const std::string& format, int width, int height, int framerate)
{
	cap.open(
			"v4l2src device=" + camera + " ! "
			"video/x-raw,format=" + format +
				",width=" + std::to_string(width) + ",height=" + std::to_string(height) +
			  ",framerate=" + std::to_string(framerate) + "/1 ! " +
			"appsink",
			// "videoconvert ! video/x-raw,format=" + format + " ! appsink",  // imxvideoconvert_g2d
			cv::CAP_GSTREAMER);
	if (!cap.isOpened())
	{
		std::cout << "Open camera error\n";
		return false;
	}

	// cap.set(cv::CAP_PROP_FRAME_WIDTH, WIDTH);
	// cap.set(cv::CAP_PROP_FRAME_HEIGHT, HEIGHT);
	// cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('N','V','1','2')); // warning
	// cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('Y','U','Y','2')); // warning

	return true;
}

void OpenCVTest::printInformation(cv::Mat& frame)
{
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
	// #pragma message("Precompiler: ARM NEON exists")
#endif

	printf("\n");
	printf("%dx%d, type=%d bits, channels=%d, step=%ld (bytes per line)\n", frame.cols, frame.rows,
			frame.type(), frame.channels(), frame.step1());
	printf("CV_CPU_FP16=%d\n", cv::checkHardwareSupport(CV_CPU_FP16));
	printf("CV_CPU_NEON=%d\n", cv::checkHardwareSupport(CV_CPU_NEON));
	printf("CPU Features: %s\n", cv::getCPUFeaturesLine().c_str());
	printf("\n");
}
