#include <fstream>
#include <iostream>

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

		std::cout << "gene begin" << "\n";
		sudu_out.open(sudu_out_string);
		//	sudu_out << "test";

		//	sudu_generation_init(first_num);
		sudu_gene_begin(num, first_num);
		//	sudu_generation_loop(0, num);//第一个数据结构中的数据,起点
		sudu_out.close();

		std::cout << "gene end" << "\n";

	}

	void sudu_solve(std::ofstream sudo_in) {
		//	sudu_solve_init(sudo_in);
		sudu_solve_begin(1, 1);//num 文件中的待解数独局的数目，xx 文件数据局保存位置
	}

private:
	std::ofstream sudu_out;
	int gene_row[9] = { 0 };
	int gene_hasput[9] = { 0 };
	int gene_33[81] = { 0 };
	int sudu[9 * 9] = { 0 };//ATTENTION
							/*	void sudu_generation_init(int first_num) {
							init the random of num(just small to large is ok, random list of the num position
							}*/
	void sudu_gene_begin(int num, int first_num) {
		int x = 0;

		std::cout << "gene begin begin" << "\n";
		sudu_gene_loop(0, x, num);
		std::cout << "gene begin end" << "\n";
	}
	void sudu_gene_loop(int order, int & now_num, int target_num) {//int order = (num-1)*10+(depth-1) - -| 
																   //如果now_num==target_num,不做任何操作 //如果大于，报错
		int canset = 0;
		int depth = order % 9;
		int num = (order - depth) / 9;//ATTENTION 是否可以直接除
		int x1 = 0400;
		//		sudu_out << "loop ! 2: " << order << " " << num << " " << depth << " " << *now_num << " " << target_num << "\n";
		if (now_num == target_num) return;
		//sudu_to_file();
		canset = gene_row[num] | gene_hasput[depth] | gene_33[order];
		for (int i = 1; i<10; i++) {

			if (!(canset & x1)) {
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
				gene_row[num] = gene_row[num] | x1;

				gene_hasput[depth] = gene_hasput[depth] | x1;

				if (depth == 0) {
					if (i<= 3) {
						gene_33[num * 9 + 1] |= 0700;
						gene_33[num * 9 + 2] |= 0700;
					}
					else if (i <= 6) {
						gene_33[num * 9 + 1] |= 0070;
						gene_33[num * 9 + 2] |= 0070;
					}
					else if (i <= 9) {
						gene_33[num * 9 + 1] |= 0007;
						gene_33[num * 9 + 2] |= 0007;
					}
				}
				else if (depth == 1) {
					if (i <= 3) {
						gene_33[num * 9 + 2] |= 0700;
					}
					else if (i <= 6) {
						gene_33[num * 9 + 2] |= 0070;
					}
					else if (i <= 9) {
						gene_33[num * 9 + 2] |= 0007;
					}
				}
				else if (depth == 3) {
					if (i <= 3) {
						gene_33[num * 9 + 4] |= 0700;
						gene_33[num * 9 + 5] |= 0700;
					}
					else if (i <= 6) {
						gene_33[num * 9 + 4] |= 0070;
						gene_33[num * 9 + 5] |= 0070;
					}
					else if (i <= 9) {
						gene_33[num * 9 + 4] |= 0007;
						gene_33[num * 9 + 5] |= 0007;
					}
				}
				else if (depth == 4) {
					if (i <= 3) {
						gene_33[num * 9 + 5] |= 0700;
					}
					else if (i <= 6) {
						gene_33[num * 9 + 5] |= 0070;
					}
					else if (i <= 9) {
						gene_33[num * 9 + 5] |= 0007;
					}
				}
				else if (depth == 6) {
					if (i <= 3) {
						gene_33[num * 9 + 7] |= 0700;
						gene_33[num * 9 + 8] |= 0700;
					}
					else if (i <= 6) {
						gene_33[num * 9 + 7] |= 0070;
						gene_33[num * 9 + 8] |= 0070;
					}
					else if (i <= 9) {
						gene_33[num * 9 + 7] |= 0007;
						gene_33[num * 9 + 8] |= 0007;
					}
				}
				else if (depth == 7) {
					if (i <= 3) {
						gene_33[num * 9 + 8] |= 0700;
					}
					else if (i <= 6) {
						gene_33[num * 9 + 8] |= 0070;
					}
					else if (i <= 9) {
						gene_33[num * 9 + 8] |= 0007;
					}
				}
				sudu_gene_loop(order + 1, now_num, target_num);

				if (now_num == target_num) return;

				//ATTENTION 是否考虑回退模式？栈存储？ 而不是再计算一遍 
				sudu[depth * 9 + i - 1] = 0;//放入数据表
												  //更新冲突表 
				gene_row[num] = gene_row[num] & (~x1);
				gene_hasput[depth] = gene_hasput[depth] & (~x1);
				if (depth == 0) {
					if (i <= 3) {
						gene_33[num * 9 + 1] &= 0077;
						gene_33[num * 9 + 2] &= 0077;
					}
					else if (i <= 6) {
						gene_33[num * 9 + 1] &= 0707;
						gene_33[num * 9 + 2] &= 0707;
					}
					else if (i <= 9) {
						gene_33[num * 9 + 1] &= 0770;
						gene_33[num * 9 + 2] &= 0770;
					}
				}
				else if (depth == 1) {
					if (i <= 3) {
						gene_33[num * 9 + 2] &= 0077;
					}
					else if (i <= 6) {
						gene_33[num * 9 + 2] &= 0707;
					}
					else if (i <= 9) {
						gene_33[num * 9 + 2] &= 0770;
					}
				}
				else if (depth == 3) {
					if (i <= 3) {
						gene_33[num * 9 + 4] &= 0077;
						gene_33[num * 9 + 5] &= 0077;
					}
					else if (i <= 6) {
						gene_33[num * 9 + 4] &= 0707;
						gene_33[num * 9 + 5] &= 0707;
					}
					else if (i <= 9) {
						gene_33[num * 9 + 4] &= 0770;
						gene_33[num * 9 + 5] &= 0770;
					}
				}
				else if (depth == 4) {
					if (i <= 3) {
						gene_33[num * 9 + 5] &= 0077;
					}
					else if (i <= 6) {
						gene_33[num * 9 + 5] &= 0707;
					}
					else if (i <= 9) {
						gene_33[num * 9 + 5] &= 0770;
					}
				}
				else if (depth == 6) {
					if (i <= 3) {
						gene_33[num * 9 + 7] &= 0077;
						gene_33[num * 9 + 8] &= 0077;
					}
					else if (i <= 6) {
						gene_33[num * 9 + 7] &= 0707;
						gene_33[num * 9 + 8] &= 0707;
					}
					else if (i <= 9) {
						gene_33[num * 9 + 7] &= 0770;
						gene_33[num * 9 + 8] &= 0770;
					}
				}
				else if (depth == 7) {
					if (i <= 3) {
						gene_33[num * 9 + 8] &= 0077;
					}
					else if (i <= 6) {
						gene_33[num * 9 + 8] &= 0707;
					}
					else if (i <= 9) {
						gene_33[num * 9 + 8] &= 0770;
					}
				}
				sudu[depth * 9 + i - 1] = 0; //后期可删 

			}
			x1 = x1 / 2;
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
			std::cout << sudu[i] << ' ';
			if (j == 8) {
				j = -1;
				sudu_out << '\n';
				std::cout << std::endl;
			}
			j++;
		}
		sudu_out << '\n';
		std::cout << "fenhang " << std::endl;

	}
	char* sudu_to_string() {	//输入数独表，返回该数独表的字符串格式
		char * x;
		return x;
	}
	void sudu_solve_init(std::ofstream sudu_in) {
		//读入文件，保存数据到某位置
	}
	void sudu_solve_begin(int num, int x) {
		for (int i = 0; i < num; i++) {
			sudu_solve_begin_init();//包括将表移到指定位置，填入可填的数字，设置回溯顺序
			sudu_solve_loop(x);//开始解题
		}
	}
	void sudu_solve_loop(int x) {
		//如果该格是最高一格且无可用解，提示无解并退出
		//如果该格标记为重置，更新可用数据表并设置开始指针
		//如果该格可用解到最末了，标记，sudo_solve_loop()上一个
		/*
		·如果该格是最后一格，#check,测试用，输出结果并退出
		else 标记下一个可用解 sudu_solve_loop 下一个
		*/
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