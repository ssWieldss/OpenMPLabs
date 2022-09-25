#include <omp.h>
#include <stdio.h>
#include <Windows.h>
#include <chrono>
#include <vector>

const int NMAX = 5000;

void main() {

    SetConsoleOutputCP(1251);

    std::vector<int> a;
    std::vector<int> b;
    int sum = 0;
    int total = 1;

    for (int i = 0; i < NMAX; i++) {
        a.push_back(rand() % 3 + 0);
        b.push_back(rand() % 3 + 0);
    }

auto start_critical = std::chrono::steady_clock::now();

#pragma omp parallel shared(a,b, total) private(i,sum)
    {
#pragma omp for private(i,sum) reduction(*:total)
        for (int i = 0; i < NMAX; i++)
        {
            sum = a[i] + b[i];
            printf("����� ��������� ������� %d ����� %d\n", i, sum);
#pragma omp critical
            if (sum > 0)
                total = total * sum;
        }
    }

auto end_critical = std::chrono::steady_clock::now();

    printf("����� ������������ critical %d\n", total);

    sum = 0;
    total = 1;

auto start_atomic = std::chrono::steady_clock::now();

#pragma omp parallel shared(a,b, total) private(i,sum)
    {
#pragma omp for
        for (int i = 0; i < NMAX; i++)
        {
            sum = a[i] + b[i];
            printf("����� ��������� ������� %d ����� %d\n", i, sum);
            if (sum > 0)
#pragma omp atomic
                total *= sum;
        }
    }
auto end_atomic = std::chrono::steady_clock::now();

    printf("����� ������������ atomic %d\n", total);

    sum = 0;
    total = 1;

auto start_thread_time = std::chrono::steady_clock::now();

    for (int i = 0; i < NMAX; i++)
    {
        sum = a[i] + b[i];
        printf("����� ��������� ������� %d ����� %d\n", i, sum);
        if (sum > 0)
            total = total * sum;
    }

auto end_thread_time = std::chrono::steady_clock::now();

    printf("����� ������������ %d\n", total);

    printf("\n����� ������ ��������� � %d �������� �������� � ����� �������: %f ���.\n", NMAX,
        (end_thread_time - start_thread_time).count() / 1'000'000'000.0);
    printf("\n����� ������ ��������� � %d �������� �������� �� ���������� ������� critical: %f ���.\n", NMAX,
        (end_critical - start_critical).count() / 1'000'000'000.0);
    printf("\n����� ������ ��������� � %d �������� �������� �� ���������� ������� atomic: %f ���.\n", NMAX,
        (end_atomic - start_atomic).count() / 1'000'000'000.0);
}