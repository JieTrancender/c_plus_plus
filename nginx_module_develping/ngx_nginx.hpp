#pragma once

#include <cassert>
#include <boost/core/ignore_unused.hpp>  //ignore_unused()函数用来忽略暂时不用的变量，显示消除编译警告

extern "C"
{
    #include <../nginx-1.4.4/src/http/ngx_http.h>
}
