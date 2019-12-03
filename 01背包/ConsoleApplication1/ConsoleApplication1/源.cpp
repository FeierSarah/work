#include <stdio.h>
#include <iostream>
#include <malloc.h>
using namespace std;
int main()
{
	char s[100];
	while (cin >> s)
	{
		for (int i = 0; i < 100; i++)
		{
			if (s[i] == 0)
				break;
			int count = 0;
			for (int j = 0; j < i; j++)
			{
				if (s[j] == s[i])
				{
					break;
				}
				else
					count++;
			}
			if (count == i)
				cout << s[i];
		}
		cout << endl;
	}
	return 0;
}