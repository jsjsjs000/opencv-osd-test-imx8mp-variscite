#include <stdio.h>
#include <string.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "draw_osd.hpp"

void DrawOsd::set_pixel(cv::Mat& bgr, int x, int y, const cv::Vec3b& colorBGR)
{
	bgr.at<cv::Vec3b>(y, x) = colorBGR;
}

void DrawOsd::draw_line(const cv::Mat& bgr, const cv::Point& p1, const cv::Point& p2,
		const cv::Scalar colorBGR, int thickness)
{
	cv::line(bgr, p1, p2, colorBGR, thickness);
}

void DrawOsd::draw_rectangle(const cv::Mat& bgr, const cv::Point& p, const cv::Point& size,
		const cv::Scalar colorBGR, int corner, int thickness)
{
	if (corner == 0)  /* normal rectangle */
	{
		draw_line(bgr, cv::Point(p.x, p.y), cv::Point(p.x + size.x, p.y),
				colorBGR, thickness);
		draw_line(bgr, cv::Point(p.x, p.y), cv::Point(p.x, p.y + size.y),
				colorBGR, thickness);
		draw_line(bgr, cv::Point(p.x + size.x, p.y), cv::Point(p.x + size.x, p.y + size.y),
				colorBGR, thickness);
		draw_line(bgr, cv::Point(p.x, p.y + size.y), cv::Point(p.x + size.x, p.y + size.y),
				colorBGR, thickness);
	}
	else  /* rectangle with corners only */
	{
		draw_line(bgr, cv::Point(p.x, p.y), cv::Point(p.x + corner, p.y),
				colorBGR, thickness);
		draw_line(bgr, cv::Point(p.x, p.y), cv::Point(p.x, p.y + corner),
				colorBGR, thickness);

		draw_line(bgr, cv::Point(p.x + size.x, p.y), cv::Point(p.x + size.x - corner, p.y),
				colorBGR, thickness);
		draw_line(bgr, cv::Point(p.x + size.x, p.y), cv::Point(p.x + size.x, p.y + corner),
				colorBGR, thickness);

		draw_line(bgr, cv::Point(p.x, p.y + size.y), cv::Point(p.x, p.y + size.y - corner),
				colorBGR, thickness);
		draw_line(bgr, cv::Point(p.x, p.y + size.y), cv::Point(p.x + corner, p.y + size.y),
				colorBGR, thickness);

		draw_line(bgr, cv::Point(p.x + size.x, p.y + size.y), cv::Point(p.x + size.x - corner, p.y + size.y),
				colorBGR, thickness);
		draw_line(bgr, cv::Point(p.x + size.x, p.y + size.y), cv::Point(p.x + size.x, p.y + size.y - corner),
				colorBGR, thickness);
	}
}

void DrawOsd::draw_cross(const cv::Mat& bgr, const cv::Point& p, const cv::Point& size,
		const cv::Scalar colorBGR, int skipCenter, int thickness)
{
	if (skipCenter == 0)  /* normal cross */
	{
		draw_line(bgr, cv::Point(p.x - size.x, p.y), cv::Point(p.x + size.x, p.y),
				colorBGR, thickness);
		draw_line(bgr, cv::Point(p.x, p.y - size.y), cv::Point(p.x, p.y + size.y),
				colorBGR, thickness);
	}
	else  /* cross with empty center */
	{
		draw_line(bgr, cv::Point(p.x - size.x, p.y), cv::Point(p.x - skipCenter, p.y),
				colorBGR, thickness);
		draw_line(bgr, cv::Point(p.x + skipCenter, p.y), cv::Point(p.x + size.x, p.y),
				colorBGR, thickness);

		draw_line(bgr, cv::Point(p.x, p.y - size.y), cv::Point(p.x, p.y - skipCenter),
				colorBGR, thickness);
		draw_line(bgr, cv::Point(p.x, p.y + skipCenter), cv::Point(p.x, p.y + size.y),
				colorBGR, thickness);
	}
}

void DrawOsd::draw_text(const cv::Mat& bgr, const cv::Point& p, const std::string text,
		double fontScale, const cv::Scalar colorBGR, bool drawFrame)
{
	if (drawFrame)
		cv::putText(bgr, text, p, cv::FONT_HERSHEY_SIMPLEX, fontScale, cv::Scalar(0, 0, 0), 2);
	cv::putText(bgr, text, p, cv::FONT_HERSHEY_SIMPLEX, fontScale, colorBGR, 1);
}
