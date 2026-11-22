#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

void EnterStr(char* str) {
	std::cin.getline(str, 301);
}

bool isPalindrom(char* word) {
	char* right;
	char* left;
	size_t len = strlen(word);
		right = word + len - 1;
		left = word;
			while(left<right){
		if (*left != *right) {
			return false;
		}
		++left;
		--right;
	}
	return true;
}


int ChoosePalidrom(char* str, char* separator, char* words[]) {
	int count = 0;
	char* word_ptr = strtok(str, separator);
	while (word_ptr!=NULL) {
		if (isPalindrom(word_ptr)) {
			words[count] = word_ptr;
			++count;
		}
		word_ptr = strtok(NULL, separator);
	}
	return count;
}

void AddWord(char* newstr, char* words[], int count) {
	newstr[0] = '\0';
	for (int i = 0; i < count; ++i) {
		strcat(newstr, words[i]);
		if (i < count - 1) {
			strcat(newstr, " ");
		}
	}
}

void Sorting(char* words[], int count) {
	for (int i = 0; i < count - 1; ++i) {
		bool swap = false;
		for (int j = 0; j < count - i - 1; ++j) {
			if (strlen(words[j]) > strlen(words[j + 1])) {
				std::swap(words[j], words[j + 1]);
				swap = true;
			}
		}
		if (swap == false) {
			break;
		}
	}
}


int main() {
	char str[301];
	std::cout << "Enter str: \n";
	EnterStr(str);
	char separator[15];
	std::cout << " Enter separators: \n";
		EnterStr(separator);
		char newstr[301];
		char* words[150];
		int count = ChoosePalidrom(str, separator, words );

		if (count == 0) {
			std::cout << "No palindrome words found in the string.\n";
			return 0;
		}

		Sorting(words, count);
		AddWord(newstr, words, count);
			std::cout <<"Polindroms: "<< newstr;

	return 0;
}
