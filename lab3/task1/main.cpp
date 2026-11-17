#include <iostream>
#include <ctime>
#include <cmath>
using std::cout;
using std::cin;

bool CheckBorder(int& a, int& b) {
	if (!(cin >> a >> b)) {
		cout << "You can write only numbers";
		return false;
	}
	if (b < a) {
		std::swap(a, b);
	}
		return true;
}


void FillArray(int size, int* arr, int a, int b) {
	for (std::size_t i = 0; i < size; ++i) {
		arr[i] = rand() % (b - a + 1) + a;
	}
}


void Print(const int* arr, int size) {
	for (std::size_t i = 0; i < size; ++i) {
		cout << arr[i] << " , ";
	}
	cout << "\n";
}


int MinValue(const int*arr, int size) {
	int min_value = arr[0];
	for (std::size_t i = 1; i < size; ++i) {
		if (std::abs(min_value) > std::abs(arr[i])) {
			min_value = arr[i];
		}
	}
	return min_value;
}

int main() {
	constexpr int MAX_SIZE = 100;
	int arr[MAX_SIZE];


	int size;
	cout << "Enter size \n";
	if (!(cin >> size) || size <= 0 || size > MAX_SIZE)
		return 0;


	std::srand(time(0));
	int a, b;
	cout << "Enter a,b \n";
	if (!CheckBorder(a, b)) {
		return 0;
	}

	FillArray(size, arr, a, b);
	Print(arr, size);

	
	cout << MinValue(arr, size);
	return 0;
}
