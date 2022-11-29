#pragma once

#include <cstdarg>
#include <cstdlib>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

class MyUtil {
public:
    template<typename ... Args>
    static
    std::string formatStr(const std::string &format, Args ... args) {
        size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
        if (size <= 0) { throw std::runtime_error("Error during formatting."); }
        std::unique_ptr<char[]> buf(new char[size]);
        snprintf(buf.get(), size, format.c_str(), args ...);
        return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
    }

    template<class T>
    static
    std::string getVectorInfoStr(std::vector<T> vec, std::string strName, std::string strItemFormat) {
        std::string strRes = "";
        strRes += MyUtil::formatStr("%s:%lu:%p:[", strName.c_str(), vec.size(), vec.data());

        for (auto item: vec) {
            strRes += MyUtil::formatStr(strItemFormat.c_str(), item);
            strRes += ", ";
        }

        strRes += "]";
        return strRes;
    }

    static std::vector<std::string> readFromFile(const std::string& strFilePath) {
        std::ifstream ifs(strFilePath);
        if (!ifs) {
            LOGSLOTH("FILE_OPEN_FAIL strFilePath:%s", strFilePath.c_str());
            std::exit(EXIT_FAILURE);
        }
        std::vector<std::string> vLine;
        std::string line;
        while (std::getline(ifs, line))
            vLine.push_back(line);
        return vLine;
    }
};

