#include <iostream> 
#include <vector> 
#include <algorithm>

using namespace std;

vector<vector<int>>  presum(vector<int>& A, int N)
{
	vector<vector<int>>  sum(N, vector<int>(N, 0));
	for (int i = 0; i <= N - 1; i++)
	{
		for (int j = i; j <= N - 1; j++)
		{
			if (j == 0)
			{
				sum[i][j] = A[j];
			}
			else  sum[i][j] = sum[i][j - 1] + A[j];
		}
	}
	return  sum;
}

vector<vector<int>>  max_min_sum(vector<int>& A, int N, int M)

{
	vector<vector<int>> C(M, vector<int>(N, 0));
	vector<vector<int>>  sum(N, vector<int>(N, 0));
	sum = presum(A, N);
	for (int i = 0; i <= N - 1; i++)
	{
		C[0][i] = sum[0][i];
	}
	for (int j = 1; j <= M - 1; j++)
	{
		for (int i = j; i <= N - 1; i++)
		{
			int  max_num = 0, min_num = 0;
			for (int k = j - 1; k < i; k++)
			{
				min_num = min(C[j - 1][k], sum[k + 1][i]);
				max_num = max(max_num, min_num);
			}
			C[j][i] = max_num;
			//cout << max_num;
		}
	}
	return C;
}

vector<int>  max_min_grouping(vector<int>& A, int  N, int M)
{
	vector<int> G(M);
	vector<vector<int>> C(M, vector<int>(N, 0));
	C = max_min_sum(A, N, M);
	cout << "Maximized minimum element of array, B: " << C[M - 1][N - 1]<<endl;
	for (int j = 0; j <= M - 1; j++)
	{
		for (int i = j; i <= N - 1; i++)
		{
			if (C[j][i] == C[M - 1][N - 1])
			{
				G[j] = i + 1;
			}
			else  if (C[j][i] < C[M - 1][N - 1])
			{
				G[j] = i + 2;
			}

		}

	}
	for (int m = M - 1; m >= 1; m--)
	{
		G[m] = G[m] - G[m - 1];
	}
	return G;
}

int  main()
{
	vector<int> A = { 3, 9, 7, 8, 2, 6, 5, 10, 1, 7, 6, 4 };
	//vector<int> A = { 3, 7, 2, 4, 1, 4, 5 };
	//vector<int> A = { 6, 9 ,10, 4, 7, 3, 9, 7 };
	int  N = A.size();
	cout << "Entered input array elements, A [ ]:  ";
	for (int i = 0; i <= N - 1; i++)
	{
		cout << A[i] << " ";
	}
	cout << endl;
	int M;
	cout << "Enter number of partitions, M: ";
	cin >> M;
	vector<int> G(M);
	
	G = max_min_grouping(A, N, M);
	cout << "G[ ]: ";
	for (int m = 0; m <= M - 1; m++)
	{
		cout << G[m] << " ";
	}
	return 0;
}
