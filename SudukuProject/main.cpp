#include <iostream>
#include "suduku.cpp"
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
	suduku sudu;
	sudu.sudu_generation(1000000, 5, "suduku.txt");
//	sudu.sudu_solve("sudup.txt");
}