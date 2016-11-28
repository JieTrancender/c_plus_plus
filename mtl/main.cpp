#include "mtl_array.hpp"

#include <iostream>
#include <array>
#include <iterator>
#include <algorithm>
#include <string>

#include <boost/assign.hpp>
#include <boost/array.hpp>
#include <boost/utility/string_ref.hpp>

//using namespace std;

void mtl_array_test()
{
	using namespace mtl;

	array<int, 5> a = { 1, 2, 3, 4, 5 };
	array<std::string, 2> a2 = { std::string("str"), std::string("ss") };

	std::copy(a.begin(), a.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	std::copy(a2.begin(), a2.end(), std::ostream_iterator<std::string>(std::cout, " "));
	std::cout << std::endl;
}

void stl_array_test()
{
	using namespace std;

	array<int, 5> a = { 1, 2, 3, 4, 5 };
	array<std::string, 2> a2 = { std::string("str"), std::string("ss") };

	copy(a.begin(), a.end(), std::ostream_iterator<int>(cout, " "));
	cout << endl;

	copy(a2.begin(), a2.end(), std::ostream_iterator<std::string>(cout, " "));
	cout << endl;
}

void boost_array_test()
{
	using namespace boost;
	using namespace boost::assign;

	array<int, 5> a = list_of(1)(2)(3);
	array<std::string, 2> a2 = { std::string("str"), std::string("ss") };
	//array < string_ref, 2> a2 = list_of(string_ref("str"))(string_ref("ss"));

	//std::copy(a2.begin(), a2.end(), std::ostream_iterator<int>(std::cout, " "));
	//std::cout << std::endl;

	//std::copy(a2.begin()->to_string(), a2.end()->to_string(), std::ostream_iterator<std::string>(std::cout, " "));
	//std::cout << std::endl;

	for (auto str : a2)
	{
		std::cout << str << ' ';
	}
	std::cout << std::endl;
}

int main()
{
	mtl_array_test();
	stl_array_test();
	boost_array_test();

    return 0;
}

