#include <iostream>
#include <ctime>
#include <string>
#include <cstring>
#include <fstream>
#include <windows.h>


template <typename Type>
Type** AllocateMatrix(int rows, int cols) {
	Type** arr = new Type * [rows];
	for (int i = 0; i < rows; ++i) {
		arr[i] = new Type[cols];
	}
	return arr;
}

template <>
char*** AllocateMatrix<char*>(int rows, int cols) {
	char*** arr = new char** [rows];
	for (int i = 0; i < rows; ++i) {
		arr[i] = new char*[cols];
		for (int j = 0; j < cols; ++j) {
			arr[i][j] = new char[50];
		}
	}
	return arr;
}


template <typename Type>
void PrintMatrix(Type** arr, int rows, int cols) {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			std::cout << arr[i][j] << '\t';
		}
		std::cout << "\n";
	}
}

template <typename Type>
void DeleteMatrix(Type**& arr, int rows, int cols) {
	for (int i = 0; i < rows;++i) {
		delete[] arr[i];
	}
	delete[] arr;
	arr = nullptr;
}

void DeleteMatrix (char***& arr, int rows, int cols) {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			delete[] arr[i][j]; 
	}
		delete[] arr[i];
	}
	delete[] arr;
	arr = nullptr;
}

template <typename Type>
void FillMatrixKeyboard(Type** arr, int rows, int cols) {
	std::cout << "Введите элементы матрицы:\n";
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			std::cin >> arr[i][j];
		}
	}
}


void FillMatrixKeyboard(char*** arr, int rows, int cols) {
	std::string temp;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			std::cin >> temp;
			strcpy_s(arr[i][j], 50, temp.c_str());
		}
	}
}



void FillMatrixRandom(int** arr, int rows, int cols) {
	int minVal, maxVal;
	std::cout << "Введите минимальное и максимальное значения:\n";
	std::cin >> minVal >> maxVal;

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			arr[i][j] = minVal + rand() % (maxVal - minVal + 1);
		}
	}
}



void FillMatrixRandom(double** arr, int rows, int cols) {
	double minVal, maxVal;
	std::cout << "Введите минимальное и максимальное значения:\n";
	std::cin >> minVal >> maxVal;

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			arr[i][j] = minVal + (static_cast<double>(rand()) / RAND_MAX) * (maxVal - minVal);
		}
	}
}


void FillMatrixRandom(char*** arr, int rows, int cols) {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			int word = 3 + rand() % 5;
			for (int k = 0; k  <word;++k){
arr[i][j][k] = 'a' + rand() % 26;
		}
			arr[i][j][word] = '\0';
	}
}
}

template <typename Type>
Type** FillMatrixFile(int& rows, int& cols, const std::string& filename) {
	std::ifstream inFile(filename); 
	if (!inFile.is_open()) {       
		return nullptr;
	}
	if (!(inFile >> rows >> cols) || rows <= 0 || cols <= 0) {
		inFile.close();
		return nullptr;
	}
	Type** arr = AllocateMatrix<Type>(rows, cols);
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (!(inFile >> arr[i][j])) { 
				DeleteMatrix(arr, rows, cols);
				inFile.close();
				return nullptr;
			}
		}
	}

	inFile.close();
	return arr;
}
template <>
char*** FillMatrixFile<char*>(int& rows, int& cols, const std::string& filename) {
	std::ifstream inFile(filename);
	if (!inFile.is_open()) {
		return nullptr;
	}
	if (!(inFile >> rows >> cols) || rows <= 0 || cols <= 0) {
		inFile.close();
		return nullptr;
	}
	char*** arr = AllocateMatrix<char*>(rows, cols);
	std::string temp;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
		 if (!(inFile >> temp)) {
			DeleteMatrix(arr, rows, cols);
			inFile.close();
			return nullptr;
		}
		strcpy_s(arr[i][j], 50, temp.c_str());
	}
}
	inFile.close();
	return arr;
}

