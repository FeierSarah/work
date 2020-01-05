

// 读取当前句柄开始的一个浮点数
double get_a_num(FILE* fl)
{
	char buffer[10];
	int k = 0;
	char c = 0;
	while (!feof(fl))
	{
		fread(&c, sizeof(char), 1, fl);
		if (c == ' ')
			break;
		else if ((c >= '0' && c <= '9') || c == '.')
			buffer[k++] = c;
	}
	if (k == 0)
		return -1;
	else
		return atof(buffer);
}

//// 读取当前句柄开始的n个浮点数
//int get_nums(FILE* fl, int n, double s[]) {
//	int k = 0;
//	for (int i = 0; i < n; i++) {
//		double c = get_a_num(fl);
//		if (c < 0)
//			break;
//		else
//			s[k++] = c;
//	}
//	return k; // actual num
//}
//
//
//// SORT AND WRITE
//void sort2f(const char fname[], double v[], int n) {
//	FILE* fl;
//	if (fopen_s(&fl, fname, "w") == 0 && fl) {
//		quickSort(v, 0, n - 1);
//		char lformat[20] = { 0 };
//		sprintf_s(lformat, "%%.%df,", 3);
//		for (int i = 0; i < n; i++) {
//			char s[11] = { 0 };
//			sprintf_s(s, 11, lformat, v[i]);
//			fwrite(s, sizeof(char), strlen(s), fl);
//			if (i % 10 == 9)
//				fwrite("\n", sizeof(char), 1, fl);
//		}
//		fclose(fl);
//	}
//	else
//		printf("Cannot write a DAC file %s", fname);
//}
//
//// DEVIDE AND SORT, using QUICK SORT
//// 子文件数限99个(%02d)，则归并次数为log99<9(%d)
//int divideSort(const char fname[], int n) {
//	char tname[_MAX_FNAME];
//	nick(fname, tname);
//	double* v = { 0 };
//	FILE* fl;
//	int m = 0; // read times
//	if (fopen_s(&fl, fname, "r") == 0 && fl) {
//		while (!feof(fl)) {
//			int q = get_nums(fl, n, v);
//			if (q == 0)
//				break;
//
//			char* dname = { 0 };
//			sprintf_s(dname, _MAX_PATH, "%s_0%02d.dat", tname, m);
//			printf("Sorting block %02d\n", m);
//			sort2f(dname, v, q);
//
//			m++;
//			if (m > 99) 
//			{
//				break;
//			}
//		}
//		fclose(fl);
//	}
//	return m;
//}
//
//// 归并两个文件
//int merge2f(const char in_fname1[], const char in_fname2[], const char out_fname[]) {
//	int k = 0;
//	char lformat[20] = { 0 };
//	sprintf_s(lformat, 20, "%%.0%uf,", 3);
//	FILE* ifl1, *ifl2, *ofl;
//	fopen_s(&ifl1, in_fname1, "r");
//	fopen_s(&ifl2, in_fname2, "r");
//	fopen_s(&ofl, out_fname, "w");
//
//	double c1 = get_a_num(ifl1);
//	double c2 = get_a_num(ifl2);
//	char* buffer = { 0 };
//	while (1)
//	{
//		if (c1 < 0 || c2 < 0)
//			break;
//
//		if (c1 <= c2) 
//		{
//			sprintf_s(buffer, 11, lformat, c1);
//			c1 = get_a_num(ifl1);
//		}
//		else 
//		{
//			sprintf_s(buffer, 11, lformat, c2);
//			c2 = get_a_num(ifl2);
//		}
//		fwrite(buffer, sizeof(char), strlen(buffer), ofl);
//		if (k % 10 == 9)
//			fwrite("\n", sizeof(char), 1, ofl);
//		k++;
//	}
//	while (c1 >= 0)
//	{
//		sprintf_s(buffer, 11, lformat, c1);
//		fwrite(buffer, sizeof(char), strlen(buffer), ofl);
//		if (k % 10 == 9)
//			fwrite("\n", sizeof(char), 1, ofl);
//		k++;
//		c1 = get_a_num(ifl1);
//	}
//	while (c2 >= 0)
//	{
//		sprintf_s(buffer, 11, lformat, c2);
//		fwrite(buffer, sizeof(char), strlen(buffer), ofl);
//		if (k % 10 == 9)
//			fwrite("\n", sizeof(char), 1, ofl);
//		k++;
//		c2 = get_a_num(ifl2);
//	}
//	fclose(ifl1);
//	fclose(ifl2);
//	fclose(ofl);
//	return k;
//}

