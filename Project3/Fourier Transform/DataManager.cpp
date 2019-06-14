#include "DataManager.h"

DataManager::DataManager(int h, int w)
{
	ImageHeight = h;
	ImageWidth = w;

	InputImage = new int*[h];
	OutputImage = new int*[h];
	FreqReal = new double*[h];
	FreqImag = new double*[h];

	for (int i = 0; i < h; i++)
	{
		InputImage[i] = new int[w];
		OutputImage[i] = new int[w];
		FreqReal[i] = new double[w];
		FreqImag[i] = new double[w];

	}

	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
		{
			InputImage[i][j] = 0;
			OutputImage[i][j] = 0;
			FreqReal[i][j] = 0;
			FreqImag[i][j] = 0;
		}
}

DataManager::DataManager(const DataManager & dataManager)
{
	ImageHeight = dataManager.ImageHeight;
	ImageWidth = dataManager.ImageWidth;

	InputImage = new int*[ImageHeight];
	OutputImage = new int*[ImageHeight];
	FreqReal = new double*[ImageHeight];
	FreqImag = new double*[ImageHeight];

	for (int i = 0; i < ImageHeight; i++)
	{
		InputImage[i] = new int[ImageWidth];
		OutputImage[i] = new int[ImageWidth];
		FreqReal[i] = new double[ImageWidth];
		FreqImag[i] = new double[ImageWidth];

	}

	for (int i = 0; i < ImageHeight; i++)
	{
		for (int j = 0; j < ImageWidth; j++)
		{
			InputImage[i][j] = dataManager.InputImage[i][j];
			OutputImage[i][j] = dataManager.OutputImage[i][j];
			FreqReal[i][j] = dataManager.FreqReal[i][j];
			FreqImag[i][j] = dataManager.FreqImag[i][j];
		}
	}
}

void DataManager::SetPixel(int x, int y, int pixelValue)
{
	InputImage[y][x] = pixelValue;
}

void DataManager::SetFreqReal(int x, int y, double value)
{
	FreqReal[y][x] = value;
}

void DataManager::SetFreqImag(int x, int y, double value)
{
	FreqReal[y][x] = value;
}

int DataManager::GetImageHeight()
{
	return ImageHeight;
}

int DataManager::GetImageWidth()
{
	return ImageWidth;
}

int ** DataManager::GetInputImage()
{
	return InputImage;
}

int ** DataManager::GetOutputImage()
{
	return OutputImage;
}

double ** DataManager::GetFreqReal()
{
	return FreqReal;
}

double ** DataManager::GetFreqImag()
{
	return FreqImag;
}

DataManager & DataManager::operator=(const DataManager &dataManager)
{
	// TODO: 於此處插入傳回陳述式
	if (this != &dataManager) 
	{
		ImageHeight = dataManager.ImageHeight;
		ImageWidth = dataManager.ImageWidth;

		// 先清除原有的資源 
		for (int delcnt = 0; delcnt < ImageHeight; delcnt++)
		{
			delete[] InputImage[delcnt];
			delete[] OutputImage[delcnt];
			delete[] FreqReal[delcnt];
			delete[] FreqImag[delcnt];
		}
		delete[] InputImage;
		delete[] OutputImage;
		delete[] FreqReal;
		delete[] FreqImag;

		InputImage = new int*[ImageHeight];
		OutputImage = new int*[ImageHeight];
		FreqReal = new double*[ImageHeight];
		FreqImag = new double*[ImageHeight];

		for (int i = 0; i < ImageHeight; i++)
		{
			InputImage[i] = new int[ImageWidth];
			OutputImage[i] = new int[ImageWidth];
			FreqReal[i] = new double[ImageWidth];
			FreqImag[i] = new double[ImageWidth];

		}

		for (int i = 0; i < ImageHeight; i++)
		{
			for (int j = 0; j < ImageWidth; j++)
			{
				InputImage[i][j] = dataManager.InputImage[i][j];
				OutputImage[i][j] = dataManager.OutputImage[i][j];
				FreqReal[i][j] = dataManager.FreqReal[i][j];
				FreqImag[i][j] = dataManager.FreqImag[i][j];
			}
		}
	}
	return *this;
}

DataManager::~DataManager()
{
	for (int delcnt = 0; delcnt < ImageHeight; delcnt++)
	{
		delete[] InputImage[delcnt];
		delete[] OutputImage[delcnt];
		delete[] FreqReal[delcnt];
		delete[] FreqImag[delcnt];
	}
	delete[] InputImage;
	delete[] OutputImage;
	delete[] FreqReal;
	delete[] FreqImag;
}
