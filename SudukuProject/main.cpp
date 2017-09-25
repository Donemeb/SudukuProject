#include <iostream>
#include <string>
#include "suduku.cpp"

int strtoInt(char str[]);
int main(int argc, char *argv[]) {
	/*	if (argc <= 1) {
	std::cout <<"argc:0 --pls put in something";
	}
	else if (argc == 2) {
	std::cout << "start generation";

	}
	else {
	std::cout << "argc:" << argc << " --not do";
	}*/
	int num;

	if (argc != 3) {
		std::cout << "input error: should be -c positive int or -s filename" << std::endl;
		return 0;
	}
	else {
		suduku sudu;
		if (strcmp(argv[1], "-c") == 0) {
			num = strtoInt(argv[2]);
			if (num < 0) {
				std::cout << "input error: should be -c positive int" << std::endl;
				return 0;
			}
			sudu.sudu_generation(num, 5, "suduku.txt");
		}
		else if (strcmp(argv[1], "-s") == 0) {
			sudu.sudu_solve(argv[2]);
		}
	}
	return 0;
}
int strtoInt(char str[]) {
	int sum = 0;
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i]<'0' | str[i]>'9') {
			return -1;
		}
		else {
			sum = sum * 10 + str[i] - '0';
		}
	}
	return sum;
}