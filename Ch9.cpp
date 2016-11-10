#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <list>
#define SIZE 20

int arr[SIZE + 1];

void randomGenerateArr() {
    srand(time(NULL));
    for (int i = 1; i <= SIZE; i++)
        arr[i] = rand() % (2 * SIZE);
    printf("Original: ");
    for (int i = 1; i <= SIZE; i++)
        printf("%d ", arr[i]);
    puts("");
}

void insertion_sort(int *A, int l, int r) {
    for (int i = l + 1; i <= r; i++)
        for (int j = i; j >= l + 1; j--)
            if (A[j] < A[j - 1]) std::swap(A[j], A[j - 1]);
            else break;
}

int partition(int *A, int n, int pivot) {
    int idx = 1;
    for (int i = 1; i <= n - 1; i++) {
        if (A[i] == pivot) std::swap(A[i], A[n]);
        if (A[i] < pivot) std::swap(A[i], A[idx++]);
    }
    std::swap(A[idx], A[n]);
    return idx;
}

int select(int *A, int n, int k) {
    if (n <= 5) {
        insertion_sort(A, 1, n);
        return A[k];
    }
    int A_copied[SIZE + 1], temp[SIZE + 1], size = 0;
    for (int i = 1; i <= n; i++)
        A_copied[i] = A[i];
    for (int i = 1; i <= n; i += 5) {
        if (i + 4 <= n) {
            insertion_sort(A_copied, i, i + 4);
            temp[++size] = A[i + 2];
        } else {
            insertion_sort(A_copied, i, n);
            temp[++size] = A[(i + n) / 2];
        }
    }
    int medianOfMedian = select(temp, size, (1 + size) / 2);
    int pos = partition(A, n, medianOfMedian);
    if (pos == k) return A[pos];
    else if (pos > k) return select(A, pos - 1, k);
    else return select(A + pos, n - pos, k - pos);
}

int main() {
    randomGenerateArr();
    printf("Select from 1 to SIZE: ");
    for (int i = 1; i <= SIZE; i++)
        printf("%d ", select(arr, SIZE, i));
    puts("");
    printf("Sorted array:          ");
    std::sort(arr + 1, arr + 1 + SIZE);
    for (int i = 1; i <= SIZE; i++)
        printf("%d ", arr[i]);
    puts("");
    return 0;
}

/*
#include <iostream>
#include <algorithm>
#include <list>
#define SIZE 11

int arr[SIZE + 1] = {0, 8, 6, 1, 4, 3, 9, 2, 10, 7, 5, 11};

void insert_sort(int *A, int l, int r) {
    for (int i = l + 1; i <= r; i++)
        for (int j = i; j >= l + 1; j--)
            if (A[j] < A[j - 1])
                std::swap(A[j], A[j - 1]);
            else break;
}

int myPartition(int *A, int n, int target) {
    int i = 1;
    for (int j = 1; j <= n - 1; j++) {
        if (A[j] == target) std::swap(A[j], A[n]);
        if (A[j] < target) std::swap(A[j], A[i++]);
    }
    std::swap(A[i], A[n]);
    return i;
}

int select(int *B, int k, int n) {
    int A[SIZE + 1];
    for (int i = 1; i <= n; i++)
        A[i] = B[i];
    if (n <= 5) {
        insert_sort(A, 1, n);
        return A[k];
    }
    int temp[SIZE + 1], idx = 0;
    for (int i = 1; i <= n; i += 5)
        if (i + 4 <= n) {
            insert_sort(A, i, i + 4);
            temp[++idx] = A[i + 2];
        } else {
            insert_sort(A, i, n);
            temp[++idx] = A[(i + n) / 2];
        }
    int medianOfmedian = select(temp, (1 + idx) / 2, idx);
    int pos = myPartition(A, n, medianOfmedian);
    if (pos == k) return A[pos];
    else if (pos < k) return select(A + pos, k - pos, n - pos);
    else return select(A, k, pos - 1);
}

std::list<int> quantile(int *A, int n, int k) {
    std::list<int> temp1, temp2;
    if (k == 1) return temp1;
    int pos = k / 2, idx = pos * (n + 1) / k;
    int toSelect = select(A, idx, n);
    myPartition(A, n, toSelect);
    temp1 = quantile(A, idx, k / 2);
    temp2 = quantile(A + idx, n - idx, (k + 1) / 2);
    temp1.push_back(toSelect);
    temp1.splice(temp1.end(), temp2);
    return temp1;
}

int main()
{
    std::list<int> ans = quantile(arr, 11, 4);
    for (auto i : ans)
        std::cout << i << ' ';
    std::cout << std::endl;
    return 0;
}
*/
