#include <iostream>
#include <bitset>
#include <boost/dynamic_bitset.hpp>

void std_bitset_test()
{
	using namespace std;

	bitset<4> b;

	cout << b << endl;	//0000
	cout << b.flip(0) << endl;	//0001
	cout << b.flip(2) << endl;	//0101
	cout << b.flip() << endl;	//1010


	bitset<8> b2(42);

	cout << b << '\n';	//00101010
	cout << b.reset(1);	//00101010
	cout << b.reset();	//00000000


	bitset<8> b3(42);

	cout << b << '\n';	//00101010
	cout << b.to_string();	//00101010
	cout << b.to_string('*');	//**1*1*1*
	cout << b.to_string('O', 'X');	//OOXOXOXO

	bitset<8> b4;

	cout << b << '\n';	//00000000
	for (size_t i = 1; i < b.size(); i += 2)
	{
		b.set(i);
	}
	cout << b << '\n';	//10101010

}

int main(int argc, char* argv[])
{
	std_bitset_test();
}
