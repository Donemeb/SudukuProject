#include <fstream>
#include <iostream>
#include <time.h>

struct sudu_num {
	int num = 0;
	int flush = 0;
	int order[10] = { 1,2,3,4,5,6,7,8,9,0 };
	int *now = order;
};

struct sudo_grid {
	int position = -1;
	int flush = 0;
	int order[10] = { 1,2,3,4,5,6,7,8,9,0 };
	int *now = order;

};
class suduku {
public:
	void sudu_generation(int num, int first_num, char sudu_out_string[]) {
		/*
		num between 0-int-1, first_num between 1-9
		sudu_out check if useful, if can write
		*/

		sudu_out.open(sudu_out_string);
		sudu_gene_init(first_num);
		sudu_gene_begin(num, first_num);
		//	sudu_generation_loop(0, num);//第一个数据结构中的数据,起点
		sudu_out.close();


	}

	void sudu_solve(char sudu_in_string[]) {	//	错误处理..
		char buf[20];
		sudu_in.open(sudu_in_string);
		sudu_out.open("suduout.txt");
		do {
			for (int i = 0; i < 9; i++) {
				sudu_in.getline(buf, 20);
				sscanf_s(buf, "%d %d %d %d %d %d %d %d %d", &sudu[i*9],&sudu[i*9+1], &sudu[i*9 + 2], &sudu[i*9 + 3], &sudu[i*9 + 4], &sudu[i*9 + 5], &sudu[i*9 + 6], &sudu[i*9 + 7], &sudu[i*9 + 8]);
			}
			sudu_to_file();
			sudu_solve_begin();
		}while (sudu_in.getline(buf, 20));
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
	int x1[9] = {0400,0200,0100,0040,0020,0010,0004,0002,0001};


	void print_arr_rand() {
		sudu_out << "rand_num_order" << std::endl;
		for (int i = 0; i < 9; i++) {
			sudu_out << rand_num_order[i] << " ";
		}
		sudu_out << std::endl;
		sudu_out << "rand_posi_order" << std::endl;
		for (int i = 0; i < 81; i++) {
			for (int j = 0; j < 9; j++) {
				sudu_out << rand_posi_order[i*9+j] << " ";
			}
			sudu_out << std::endl;
		}
	}

	void sudu_gene_init(int first_num) {
		int i = 0;
		srand(clock());
		gene_33[0] = 0377;
		for (i = 0; i < 81; i++) {
			sudu_rand(&rand_posi_order[i * 9], 1, 9);
		}
		sudu_rand(rand_num_order, 0, 8);
		for (i = 0; rand_num_order[i] != first_num-1; i++);
		rand_num_order[i] = rand_num_order[0];
		rand_num_order[0] = first_num-1;
	}

	void sudu_rand(int arr[], int begin, int end) {
		int x = 0,k;
		for (int i = end; i >= begin; i--, x++) {
			arr[x] = i;
		}
		for (int i = 0; i < x; i++) {
			k = rand() % x;
			swap(arr[i], arr[k]);
		}
	}

	void swap(int & a, int & b) {
		int c;
		c = a;
		a = b;
		b = c;
	}

	void sudu_gene_begin(int num, int first_num) {
		int x = 0;
		
		sudu_gene_loop(0, x, num);
	}
	void sudu_gene_loop(int order, int & now_num, int target_num) {//int order = (num-1)*10+(depth-1) - -| 
																   //如果now_num==target_num,不做任何操作 //如果大于，报错
		int canset = 0;
		int depth = order % 9;
		int num = rand_num_order[(order - depth) / 9];//ATTENTION 是否可以直接除
		int order_num = (order - depth) / 9;
		int i;
		//		sudu_out << "loop ! 2: " << order << " " << num << " " << depth << " " << *now_num << " " << target_num << "\n";
		if (now_num == target_num) return;
		//sudu_to_file();
		canset = gene_row[num] | gene_hasput[depth] | gene_33[order];
		for (int i1 = 1; i1<10; i1++) {
			i = rand_posi_order[order * 9 + i1 - 1];
			if (!(canset & x1[i-1])) {
				sudu[depth * 9 + i - 1] = num + 1;//放入数据表
												  //sudu_to_file();
				if (order == 80) {
					check();//检查
					sudu_to_file();
					sudu[depth * 9 + i - 1] = 0;
					now_num++;
					//	sudu_out << now_num;
					//输出到文件 //ATTENTION 考虑缓存、效率 
				}
				//更新冲突表 
				gene_row[num] = gene_row[num] | x1[i - 1];

				gene_hasput[depth] = gene_hasput[depth] | x1[i - 1];

				if (depth == 0) {
					if (i <= 3) {
						gene_33[order_num * 9 + 1] |= 0700;
						gene_33[order_num * 9 + 2] |= 0700;
					}
					else if (i <= 6) {
						gene_33[order_num * 9 + 1] |= 0070;
						gene_33[order_num * 9 + 2] |= 0070;
					}
					else if (i <= 9) {
						gene_33[order_num * 9 + 1] |= 0007;
						gene_33[order_num * 9 + 2] |= 0007;
					}
				}
				else if (depth == 1) {
					if (i <= 3) {
						gene_33[order_num * 9 + 2] |= 0700;
					}
					else if (i <= 6) {
						gene_33[order_num * 9 + 2] |= 0070;
					}
					else if (i <= 9) {
						gene_33[order_num * 9 + 2] |= 0007;
					}
				}
				else if (depth == 3) {
					if (i <= 3) {
						gene_33[order_num * 9 + 4] |= 0700;
						gene_33[order_num * 9 + 5] |= 0700;
					}
					else if (i <= 6) {
						gene_33[order_num * 9 + 4] |= 0070;
						gene_33[order_num * 9 + 5] |= 0070;
					}
					else if (i <= 9) {
						gene_33[order_num * 9 + 4] |= 0007;
						gene_33[order_num * 9 + 5] |= 0007;
					}
				}
				else if (depth == 4) {
					if (i <= 3) {
						gene_33[order_num * 9 + 5] |= 0700;
					}
					else if (i <= 6) {
						gene_33[order_num * 9 + 5] |= 0070;
					}
					else if (i <= 9) {
						gene_33[order_num * 9 + 5] |= 0007;
					}
				}
				else if (depth == 6) {
					if (i <= 3) {
						gene_33[order_num * 9 + 7] |= 0700;
						gene_33[order_num * 9 + 8] |= 0700;
					}
					else if (i <= 6) {
						gene_33[order_num * 9 + 7] |= 0070;
						gene_33[order_num * 9 + 8] |= 0070;
					}
					else if (i <= 9) {
						gene_33[order_num * 9 + 7] |= 0007;
						gene_33[order_num * 9 + 8] |= 0007;
					}
				}
				else if (depth == 7) {
					if (i <= 3) {
						gene_33[order_num * 9 + 8] |= 0700;
					}
					else if (i <= 6) {
						gene_33[order_num * 9 + 8] |= 0070;
					}
					else if (i <= 9) {
						gene_33[order_num * 9 + 8] |= 0007;
					}
				}
				sudu_gene_loop(order + 1, now_num, target_num);

				if (now_num == target_num) return;

				//ATTENTION 是否考虑回退模式？栈存储？ 而不是再计算一遍 
				sudu[depth * 9 + i - 1] = 0;//放入数据表
												  //更新冲突表 
				gene_row[num] = gene_row[num] & (~x1[i - 1]);
				gene_hasput[depth] = gene_hasput[depth] & (~x1[i - 1]);
				if (depth == 0) {
					if (i <= 3) {
						gene_33[order_num * 9 + 1] &= 0077;
						gene_33[order_num * 9 + 2] &= 0077;
					}
					else if (i <= 6) {
						gene_33[order_num * 9 + 1] &= 0707;
						gene_33[order_num * 9 + 2] &= 0707;
					}
					else if (i <= 9) {
						gene_33[order_num * 9 + 1] &= 0770;
						gene_33[order_num * 9 + 2] &= 0770;
					}
				}
				else if (depth == 1) {
					if (i <= 3) {
						gene_33[order_num * 9 + 2] &= 0077;
					}
					else if (i <= 6) {
						gene_33[order_num * 9 + 2] &= 0707;
					}
					else if (i <= 9) {
						gene_33[order_num * 9 + 2] &= 0770;
					}
				}
				else if (depth == 3) {
					if (i <= 3) {
						gene_33[order_num * 9 + 4] &= 0077;
						gene_33[order_num * 9 + 5] &= 0077;
					}
					else if (i <= 6) {
						gene_33[order_num * 9 + 4] &= 0707;
						gene_33[order_num * 9 + 5] &= 0707;
					}
					else if (i <= 9) {
						gene_33[order_num * 9 + 4] &= 0770;
						gene_33[order_num * 9 + 5] &= 0770;
					}
				}
				else if (depth == 4) {
					if (i <= 3) {
						gene_33[order_num * 9 + 5] &= 0077;
					}
					else if (i <= 6) {
						gene_33[order_num * 9 + 5] &= 0707;
					}
					else if (i <= 9) {
						gene_33[order_num * 9 + 5] &= 0770;
					}
				}
				else if (depth == 6) {
					if (i <= 3) {
						gene_33[order_num * 9 + 7] &= 0077;
						gene_33[order_num * 9 + 8] &= 0077;
					}
					else if (i <= 6) {
						gene_33[order_num * 9 + 7] &= 0707;
						gene_33[order_num * 9 + 8] &= 0707;
					}
					else if (i <= 9) {
						gene_33[order_num * 9 + 7] &= 0770;
						gene_33[order_num * 9 + 8] &= 0770;
					}
				}
				else if (depth == 7) {
					if (i <= 3) {
						gene_33[order_num * 9 + 8] &= 0077;
					}
					else if (i <= 6) {
						gene_33[order_num * 9 + 8] &= 0707;
					}
					else if (i <= 9) {
						gene_33[order_num * 9 + 8] &= 0770;
					}
				}
				sudu[depth * 9 + i - 1] = 0; //后期可删 

			}
		}

		/*
		填入该数据的下一个可用数据可能到N*N表

		*/
		/*
		如果这是最后一个数据了
		//整体check 前期验证使用， 后期可删去
		表正确，输出到文件 //PS:考虑缓存，一起输出以提高效率
		now_num += 1;
		else
		更新下一个数据的可用表
		sudu_generation_loop() 下一个数据
		*/

	}
	void sudu_to_file() {
		for (int i = 0, j = 0; i < 81; i++) {
			sudu_out << sudu[i] << ' ';
		//	std::cout << sudu[i] << ' ';
			if (j == 8) {
				j = -1;
				sudu_out << '\n';
		//		std::cout << std::endl;
			}
			j++;
		}
	//	std::cout << "fenhang " << std::endl;
		sudu_out << '\n';
	}


	void sudu_solve_begin() {
		int x = 0;
		sudu_solve_loop(0, x);
	}
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
			}
		}
	}
	int sudu_insert(int posi, int num) {
		int block, col, row, x, y;
		x = posi % 9;
		for (int i = 0; i < 9; i++) {
			if (sudu[i * 9 + x] == num) {
				return 0;
			}
		}
		y = (posi - x) / 9;
		for (int i = 0; i < 9; i++) {
			if (sudu[y * 9 + i] == num) {
				return 0;
			}
		}
		block = sudu_block_num(posi);
		col = block % 3;
		row = (block - col) / 3;
		for (int i = col*3; i < col * 3+3; i++) {
			for (int j = row*3; j < row * 3+3; j++) {
				if (sudu[j * 9 + i] == num) return 0;
			}
		}
		return 1;
	}
	int sudu_block_num(int posi) {
		int col = posi % 9;
		int row = (posi - col) / 9;
		col = (col - col % 3) / 3;
		row = (row - row % 3) / 3;
		return row * 3 + col;
	}
	void sudu_solve_begin_init() {
		//包括将表移到指定位置，填入可填的数字，设置回溯顺序
	}
	void sudu_solve_fillin() {
		//对数据的可用数据为1的值直接填入。
		//考虑多次生成数据并填入直到无法确定
	}
	void check() {

	}

};