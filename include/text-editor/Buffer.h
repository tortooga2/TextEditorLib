#pragma once
#include <iostream>
#include <fstream>
#include <memory>
#include <iterator>
#include <string>


class Buffer{
    public:
        Buffer(const char* filename);
        Buffer();

        void ShowBuffer();

        size_t GetLength();

        

    private:
        std::string buffer;

        std::string ReadBuffer(const char* filename);

        void Append(std::string edit);
};


