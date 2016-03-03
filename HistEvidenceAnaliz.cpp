#include "Header.h"

// Функция анализирует гистограмму, если кадр "подходящий" то добавляет его номер в вектор.

bool HistEvidenceAnaliz(const Mat* hist_red, const int sizeHist, const long int amount_pixels, vector<int>* vec, int &numbedr_frame)
{ 
	double* ProbRed = (double*)malloc(sizeHist*sizeof(double));
	if (ProbRed == NULL) return false;

	double meanRed = 0.0; // мат. ожидание 
	double varianceRed = 0.0; // дисперсия
	double energyRed = 0.0;  // енергия

	for (int i = 0; i < sizeHist; i++)
	{
		ProbRed[i] = (double)hist_red->at<float>(i) / amount_pixels;
		meanRed += i * ProbRed[i];
		energyRed += ProbRed[i] * ProbRed[i];
	}

	for (int i = 0; i < sizeHist; i++)
		varianceRed += (i - meanRed) * (i - meanRed) * ProbRed[i];

	//cout << " Mean of Red channel: " << meanRed << endl;
	//cout << " Variance of Red channel: " << varianceRed << endl;
	//cout << " Energy of Red channel: " << energyRed << endl;
	//cout << endl;

	// Кадр является местом сшивки если гистограммные прищнаки удовлетворяют следующим условиям
	if (energyRed > THRESHOLD_ENERGY && varianceRed < THRESHOLD_VARIANCE && meanRed > THRESHOLD_BRIGHTNESS)
		vec->push_back(numbedr_frame);

	numbedr_frame++;
	free(ProbRed);

	return true;
}
