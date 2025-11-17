// error_codes.cpp
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include "task1_1.hpp"

Result DivideIntegers(int a, int b) {
    if (b == 0) {
            // return MakeError(ResultCode::InvalidParameter); 
            throw std::invalid_argument("Divide to zero");
        // TODO: заменить на исключение std::invalid_argument
    }
    return MakeSuccess(a / b);
}

Result OpenAndReadFile(const std::string& filename, std::vector<char>& buffer) {

    if (filename.empty()) {
        // return MakeError(ResultCode::InvalidParameter); 
        throw std::invalid_argument("Filename empty");
        // TODO: заменить на исключение std::invalid_argument
    }
    
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        // return MakeError(ResultCode::FileNotFound); 
        throw std::runtime_error("File not found");
        // TODO: заменить на исключение std::runtime_error
    }
    
    std::streamsize size = file.tellg();
    if (size < 0) {
        throw std::runtime_error("File not found");
        // return MakeError(ResultCode::FileNotFound);
    }
    
    file.seekg(0, std::ios::beg);
    buffer.resize(static_cast<size_t>(size));
    
    if (!file.read(buffer.data(), size)) {
        throw std::runtime_error("File not found");
        // return MakeError(ResultCode::FileNotFound); 
        // TODO: заменить на исключение std::runtime_error
    }
    
    return MakeSuccess(0);
}

Result ProcessConfigFile(const std::string& configPath) {
    int ret=0;
    std::vector<char> buffer;
    try{
        Result readRes = OpenAndReadFile(configPath, buffer);
    }
    catch(std::invalid_argument& e){
        std::cout<<"Exeption: "<<e.what()<<std::endl;
        ret = 3;
    }
    catch(std::runtime_error& e){
        std::cout<<"Exeption: "<<e.what()<<std::endl;
        ret = 2;
    }
    catch(std::exception &e){
        std::cout<<"Exeption: "<<e.what()<<std::endl;
        ret = 1;
    }
    // if (IsError(readRes)) {
    //     return readRes; // TODO: обработать здесь или перенести в main ?
    // }

    // some mock processing here
    
    if(ret == 0 ) std::cout << "Config processed successfully, size " << buffer.size() << " bytes\n";
    return MakeSuccess(ret);
}

int main() {
    // TODO: Обернуть вызовы функций в try-catch и вывести инфо о исключениях
    // Что будет, если исключения не будут пойманы?
    try{
    Result resDiv = DivideIntegers(5, 0);
    // std::cout << GetErrorString(resDiv.code) << "\n";
    }
    catch(std::runtime_error& e){
        std::cout<<"Exeption: "<<e.what()<<std::endl;
    }
    catch(std::invalid_argument& e){
        std::cout<<"Exeption: "<<e.what()<<std::endl;
    }
    catch(std::exception& e){
        std::cout<<"Exeption: "<<e.what()<<std::endl;
    }


    Result resCfg = ProcessConfigFile("config.dat");
    // std::cout << GetErrorString(resCfg.code) << "\n";

    return 0;
}
