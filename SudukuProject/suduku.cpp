// sudoku.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<time.h>

using namespace std;

<<<<<<< HEAD
		sudu_out.open(sudu_out_string);

		sudu_out << "can i write?1";
		sudu_gene_init(first_num);
		sudu_gene_begin(num, first_num);
		//	sudu_generation_loop(0, num);//第一个数据结构中的数据,起点
		sudu_to_file_flush();
		sudu_out.close();

	}

	void sudu_solve(char sudu_in_string[]) {	//	错误处理..
		char buf[20];
		bool ef = true;
		sudu_in.open(sudu_in_string);
		sudu_out.open("suduout.txt");
		do {
			for (int i = 0; i < 9; i++) {
				if (sudu_in.getline(buf, 20)) {
					sscanf_s(buf, "%d %d %d %d %d %d %d %d %d", &sudu[i * 9], &sudu[i * 9 + 1], &sudu[i * 9 + 2], &sudu[i * 9 + 3], &sudu[i * 9 + 4], &sudu[i * 9 + 5], &sudu[i * 9 + 6], &sudu[i * 9 + 7], &sudu[i * 9 + 8]);
				}
				else {
					ef = false;
				}
			}
			//	sudu_to_file();
			if (!ef) {
				break;
			}
			sudu_solve_begin();
		} while (sudu_in.getline(buf, 20));
		sudu_to_file_flush();
		sudu_in.close();
		sudu_out.close();
	}

private:
	std::ofstream sudu_out;
	std::ifstream sudu_in;

	int gene_row[9] = { 0 };
	int gene_hasput[9] = { 0 };
	int gene_33[81] = { 0 };
	int sudu[9 * 9] = { 0 };//ATTENTION
							/*	void sudu_generation_init(int first_num) {
							init the random of num(just small to large is ok, random list of the num position
							}*/
	int rand_posi_order[81 * 9];
	int rand_num_order[9];
	int x1[9] = { 0400,0200,0100,0040,0020,0010,0004,0002,0001 };
	char sudubuf[100000];
	int sudulen = 0;

	void print_arr_rand() {
		sudu_out << "rand_num_order" << std::endl;
=======

class sudoku {

	int array[9][9];

public:
	sudoku() {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				array[i][j] = 0;
			}
		}
		array[0][0] = 7;//设置第一个恒为7
	}
	sudoku(int array[9][9]) {
>>>>>>> a4cb8b50d5ad5b32eefe4a7d8ed90bf2ca0cf904
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
<<<<<<< HEAD
				sudu_out << rand_posi_order[i * 9 + j] << " ";
=======
				this->array[i][j] = array[i][j];
>>>>>>> a4cb8b50d5ad5b32eefe4a7d8ed90bf2ca0cf904
			}
		}
	}

<<<<<<< HEAD
	void sudu_gene_init(int first_num) {
		int i = 0;
		srand(clock());
		for (i = 0; i < 81; i++) {
			sudu_rand(&rand_posi_order[i * 9], 0, 8);
		}
		sudu_rand(rand_num_order, 0, 8);
		for (i = 0; rand_num_order[i] != first_num - 1; i++);
		rand_num_order[i] = rand_num_order[0];
		rand_num_order[0] = first_num - 1;
	}

	void sudu_rand(int arr[], int begin, int end) {
		int x = 0, k;
		for (int i = end; i >= begin; i--, x++) {
			arr[x] = i;
		}
		for (int i = 0; i < x; i++) {
			k = rand() % x;
			swap(arr[i], arr[k]);
		}
	}
=======
	bool isinraw(int num, int raw_num);//数字是否在一行中已存在
	bool isincolumn(int num, int c_num);//数字是否在一列中已存在
	bool isinblock(int num, int blocknum);//数字是否在3*3的小块中已存在
	int insert(int num, int blocknum, int marked[]);
	int insert(int num, int x, int y, int marked[]);
	void printsudoku();
	bool del(int judge, int blocknum, int pos);
};

void getsudoku(char * string);
void solve(sudoku sudo, int x[], int y[], int total, int & count);
bool isAllNum(char * string);
void produce(int total, int nums[], int block_num, int & count_total, int count_nums, sudoku s);
>>>>>>> a4cb8b50d5ad5b32eefe4a7d8ed90bf2ca0cf904