template <typename Type>
void InsertionSort(Type** arr,int rows, int cols, bool arrange) {
	for (int k = 0; k < rows;++k) {
		for (std::size_t i = 0; i < cols; ++i) {
			Type key = arr[k][i];
			std::size_t j = i;
				while (j > 0 && ((arrange && arr[k][j - 1] > key) || (!arrange && arr[k][j - 1] < key))) {
				arr[k][j] = arr[k][j - 1];
				--j;
			}
			arr[k][j] = key;
		}
	}
}

void InsertionSort(char*** arr, int rows, int cols, bool arrange) {
	for (int k = 0; k < rows;++k) {
		for (std::size_t i = 0; i < cols; ++i) {
			char* key = arr[k][i];
			std::size_t j = i;
			while (j > 0 && ((arrange && strcmp(arr[k][j - 1], key) > 0) || (!arrange && strcmp(arr[k][j - 1], key) < 0))) {
				arr[k][j] = arr[k][j - 1];
				--j;
			}
			arr[k][j] = key;
		}
	}
}

template <typename Type>
bool SaveMatrixFile(Type** arr, int rows, int cols, const std::string& filename) {
	std::ofstream outFile(filename);
	if (!outFile.is_open()) {       
		return false;
	}
	outFile << rows << " " << cols << "\n";
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			outFile << arr[i][j] << " ";
		}
		outFile << "\n";
	}
	outFile.close(); 
	return true;
}

template <typename Type>
void RunProgram () {
int rows, cols;
std::cout << "Введите количество строк и столбцов матрицы \n";
if (!(std::cin >> rows) || !(std::cin >> cols) || rows <= 0 || cols <= 0) {
	std::cout << "Некорректные размеры\n";
	return;
}
Type** arr = AllocateMatrix<Type>(rows, cols);


int a;
std::cout << "Выберете способ заполнения массива \n";
std::cout << "1 - непосредственный ввод и запись в текстовый файл \n";
std::cout << "2 - генерирование с помощью датчика случайных чисел и запись в текстовый файл  \n";
std::cout << "3 - ввод из текстового файла, а вывод - в консоль  \n";
std::cin >> a;
switch (a) {
case 1:
	FillMatrixKeyboard(arr, rows, cols);
	SaveMatrixFile(arr, rows, cols, "data.txt");
	break;


case 2: {
	
	FillMatrixRandom(arr, rows, cols);
	SaveMatrixFile(arr, rows, cols, "data.txt");
	break;
}

case 3:
	DeleteMatrix(arr, rows, cols);
	arr = FillMatrixFile<Type>(rows, cols, "data.txt");
	if (arr == nullptr) {
		std::cout << "Ошибка чтения файла (возможно, он не создан или поврежден)!\n";
		return;
	}
	break;


default:
	std::cout << "Ошибка, попробуйте еще раз \n";
	DeleteMatrix(arr, rows, cols);
	return;
}

std::cout << "\nВаша матрица:\n";
PrintMatrix(arr, rows, cols);

int por;
std::cout << "\nВыберите порядок сортировки 1 - по возрастанию, 2 - по убыванию:\n";
std::cin >> por;

bool arrange = false;
switch (por) {
case 1:
	arrange = true;
	break;
case 2:
	arrange = false;
	break;
default:
	std::cout << "Ошибка, попробуйте еще раз\n";
	DeleteMatrix(arr, rows, cols);
	return;
}

InsertionSort(arr, rows, cols, arrange);

std::cout << "\nОтсортированная матрица:\n";
PrintMatrix(arr, rows, cols);


DeleteMatrix(arr, rows, cols);
}

int main() {
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	srand(static_cast<unsigned int>(time(0)));


	int choice;
	std::cout << "С каким типом вы хотите работать 1 - цeлочисленный, 2 - дробный, 3 - символьный \n";
	std::cin >> choice;


	switch (choice) {
	case 1:
		RunProgram<int>();
		break;
	case 2: 
		RunProgram<double>();
		break;
	case 3: 
		RunProgram<char*>();
		break;
	default:
		std::cout << "Ошибка";
	}
	
		return 0;
	
}
