// Part 1
#include <iostream>
#include <random>
#include <iomanip>

using namespace std;

int main() {

    int large_nums{0};
    int small_nums{0};

    cout << "Enter number of large and small numbers to average: ";
    cin >> large_nums >> small_nums;

    double large_arr[large_nums] = {};
    double small_arr[small_nums] = {};

    int seed = time(NULL);
    mt19937 generator(seed);
    uniform_real_distribution<double> large_distribution(0.0, 100000000.0);
    uniform_real_distribution<double> small_distribution(0.0000001, 0.00000001);

    // Create an array of desired length for large nums and populate it w/ random nums witnin appropiate range
    for (int i = 0; i < large_nums; i++) {
        large_arr[i] = large_distribution(generator);
    }

    // Create an array of desired length for small nums and populate it w/ random nums witnin appropiate range
    for (int j = 0; j < small_nums; j++) {
        small_arr[j] = small_distribution(generator);
    }

    // Method 1: Sum large then add small nums then average
    double sum_m1{0.0};
    for (int i = 0; i < large_nums; i++) {
        sum_m1 += large_arr[i];
    }

    for (int j = 0; j < small_nums; j++) {
        sum_m1 += small_arr[j];
    }

    double avg_m1 = sum_m1 / (large_nums + small_nums);
    cout << fixed << setprecision(40) << "average with large numbers first is: " << avg_m1 << endl;

    // Method 2: Sum small then add large nums then average
    double sum_m2{0.0};
    for (int i = 0; i < small_nums; i++) {
        sum_m2 += small_arr[i];
    }

    for (int j = 0; j < large_nums; j++) {
        sum_m2 += large_arr[j];
    }

    double avg_m2 = sum_m2 / (large_nums + small_nums);
    cout << fixed << setprecision(40) << "average with small mumbers first: " << avg_m2 << endl;
    
    // Method 3: Welford's Algorithm -> Running Avg
    int total_num_sample = large_nums + small_nums;
    double total_arr[total_num_sample];

    for (int i = 0; i < large_nums; i++) {
        total_arr[i] = large_arr[i];
    }
    for (int j = 0; j < small_nums; j++) {
        total_arr[large_nums + j] = small_arr[j];
    }

    double running_avg{0.0};
    for (int k = 0; k < total_num_sample; k++) {
        int n = k + 1;
        running_avg = running_avg + ((total_arr[k] - running_avg) / n);
    }
    cout << fixed << setprecision(40) << "average with small mumbers first: " << avg_m2 << endl;

}