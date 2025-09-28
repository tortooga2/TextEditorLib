#pragma once
#include <iostream>
#include <fstream>
#include <memory>
#include <iterator>
#include <string>

enum class BufferType {OG, ADD};

class Buffer{
    public:
        Buffer(const char* filename);
        Buffer();

        void ShowBuffer();

        size_t GetLength();

        std::string GetString(size_t start_index, size_t length);

        void Append(std::string edit);

    private:
        std::string buffer;

        std::string ReadBuffer(const char* filename);

        
};


