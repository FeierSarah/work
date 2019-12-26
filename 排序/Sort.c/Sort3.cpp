/* ********************************************************************************
* BY LEIDING
* 2019.10.21
******************************************************************************** */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <io.h>

#define NUM_INT_BIT 5
#define NUM_DEC_BIT 3
#define NUM_BIT (NUM_INT_BIT + NUM_DEC_BIT + 1)
#define NUM_A_LINE 10
#define MAX_READ_TIMES 99

void printl(double v[], int n) {
	char lformat[20] = { 0 };
	sprintf_s(lformat, 20, "%%.0%uf,", NUM_DEC_BIT);
	for (int i = 0; i < n; i++) {
		printf(lformat, v[i]);
		if (i % NUM_A_LINE == (NUM_A_LINE - 1))
			printf("\n");
	}
	printf("\n");
}

void pausel(double v[], int n) {
	printl(v, n);
	char c = getchar();
}

bool is_exist(const char fname[]) {
	return _access(fname, 0) == 0;
}

void nick(const char fpath[], char fname[]) {
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char ext[_MAX_EXT];
	_splitpath_s(fpath, drive, _MAX_DRIVE, dir, _MAX_DIR, fname, _MAX_FNAME, ext, _MAX_EXT);
}

void copy_file(const char sname[], const char dname[]) {
	FILE* sfl, * dfl;
	if (fopen_s(&sfl, sname, "r") == 0 && sfl && fopen_s(&dfl, dname, "w") == 0 && dfl) {
		char c;
		while (!feof(sfl)) {
			fread(&c, sizeof(char), 1, sfl);
			fwrite(&c, sizeof(char), 1, dfl);
		}
		fclose(sfl);
		fclose(dfl);
	}
	else
		printf("Copy %s to %s failed\n", sname, dname);
}

/* ********************************************************************************
* DATA
******************************************************************************** */

// 随机产生n个数
void rnd2l(double v[], int n) {
	int dec_size = (int)pow(10, NUM_DEC_BIT);
	srand((unsigned)time(NULL));
	for (int i = 0; i < n; i++) {
		v[i] = rand();
		v[i] += (rand() % dec_size) / (double)dec_size;
	}
}

// 随机产生n个数，并写入文件
void rnd2f(const char* fname, int n) {
	FILE* fl;
	if (fopen_s(&fl, fname, "w") == 0 && fl) {
		int dec_size = (int)pow(10, NUM_DEC_BIT);
		char lformat[20] = { 0 };
		sprintf_s(lformat, 20, "%%d.%%0%ud,", NUM_DEC_BIT);
		srand((unsigned)time(NULL));
		for (int i = 0; i < n; i++) {
			char s[NUM_BIT + 2] = { 0 };
			sprintf_s(s, NUM_BIT + 2, lformat, rand(), rand() % dec_size);
			fwrite(s, sizeof(char), strlen(s), fl);
			if (i % NUM_A_LINE == (NUM_A_LINE - 1))
				fwrite("\n", sizeof(char), 1, fl);
		}
		fclose(fl);
	}
	else
		printf("Cannot write file %s\n", fname);
}

/* ********************************************************************************
* INTERNAL SORT
******************************************************************************** */

// swap two numbers
void swap(double* pa, double* pb) {
	double c = *pa;
	*pa = *pb;
	*pb = c;
}

// BUBBLE SORT, O(n^2), stable
void bubbleSort(double s[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = n - 1; j > i; j--) {
			if (s[j] < s[j - 1])
				swap(&s[j], &s[j - 1]);
		}
	}
}

// BUBBLE SORT, improved
void bubbleSort1(double s[], int n) {
	bool flag; // if or not swap
	for (int i = 0; i < n - 1; i++) {
		flag = false;
		for (int j = n - 1; j > i; j--) {
			if (s[j] < s[j - 1]) {
				swap(&s[j], &s[j - 1]);
				flag = true;
			}
		}
		if (!flag)
			break;
	}
}

