#include <iostream>
#include <bitset>
#include <boost/dynamic_bitset.hpp>
#include <boost/utility.hpp>

void std_bitset_test()
{
	using namespace std;

	bitset<4> b;

    cout << __FILE__ << '#' << __LINE__ << " --- " << __FUNCTION__ << endl;
	cout << b << endl;	//0000
	cout << b.flip(0) << endl;	//0001
	cout << b.flip(2) << endl;	//0101
	cout << b.flip() << endl;	//1010


	bitset<8> b2(42);

	cout << b2 << '\n';	//00101010
	cout << b2.reset(1) << '\n';	//00101000
	cout << b2.reset() << '\n';	//00000000


	bitset<8> b3(42);

	cout << b3 << '\n';	//00101010
	cout << b3.to_string() << '\n';	//00101010
	cout << b3.to_string('*') <<  '\n';	//**1*1*1*
	cout << b3.to_string('O', 'X') << '\n';	//OOXOXOXO

	bitset<8> b4;

	cout << b4 << '\n';	//00000000
	for (size_t i = 1; i < b4.size(); i += 2)
	{
		b4.set(i);
	}
	cout << b4 << '\n';	//10101010
    for (size_t i = 1; i < b4.size(); i += 2)
    {
        b4.set(i, 0);
    }
    cout << b4 << '\n';

}

void boost_dynamic_bitset_test()
{
    using namespace boost;

    dynamic_bitset<> db1;
    dynamic_bitset<> db2(10);
    dynamic_bitset<> db3(0x16, BOOST_BINARY(10101));
    dynamic_bitset<> db4(std::string("0100"));
    dynamic_bitset<> db5(db3);
    dynamic_bitset<> db6;

    db6 = db4;
    
    std::cout << __FILE__ << '#' << __LINE__ << " --- " << __FUNCTION__ << std::endl;
    std::cout << db5.to_ulong() << std::endl;

    db1.resize(10, true);
    std::cout << db1 << std::endl;

    assert(dynamic_bitset<>(64).num_blocks() == 1);
    assert(dynamic_bitset<>(65).num_blocks() == 2);

    db1.resize(4, BOOST_BINARY(1010));    //因为是缩小范围，所以给的初始值直接被忽略
    db1 = std::move(dynamic_bitset<>(4, BOOST_BINARY(1010)));
    std::cout << "db1 = " << db1 << std::endl;
    db1[0] &= 1;
    db1[1] ^= 1;
    std::cout << "db1 = " << db1 << std::endl;

    db2.resize(4, BOOST_BINARY(0101));
    db2 = std::move(dynamic_bitset<>(4, BOOST_BINARY(0101)));
    assert(db1 > db2);

    std::cout << (db1 ^ db2) << std::endl;
    std::cout << (db1 | db2) << std::endl;

    assert(db1.test(0) && !db1.test(1));
    std::assert(db1.test(0));
}

int main(int argc, char* argv[])
{
    std_bitset_test();
    boost_dynamic_bitset_test();
}
