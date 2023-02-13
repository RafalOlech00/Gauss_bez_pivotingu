#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;


// funkcja rozwiązująca układ n równań liniowych o n niewiadomych metodą Gaussa bez pivoting'u 

void GaussWithoutPivot(float**Tab, int size)
{
	float mnoznik = 0.0f;
	for (int k = 0; k < (size - 1); k++)
	{
		for (int i = (k + 1); i < size; i++)
		{
			if (Tab[k][k] == 0) // sprawdzenie czy na przekątnej nie ma 0
			{
				cout << "Na przekatnej macierzy wystapila wartosc 0 !!!" << endl;
				return;
			}
			mnoznik = Tab[i][k] / Tab[k][k]; // obliczamy mnoznik
			for (int j = k; j < (size + 1); j++)
			{
				Tab[i][j] -= (mnoznik * Tab[k][j]); // od i-tego wiersza odejmujemy wiersz zerowy pomnożony przez mnożnik 
			}
		}
	}
}


// funkcja rozwiązująca układ n równań liniowych o n niewiadomych metodą Gaussa wykorzystując pivot 

void GaussWithPivot(float**Tab, int size )
{
	for (int k = 0; k < (size - 1); k++)
	{
		int w = k;
		float max = abs(Tab[k][k]); // abs - absolute value zwraca wartość bezwględną z podanej liczby

		for (int i = (k + 1); i < size; i++)
		{
			if (abs(Tab[i][k]) > max) // jeżeli istnieje element większy od max zmiana elementu największego
			{
				max = abs(Tab[i][k]);
				w = i;
			}
		}
		
		if (max == 0)  // jeżeli element maksymalny jest równy 0, zostaje wypisany komunikat 
		{
			cout << "Max = 0, nie da sie rozwiazac !" << endl;  // ponieważ już jest to największy element w kolumnie a nie może być 0 na przekątnej 
			return;
		}
		
		if (w != k)
		{
			float p;
			for (int i = 0; i < (size + 1); i++)
			{
				p = Tab[k][i];
				Tab[k][i] = Tab[w][i];  // podmiana wartości
				Tab[w][i] = p;
			}
		}

		// dalsza część taka sama jak bez pivota
		float mnoznik = 0.0f;
		for (int k = 0; k < (size - 1); k++)
		{
			for (int i = (k + 1); i < size; i++)
			{
				if (Tab[k][k] == 0) // sprawdzenie czy na przekątnej nie ma 0
				{
					cout << "Na przekatnej macierzy wystapila wartosc 0 !!!" << endl;
					return;
				}
				mnoznik = Tab[i][k] / Tab[k][k]; // obliczamy mnoznik
				for (int j = k; j < (size + 1); j++)
				{
					Tab[i][j] -= (mnoznik * Tab[k][j]); // od i-tego wiersza odejmujemy wiersz zerowy pomnożony przez mnożnik 
				}
			}
		}

	}

}


void ShowTab(float** Tab, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < (size + 1); j++)
		{
			cout << Tab[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int main()
{
	// odczytanie z pliku tekstowego danych 
	fstream read;
	int size = 0;
	read.open("RURL_dane2.txt"); // otwarcie pliku tekstowego
	read >> size; // rozmiar macierzy

	float x;
	float** Tab = new float* [size]; // przygotowana tablica dla macierzy rozszerzonej

	for (int i = 0; i < size; i++)
	{
		Tab[i] = new float[size + 1];
	}

	// wczytanie wartości do tablicy (macierz rozszerzona)
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < (size + 1); j++)
		{
			read >> x;
			Tab[i][j] = x;
		}
	}
	read.close(); // zamknięcie pliku tekstowego


	// Wypisanie macierzy rozszerzonej przed obliczeniami 
	cout << "Macierz rozszerzona przed obliczeniami:" << endl;
	ShowTab(Tab, size);

	//GaussWithoutPivot(Tab, size);
	GaussWithPivot(Tab, size);

	// Wypisanie macierzy rozszerzonej po obliczeniach 
	cout << "Macierz rozszerzona po obliczeniach:" << endl;
	ShowTab(Tab, size);

	float* ResultTab = new float[size];
	for (int i = 0; i < size; i++)
	{
		ResultTab[i] = 1;
	}

	float l = 0;
	for (int i = (size - 1); i >= 0; i--)
	{
		l = Tab[i][size];
		for (int j = (size - 1); j > i; j--)
		{
			l -= Tab[i][j] * ResultTab[j];
		}
		ResultTab[i] = l / Tab[i][i];
 	}

	// Wypisanie wyników
	cout << "Rozwiazanie ukladu rownan:" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << "x" << i << " = " << ResultTab[i] << endl;
	}
	
	



	

}

