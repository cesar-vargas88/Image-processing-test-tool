// Image Processing Test tool.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <opencv2\core\core.hpp>
#include "opencv2\highgui.hpp"
#include "opencv2\imgproc.hpp"

using namespace cv;
using namespace std;

vector<String> getFileNames(string sourcePath);
Mat cropImage(Mat img_source, int imageWidht, int imageHeight);
Mat getBGR(Mat source);
Mat getGray(Mat source);
Mat getBlur(Mat source, int kernelSize, int borderType);
Mat getHSV_Channel(Mat source, int channel);
Mat getRGB_Channel(Mat source, int channel);
Mat getHistogram(Mat source, int size, cv::Scalar color);
pair<int, int> getHistogramMin(Mat source, int size);
Mat getHistogramThreshold(Mat source, int size);
Mat getEqualizeHist(Mat source);
Mat getHistogramSmoothing(Mat source, int size, cv::Scalar color, int windowSize, int smoothingRepeat);

int main()
{
	int imageWidht = 320;
	int imageHeight = 320;
	string sourcePath = "C:/Imagenes/Originales/";
	Mat window(Size(imageWidht * 9, imageHeight * 4), CV_8UC3);

	vector<String> fileNames = getFileNames(sourcePath);

	Mat img_source	= imread(fileNames.back());
	Mat img_cropped = cropImage(img_source, imageWidht, imageWidht);

	//////////////////
	//	Pipeline	//
	//////////////////

	// Row 0
	img_cropped.copyTo(															window(Rect(imageWidht * 0, imageHeight * 0, imageWidht, imageHeight)));
	getBGR(getGray(img_cropped)).copyTo(										window(Rect(imageWidht * 1, imageHeight * 0, imageWidht, imageHeight)));
	getHistogram(getGray(img_cropped), 256, Scalar(0, 255, 255)).copyTo(		window(Rect(imageWidht * 2, imageHeight * 0, imageWidht, imageHeight)));
	getBGR(getHSV_Channel(img_cropped, 0)).copyTo(								window(Rect(imageWidht * 3, imageHeight * 0, imageWidht, imageHeight)));
	getHistogram(getHSV_Channel(img_cropped, 0), 180, Scalar(255, 0, 0)).copyTo(window(Rect(imageWidht * 4, imageHeight * 0, imageWidht, imageHeight)));
	getBGR(getHSV_Channel(img_cropped, 1)).copyTo(								window(Rect(imageWidht * 5, imageHeight * 0, imageWidht, imageHeight)));
	getHistogram(getHSV_Channel(img_cropped, 1), 180, Scalar(0, 255, 0)).copyTo(window(Rect(imageWidht * 6, imageHeight * 0, imageWidht, imageHeight)));
	getBGR(getHSV_Channel(img_cropped, 2)).copyTo(								window(Rect(imageWidht * 7, imageHeight * 0, imageWidht, imageHeight)));
	getHistogram(getHSV_Channel(img_cropped, 2), 180, Scalar(0, 0, 255)).copyTo(window(Rect(imageWidht * 8, imageHeight * 0, imageWidht, imageHeight)));

	// Row 1
	img_cropped.copyTo(															window(Rect(imageWidht * 0, imageHeight * 1, imageWidht, imageHeight)));
	getBGR(getGray(img_cropped)).copyTo(										window(Rect(imageWidht * 1, imageHeight * 1, imageWidht, imageHeight)));
	getHistogram(getGray(img_cropped), 256, Scalar(0, 255, 255)).copyTo(		window(Rect(imageWidht * 2, imageHeight * 1, imageWidht, imageHeight)));
	getBGR(getRGB_Channel(img_cropped, 0)).copyTo(								window(Rect(imageWidht * 3, imageHeight * 1, imageWidht, imageHeight)));
	getHistogram(getRGB_Channel(img_cropped, 0), 180, Scalar(255, 0, 0)).copyTo(window(Rect(imageWidht * 4, imageHeight * 1, imageWidht, imageHeight)));
	getBGR(getRGB_Channel(img_cropped, 1)).copyTo(								window(Rect(imageWidht * 5, imageHeight * 1, imageWidht, imageHeight)));
	getHistogram(getRGB_Channel(img_cropped, 1), 180, Scalar(0, 255, 0)).copyTo(window(Rect(imageWidht * 6, imageHeight * 1, imageWidht, imageHeight)));
	getBGR(getRGB_Channel(img_cropped, 2)).copyTo(								window(Rect(imageWidht * 7, imageHeight * 1, imageWidht, imageHeight)));
	getHistogram(getRGB_Channel(img_cropped, 2), 180, Scalar(0, 0, 255)).copyTo(window(Rect(imageWidht * 8, imageHeight * 1, imageWidht, imageHeight)));

	Mat img_blur = getBlur(img_cropped, 1, 0);
	
	// Row 2
	img_blur.copyTo(																	window(Rect(imageWidht * 0, imageHeight * 2, imageWidht, imageHeight)));
	getBGR(getGray(img_blur)).copyTo(													window(Rect(imageWidht * 1, imageHeight * 2, imageWidht, imageHeight)));
	getHistogram(getGray(img_blur), 256, Scalar(0, 255, 255)).copyTo(					window(Rect(imageWidht * 2, imageHeight * 2, imageWidht, imageHeight)));
	getHistogramSmoothing(getGray(img_blur), 256, Scalar(0, 255, 255), 11, 0).copyTo(	window(Rect(imageWidht * 3, imageHeight * 2, imageWidht, imageHeight)));
	getHistogramSmoothing(getGray(img_blur), 256, Scalar(0, 255, 255), 11, 2).copyTo(	window(Rect(imageWidht * 4, imageHeight * 2, imageWidht, imageHeight)));
	getHistogramSmoothing(getGray(img_blur), 256, Scalar(0, 255, 255), 11, 4).copyTo(	window(Rect(imageWidht * 5, imageHeight * 2, imageWidht, imageHeight)));
	getHistogramSmoothing(getGray(img_blur), 256, Scalar(0, 255, 255), 11, 6).copyTo(	window(Rect(imageWidht * 6, imageHeight * 2, imageWidht, imageHeight)));
	getHistogramSmoothing(getGray(img_blur), 256, Scalar(0, 255, 255), 11, 8).copyTo(	window(Rect(imageWidht * 7, imageHeight * 2, imageWidht, imageHeight)));
	getHistogramSmoothing(getGray(img_blur), 256, Scalar(0, 255, 255), 11, 10).copyTo(	window(Rect(imageWidht * 8, imageHeight * 2, imageWidht, imageHeight)));

	// Row 3
	//getBGR(getEqualizeHist(getGray(img_cropped))).copyTo(						window(Rect(imageWidht * 1, imageHeight * 3, imageWidht, imageHeight)));
	//getHistogram(getEqualizeHist(getGray(img_cropped)), 256, Scalar(255, 255, 255)).copyTo(window(Rect(imageWidht * 2, imageHeight * 3, imageWidht, imageHeight)));

	//getHistogram(getHSV_Channel(img_cropped, 0), 180, Scalar(255, 0, 0)).copyTo(window(Rect(imageWidht * 2, imageHeight * 0, imageWidht, imageHeight)));
	//getHistogram(getHSV_Channel(img_cropped, 1), 180, Scalar(0, 255, 0)).copyTo(window(Rect(imageWidht * 4, imageHeight * 0, imageWidht, imageHeight)));
	//getHistogram(getHSV_Channel(img_cropped, 2), 180, Scalar(0, 0, 255)).copyTo(window(Rect(imageWidht * 6, imageHeight * 0, imageWidht, imageHeight)));

	//getBGR(getHSV_Channel(img_cropped, 2)).copyTo(window(Rect(imageWidht * 5, 0, imageWidht, imageHeight)));

	// Row 1
	/*getBGR(getGray(img_cropped)).copyTo(window(Rect(imageWidht * 0, imageHeight * 1, imageWidht, imageHeight)));
	getBGR(getHistogramThreshold(getHSV_Channel(img_cropped, 0), 180)).copyTo(window(Rect(imageWidht * 1, imageHeight * 1, imageWidht, imageHeight)));
	getBGR(getHistogramThreshold(getHSV_Channel(img_cropped, 1), 180)).copyTo(window(Rect(imageWidht * 3, imageHeight * 1, imageWidht, imageHeight)));
	getBGR(getHistogramThreshold(getHSV_Channel(img_cropped, 2), 180)).copyTo(window(Rect(imageWidht * 5, imageHeight * 1, imageWidht, imageHeight)));
	
	// Row 2
	getBGR(getEqualizeHist(getHSV_Channel(img_cropped, 0))).copyTo(window(Rect(imageWidht * 1, imageHeight * 2, imageWidht, imageHeight)));
	getHistogram(getEqualizeHist(getHSV_Channel(img_cropped, 0)), 180, Scalar(255, 0, 0)).copyTo(window(Rect(imageWidht * 2, imageHeight * 2, imageWidht, imageHeight)));
	getBGR(getEqualizeHist(getHSV_Channel(img_cropped, 1))).copyTo(window(Rect(imageWidht * 3, imageHeight * 2, imageWidht, imageHeight)));
	getBGR(getEqualizeHist(getHSV_Channel(img_cropped, 2))).copyTo(window(Rect(imageWidht * 5, imageHeight * 2, imageWidht, imageHeight)));
	*/
	namedWindow("Pipeline", WINDOW_NORMAL);
	imshow("Pipeline", window);

	waitKey(0);
	return 0;
}