// SELECT SORT, O(n^2), unstable
void selectSort(double s[], int n) {
	for (int i = 0; i < n - 1; i++) {
		int minIndex = i;
		for (int j = i + 1; j < n; j++) {
			if (s[j] < s[minIndex])
				minIndex = j;
		}
		if (minIndex != i)
			swap(&s[i], &s[minIndex]);
	}
}

// INSERT SORT, O(n^2), stable
void insertSort(double s[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j > 0; j--) {
			if (s[j] < s[j - 1])
				swap(&s[j], &s[j - 1]);
			else
				break;
		}
	}
}

// SHELL SORT
void shellSort(double s[], int n) {
	int delta = n;
	while (true) {
		delta = delta / 2;
		for (int k = 0; k < delta; k++) {
			for (int i = k + delta; i < n; i += delta) {
				for (int j = i; j > k; j -= delta) {
					if (s[j] < s[j - delta])
						swap(&s[j], &s[j - delta]);
					else
						break;
				}
			}
		}
		if (delta == 1)
			break;
	}
}

// QUICK SORT
void quickSort(double s[], int p, int r) {
	if (p < r) {
		int i = p, j = r + 1;
		double x = s[p];
		while (true) {
			while (s[++i] < x && i < r);
			while (s[--j] > x&& j > 0);
			if (i >= j)
				break;
			swap(&s[i], &s[j]);
		}
		s[p] = s[j];
		s[j] = x;

		quickSort(s, p, j - 1);
		quickSort(s, j + 1, r);
	}
}

// MERGE SORT
void mergev(double c[], double d[], int l, int m, int r) {
	int i = l, j = m + 1, k = l;
	while ((i <= m) && (j <= r)) {
		if (c[i] <= c[j])
			d[k++] = c[i++];
		else
			d[k++] = c[j++];
	}

	if (i > m) {
		for (int q = j; q <= r; q++)
			d[k++] = c[q];
	}
	else {
		for (int q = i; q <= m; q++)
			d[k++] = c[q];
	}
}

void mergePass(double x[], double y[], int p, int n) {
	int i = 0;
	while (n > 2 * p && i <= (n - 2 * p)) {
		mergev(x, y, i, i + p - 1, i + 2 * p - 1);
		i = i + 2 * p;
	}

	if (i + p < n)
		mergev(x, y, i, i + p - 1, n - 1);
	else
		for (int j = i; j <= n - 1; j++)
			y[j] = x[j];
}

void mergeSort(double s[], int n) {
	double* b = new double[n] { 0 };
	int p = 1;
	while (p < n) {
		mergePass(s, b, p, n);
		p += p;
		mergePass(b, s, p, n);
		p += p;
	}
	delete[] b;
}

// HEAP SORT
void down2MaxHeap(double s[], int l, int r) {
	int child;
	int parent = l;
	while ((child = parent * 2 + 1) < r) {
		if ((child < r - 1) && (s[child] < s[child + 1]))
			child++;

		if (s[child] > s[parent])
			swap(&s[child], &s[parent]);
		else
			break;

		parent = child;
	}
}

void buildMaxHeap(double s[], int l, int r) {
	if (l >= r - 1)
		return;

	int parent = r / 2 - 1;
	while (parent >= 0) {
		down2MaxHeap(s, parent, r);
		parent--;
	}
}

void heapSort(double s[], int n) {
	buildMaxHeap(s, 0, n);
	int r = n;
	while (r > 1) {
		swap(&s[0], &s[--r]);
		down2MaxHeap(s, 0, r);
	}
}

/* ********************************************************************************
* OUTERNAL SORT
******************************************************************************** */

// 读取当前句柄开始的一个浮点数
double get_a_num(FILE* fl) {
	char buffer[NUM_BIT + 1]{ 0 };
	int k = 0;
	char c = 0;
	while (!feof(fl)) {
		fread(&c, sizeof(char), 1, fl);
		if (c == ',')
			break;
		else if ((c >= '0' && c <= '9') || c == '.')
			buffer[k++] = c;
	}
	if (k == 0)
		return -1;  // failed
	else
		return atof(buffer);
}

