#include "Header.h"

int main(int argc, char* argv[])
{
	char* filename = argc == 2 ? argv[1] : "test.avi";
	VideoCapture capture(filename); 
	
	if (!capture.isOpened()) 
		return -1;

	namedWindow("Video", CV_WINDOW_AUTOSIZE);
	//namedWindow("Hist", CV_WINDOW_AUTOSIZE);

	vector<int> vec;
	int number = 0;
	int width = capture.get(CV_CAP_PROP_FRAME_WIDTH);
	int height = capture.get(CV_CAP_PROP_FRAME_HEIGHT);
	int wait = 1000 / capture.get(CV_CAP_PROP_FPS);
	int temp = width * PERCENT_EDGE;
	long int amount_pixels = (width * height) - (2 * temp * height);
	cv::Mat mask(height, width, CV_8U, 0.0); // создание маски, для подсчета гистограммы без учёта краёв
	rectangle(mask, cv::Point(temp,0), cv::Point(width - temp, height), 1, CV_FILLED);

	// Параметры гистограммы
	int histSize = 256;
	float range[] = { 0, 256 };
	const float* histRange = { range };
	bool uniform = true; 
	bool accumulate = false;
	int hist_w = 512; 
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);

	while (capture.isOpened())
	{
		Mat src;
		if (!capture.read(src)) break;
		imshow("Video", src);

		// Будем считать гистогрмму только для канала R
		std::vector<Mat> bgr_planes;
		split(src, bgr_planes);

		Mat r_hist;

		calcHist(&bgr_planes[2], 1, 0, mask, r_hist, 1, &histSize, &histRange, uniform, accumulate);

		Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

		HistEvidenceAnaliz(&r_hist,  histSize, amount_pixels, &vec, number);

		// Normalize the result to [ 0, histImage.rows ]
		//normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

		// Draw Hist
		/*for (int i = 1; i < histSize; i++)
		{
			line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
				Point(bin_w*(i), hist_h - cvRound(r_hist.at<float>(i))),
				Scalar(0, 0, 255), 2, 8, 0);
		}*/

		//imshow("Hist", histImage);

		if (waitKey(wait) >= 0) break;
	}

	vector<pair<int, int>> linking_frames;
	int counter = 0;
	int start = 0;

	for (vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
	{ // рассчёт мест сшивки, чтобы избежать попадания случайных кадров
		if ((it + 1) != vec.end())
		{
			if (*(it + 1) - *it <= THRESHOLD_GAP_FRAME)
			{
				if (counter == 0) start = *it;
				counter++;
			}
			else
			{
				if (counter < THRESHOLD_FRAME_SEQUENCE) counter = 0;
				else
				{
					if ((*it) - start > MIN_LENGTH_SEQUENCE_FRAME) linking_frames.push_back(pair<int, int>(start, *it));
					counter = 0;
				}
			}
		}
		else if (counter >= THRESHOLD_FRAME_SEQUENCE)
		{
			if ((*it) - start > MIN_LENGTH_SEQUENCE_FRAME)
				linking_frames.push_back(pair<int, int>(start, *it));
		}
	}

	cout << "Linking frames:" << endl;
	for (vector<pair<int, int>>::iterator it = linking_frames.begin(); it != linking_frames.end(); it++)
		cout << it->first << " - " << it->second << endl;

	getchar();

	return 0;
}