vector<String> getFileNames(string sourcePath)
{
	vector<String> fileNames;
	glob(sourcePath, fileNames);

	return fileNames;
}
Mat cropImage(Mat img_source, int imageWidht, int imageHeight)
{
	Mat img_cropped;

	// Crop image
	if (img_source.cols > img_source.rows)
	{
		Rect myROI((img_source.cols - img_source.rows) / 2, 0, img_source.rows, img_source.rows);
		img_cropped = img_source(myROI);
	}
	else if (img_source.cols < img_source.rows)
	{
		Rect myROI(0, (img_source.rows - img_source.cols) / 2, img_source.cols, img_source.cols);
		img_cropped = img_source(myROI);
	}
	else
		img_cropped = img_source.clone();

	resize(img_cropped, img_cropped, Size(imageWidht, imageHeight));

	return img_cropped;
}
Mat getBGR(Mat source)
{
	Mat BGR;

	cvtColor(source, BGR, COLOR_GRAY2BGR);

	return BGR;
}
Mat getGray(Mat source)
{
	Mat Gray;

	cvtColor(source, Gray, COLOR_BGR2GRAY);

	return Gray;
}
Mat getBlur(Mat source, int kernelSize, int borderType)
{
	Mat blur;

	GaussianBlur(source, blur, Size(kernelSize, kernelSize), borderType);

	return blur;
}
Mat getHSV_Channel(Mat source, int channel)
{
	Mat HSV;
	vector <Mat> HSV_planes;

	cvtColor(source, HSV, COLOR_BGR2HSV);
	split(HSV, HSV_planes);

	return HSV_planes[channel];
}
Mat getRGB_Channel(Mat source, int channel)
{
	Mat RGB;
	vector <Mat> RGB_planes;

	cvtColor(source, RGB, COLOR_BGR2RGB);
	split(RGB, RGB_planes);

	return RGB_planes[channel];
}
Mat getHistogram(Mat source, int size, cv::Scalar color)
{
	float range[] = { 0, size };
	const float* histRange = { range };
	bool uniform = true; 
	bool accumulate = false;

	Mat h_hist;

	calcHist(&source, 1, 0, Mat(), h_hist, 1, &size, &histRange, uniform, accumulate);

	int hist_w = source.cols;
	int hist_h = source.rows;
	int bin_w = cvRound((double)hist_w / size);

	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

	/// Normalize the result to [ 0, histImage.rows ]
	normalize(h_hist, h_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	/// Draw for each channel
	for (int i = 1; i < size; i++)
	{
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(h_hist.at<float>(i - 1))), Point(bin_w*(i), hist_h - cvRound(h_hist.at<float>(i))), color, 2, 8, 0);
		//cout << i << " - " << h_hist.at<float>(i - 1) << endl;
	}
		
	return histImage;
}
pair<int, int> getHistogramMin(Mat source, int size)
{
	float range[] = { 0, size };
	const float* histRange = { range };
	bool uniform = true;
	bool accumulate = false;

	Mat h_hist;

	calcHist(&source, 1, 0, Mat(), h_hist, 1, &size, &histRange, uniform, accumulate);

	int hist_w = source.cols;
	int hist_h = source.rows;
	int bin_w = cvRound((double)hist_w / size);

	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

	/// Normalize the result to [ 0, histImage.rows ]
	normalize(h_hist, h_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	
	int Max = 0;
	float MaxValue = 0;

	pair <int, int> Mins;

	for (int index = 1; index < h_hist.rows; index++)
	{
		if (h_hist.at<float>(index - 1) >= (float)hist_h)
		{
			Max = index;
			break;
		}	
	}

	float lastValue = (float)hist_h;

	// Get the first min
	for (int index = Max - 1; index < h_hist.rows; index--)
	{
		if (h_hist.at<float>(index - 1) > (float)lastValue)
		{
			Mins.first = index;
			break;
		}
		else
			lastValue = h_hist.at<float>(index - 1);
	}

	lastValue = (float)hist_h;

	// Get the second min
	for (int index = Max + 1; index < h_hist.rows; index++)
	{
		if (h_hist.at<float>(index - 1) > (float)lastValue)
		{
			Mins.second = index;
			break;
		}
		else
			lastValue = h_hist.at<float>(index - 1);
	}

	cout << endl << " Min - " << Mins.first << endl;
	cout << " MAX - " << Max << endl;
	cout << " Min - " << Mins.second << endl << endl;

	// Get the second min
	for (int index = Mins.first; index <= Mins.second; index++)
		cout << index << " - " << h_hist.at<float>(index - 1) << endl;

	return Mins;
}
Mat getHistogramThreshold(Mat source, int size)
{
	Mat threshold;

	pair<int, int> Mins = getHistogramMin(source, size);
	inRange(source, Mins.first + 1, Mins.second - 1, threshold);

	//bitwise_and(mask, source, interestRegion);

	return threshold;
}
Mat getEqualizeHist(Mat source)
{
	Mat equalized;

	equalizeHist(source, equalized);

	return equalized;
}
Mat getHistogramSmoothing(Mat source, int size, cv::Scalar color, int windowSize, int smoothingRepeat)
{
	float range[] = { 0, size };
	const float* histRange = { range };
	bool uniform = true;
	bool accumulate = false;

	Mat h_hist;

	calcHist(&source, 1, 0, Mat(), h_hist, 1, &size, &histRange, uniform, accumulate);

	//int hist_w = source.cols;
	//int hist_h = source.rows;
	//int bin_w = cvRound((double)hist_w / size);

	//Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

	/// Normalize the result to [ 0, histImage.rows ]
	//normalize(h_hist, h_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	Mat h_histSmooth = h_hist.clone();
	float Mean;
	float CurrentPoint;

	while (smoothingRepeat + 1)
	{
		for (int i = 0; i < size; i++)
		{
			Mean = 0;

			for (int v = -(windowSize / 2) ; v <= (windowSize / 2); v++)
			{
				if ((i + v) < 0 || (i + v) > size - 1)
				{
					CurrentPoint = h_hist.at<float>(i);
					Mean += h_hist.at<float>(i);
				}	
				else
				{
					CurrentPoint = h_hist.at<float>(i + v);
					Mean += h_hist.at<float>(i + v);
				}				
			}

			if (Mean == 0)
				h_histSmooth.at<float>(i) = (float) 0;
			else
				h_histSmooth.at<float>(i) = (float) Mean / windowSize;
		}
		for (int i = 1; i < size; i++)
			h_hist.at<float>(i) = h_histSmooth.at<float>(i);

		smoothingRepeat--;
	}

	int hist_w = source.cols;
	int hist_h = source.rows;
	int bin_w = cvRound((double)hist_w / size);

	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

	/// Normalize the result to [ 0, histImage.rows ]
	normalize(h_hist, h_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	/// Draw for each channel
	for (int i = 1; i < size; i++)
	{
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(h_hist.at<float>(i - 1))), Point(bin_w*(i), hist_h - cvRound(h_hist.at<float>(i))), color, 2, 8, 0);
		//cout << i << " - " << h_hist.at<float>(i - 1) << endl;
	}

	return histImage;
}