//// 中间文件的格式 e.g., fname_dac1_02.dat
//void outrSort(const char fname[], int n) {
//	char tname[_MAX_FNAME];
//	nick(fname, tname);
//
//	int m = divideSort(fname, n);
//	int q = m; // 当前层文件数
//	int p = (int)ceil(log2(m));
//	char* in_fname1 = { 0 };
//	char* in_fname2 = { 0 };
//	char* out_fname = { 0 };
//	for (int i = 0; i < p; i++) 
//	{
//		printf("Merging %d\n", i);
//		int k = 0; // 下层文件数
//		if (q % 2) {
//			for (int j = 0; j < (q - 1); j++) { // 合并偶数个
//				sprintf_s(in_fname1, _MAX_PATH, "%s_%d%02d.dat", tname, i, j++);
//				sprintf_s(in_fname2, _MAX_PATH, "%s_%d%02d.dat", tname, i, j);
//				sprintf_s(out_fname, _MAX_PATH, "%s_%d%02d.dat", tname, i + 1, k++);
//				int l = merge2f(in_fname1, in_fname2, out_fname);
//				printf("Merge %s and %s to %s, Total %d numbers\n", in_fname1, in_fname2, out_fname, l);
//			}
//			sprintf_s(in_fname1, _MAX_PATH, "%s_%d%02d.dat", tname, i, q - 1);
//			sprintf_s(out_fname, _MAX_PATH, "%s_%d%02d.dat", tname, i + 1, k++);
//			//CopyFile((LPCWSTR)in_fname1, (LPCWSTR)out_fname, false);
//			copy_file(in_fname1, out_fname);
//			printf("Copy %s to %s\n", in_fname1, out_fname);
//		}
//		else {
//			for (int j = 0; j < q; j++) { // 合并偶数个
//				sprintf_s(in_fname1, _MAX_PATH, "%s_%d%02d.dat", tname, i, j++);
//				sprintf_s(in_fname2, _MAX_PATH, "%s_%d%02d.dat", tname, i, j);
//				sprintf_s(out_fname, _MAX_PATH, "%s_%d%02d.dat", tname, i + 1, k++);
//				int l = merge2f(in_fname1, in_fname2, out_fname);
//				printf("Merge %s and %s to %s, Total %d numbers\n", in_fname1, in_fname2, out_fname, l);
//			}
//		}
//		q = k;
//	}
//}

void testTime2()
{
	FILE* fl;
	if ((fl = fopen("test.txt", "w+")) != NULL)
	{
		int nums = 2000000;
		double* c = (double*)malloc(nums * sizeof(float));
		for (int i = 0; i < nums; i++)
		{
			int random_nums1 = rand();
			int random_nums2 = rand() % 100;
			double random = random_nums1 + 0.01 * random_nums2;
			c[i] = random;
			fprintf(fl, "%lf  ", c[i]);
			if ((i + 1) % 40 == 0)
			{
				fprintf(fl, "\n");
			}
		}
	}
	else
		printf("不能写入文件\n");
	rewind(fl);

	FILE* fr[20];
	fr[0] = fopen("1.txt", "w");
	fr[1] = fopen("2.txt", "w");
	fr[2] = fopen("3.txt", "w");
	fr[3] = fopen("4.txt", "w");
	fr[4] = fopen("5.txt", "w");
	fr[5] = fopen("6.txt", "w");
	fr[6] = fopen("7.txt", "w");
	fr[7] = fopen("8.txt", "w");
	fr[8] = fopen("9.txt", "w");
	fr[9] = fopen("10.txt", "w");
	fr[10] = fopen("11.txt", "w");
	fr[11] = fopen("12.txt", "w");
	fr[12] = fopen("13.txt", "w");
	fr[13] = fopen("14.txt", "w");
	fr[14] = fopen("15.txt", "w");
	fr[15] = fopen("16.txt", "w");
	fr[16] = fopen("17.txt", "w");
	fr[17] = fopen("18.txt", "w");
	fr[18] = fopen("19.txt", "w");
	fr[19] = fopen("20.txt", "w");
	double d[100000];
	for (int j = 0; j < 20; j++)
	{
		int k = 0;
		for (int i = 100000 * j; i < 2000000; i++)
		{
			k++;
			d[k - 1] = get_a_num(fl);
		}
		MergeSort(d, 100000);
		fprintf(fr[j], "%lf  ", d[k - 1]);
	}
	for (int i = 0; i < 20; i++)
	{
		fclose(fr[i]);
	}
	fclose(fl);
}
