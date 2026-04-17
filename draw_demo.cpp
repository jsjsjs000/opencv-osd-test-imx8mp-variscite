#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#include "draw.h"
#include "draw_demo.hpp"

void DrawDemo::drawDemo(cv::Mat& bgr, uint64_t frameNo)
{
		/* draw points array 10x10 */
	for (uint x = 0; x < 10; x++)
		for (uint y = 0; y < 10; y++)
			set_pixel(bgr, 384 + x * 5, 150 + y * 5, cv::Vec3b(0x00, 0xff, 0x00));

		/* draw line 1 */
	draw_line(bgr, cv::Point(40, 100), cv::Point(40 + 40, 100 + 20), cv::Scalar(0xff, 0x00, 0x00));

		/* draw line 2 */
	draw_line(bgr, cv::Point(40, 120), cv::Point(40 + 20, 120 + 40), cv::Scalar(0x00, 0x00, 0xff));

		/* draw line 3 */
	draw_line(bgr, cv::Point(60, 200), cv::Point(60 - 20, 200 + 40), cv::Scalar(0x00, 0x00, 0xff));

		/* draw line 4 */
	draw_line(bgr, cv::Point(80, 180), cv::Point(80 + 20, 180 - 40), cv::Scalar(0x00, 0xff, 0x00));

		/* draw line 4 */
	draw_line(bgr, cv::Point(80, 160), cv::Point(80 - 40, 160 - 20), cv::Scalar(0x00, 0xff, 0x00), 2);

		/* draw rectangle 1 */
	draw_rectangle(bgr, cv::Point(160, 100), cv::Point(100, 50), cv::Scalar(0x00, 0x00, 0xff));

		/* draw rectangle 2 */
	draw_rectangle(bgr, cv::Point(180, 160), cv::Point(60, 80), cv::Scalar(0xff, 0x00, 0x00), 20);

		/* draw cross 1 */
	draw_cross(bgr, cv::Point(350, 100), cv::Point(50, 30), cv::Scalar(0xff, 0xff, 0xff));

		/* draw cross 2 */
	draw_cross(bgr, cv::Point(330, 175), cv::Point(30, 50), cv::Scalar(0xff, 0xff, 0xff), 7);

		/* draw text 1 */
	char s[128];
	sprintf(s, "Frame number: %lu", frameNo);
	draw_text(bgr, cv::Point(10, 20), s, 0.7, cv::Scalar(0xff, 0xff, 0xff), true);

		/* draw text 2 */
	sprintf(s, "DrawDemo::drawDemo()");
	draw_text(bgr, cv::Point(10, 50), s, 0.9, cv::Scalar(0x00, 0x00, 0xff), true);
}