// 读取当前句柄开始的n个浮点数
int get_nums(FILE* fl, int n, double s[]) {
	int k = 0;
	for (int i = 0; i < n; i++) {
		double c = get_a_num(fl);
		if (c < 0)
			break;
		else
			s[k++] = c;
	}
	return k; // actual num
}


// SORT AND WRITE
void sort2f(const char fname[], double v[], int n) {
	FILE* fl;
	if (fopen_s(&fl, fname, "w") == 0 && fl) {
		quickSort(v, 0, n - 1);
		char lformat[20] = { 0 };
		sprintf_s(lformat, "%%.%df,", NUM_DEC_BIT);
		for (int i = 0; i < n; i++) {
			char s[NUM_BIT + 2] = { 0 };
			sprintf_s(s, NUM_BIT + 2, lformat, v[i]);
			fwrite(s, sizeof(char), strlen(s), fl);
			if (i % NUM_A_LINE == (NUM_A_LINE - 1))
				fwrite("\n", sizeof(char), 1, fl);
		}
		fclose(fl);
	}
	else
		printf("Cannot write a DAC file %s", fname);
}

// DEVIDE AND SORT, using QUICK SORT
// 子文件数限99个(%02d)，则归并次数为log99<9(%d)
int divideSort(const char fname[], int n) {
	char tname[_MAX_FNAME];
	nick(fname, tname);
	double* v = new double[n]{ 0 };
	FILE* fl;
	int m = 0; // read times
	if (fopen_s(&fl, fname, "r") == 0 && fl) {
		while (!feof(fl)) {
			int q = get_nums(fl, n, v);
			if (q == 0)
				break;

			char* dname = new char[_MAX_PATH] { 0 };
			sprintf_s(dname, _MAX_PATH, "%s_0%02d.dat", tname, m);
			printf("Sorting block %02d\n", m);
			sort2f(dname, v, q);
			delete[] dname;

			m++;
			if (m > MAX_READ_TIMES) {
				printf("Stopped, too Many Reading Times, lt %d\n", MAX_READ_TIMES);
				break;
			}				
		}
		fclose(fl);
	}
	delete[] v;
	return m;
}

// 归并两个文件
int merge2f(const char in_fname1[], const char in_fname2[], const char out_fname[]) {
	int k = 0;
	char lformat[20] = { 0 };
	sprintf_s(lformat, 20, "%%.0%uf,", NUM_DEC_BIT);
	FILE* ifl1, * ifl2, * ofl;
	try {
		fopen_s(&ifl1, in_fname1, "r");
		fopen_s(&ifl2, in_fname2, "r");
		fopen_s(&ofl, out_fname, "w");
		if (!(ifl1 && ifl2 && ofl)) throw;

		double c1 = get_a_num(ifl1);
		double c2 = get_a_num(ifl2);
		char* buffer = new char[NUM_BIT + 2]{ 0 };
		while (true) {
			if (c1 < 0 || c2 < 0)
				break;

			if (c1 <= c2) {
				sprintf_s(buffer, NUM_BIT + 2, lformat, c1);
				c1 = get_a_num(ifl1);
				
			}
			else {
				sprintf_s(buffer, NUM_BIT + 2, lformat, c2);
				c2 = get_a_num(ifl2);
			}

			fwrite(buffer, sizeof(char), strlen(buffer), ofl);
			if (k % NUM_A_LINE == (NUM_A_LINE - 1))
				fwrite("\n", sizeof(char), 1, ofl);
			k++;
		}

		while (c1 >= 0) {
			sprintf_s(buffer, NUM_BIT + 2, lformat, c1);
			fwrite(buffer, sizeof(char), strlen(buffer), ofl);
			if (k % NUM_A_LINE == (NUM_A_LINE - 1))
				fwrite("\n", sizeof(char), 1, ofl);
			k++;
			c1 = get_a_num(ifl1);
		}

		while (c2 >= 0) {
			sprintf_s(buffer, NUM_BIT + 2, lformat, c2);
			fwrite(buffer, sizeof(char), strlen(buffer), ofl);
			if (k % NUM_A_LINE == (NUM_A_LINE - 1))
				fwrite("\n", sizeof(char), 1, ofl);
			k++;
			c2 = get_a_num(ifl2);
		}

		delete[] buffer;
		fclose(ifl1);
		fclose(ifl2);
		fclose(ofl);
	}
	catch (...) {
		printf("Failed to merge %s and %s", in_fname1, in_fname2);
		throw;
	}
	return k;
}

