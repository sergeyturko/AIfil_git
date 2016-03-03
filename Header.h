#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

#define THRESHOLD_BRIGHTNESS 90.0 // порог €ркости. Ќа кадрах сшивки не должна быть мала т.к. кадры сшивки серые или светлее 
#define THRESHOLD_VARIANCE 500.0 // дисперси€. –азброс значений на кадрах сшивки должен быть достаточно мал
#define THRESHOLD_ENERGY 0.02 // енерги€ на кадрах сшивки будет максимальна, но на темных кадрах тоже
#define THRESHOLD_GAP_FRAME 8 // рассто€ние между "подход€щими" кадрами
#define THRESHOLD_FRAME_SEQUENCE 8 // длина последовательности кадров, которые можно считать местом сшивки
#define MIN_LENGTH_SEQUENCE_FRAME 25 // минимальна€ длина места сшивки
#define PERCENT_EDGE 0.07 // дол€ удал€ема€ с краев изображени€ (т.к. они черные и никакой информации не несут)

bool HistEvidenceAnaliz(const Mat*, const int, const long int, vector<int>*, int&);



