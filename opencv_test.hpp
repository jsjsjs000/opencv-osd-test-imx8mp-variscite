#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

class OpenCVTest
{
public:
	bool initializeCamera(cv::VideoCapture& cap, const std::string& camera,
			const std::string& format, int width, int height, int framerate);
	void printInformation(cv::Mat& frame);
};
