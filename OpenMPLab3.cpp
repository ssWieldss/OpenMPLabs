#include <omp.h>
#include <stdio.h>
#include <Windows.h>
#include <chrono>

const int NMAX = 20;

void main() {

    SetConsoleOutputCP(1251);

    int a[NMAX];
    int b[NMAX];
    int sum = 0;
    int total = 1;

    for (int i = 0; i < NMAX; i++) {
        a[i] = rand() % 3 + 0;
        b[i] = rand() % 3 + 0;
    }
    auto start_threads_time = std::chrono::steady_clock::now();

#pragma omp parallel shared(a)
    {
#pragma omp for private(i,sum) reduction(*:total)
        for (int i = 0; i < NMAX; i++)
        {
            sum = a[i] + b[i];
            printf("Сумма элементов индекса %d равна %d\n", i, sum);
            if (sum > 0)
                total = total * sum;
        }
    }
    auto end_threads_time = std::chrono::steady_clock::now();

    printf("Общее произведение %d\n", total);

    sum = 0;
    total = 1;

    auto start_thread_time = std::chrono::steady_clock::now();

    for (int i = 0; i < NMAX; i++)
    {
        sum = a[i] + b[i];
        printf("Сумма элементов индекса %d равна %d\n", i, sum);
        if (sum > 0)
            total = total * sum;
    }

    auto end_thread_time = std::chrono::steady_clock::now();

    printf("Общее произведение %d\n", total);

    printf("\nВремя работы программы с %d размером массивов и одним потоком: %f сек.\n", NMAX,
        (end_thread_time - start_thread_time).count() / 1'000'000'000.0);
    printf("\nВремя работы программы с %d размером массивов со множеством потоков: %f сек.\n", NMAX,
        (end_threads_time - start_threads_time).count() / 1'000'000'000.0);
}