// 中间文件的格式 e.g., fname_dac1_02.dat
void outrSort(const char fname[], int n) {
	char tname[_MAX_FNAME];
	nick(fname, tname);

	int m = divideSort(fname, n);
	int q = m; // 当前层文件数
	int p = (int)ceil(log2(m));
	char* in_fname1 = new char[_MAX_PATH]{ 0 };
	char* in_fname2 = new char[_MAX_PATH]{ 0 };
	char* out_fname = new char[_MAX_PATH]{ 0 };
	for (int i = 0; i < p;i++) {
		printf("Merging %d\n", i);
		int k = 0; // 下层文件数
		if (q % 2) {
			for (int j = 0; j < (q - 1); j++) { // 合并偶数个
				sprintf_s(in_fname1, _MAX_PATH, "%s_%d%02d.dat", tname, i, j++);
				sprintf_s(in_fname2, _MAX_PATH, "%s_%d%02d.dat", tname, i, j);
				sprintf_s(out_fname, _MAX_PATH, "%s_%d%02d.dat", tname, i + 1, k++);
				int l = merge2f(in_fname1, in_fname2, out_fname);
				printf("Merge %s and %s to %s, Total %d numbers\n", in_fname1, in_fname2, out_fname, l);
			}
			sprintf_s(in_fname1, _MAX_PATH, "%s_%d%02d.dat", tname, i, q - 1);
			sprintf_s(out_fname, _MAX_PATH, "%s_%d%02d.dat", tname, i + 1, k++);
			//CopyFile((LPCWSTR)in_fname1, (LPCWSTR)out_fname, false);
			copy_file(in_fname1, out_fname);
			printf("Copy %s to %s\n", in_fname1, out_fname);
		}
		else {
			for (int j = 0; j < q; j++) { // 合并偶数个
				sprintf_s(in_fname1, _MAX_PATH, "%s_%d%02d.dat", tname, i, j++);
				sprintf_s(in_fname2, _MAX_PATH, "%s_%d%02d.dat", tname, i, j);
				sprintf_s(out_fname, _MAX_PATH, "%s_%d%02d.dat", tname, i + 1, k++);
				int l = merge2f(in_fname1, in_fname2, out_fname);
				printf("Merge %s and %s to %s, Total %d numbers\n", in_fname1, in_fname2, out_fname, l);
			}
		}
		q = k;
	}

	delete[] in_fname1;
	delete[] in_fname2;
	delete[] out_fname;
}


