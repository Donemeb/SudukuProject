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
		//	sudu_generation_loop(0, num);//��һ�����ݽṹ�е�����,���
		sudu_out.close();

		std::cout << "gene end" << "\n";

	}

	void sudu_solve(std::ofstream sudo_in) {
		//	sudu_solve_init(sudo_in);
		sudu_solve_begin(1, 1);//num �ļ��еĴ��������ֵ���Ŀ��xx �ļ����ݾֱ���λ��
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
																   //���now_num==target_num,�����κβ��� //������ڣ�����
		int canset = 0;
		int depth = order % 9;
		int num = (order - depth) / 9;//ATTENTION �Ƿ����ֱ�ӳ�
		int x1 = 0400;
		//		sudu_out << "loop ! 2: " << order << " " << num << " " << depth << " " << *now_num << " " << target_num << "\n";
		if (now_num == target_num) return;
		//sudu_to_file();
		canset = gene_row[num] | gene_hasput[depth] | gene_33[order];
		for (int i = 1; i<10; i++) {

			if (!(canset & x1)) {
				sudu[depth * 9 + i - 1] = num + 1;//�������ݱ�
												  //sudu_to_file();
				if (order == 80) {
					check();//���
					sudu_to_file();
					sudu[depth * 9 + i - 1] = 0;
					now_num++;
					//	sudu_out << now_num;
					//������ļ� //ATTENTION ���ǻ��桢Ч�� 
				}
				//���³�ͻ�� 
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

				//ATTENTION �Ƿ��ǻ���ģʽ��ջ�洢�� �������ټ���һ�� 
				sudu[depth * 9 + i - 1] = 0;//�������ݱ�
												  //���³�ͻ�� 
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
				sudu[depth * 9 + i - 1] = 0; //���ڿ�ɾ 

			}
			x1 = x1 / 2;
		}

		/*
		��������ݵ���һ���������ݿ��ܵ�N*N��

		*/
		/*
		����������һ��������
		//����check ǰ����֤ʹ�ã� ���ڿ�ɾȥ
		����ȷ��������ļ� //PS:���ǻ��棬һ����������Ч��
		now_num += 1;
		else
		������һ�����ݵĿ��ñ�
		sudu_generation_loop() ��һ������
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
	char* sudu_to_string() {	//�������������ظ���������ַ�����ʽ
		char * x;
		return x;
	}
	void sudu_solve_init(std::ofstream sudu_in) {
		//�����ļ����������ݵ�ĳλ��
	}
	void sudu_solve_begin(int num, int x) {
		for (int i = 0; i < num; i++) {
			sudu_solve_begin_init();//���������Ƶ�ָ��λ�ã������������֣����û���˳��
			sudu_solve_loop(x);//��ʼ����
		}
	}
	void sudu_solve_loop(int x) {
		//����ø������һ�����޿��ý⣬��ʾ�޽Ⲣ�˳�
		//����ø���Ϊ���ã����¿������ݱ����ÿ�ʼָ��
		//����ø���ý⵽��ĩ�ˣ���ǣ�sudo_solve_loop()��һ��
		/*
		������ø������һ��#check,�����ã����������˳�
		else �����һ�����ý� sudu_solve_loop ��һ��
		*/
	}
	void sudu_solve_begin_init() {
		//���������Ƶ�ָ��λ�ã������������֣����û���˳��
	}
	void sudu_solve_fillin() {
		//�����ݵĿ�������Ϊ1��ֱֵ�����롣
		//���Ƕ���������ݲ�����ֱ���޷�ȷ��
	}
	void check() {

	}

};