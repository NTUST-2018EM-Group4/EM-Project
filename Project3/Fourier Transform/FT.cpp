#include "FT.h"

#define  PI  3.14159265358979363846
using namespace std;

FT::FT()
{
}

void FT::DiscreteFourierTransform(int** InputImage, int** OutputImage, double ** FreqReal, double ** FreqImag, int h, int w)
{
	int M = h;
	int N = w;

	double** pFreq = new double*[M];
	for (int newcnt = 0; newcnt<M; newcnt++)
	{
		pFreq[newcnt] = new double[N]; // 傅立葉頻率陣列
	}
	for (int forzero_i = 0; forzero_i<M; forzero_i++)
	{
		for (int forzero_j = 0; forzero_j<N; forzero_j++)
		{
			pFreq[forzero_i][forzero_j] = 0.0f;
		}
	}
	//-------------------------------------------
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			DFT(FreqReal, FreqImag, InputImage,M, N, j, i);
		}
	}
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			// 將計算好的傅立葉實數與虛數部分作結合 
			pFreq[i][j] = sqrt(pow(FreqReal[i][j], (double) 2.0) + pow(FreqImag[i][j], (double) 2.0));
			// 結合後之頻率域丟入影像陣列中顯示 
			OutputImage[i][j] = pFreq[i][j];
		}
	}
	//-------------------------------------------
	for (int delcnt = 0; delcnt < M; delcnt++)
	{
		delete[] pFreq[delcnt];
	}
	delete[] pFreq;
}

void FT::DFT(double ** pFreqReal, double ** pFreqImag, int ** InputImage, int h, int w, int u, int v)
{
	// M = N 必須是方陣
	int M = h;
	int N = w;

	for (int y = 0; y < M; y++)
	{
		for (int x = 0; x < N; x++)
		{
			// 可先計算Eular's equation e^{j*theta} = cos{theta}+j*sin{theta}			
			double angleDFT = (-1.0f * 2.0f * 3.14159 * (double)(u*x + v*y) / (double)M);
			double c = cos(angleDFT);
			double s = sin(angleDFT);

			// 利用Eular's equation計算傅立葉之實虛數部分
			pFreqReal[u][v] += (double)InputImage[y][x] * c;
			pFreqImag[u][v] -= (double)InputImage[y][x] * s;
		}
	}

	pFreqReal[u][v] = pFreqReal[u][v] / (double)(M);
	pFreqImag[u][v] = pFreqImag[u][v] / (double)(M);
}

void FT::InverseDiscreteFourierTransform(int ** InputImage, int ** OutputImage, double ** FreqReal, double ** FreqImag, int h, int w)
{
	int M = h;
	int N = w;

	double** InverseReal = new double*[M];
	double** InverseImag = new double*[M];
	double** pFreq = new double*[M];

	for (int i = 0; i<M; i++)
	{
		InverseReal[i] = new double[N];
		InverseImag[i] = new double[N];
		pFreq[i] = new double[N]; // 傅立葉頻率陣列
	}

	for (int i = 0; i<M; i++)
	{
		for (int j = 0; j<N; j++)
		{
			InverseReal[i][j] = 0.0f;
			InverseImag[i][j] = 0.0f;
			pFreq[i][j] = 0.0f;
		}
	}
	//-------------------------------------------
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			InverseDFT(InverseReal, InverseImag,FreqReal, FreqImag, M, N, j, i);
		}
	}
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			// 將計算好的傅立葉實數與虛數部分作結合 
			pFreq[i][j] = sqrt(pow(InverseReal[i][j], (double) 2.0) + pow(InverseImag[i][j], (double) 2.0));
			// 結合後之頻率域丟入影像陣列中顯示 
			OutputImage[i][j] = pFreq[i][j];
			//存下反傅立葉實數與虛數部分
			FreqReal[i][j] = InverseReal[i][j];
			FreqImag[i][j] = InverseImag[i][j];

		}
	}
	//-------------------------------------------
	for (int i = 0; i < M; i++)
	{
		delete[] pFreq[i];
		delete[] InverseReal[i];
		delete[] InverseImag[i];

	}
	delete[] pFreq;
	delete[] InverseReal;
	delete[] InverseImag;

}

