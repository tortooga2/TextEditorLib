#include <Buffer.h>

Buffer::Buffer(const char* filename){
    buffer = ReadBuffer(filename);
};

Buffer::Buffer() : buffer(""){};

std::string Buffer::ReadBuffer(const char* filename){
    std::ifstream file(filename, std::ios::binary);
    
    if(!file){
        throw std::runtime_error("Failed to open file");
    }

    return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()); 
}

void Buffer::Append(std::string edit)
{
    buffer += edit;
};

void Buffer::ShowBuffer(){
    std::cout << buffer << std::endl;
};

size_t Buffer::GetLength(){
    return buffer.length();
};


std::string Buffer::GetString(size_t start_index, size_t length)
{
    return buffer.substr(start_index, length);
};


