#include <CLI/CLI.hpp>
#include <iostream>
#include <string>

int main(int argc, char **argv) {
    CLI::App app("Validator checker");

    // option には check() で validator を設定できる
    // validator : std::function<std::string(std::string &)>
    //  -> 成功時は "" , 失敗時はエラーメッセージを返す
    std::string file;
    app.add_option("-f,--file", file, "File name")  // option with validator
        ->check(CLI::ExistingFile);                 // check if file exists

    int count{0};
    app.add_option("-v,--value", count, "Value in range")
        ->check(CLI::Range(0, 100));  // check if value is in range [0, 100]
    CLI11_PARSE(app, argc, argv);

    std::cout << "-f,--file: " << file << std::endl;
    std::cout << "-v,--value: " << count << std::endl;

    return 0;
}