void FT::InverseDFT(double ** InverseReal, double ** InverseImag, double ** pFreqReal, double ** pFreqImag, int h, int w, int x, int y)
{
	// M = N 必須是方陣
	int M = h;
	int N = w;

	for (int v = 0; v < M; v++)
	{
		for (int u = 0; u < N; u++)
		{
			// 可先計算Eular's equation e^{j*theta} = cos{theta}+j*sin{theta}			
			double angleIDFT = (2.0f * 3.14159 * (double)(u*x + v*y) / (double)M);
			double c = cos(angleIDFT);
			double s = sin(angleIDFT);

			// 利用Eular's equation計算傅立葉之實虛數部分
			InverseReal[x][y] += (pFreqReal[v][u] * c - pFreqImag[v][u] * s);
			InverseImag[x][y] += (pFreqReal[v][u] * s + pFreqImag[v][u] * c);
		}
	}
	InverseReal[x][y] = InverseReal[x][y] / (float)M;
	InverseImag[x][y] = InverseImag[x][y] / (float)M;
}

void FT::FastFourierTransform(int ** InputImage, int ** OutputImage, double ** FreqReal, double ** FreqImag, int h, int w)
{
	int M = h;
	int N = w;
	
	vector<complex<double>> x;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			complex<double> temp(InputImage[i][j], 0);
			x.push_back(temp);
		}
		//FFT
		FFT(x, M, N);
		for (int j = 0; j < N; j++)
		{
			FreqReal[i][j] = x[j].real();
			FreqImag[i][j] = x[j].imag();

		}
		x.clear();
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			complex<double> temp(FreqReal[j][i], FreqImag[j][i]);
			x.push_back(temp);
		}
		//FFT
		FFT(x, M, N);
		for (int j = 0; j < N; j++)
		{
			FreqReal[j][i] = x[j].real();
			FreqImag[j][i] = x[j].imag();
		}
		x.clear();
	}

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			// 將計算好的傅立葉實數與虛數部分作結合 
			// 結合後之頻率域丟入影像陣列中顯示 
			OutputImage[j][i] = sqrt(pow(FreqReal[i][j] / N, (double)2.0) + pow(FreqImag[i][j] / N, (double)2.0));
		}
	}
	
}

void FT::FFT(vector<complex<double>>& x, int h, int w)
{
	//M=N square
	int N = w;

	/* bit-reversal permutation */
	for (int i = 1, j = 0; i < N; ++i)
	{
		for (int k = N >> 1; !((j ^= k) & k); k >>= 1);
		if (i > j) swap(x[i], x[j]);
	}

	/* dynamic programming */
	for (int k = 2; k <= N; k <<= 1)
	{
		double omega = -2.0 * PI / k;
		complex<double> dTheta(cos(omega), sin(omega));
		
		// 每k個做一次FFT
		for (int j = 0; j < N; j += k)
		{
			// 前k/2個與後k/2的三角函數值恰好對稱，
			// 因此兩兩對稱的一起做。
			complex<double> theta(1, 0);
			for (int i = j; i < j + k / 2; i++)
			{
				complex<double> a = x[i];
				complex<double> b = x[i + k / 2] * theta;
				x[i] = a + b;
				x[i + k / 2] = a - b;
				theta *= dTheta;
			}
		}
	}
}

