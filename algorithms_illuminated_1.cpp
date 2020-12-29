#include <iostream>
#include <chrono>
#include "algorithm"
using namespace std::chrono;

int RecIntMult(int, int, int);
int add_trailing_zeros(int, int);
int Karatsuba(int, int, int);
int* MergeSort(int*, int);
int* Merge(int*, int*, int);

int main() {
    auto start = high_resolution_clock::now();
    std::cout << RecIntMult(5678, 1234, 4) << std::endl;
    auto stop1 = high_resolution_clock::now();

    std::cout << Karatsuba(5678, 1234, 4) << std::endl;
    auto stop2 = high_resolution_clock::now();

    int *A = new int[]{5, 4, 1, 8, 7, 2, 6, 3};
    int *sortedA = MergeSort(A, 8);
    auto stop3 = high_resolution_clock::now();

    std::cout << "Sorted array: ";
    for (int i = 0; i < 8; i++) {
        std::cout << sortedA[i] << " ";
    }
    std::cout << std::endl;

    auto duration1 = duration_cast<microseconds>(stop1 - start);
    auto duration2 = duration_cast<microseconds>(stop2 - stop1);
    auto duration3 = duration_cast<microseconds>(stop3 - stop2);

    std::cout << "\nTime taken by function:\nRecIntMult: "
         << duration1.count() << " microseconds\nKaratsuba: " << duration2.count() << " microseconds" << std::endl
         << "MergeSort: " << duration3.count() << " microseconds" << std::endl;
    return 0;
}

// Algorithms Illuminated: Part 1 (p. 9)
//
// Input: two n-digit positive integers x and y
// Output: the product x * y
// Assumption: n is a power of 2
int RecIntMult(int x, int y, int n) {
    if (n == 1) return x * y;
    else {
        int a = std::stoi(std::to_string(x).substr(0, n / 2));
        int b = std::stoi(std::to_string(x).substr(n / 2, n / 2));
        int c = std::stoi(std::to_string(y).substr(0, n / 2));
        int d = std::stoi(std::to_string(y).substr(n / 2, n / 2));

        int ac = RecIntMult(a, c, n / 2);
        int ad = RecIntMult(a, d, n / 2);
        int bc = RecIntMult(b, c, n / 2);
        int bd = RecIntMult(b, d, n / 2);

        return add_trailing_zeros(ac, n) + add_trailing_zeros(ad + bc, n / 2) + bd;
    }
}

int add_trailing_zeros(int x, int num_zeros) {
    std::string str = std::to_string(x);
    for (int i = 0; i < num_zeros; i++) {
        str += "0";
    }
    return std::stoi(str);
}


// Algorithms Illuminated: Part 1 (p. 11)
//
// Input: two n-digit positive integers x and y
// Output: the product x * y
// Assumption: n is a power of 2
int Karatsuba(int x, int y, int n) {
    if (n == 1) return x * y;
    else {
        int a = std::stoi(std::to_string(x).substr(0, n / 2));
        int b = std::stoi(std::to_string(x).substr(n / 2, n / 2));
        int c = std::stoi(std::to_string(y).substr(0, n / 2));
        int d = std::stoi(std::to_string(y).substr(n / 2, n / 2));

        int p = a + b;
        int q = c + d;

        int ac = Karatsuba(a, c, n / 2);
        int bd = Karatsuba(b, d, n / 2);
        int pq = Karatsuba(p, q, (n / 2) + 1);

        int adbc = pq - ac - bd;

        return add_trailing_zeros(ac, n) + add_trailing_zeros(adbc, n / 2) + bd;
    }
}


// Algorithms Illuminated: Part 1 (p. 16)
//
// Input: array A of n distinct integers
// Output: array with the same integers, sorted from smallest to largest
int* MergeSort(int *A, int n) {
    if (n < 2) return A;

    int half = n / 2;

    int* C = new int[half];
    int* D = new int[n - half];

    for (int i = 0; i < half; i++) {
        C[i] = A[i];
    }

    for (int i = half; i < n; i++) {
        D[i - half] = A[i];
    }

    int* sortedC = MergeSort(C, half);
    int* sortedD = MergeSort(D, n - half);

    return Merge(sortedC, sortedD, n);
}


// Algorithms Illuminated: Part 1 (p. 17)
//
// Input: sorted arrays C and D (length n/2 each)
// Output: sorted array B (length n)
int* Merge(int *C, int *D, int n) {
    int *B = new int[n];

    int half = n / 2;
    int i = 0, j = 0, k = 0;

    while (i < half && j < n - half) {
        if (C[i] < D[j]) B[k++] = C[i++];
        else B[k++] = D[j++];
    }

    while (i < half) {
        B[k++] = C[i++];
    }

    while (j < n - half) {
        B[k++] = D[j++];
    }

    return B;
}