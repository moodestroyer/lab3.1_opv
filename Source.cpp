#include <iostream>
#include <omp.h>
#include <algorithm>

using namespace std;

int main() {

    setlocale(LC_ALL, "Russian");
    int k, N;
    cout << "Количество потоков: ";
    cin >> k;
    cout << "Сумма чисел: ";
    cin >> N;

    int actualThreads = std::min(k, N);

    int sum = 0;

#pragma omp parallel num_threads(actualThreads) reduction(+:sum)
    {
        int id = omp_get_thread_num();
        int partial_sum = 0;

        for (int i = id + 1; i <= N; i += k) {
            partial_sum += i;
        }
#pragma omp critical
        {
            cout << "Поток" << " " << id << "  : Сумма = " << partial_sum << endl;
        }
        sum += partial_sum;
    }

    cout << "Конечная сумма = " << sum << endl;

    return 0;
}