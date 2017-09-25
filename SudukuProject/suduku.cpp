// sudoku.cpp: �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<time.h>

using namespace std;


class sudoku {

	int array[9][9];

public:
	sudoku() {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				array[i][j] = 0;
			}
		}
		array[0][0] = 7;//���õ�һ����Ϊ7
	}
	sudoku(int array[9][9]) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				this->array[i][j] = array[i][j];
			}
		}
	}

	bool isinraw(int num, int raw_num);//�����Ƿ���һ�����Ѵ���
	bool isincolumn(int num, int c_num);//�����Ƿ���һ�����Ѵ���
	bool isinblock(int num, int blocknum);//�����Ƿ���3*3��С�����Ѵ���
	int insert(int num, int blocknum, int marked[]);
	int insert(int num, int x, int y, int marked[]);
	void printsudoku();
	bool del(int judge, int blocknum, int pos);
};

void getsudoku(char * string);
void solve(sudoku sudo, int x[], int y[], int total, int & count);
bool isAllNum(char * string);
void produce(int total, int nums[], int block_num, int & count_total, int count_nums, sudoku s);


int main(int argc, char* argv[])
{
	int total = 0;
	char * s1, *s2;
	s1 = "-c";//���������վ�
	s2 = "-s";//������

	srand((unsigned)(time(NULL)));//���������

	int nums[9] = { 7,1,2,3,4,5,6,8,9 };
	int count_total = 0;
	sudoku s;
	if (argc < 3) {
		cout << "the number of arguments is at least two" << endl;
		return 0;
	}
	if (argc > 3) cout << "too many arguments " << endl;
	if (strcmp(argv[1], s1) == 0) {//���������վ�
		if (!isAllNum(argv[2])) {
			cout << "error: argument is not a positive integer" << endl;
			return 0;
		}
		total = atoi(argv[2]);
		if (total <= 0) {
			cout << "error: argument is not a positive integer" << endl;
			return 0;
		}
		produce(total, nums, 1, count_total, 0, s);

	}
	else if (strcmp(argv[1], s2) == 0) {//������
		getsudoku(argv[2]);
	}
	else {
		cout << "no such instruction" << endl;
		return 0;
	}


	cout << "end" << endl;
	return 0;
}

void getsudoku(char * string) {
	int sudo[9][9];
	int x[81];
	int y[81];
	int count = 0, total = 0;
	fstream f(string);
	if (!f) {
		cout << string << " can't open" << endl;
		return;
	}
	while (!f.eof()) {

		count = 0;
		total = 0;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				f >> sudo[i][j];
				if (f.eof()) return;
				if (sudo[i][j] == 0) {
					x[total] = i;
					y[total] = j;
					total++;
				}
			}
		}
		sudoku s(sudo);
		solve(sudo, x, y, total, count);
	}


}

void solve(sudoku sudo, int x[], int y[], int total, int & count) {
	int marked[9] = { 0 };
	int new_count = count;
	while (true) {

		int now = sudo.insert(1, x[new_count], y[new_count], marked);

		if (now < 0) return;
		else marked[now - 1] = 1;

		if (new_count == total - 1) {
			//cout << count<<" "<<new_count << endl;
			sudo.printsudoku();
			return;
		}
		count = new_count + 1;
		solve(sudo, x, y, total, count);
		if (count == total - 1) return;
		sudo.del(1, x[new_count], y[new_count]);
	}

}

bool isAllNum(char * string) {//֧������
	if (*string == '+') string++;
	while (*string != '\0') {
		if ((*string - '0') > 9 || (*string - '0') < 0) return false;
		string++;
	}
	return true;
}
void produce(int total, int nums[], int block_num, int & count_total, int count_nums, sudoku s) {
	int marked[9] = { 0 };//����Ѿ��Թ���λ��
	int new_block_num, new_count_nums;

	while (true) {
		new_block_num = block_num + 1;
		new_count_nums = count_nums;

		int now = s.insert(nums[new_count_nums], new_block_num, marked);

		if (now <0) return;
		else marked[now] = 1;

		if (new_block_num == 9) {
			if (new_count_nums < 8) {
				new_count_nums = count_nums + 1;
				new_block_num = 0;
			}
			else {//��д�����һ��
				count_total++;
				s.printsudoku();//��ӡ����
				s.del(0, new_block_num, now);
				return;
			}
		}
		produce(total, nums, new_block_num, count_total, new_count_nums, s);
		if (count_total == total) return;
		s.del(0, new_block_num, now);
	}
}


//function in sudoku
bool sudoku::isinraw(int num, int raw_num) {//��
	for (int i = 0; i < 9; i++) {
		if (this->array[raw_num][i] == num) return true;
	}
	return false;
}
bool sudoku::isincolumn(int num, int c_num) {//��
	for (int i = 0; i < 9; i++) {
		if (this->array[i][c_num] == num) return true;
	}
	return false;
}
bool sudoku::isinblock(int num, int blocknum) {//��
	int x, y;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			x = i + ((blocknum - 1) / 3) * 3;
			y = j + (((blocknum - 1) % 3) * 3);
			if (this->array[x][y] == num) return true;
		}
	}
	return false;
}
int sudoku::insert(int num, int blocknum, int marked[]) {
	//�������һ��0-8����
	int pos[9] = { 0,1,2,3,4,5,6,7,8 };
	//int mark[9] = { 0 };
	//int pos[9] = { 0 };


	/*for (int i = 0; i < 9; i++) {
	int count = 0;
	int move = (rand() % (9-i) + 1);

	for (int j = 0; j < 9; j++) {
	if (mark[j]==0) count++;
	if (count == move) {
	pos[i] = pos1[j];
	mark[j] = 1;
	break;
	}
	}
	//cout << pos[i] << " ";
	}
	//cout << endl;*/

	int x;
	int y;
	for (int i = 0; i < 9; i++) {
		x = (pos[i] / 3) + ((blocknum - 1) / 3) * 3;
		y = (pos[i] % 3) + (((blocknum - 1) % 3) * 3);
		if (this->array[x][y] != 0 || marked[pos[i]] == 1 || this->isinraw(num, x) || this->isincolumn(num, y)) continue;
		else {
			this->array[x][y] = num;
			return pos[i];
		}
	}
	return -1;
}

int sudoku::insert(int n, int x, int y, int marked[]) {

	int num[9] = { 1,2,3,4,5,6,7,8,9 };
	int blocknum = x / 3 * 3 + y / 3 + 1;

	for (int i = 0; i < 9; i++) {
		if (marked[num[i] - 1] == 1 || this->isinblock(num[i], blocknum) || this->isincolumn(num[i], y) || this->isinraw(num[i], x)) continue;
		else {
			this->array[x][y] = num[i];
			return num[i];
		}
	}
	return -1;
}

void sudoku::printsudoku() {
	ofstream f;
	f.open("sudoku.txt", ios::app);
	if (!f) {
		cout << "sudoku.txt can't open" << endl;
		return;
	}
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (j == 8) f << this->array[i][j];
			else f << this->array[i][j] << " ";
			//cout << this->array[i][j] << " ";
		}
		f << endl;
	}
	f << endl;
	f.close();


}
bool sudoku::del(int judge, int blocknum, int pos) {
	if (judge == 1) {
		this->array[blocknum][pos] = 0;
		return true;
	}
	int x;
	int y;
	x = (pos / 3) + ((blocknum - 1) / 3) * 3;
	y = (pos % 3) + (((blocknum - 1) % 3) * 3);
	this->array[x][y] = 0;
	return true;
}

