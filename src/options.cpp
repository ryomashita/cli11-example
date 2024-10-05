#include <CLI/CLI.hpp>
#include <iostream>

int main(int argc, char** argv) {
    CLI::App app{"Minimum CLI11 example"};
    // options = parameters with arguments

    // - 整数 (e.g., 0, 0xAB, 0b1010, 1'000'000) パラメタを受け取る
    // - `-` が無いと positional argument として扱われる
    // - 整数型でなくても、整数から変換可能な型なら受け取れる
    int int_option = 0;
    app.add_option("-i,--int", int_option, "This is an int option")
        ->capture_default_str()  // display default value
        ->required();            // required option
    // 他にも envname (環境変数から取得), needs (他のオプションとの依存関係),
    // などの設定が可能

    // string option
    std::string str_option = "default-string";
    app.add_option("-s,--str", str_option, "This is a string option");

    // tuple option
    std::tuple<int, std::string> tuple_option = {0, "default-string"};
    app.add_option("--tuple", tuple_option, "This is a tuple option");

    CLI11_PARSE(app, argc, argv);

    std::cout << "-i,--int = " << int_option << std::endl;
    std::cout << "-s,--str = " << str_option << std::endl;
    std::cout << "--tuple = (" << std::get<0>(tuple_option) << ", "
              << std::get<1>(tuple_option) << ")" << std::endl;
}
