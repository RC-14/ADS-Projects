#include "sorting.h"

namespace sorting {
	//************
	// QuickSort *
	//************
	void QuickSort(vector<int>& arr, int left, int right) {
		if (left >= right) return;

		// Use InsertionSort if below cross over
		if (arr.size() < 49) {
			// Insertion Sort
			for (int i = 1; i < arr.size(); i++) {
				int tmp = arr[i];

				int j = i - 1;
				while (j >= 0 && arr[j] > tmp) {
					arr[j + 1] = arr[j];
					j--;
				}

				arr[j + 1] = tmp;
			}
			return;
		}

		int x = max(min(arr[left], arr[right]), min(max(arr[left], arr[right]), arr[(right - left) / 2]));
		int i = left - 1;

		for (int j = left; j < right; j++) {
			if (arr[j] > x) continue;

			i++;
			swap(arr[i], arr[j]);
		}

		i++;
		swap(arr[i], arr[right]);

		QuickSort(arr, left, i - 1);
		QuickSort(arr, i + 1, right);
	}

	//****************
	// InsertionSort *
	//****************
	void insertionSort(vector<int>& a) {
		for (size_t i = 1; i < a.size(); i++) {
			int tmp = a[i];

			int j = i - 1;
			while (j >= 0 && a[j] > tmp) {
				a[j + 1] = a[j];
				j--;
			}

			a[j + 1] = tmp;
		}
	}

	//************
	// MergeSort *
	//************
	void Merge(vector<int>& a, vector<int>& b, int low, int pivot, int high) {
		int left = low;
		int right = pivot;
		for (int i = low; i <= high; i++) {
			if (left < pivot && (right > high || a[left] <= a[right])) {
				b[i] = a[left];
				left++;
			} else {
				b[i] = a[right];
				right++;
			}
		}

		for (int i = low; i <= high; i++) {
			a[i] = b[i];
		}
	}

	void MergeSort(vector<int>& a, vector<int>& b, int low, int high) {
		if (low < high) {
			int pivot = (low + high) / 2;
			MergeSort(a, b, low, pivot);
			MergeSort(a, b, pivot + 1, high);
			Merge(a, b, low, pivot + 1, high);
		}
	}

	vector<pair<int, int>> getRuns(const vector<int>& a) {
		std::vector<std::pair<int, int>> runs;
		int n = a.size();
		int start = 0;

		while (start < n) {
			int end = start;
			while (end < n - 1 && a[end] <= a[end + 1])
				end++;
			runs.push_back({ start, end });
			start = end + 1;
		}
		return runs;
	}

	void natMerge(vector<int>& a, vector<int>& b, int left, int middle, int right) {
		Merge(a, b, left, middle + 1, right);
	}

	void natMergeSort(vector<int>& a, vector<int>& b) {
		vector<pair<int, int>> runs = getRuns(a);

		while (runs.size() > 1) {
			vector<pair<int, int>> newRuns;

			for (size_t i = 0; i < runs.size(); i += 2) {
				if (i + 1 < runs.size()) {
					int low = runs[i].first;
					int pivot = runs[i].second;
					int high = runs[i + 1].second;
					natMerge(a, b, low, pivot, high);
					newRuns.push_back({ low, high });
				} else {
					newRuns.push_back(runs[i]);
				}
			}
			runs = newRuns;
		}
	}

	//************
	// Heapsort  *
	//************

	int left(int i) {
		return 2 * i;
	}
	int right(int i) {
		return 2 * i + 1;
	}

	void max_heapify(std::vector<int>& a, int heap_size, int i) {
		int l = left(i);
		int r = right(i);
		int largest = i;

		if (l < heap_size && a[l] > a[i]) {
			largest = l;
		}
		if (r < heap_size && a[r] > a[largest]) {
			largest = r;
		}
		if (largest != i) {
			swap(a[i], a[largest]);
			max_heapify(a, heap_size, largest);
		}
	}

	void build_max_heap(std::vector<int>& a) {
		int heap_size = a.size();
		for (int i = heap_size / 2 - 1; i >= 0; --i) {
			max_heapify(a, heap_size, i);
		}
	}

	void HeapSort(std::vector<int>& a, int n) {
		build_max_heap(a);
		for (int i = n - 1; i > 0; --i) {
			swap(a[0], a[i]);
			max_heapify(a, i, 0);
		}
	}

	//************
	// Shellsort *
	//************
	// Hier soll Hibbard implementiert werden
	void ShellSort_2n(vector<int>& a, int n) {
		int k = 1;
		while (pow(2, k) - 1 < n) {
			k++;
		}
		k--;

		while (k > 0) {
			int gap = pow(2, k) - 1;
			for (int i = gap; i < n; i++) {
				int tmp = a[i];
				int j = i;
				while (j >= gap && a[j - gap] > tmp) {
					a[j] = a[j - gap];
					j -= gap;
				}
				a[j] = tmp;
			}
			k--;
		}
	}

	void ShellSort_3n(vector<int>& a, int n) {
		int k = 1;

		while (pow(3, k) - 1 < n) {
			k++;
		}
		k--;

		while (k > 0) {
			int gap = pow(3, k) - 1;
			for (int i = gap; i < n; i++) {
				int temp = a[i];
				int j = i;
				while (j >= gap && a[j - gap] > temp) {
					a[j] = a[j - gap];
					j -= gap;
				}
				a[j] = temp;
			}
			k--;
		}
		insertionSort(a);
	}

	void randomizeVector(vector<int>& array, int n) {
		array.resize(n);

		for (unsigned int i = 0; i < array.size(); i++)
			array[i] = rand() % 1000000;
	}
}
