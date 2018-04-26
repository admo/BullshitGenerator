#include <iostream>
#include <fstream>
#include <memory>

#include <boost/program_options.hpp>

#include "BullshitGenerator.h"

namespace {
std::fstream openFile(const std::string& filename, std::ios::openmode mode) {
    std::fstream file(filename, mode);
    if (!file.is_open())
        throw std::runtime_error(std::string("Could not open ") + filename + " file");

    return file;
}
}

int main(int argc, char* argv[]) try {
    std::string word, inputFilename{'-'}, outputFilename{'-'};
    std::size_t count;

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
            ("help,h", "print usage message")
            ("word,w", po::value<std::string>(&word), "first word of the generated bullshit")
            ("input,i", po::value<std::string>(&inputFilename), "input file to feed bullshit generator")
            ("output,o", po::value<std::string>(&outputFilename), "output file where the bullshit will be written")
            ("count,c", po::value<std::size_t>(&count), "number of word in generated bullshit");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << '\n';
        return 0;
    }

    if (0 == vm.count("count"))
        throw std::runtime_error("Missing count switch");

    if (0 == vm.count("word"))
        throw std::runtime_error("Missing word switch");

    std::fstream inputFile;
    if (vm.count("input"))
        inputFile = openFile(inputFilename, std::ios::in);

    std::fstream outputFile;
    if (vm.count("output"))
        outputFile = openFile(outputFilename, std::ios::out);

    std::istream* inputStream = vm.count("input") ? &inputFile : &std::cin;
    std::ostream* outputStream = vm.count("output") ? &outputFile : & std::cout;

    BullshitGenerator{*inputStream}.generate(*outputStream, word, count);

    return 0;
}
catch (std::exception& e) {
    std::cout << "Error occured:\n\t" << e.what() << '\n';
    return -1;
}
catch (...) {
    std::cout << "Error occured:\n\tUnknown\n";
    return -1;
}