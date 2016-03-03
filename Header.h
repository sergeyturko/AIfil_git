#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

#define THRESHOLD_BRIGHTNESS 90.0 // ����� �������. �� ������ ������ �� ������ ���� ���� �.�. ����� ������ ����� ��� ������� 
#define THRESHOLD_VARIANCE 500.0 // ���������. ������� �������� �� ������ ������ ������ ���� ���������� ���
#define THRESHOLD_ENERGY 0.02 // ������� �� ������ ������ ����� �����������, �� �� ������ ������ ����
#define THRESHOLD_GAP_FRAME 8 // ���������� ����� "�����������" �������
#define THRESHOLD_FRAME_SEQUENCE 8 // ����� ������������������ ������, ������� ����� ������� ������ ������
#define MIN_LENGTH_SEQUENCE_FRAME 25 // ����������� ����� ����� ������
#define PERCENT_EDGE 0.07 // ���� ��������� � ����� ����������� (�.�. ��� ������ � ������� ���������� �� �����)

bool HistEvidenceAnaliz(const Mat*, const int, const long int, vector<int>*, int&);



