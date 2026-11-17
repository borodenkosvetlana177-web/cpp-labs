#include <iostream>
#include <random>

int** AllocateMatrix(int n) {
	int** arr = new int* [n];
	for (int i = 0; i < n; ++i) {
		arr[i] = new int[n];
	}
	return arr;
}

void PrintMatrix(const int* const* arr, int n) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			std::cout << arr[i][j] << '\t';
		}
		std::cout << "\n";
	}
}

void FillMatrixKeyboard(int** arr, int n) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0;j < n;++j) {
			std::cin >> arr[i][j];
		}
	}
}

void FillMatrixRandom(int** arr, int n, int minVal, int maxVal) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(minVal, maxVal);
	for (int i = 0; i < n; ++i) {
		for (int j = 0;j < n;++j) {
			arr[i][j] = dist(gen);
		}
	}
}

int FindMax(const int* const* arr, int n) {
	int max = arr[n - 1][n - 1];
	for (int i = 0; i < n; ++i) {
		for (int j = n - 1 - i; j < n; ++j) {
			if (arr[i][j] > max) {
				max = arr[i][j];
			}
		}
	}
	return max;
}

bool HavePositiveElements(const int* const* arr, int n) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (arr[i][j] > 0) {
				return true;
				}
			}
		}
	return false;
}

int FindMaxRow(const int* const* arr, int n) {
	int maxPos = 0;
	int maxRow = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
				if ( arr[i][j] > maxPos) {
					maxPos = arr[i][j];
					maxRow = i;
			}
		}
	}
	return maxRow;
}
int FindMaxCol(const int* const*  arr, int n) {
	int maxPos = 0;
	int maxCol = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
				if (arr[i][j] > maxPos) {
					maxPos = arr[i][j];
					maxCol = j;
			}
		}
	}
	return maxCol;
}


void SwapRows(int** arr, int row1, int row2) {
	if (row1 != row2) {
		std::swap(arr[row1], arr[row2]);
	}
}


void SwapCols(int** arr, int n, int col1, int col2) {
	if (col1 != col2) {
		for (int i = 0; i < n; ++i) {
			std::swap(arr[i][col1], arr[i][col2]);
		}
	}
}


void DeleteMatrix(int**& arr, int n) {
	for (int i = 0; i < n;++i) {
		delete[] arr[i];
	}
	delete[] arr;
	arr = nullptr;
}

int main() {
	system("chcp 65001 > nul");
	setlocale(LC_ALL, ".UTF8");
	int n;
	std::cout << "Введите количество строк матрицы \n";
	if (!(std::cin >> n) || n <= 0) 
		return 0;
	int** arr = AllocateMatrix(n);


	int a;
	std::cout << "Выберете способ заполнения массива, введите 1 для ввода с клавиатуры, 2 - случайное заполнение \n";
	std::cin >> a;



	if (a == 1) {
		std::cout << "Введите элементы матрицы \n";
		FillMatrixKeyboard(arr, n);
	}


	else if (a == 2) {
		std::cout << "Введите интервал заполнения \n";
		int minVal, maxVal;
		std::cin >> minVal >> maxVal;
		if (minVal > maxVal)
			std::swap(minVal, maxVal);
		FillMatrixRandom(arr, n ,minVal ,maxVal);
	}


	else {
		DeleteMatrix(arr, n); 
		return 0;
	}

	PrintMatrix(arr, n);
	std::cout << "Максимальное значение: " << FindMax(arr,n) << std::endl;

	
	if (HavePositiveElements(arr, n)) {
		int maxRow = FindMaxRow(arr, n);
		int maxCol = FindMaxCol(arr, n);
		std::cout << "Максимальный положительный элемент :" << arr[maxRow][maxCol]
			<< " его позиция [" <<  maxRow << "][" <<maxCol << "]" << std::endl;
		SwapRows(arr, 0, maxRow);
		SwapCols(arr, n, 0, maxCol);
		PrintMatrix(arr, n);
	}


	else {
		std::cout << "Положительных элементов не найдено" << std::endl;
	}

	DeleteMatrix(arr, n); 
	return 0;
} 