<<<<<<< HEAD
	void sudu_gene_begin(int num, int first_num) {
		int x = 0;

		sudu_gene_loop(0, x, num);
	}
	void sudu_gene_loop(int order, int & now_num, int target_num) {
		int canset = 0;
		int depth = order % 9;
		int order_num = order / 9;
		int num = rand_num_order[order_num];//ATTENTION 是否可以直接除
		int i;
		//		sudu_out << "loop ! 2: " << order << " " << num << " " << depth << " " << *now_num << " " << target_num << "\n";
		if (order == 0) {
			sudu[0] = num + 1;
			gene_row[num] = gene_row[num] | 0400;
			gene_hasput[depth] = gene_hasput[depth] | 0400;
			gene_33[0] = 0700;
			sudu_gene_loop(order + 1, now_num, target_num);
		}
		else {
			if (now_num == target_num) return;
			//	sudu_to_file();
			canset = gene_row[num] | gene_hasput[depth] | gene_33[order_num * 9 + depth / 3];
			for (int i1 = 1; i1 < 10; i1++) {
				i = rand_posi_order[order * 9 + i1 - 1];	//change the name of i
				if (!(canset & x1[i])) {
					//放入数据表
					//sudu_to_file();
					if (order == 80) {
						sudu[depth * 9 + i] = num + 1;
						sudu_to_file();
						sudu[depth * 9 + i] = 0;
						now_num++;
						return;
						//	sudu_out << now_num;
						//输出到文件 //ATTENTION 考虑缓存、效率 
					}
					//更新冲突表 
					sudu_insert_0(i, num, depth, order_num);

					sudu_gene_loop(order + 1, now_num, target_num);

					if (now_num == target_num) return;

					sudu_delete_0(i, num, depth, order_num);
				}
			}
=======
int main(int argc, char* argv[])
{
	int total = 0;
	char * s1, *s2;
	s1 = "-c";//生成数独终局
	s2 = "-s";//解数独

	srand((unsigned)(time(NULL)));//随机数种子

	int nums[9] = { 7,1,2,3,4,5,6,8,9 };
	int count_total = 0;
	sudoku s;
	if (argc < 3) {
		cout << "the number of arguments is at least two" << endl;
		return 0;
	}
	if (argc > 3) cout << "too many arguments " << endl;
	if (strcmp(argv[1], s1) == 0) {//生成数独终局
		if (!isAllNum(argv[2])) {
			cout << "error: argument is not a positive integer" << endl;
			return 0;
>>>>>>> a4cb8b50d5ad5b32eefe4a7d8ed90bf2ca0cf904
		}
		total = atoi(argv[2]);
		if (total <= 0) {
			cout << "error: argument is not a positive integer" << endl;
			return 0;
		}
		produce(total, nums, 1, count_total, 0, s);

	}
	else if (strcmp(argv[1], s2) == 0) {//解数独
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
<<<<<<< HEAD
	void sudu_delete_0(int i, int num, int depth, int order_num) {
		//ATTENTION 是否考虑回退模式？栈存储？ 而不是再计算一遍 
		sudu[depth * 9 + i] = 0;//放入数据表
								//更新冲突表 
		gene_row[num] = gene_row[num] & (~x1[i]);
		gene_hasput[depth] = gene_hasput[depth] & (~x1[i]);
		if (depth < 3) {
			if (i <= 2) {
				gene_33[order_num * 9 + 0] &= 0077;
			}
			else if (i <= 5) {
				gene_33[order_num * 9 + 0] &= 0707;
			}
			else if (i <= 8) {
				gene_33[order_num * 9 + 0] &= 0770;
			}
		}
		else if (depth < 6) {
			if (i <= 2) {
				gene_33[order_num * 9 + 1] &= 0077;
			}
			else if (i <= 5) {
				gene_33[order_num * 9 + 1] &= 0707;
			}
			else if (i <= 8) {
				gene_33[order_num * 9 + 1] &= 0770;
			}
		}

		else if (depth < 9) {
			if (i <= 2) {
				gene_33[order_num * 9 + 2] &= 0077;
			}
			else if (i <= 5) {
				gene_33[order_num * 9 + 2] &= 0707;
			}
			else if (i <= 8) {
				gene_33[order_num * 9 + 2] &= 0770;
			}
		}

		//	sudu[depth * 9 + i] = 0; //后期可删 
	}

	void sudu_insert_0(int i, int num, int depth, int order_num) {
		sudu[depth * 9 + i] = num + 1;
		gene_row[num] = gene_row[num] | x1[i];
		gene_hasput[depth] = gene_hasput[depth] | x1[i];
		if (depth < 3) {
			if (i <= 2) {
				gene_33[order_num * 9 + 0] |= 0700;
			}
			else if (i <= 5) {
				gene_33[order_num * 9 + 0] |= 0070;
			}
			else if (i <= 8) {
				gene_33[order_num * 9 + 0] |= 0007;
			}
		}
		else if (depth < 6) {
			if (i <= 2) {
				gene_33[order_num * 9 + 1] |= 0700;
			}
			else if (i <= 5) {
				gene_33[order_num * 9 + 1] |= 0070;
			}
			else if (i <= 8) {
				gene_33[order_num * 9 + 1] |= 0007;
			}
		}
		else if (depth < 8) {
			if (i <= 2) {
				gene_33[order_num * 9 + 2] |= 0700;
			}
			else if (i <= 5) {
				gene_33[order_num * 9 + 2] |= 0070;
			}
			else if (i <= 8) {
				gene_33[order_num * 9 + 2] |= 0007;
			}
		}
	}
	void sudu_to_file() {
		if (sudulen > 99800) {
			sudubuf[sudulen] = '\0';
			sudu_out << sudubuf;
			sudulen = 0;
		}
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 8; j++) {
				sudubuf[sudulen++] = sudu[i * 9 + j] + '0';
				sudubuf[sudulen++] = ' ';
=======
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
>>>>>>> a4cb8b50d5ad5b32eefe4a7d8ed90bf2ca0cf904
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

bool isAllNum(char * string) {//支持正号
	if (*string == '+') string++;
	while (*string != '\0') {
		if ((*string - '0') > 9 || (*string - '0') < 0) return false;
		string++;
	}
<<<<<<< HEAD
	void sudu_solve_loop(int order, int &num) {
		//如果该格是最高一格且无可用解，提示无解并退出
		//如果该格标记为重置，更新可用数据表并设置开始指针
		//如果该格可用解到最末了，标记，sudo_solve_loop()上一个
		/*
		·如果该格是最后一格，#check,测试用，输出结果并退出
		else 标记下一个可用解 sudu_solve_loop 下一个
		*/
		//		sudu_out << order << " " << num << "\n";
		if (sudu[order] != 0) {
			if (order == 80) {
				sudu_to_file();
				num = 1;
				return;
			}
			sudu_solve_loop(order + 1, num);
		}
		else {
			for (int i = 1; i < 10; i++) {
				//				sudu_out << "loop order:" << order << " i:" << i << "\n";
				//				sudu_to_file();
				if (num == 1) return;
				if (sudu_insert(order, i)) {
					sudu[order] = i;
					//					sudu_to_file();
					if (order == 80) {
						sudu_to_file();
						num = 1;
						return;
					}
					else {
						sudu_solve_loop(order + 1, num);
						sudu[order] = 0;
					}
				}
=======
	return true;
}
void produce(int total, int nums[], int block_num, int & count_total, int count_nums, sudoku s) {
	int marked[9] = { 0 };//标记已经试过的位置
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
			else {//填写至最后一个
				count_total++;
				s.printsudoku();//打印数独
				s.del(0, new_block_num, now);
				return;
>>>>>>> a4cb8b50d5ad5b32eefe4a7d8ed90bf2ca0cf904
			}
		}
		produce(total, nums, new_block_num, count_total, new_count_nums, s);
		if (count_total == total) return;
		s.del(0, new_block_num, now);
	}
}


//function in sudoku
bool sudoku::isinraw(int num, int raw_num) {//行
	for (int i = 0; i < 9; i++) {
		if (this->array[raw_num][i] == num) return true;
	}
	return false;
}
bool sudoku::isincolumn(int num, int c_num) {//列
	for (int i = 0; i < 9; i++) {
		if (this->array[i][c_num] == num) return true;
	}
	return false;
}
bool sudoku::isinblock(int num, int blocknum) {//块
	int x, y;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			x = i + ((blocknum - 1) / 3) * 3;
			y = j + (((blocknum - 1) % 3) * 3);
			if (this->array[x][y] == num) return true;
		}
<<<<<<< HEAD
		block = sudu_block_num(posi);
		col = block % 3;
		row = (block - col) / 3;
		for (int i = col * 3; i < col * 3 + 3; i++) {
			for (int j = row * 3; j < row * 3 + 3; j++) {
				if (sudu[j * 9 + i] == num) return 0;
			}
=======
	}
	return false;
}
int sudoku::insert(int num, int blocknum, int marked[]) {
	//随机生成一个0-8序列
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
>>>>>>> a4cb8b50d5ad5b32eefe4a7d8ed90bf2ca0cf904
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

