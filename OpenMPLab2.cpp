#include <omp.h>
#include <stdio.h>
#include <Windows.h>
#include <chrono>

const int NMAX = 100;
const int LIMIT = 120;

void main()
{
    SetConsoleOutputCP(1251);

    int i, j;
    float sum;
    float a[NMAX][NMAX];

    for (i = 0; i < NMAX; i++)
        for (j = 0; j < NMAX; j++)
            a[i][j] = i + j;

    auto start = std::chrono::steady_clock::now();

#pragma omp parallel shared(a) if (NMAX>LIMIT)
    {
#pragma omp for private(i,j,sum) 
        for (i = 0; i < NMAX; i++)
        {
            sum = 0;
            for (j = 0; j < NMAX; j++)
                sum += a[i][j];
            printf("����� ��������� ������ %d ����� %f\n", i, sum);
        }
    } /* ���������� ������������� ��������� */

    auto end = std::chrono::steady_clock::now();

    printf("\n����� ������ ��������� � %d �������� ������� � ������� %d: %f ���.\n", NMAX, 
        LIMIT, (end - start).count() / 1'000'000'000.0);
}
