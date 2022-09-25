#include <omp.h>
#include <stdio.h>
#include <Windows.h>
#include <chrono>
#include <vector>

const int NMAX = 5000;

void main() {

    omp_set_num_threads(4);

    SetConsoleOutputCP(1251);

    std::vector<int> a;
    std::vector<int> b;

    int sum = 0;
    int total = 1;

    for (int i = 0; i < NMAX; i++) {
        a.push_back(rand() % 3 + 0);
        b.push_back(rand() % 3 + 0);
    }
    auto start_threads_time = std::chrono::steady_clock::now();

#pragma omp parallel shared(a)
    {
#pragma omp for private(i,sum) reduction(*:total)

#pragma omp section private(i,sum)
        for (int i = 0; i < NMAX; i++)
        {
            sum = a[i] + b[i];
            printf("Сумма элементов индекса %d равна %d\n", i, sum);
            if (sum > 0)
                total = total * sum;
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
}
