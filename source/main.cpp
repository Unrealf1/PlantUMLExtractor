//
// Created by fedor on 8/10/19.
//

#include <iostream>
#include "Reader.hpp"
#include "Writer.hpp"

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cout << "Usage: ./a.out [class name] [filename]" << std::endl;
        return 0;
    }
    std::string classname = argv[1];
    std::string filename = argv[2];
    std::string outFilename = PUMLE::Writer::ComposeFileName(filename);

    PUMLE::Reader reader(filename);
    PUMLE::ClassSource classSource = reader.FindClass(classname);

    PUMLE::Writer writer(outFilename);
    writer.Write(classSource);

}