#include <iostream>
#include <string>

using namespace std;

class Solution
{
public:
	// redo:当有大量s时，可以尝试先判断s中是否有不存在于t中的字符
	bool isSubsequence(string s, string t)
	{
		if (s.size() == 0)
		{
			return true;
		}

		int indexFirst = 0;
		int indexSecond = 0;

		for (auto &ch : t)
		{
			if (ch == s[indexFirst])
			{
				++indexFirst;

				if (indexFirst == s.size())
				{
					return true;
				}
			}
		}

		return false;
	}
};

int main(int argc, char* argv[])
{
	Solution solution;
	string s = "abc";
	string t = "ahbgdc";

	cout << solution.isSubsequence(s, t) << endl;

	s = "axc";
	t = "ahbgdc";
	cout << solution.isSubsequence(s, t) << endl;
}