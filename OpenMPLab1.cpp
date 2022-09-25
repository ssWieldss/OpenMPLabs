#include <omp.h>
#include <stdio.h>
#include <Windows.h>
#include <chrono>

const int NMAX = 500;
const int MMAX = 500;

void main()
{
    SetConsoleOutputCP(1251);

    int i, j;
    int k;
    int sum;
    int temp;
    int count_number = 0;
    int a[NMAX][MMAX];

    for (i = 0; i < NMAX; i++)
        for (j = 0; j < MMAX; j++)
            a[i][j] = rand() % 500 + 1;

    auto start_threads_time = std::chrono::steady_clock::now();

#pragma omp parallel shared(a) private(i) 
    {
#pragma omp for private(j,sum, count_number,k) 
        for (i = 0; i < NMAX; i++)
        {
            count_number = 0;
            sum = 0;
            for (j = 0; j < MMAX - 1; j++) {
                for (k = j + 1; k < MMAX; k++) {
                    sum = a[i][j] + a[i][k];
                    while (sum != 0) {
                        temp = 0;
                        temp = sum % 10;
                        if (temp == 7)
                            count_number += 1;
                        sum = sum / 10;
                    }
                }
            }
            printf("\nКоличество семерок в попарных суммах элементов строки %d равна %d\n", i, count_number);
        }
    }

    auto end_threads_time = std::chrono::steady_clock::now();

    for (int i = 0; i < NMAX; i++) {
        printf("%d\t", a[1][i]);
    }


    sum;
    temp;
    count_number = 0;

    auto start_thread_time = std::chrono::steady_clock::now();

    for (i = 0; i < NMAX; i++)
    {
        count_number = 0;
        sum = 0;
        for (j = 0; j < MMAX; j++) {
            for (k = 0; k < MMAX - 1; k++) {
                sum = a[i][j] + a[i][k + 1];
                while (sum != 0) {
                    temp = 0;
                    temp = sum % 10;
                    if (temp == 7)
                        count_number += 1;
                    sum = sum / 10;
                }
            }
        }
        printf("\nКоличество семерок в попарных суммах элементов строки %d равна %d\n", i, count_number);
    }
    auto end_thread_time = std::chrono::steady_clock::now();

    printf("\nВремя работы программы с %d размером матрицы с одним потоком : %f сек.\n", NMAX,
        (end_thread_time - start_thread_time).count() / 1'000'000'000.0);
    printf("\nВремя работы программы с %d размером матрицы с несколькими потоками: %f сек.\n",
        NMAX, (end_threads_time - start_threads_time).count() / 1'000'000'000.0);
}