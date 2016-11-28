/*************************************************************************
	> File Name: string_using.cpp
	> Author: JieTrancender
	> Mail: jie-email@jie-trancender.org
	> Created Time: Mon Nov 28 10:34:57 2016
 ************************************************************************/

#include <iostream>
#include <boost/lexical_cast.hpp>

using namespace boost;

namespace mtl
{
    //C++ style conversion
    //only can include e/E when string convent to int/float/double
    //only can use 0/1 when string convent to bool
    //Using this must include operator<<, operator>>, default constructor, copy constructor
    template <typename Target, typename Source>
    inline Target lexical_cast(const Source& arg);

    //C style conversion
    template <typename Target>
    inline Target lexical_cast(const char* chars, std::size_t count);

    //In conversion namespace
    //C++ style conversion with no throw exception
    template <typename Target, typename Source>
    inline bool try_lexical_convert(Source& arg, Target& result);

    //C style conversion with on throw exception
    template <typename Target, typename CharacterT>
    inline bool try_lexical_convert(const CharacterT* chars, std::size_t count, Target& result);
}

class DemoLexicalCast
{
public:
    DemoLexicalCast() = default;
    ~DemoLexicalCast() = default;

    friend std::ostream& operator<<(std::ostream& os, const DemoLexicalCast& x)
    {
        os << "DemoLExicalCast's name";
        return os;
    }
};

void lexical_cast_test()
{
    int a = lexical_cast<int>("100");
    long b = lexical_cast<long>("3000");
    float pai = lexical_cast<float>("3.14159");
    double c = lexical_cast<double>("32.323");
    double d = lexical_cast<double>("1.414, x", 5);

    std::cout << a << ' ' << b << ' ' << c << ' ' << d << ' ' << pai << std::endl;

    std::string str = lexical_cast<std::string>(1234);
    std::cout << str << std::endl;

    std::cout << lexical_cast<std::string>(0x10) << std::endl << std::endl;

    try
    {
        std::cout << lexical_cast<int>("0x100") << std::endl;
        std::cout << lexical_cast<double>("Hello, World") << std::endl;
        std::cout << lexical_cast<long>("1000L") << std::endl;
        std::cout << lexical_cast<bool>("false") << std::endl;
    }
    catch (bad_lexical_cast& e)
    {
        std::cerr << "Error: " << e.what() << " in " << __FILE__ << '#' << __LINE__ << " --- " << __FUNCTION__ << std::endl;
    }
}

void try_lexical_convert_test()
{
    long num;
    std::string str = "1000L";
    assert(!conversion::try_lexical_convert(str, num));  //This will be failed
    std::cout << __FILE__ << '#' << __LINE__ << " --- " << __FUNCTION__ << std::endl;
}

int main(int argc, char* argv[])
{
    lexical_cast_test();
    try_lexical_convert_test();

    std::cout << lexical_cast<std::string>(DemoLexicalCast()) << std::endl;

    std::cout << typeid(std::string).name() << std::endl;
}

