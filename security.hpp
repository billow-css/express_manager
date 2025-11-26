#pragma once
#include <string>
#include "md5-master\md5-master\src\md5.h"

std::string generateSecurityHash(const std::string& input) {
    /*一切密码在类内存储严格经过哈希值!!!!!!!!!!!!*/
    MD5 md5(input);
    return md5.toStr();
}