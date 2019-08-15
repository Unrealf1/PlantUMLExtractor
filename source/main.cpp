//
// Created by fedor on 8/10/19.
//

#include <iostream>
#include "Argparser/Argparser.hpp"
#include "Reader/KotlinReader.hpp"
#include "Writer.hpp"

int main(int argc, char** argv) {
    Argparser parser(argc, argv);
    if (parser.GetHelp() || parser.GetInputFileName().empty()) {
        std::string helpMessage = "Usage: [inputFileName] [arguments]\n"
                                  "-o [string]  output file name(optional)\n"
                                  "-c [string]  name of class to extract(optional)\n"
                                  "-h           this message\n";
        std::cout << helpMessage << std::flush;
        return 0;
    }
    std::ifstream ifstr(parser.GetInputFileName());
    PUMLE::KotlinReader reader(ifstr);

    std::string outputFileName = parser.GetOutputFileName();
    if (outputFileName.empty()) {
        outputFileName = PUMLE::Writer::ComposeFileName(parser.GetInputFileName());
    }
    PUMLE::Writer writer(outputFileName);
    std::vector<PUMLE::ClassSource> classes;
    if (parser.GetClassname().empty()) {
        auto classNames = reader.GetAllClasses();
        for (auto& className : classNames) {
            classes.emplace_back(reader.ExtractClass(className));
        }
    } else {
        classes.emplace_back(reader.ExtractClass(parser.GetClassname()));
    }


    writer.Begin();
    for (auto& class_ : classes) {
        writer.Write(class_);
    }
    writer.End();
}