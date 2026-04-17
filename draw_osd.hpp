#pragma once

#include <string.h>
#include <opencv2/core.hpp>

class DrawOsd
{
public:
  static void set_pixel(cv::Mat& bgr, int x, int y, const cv::Vec3b& colorBGR);
  static void draw_line(const cv::Mat& bgr, const cv::Point& p1, const cv::Point& p2,
      const cv::Scalar colorBGR, int thickness = 1);
  static void draw_rectangle(const cv::Mat& bgr, const cv::Point& p, const cv::Point& size,
      const cv::Scalar colorBGR, int corner = 0, int thickness = 1);
  static void draw_cross(const cv::Mat& bgr, const cv::Point& p, const cv::Point& size,
      const cv::Scalar colorBGR, int skipCenter = 0, int thickness = 1);
  static void draw_text(const cv::Mat& bgr, const cv::Point& p, const std::string text,
      double fontScale, const cv::Scalar colorBGR, bool drawFrame = false);
};
