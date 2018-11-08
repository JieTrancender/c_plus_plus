#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
	vector<int> sortArrayByParity(vector<int>& A)
	{
		int indexFirst = 0;
		int indexSecond = A.size() - 1;

		while (indexFirst < indexSecond)
		{
			while (indexFirst < indexSecond && A[indexFirst] % 2 == 0)
				++indexFirst;

			while (indexFirst < indexSecond && A[indexSecond] % 2 == 1)
				--indexSecond;

			if (indexFirst < indexSecond)
			{
				swap(A[indexFirst], A[indexSecond]);
				++indexFirst;
				--indexSecond;
			}
		}

		return A;
	}
};

int main(int argc, char* argv[])
{
	Solution solution;
	vector<int> A = {};

	for (auto &it : solution.sortArrayByParity(A))
	{
		cout << it << ' ';
	}

	cout << endl;

	// A = {3, 1, 2, 4};
	// cout << solution.isSubsequence(s, t) << endl;
}