int main(int argc, char* argv[])
{
	if (argc < 2) {		
		return -2;
	}

	if (argc == 2 && (strcmp(argv[1], "-h") == 0)) {
		printf("Usage: rand, read, intr, outr\n");
		return -2;
	}
	
	char command[64];
	strcpy_s(command, 64, argv[1]);

	// 生成n个数，并打印
	if (strcmp(command, "rand") == 0) {
		if (argc == 3 && (strcmp(argv[2], "-h") == 0)) {
			printf("rand num_to_gen [file_name]\n");
			return -2;
		}

		if (argc == 3) {
			int n = atoi(argv[2]);
			double* v = new double[n] {0};
			rnd2l(v, n);
			printl(v, n);
			delete[] v;
		}
		else if (argc == 4) {
			rnd2f(argv[3], atoi(argv[2]));
			printf("Done!\n");
		}
	}
	// 从文件中读n个数
	else if (strcmp(command, "read") == 0) {
		if (argc == 3 && (strcmp(argv[2], "-h") == 0)) {
			printf("read file_name [num]\n");
			return -2;
		}

		int n = 10;
		if (argc < 3) return -1;
		if (!is_exist(argv[2])) {
			printf("file doesnot exist %s\n", argv[2]);
			return -1;
		}
		if (argc >= 4) n = atoi(argv[3]);
		if (n < 0) return -1;
		double* v = new double[n]{ 0 };
		int q = 0;
		FILE* fl;
		if (fopen_s(&fl, argv[2], "r") == 0 && fl) {
			q = get_nums(fl, n, v);
			fclose(fl);
		}
		printl(v, q);
		printf("Read %d numbers\n", q);
		delete[] v;
	}
	// 内排序
	else if (strcmp(command, "intr") == 0) {
		if (argc == 3 && (strcmp(argv[2], "-h") == 0)) {
			printf("intr sort_alg num_rnd [if_print]\n");
			printf("alg: bubble, select, insert, shell, quick, merge, heap\n");
			return -2;
		}

		if (argc < 4) return -1;
		bool is_print = true;
		int n = atoi(argv[3]);
		if (argc >= 5 && (strcmp(argv[4], "0") == 0)) is_print = false;
		
		double* v = new double[n] {0};
		rnd2l(v, n);
		if (is_print) printl(v, n);

		clock_t run_start = clock();
		if (strcmp(argv[2], "bubble") == 0)
			bubbleSort1(v, n);
		else if (strcmp(argv[2], "select") == 0)
			selectSort(v, n);
		else if (strcmp(argv[2], "insert") == 0)
			insertSort(v, n);
		else if (strcmp(argv[2], "shell") == 0)
			shellSort(v, n);
		else if (strcmp(argv[2], "quick") == 0)
			quickSort(v, 0, n - 1);
		else if (strcmp(argv[2], "merge") == 0)
			mergeSort(v, n);
		else if (strcmp(argv[2], "heap") == 0)
			heapSort(v, n);
		else
			printf("Invalid Sorting Algorithm!\n");
		clock_t run_end = clock();

		if (is_print) printl(v, n);
		double runtime = ((double)run_end - (double)run_start) / CLOCKS_PER_SEC;
		delete[] v;
		printf("Run Time: %.3f s\n", runtime);
	}
	// 外排序
	else if (strcmp(command, "outr") == 0) {
		if (argc == 3 && (strcmp(argv[2], "-h") == 0)) {
			printf("outr divide file_name per_num\n");
			printf("outr merge in_file1 in_file2 out_file\n");
			printf("outr auto file_name per_line_num\n");
			return -2;
		}
		
		if (argc < 3) return -1;
		if (strcmp(argv[2], "divide") == 0) {
			if (argc < 5) {
				printf("outr divide file_name per_num\n");
				return -1;
			}

			if (!is_exist(argv[3])) {
				printf("file doesnot exist %s\n", argv[3]);
				return -1;
			}
			int per_ln = atoi(argv[4]);
			int m = divideSort(argv[3], per_ln);
			printf("Divided and Sorted %d blocks\n", m);
		}
		else if (strcmp(argv[2], "merge") == 0) {
			if (argc < 6) {
				printf("outr merge in_file1 in_file2 out_file");
				return -1;
			}

			if (!is_exist(argv[3])) {
				printf("file doesnot exist %s\n", argv[3]);
				return -1;
			}
			if (!is_exist(argv[4])) {
				printf("file doesnot exist %s\n", argv[4]);
				return -1;
			}
			int m = merge2f(argv[3], argv[4], argv[5]);
			printf("Merged %d numbers\n", m);
		}
		else if (strcmp(argv[2], "auto") == 0) {
			if (argc < 5) {
				printf("outr auto file_name per_num\n");
				return -1;
			}

			if (!is_exist(argv[3])) {
				printf("file doesnot exist %s\n", argv[3]);
				return -1;
			}
			int per_ln = atoi(argv[4]);

			clock_t run_start = clock();
			outrSort(argv[3], per_ln);
			clock_t run_end = clock();

			double runtime = ((double)run_end - (double)run_start) / CLOCKS_PER_SEC;
			printf("Run Time: %.3f s\n", runtime);
		}
	}

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