void FT::InverseFastFourierTransform(int** InputImage, int** OutputImage, double** FreqReal, double** FreqImag, int h, int w)
{
	int M = h;
	int N = w;
	
	vector<complex<double>> x;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			complex<double> temp(FreqReal[i][j], FreqImag[i][j]);
			x.push_back(temp);
		}
		//InverseFFT
		InverseFFT(x, M, N);
		for (int j = 0; j < N; j++)
		{
			FreqReal[i][j] = x[j].real();
			FreqImag[i][j] = x[j].imag();

		}
		x.clear();
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			complex<double> temp(FreqReal[j][i], FreqImag[j][i]);
			x.push_back(temp);
		}
		//InverseFFT
		InverseFFT(x, M, N);
		for (int j = 0; j < N; j++)
		{
			FreqReal[j][i] = x[j].real();
			FreqImag[j][i] = x[j].imag();
		}
		x.clear();
	}
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			// 將計算好的傅立葉實數與虛數部分作結合
			// 結合後之頻率域丟入影像陣列中顯示 
			OutputImage[i][j] = sqrt(pow(FreqReal[i][j] / N, (double)2.0) + pow(FreqImag[i][j] / N, (double)2.0));
		}
	}
}

void FT::InverseFFT(vector<complex<double>>& x, int h, int w)
{
	//M=N square
	int N = w;

	/* bit-reversal permutation */
	for (int i = 1, j = 0; i < N; ++i)
	{
		for (int k = N >> 1; !((j ^= k) & k); k >>= 1);
		if (i > j) swap(x[i], x[j]);
	}

	/* dynamic programming */
	for (int k = 2; k <= N; k <<= 1)
	{
		double omega = 2.0 * PI / k;
		complex<double> dTheta(cos(omega), sin(omega));

		// 每k個做一次FFT
		for (int j = 0; j < N; j += k)
		{
			// 前k/2個與後k/2的三角函數值恰好對稱，
			// 因此兩兩對稱的一起做。
			complex<double> theta(1, 0);
			for (int i = j; i < j + k / 2; i++)
			{
				complex<double> a = x[i];
				complex<double> b = x[i + k / 2] * theta;
				x[i] = a + b;
				x[i + k / 2] = a - b;
				theta *= dTheta;
			}
		}
	}
}

void FT::LowpassFilter(double** Real, double** Img, int** OutputImage, int h, int w)
{
	int cutoff = 10;
	double n = 2;
	int midX = w / 2;
	int midY = h / 2;
	for (int v = 0; v < h; v++) {
		for (int u = 0; u < w; u++)
		{
			complex<double> temp(Real[v][u], Img[v][u]);
			temp *= 1 / (1 + pow(sqrt(pow(u - midX, 2.0) + pow(v - midY, 2.0)) / cutoff, 2.0 * n));
			Real[v][u] = temp.real() / h;
			Img[v][u] = temp.imag() / h;
			// 將計算好的傅立葉實數與虛數部分作結合 
			// 結合後之頻率域丟入影像陣列中顯示 
			OutputImage[u][v] = sqrt(pow(temp.real() / h, (double)2.0) + pow(temp.imag() / h, (double)2.0));
		}
	}	
}

void FT::HighpassFilter(double** Real, double** Img, int** OutputImage, int h, int w)
{
	int cutoff = 10;
	double n = 2;
	int midX = w / 2;
	int midY = h / 2;
	for (int v = 0; v < h; v++) {
		for (int u = 0; u < w; u++)
		{
			complex<double> temp(Real[v][u], Img[v][u]);
			temp *= 1 - 1 / (1 + pow(sqrt(pow(u - midX, 2.0) + pow(v - midY, 2.0)) / cutoff, 2.0 * n));
			Real[v][u] = temp.real() / h;
			Img[v][u] = temp.imag() / h;
			// 將計算好的傅立葉實數與虛數部分作結合 
			// 結合後之頻率域丟入影像陣列中顯示 
			OutputImage[u][v] = sqrt(pow(temp.real() / h, (double)2.0) + pow(temp.imag() / h, (double)2.0));
		}
	}
}
