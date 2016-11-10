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

std::list<int> quantile(int *A, int n, int k) {
    std::list<int> temp1, temp2;
    if (k == 1) return temp1;
    int pos = k / 2, idx = n / k * pos + 1;
    int mid = select(A, n, idx);
    partition(A, n, mid);
    temp1 = quantile(A, idx - 1, k / 2);
    temp2 = quantile(A + idx, n - idx, (k + 1) / 2);
    temp1.push_back(mid);
    temp1.splice(temp1.end(), temp2);
    return temp1;
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
    printf("list: ");
    std::list<int> ans = quantile(arr, SIZE, 3);
    for (auto i : ans)
        printf("%d ", i);
    puts("");
    return 0;
}
