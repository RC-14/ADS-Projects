#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>

using namespace std;

void printVector(vector<int> v) {
	cout << "[";

	bool first = true;
	for (int i : v) {
		if (first) {
			first = false;
		} else {
			cout << ", ";
		}
		cout << i;
	}

	cout << " ]" << endl;
}

void insertionSort(vector<int>& arr) {
	for (int i = 1; i < arr.size(); i++) {
		int tmp = arr[i];

		int j = i - 1;
		while (j >= 0 && arr[j] > tmp) {
			arr[j + 1] = arr[j];
			j--;
		}

		arr[j + 1] = tmp;
	}
}

void quickSort(vector<int>& arr, int left, int right) {
	if (left >= right) return;

	int x = max(min(arr[left], arr[right]), min(max(arr[left], arr[right]), arr[(right - left) / 2]));
	int i = left - 1;

	for (int j = left; j < right; j++) {
		if (arr[j] > x) continue;

		i++;
		swap(arr[i], arr[j]);
	}

	i++;
	swap(arr[i], arr[right]);

	quickSort(arr, left, i - 1);
	quickSort(arr, i + 1, right);
}

void randomizeVector(vector<int>& array, int n) {
	array.resize(n);

	for (unsigned int i = 0;i < array.size();i++)
		array[i] = rand() % 1000000;
}

int main() {
	//file stream
	ofstream quicksort_measurement("quicksort.txt", ios::out);
	ofstream insertsort_measurement("insertsort.txt", ios::out);

	//benchmark parameters / variables
	chrono::steady_clock::time_point begin, end;
	chrono::nanoseconds dtime;
	int n_start = 1;
	int n_step = 1;
	int n_end = 200;

	vector<int> V1;
	vector<int> V2;

	//actual benchmark loop
	for (int n = n_start; n <= n_end; n += n_step) {
		//"progress bar"
		std::cout << "Running Benchmark with n: " << n << std::endl;

		//generate n random integers
		randomizeVector(V1, n);
		V2 = V1;

		//start measurement
		begin = std::chrono::steady_clock::now();

		//execzute sorting algorithm
		quickSort(V1, 0, V1.size() - 1);

		//stop time
		end = std::chrono::steady_clock::now();
		dtime = end - begin;

		//write to file
		quicksort_measurement << n << "\t" << setprecision(10) << scientific << dtime.count() << endl;

		//start measurement
		begin = std::chrono::steady_clock::now();

		//execzute sorting algorithm
		insertionSort(V2);

		//stop time
		end = std::chrono::steady_clock::now();
		dtime = end - begin;

		//write to file
		insertsort_measurement << n << "\t" << setprecision(10) << scientific << dtime.count() << endl;
	}

	//close file handle
	quicksort_measurement.close();
	insertsort_measurement.close();

	return 0;
}
