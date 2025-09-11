#include <CLI/CLI.hpp>
#include <iostream>

// Reference: https://cliutils.github.io/CLI11/book/chapters/options.html

int main(int argc, char** argv) {
    CLI::App app{"CLI11 Options example"};
    app.failure_message(CLI::FailureMessage::help);
    app.allow_windows_style_options();  // Enable Windows style options as well.
                                        // (e.g., /a, /long, /file:filename)

    // options := parameters with arguments

    // 整数パラメタを受け取る
    // 入力について:
    //  - (0, 0xAB, 0b1010, 1'000'000) いずれの形式にも対応している.
    // バインドする変数について:
    //  - フラグが渡されない場合は, デフォルト値が使われる
    //  - 引数に渡す値は、組み込み整数型でなくても、整数から生成可能な型 (enum
    //  や独自コンストラクタ) なら何でも良い.
    //  - `-` が無いと positional argument として扱われる
    int int_option = 1;
    app.add_option("-i,--int", int_option, "This is an int option")
        ->capture_default_str()      // display default value
        ->check(CLI::Range(0, 255))  // check with validator
        ->envname("INT_OPTION")      // フラグが渡されなかった場合,
                                     // 環境変数から値を取得する
        ->required();                // required option
    // 他にも envname (環境変数から取得), needs (他のオプションとの依存関係),
    // などの設定が可能

    // string option
    std::string str_option = "default-string";
    app.add_option("-s,--str", str_option, "This is a string option")
        ->disable_flag_override();  // 2回以上のフラグ入力を禁止する

    // file option
    std::string file_option = "default-file";
    app.add_option("-f,--file", file_option, "This is a file option")
        ->check(CLI::ExistingFile);  // check if file exists

    // tuple option
    std::tuple<int, std::string> tuple_option = {0, "default-string"};
    app.add_option("--tuple", tuple_option, "This is a tuple option");

    // enum option
    // map を用意すれば, 文字列("red") と 数値(0) の両方を受け付けられる
    enum class Color : int8_t { red = 0, green = 1, blue = 2 };
    const std::map<std::string, Color> color_map = {
        {"red", Color::red}, {"green", Color::green}, {"blue", Color::blue}};
    Color color_option{Color::red};
    app.add_option("--color", color_option, "This is an enum option")
        ->transform(CLI::CheckedTransformer(color_map, CLI::ignore_case))
        ->default_val("red");

    // vector option
    std::vector<int> vec_option;
    app.add_option("--vec", vec_option, "This is a vector option")
        ->delimiter(',')  // specify delimiter (空白区切り　' ' は常に有効)
        ->expected(0, 5)  // [0, 5] 個の値を受け取る (default: -1 := unlimited)
        ->check(CLI::Range(0, 10));  // check each value

    // Nested type
    std::map<int, std::pair<int, std::string>> nested_option;
    app.add_option("--nested", nested_option, "This is a nested option")
        ->delimiter(',')   // specify delimiter for outer container
        ->expected(0, 3);  // [0, 3] 個の値を受け取る (default: -1 := unlimited)

    // CLI11_PARSE(app, argc, argv);
    try {
        app.parse(
            "-i 2 --str hello --file src/flags.cpp --tuple 123 world --color "
            "Blue "
            "--vec 1,2,3 --nested 1,2,hello 3,4,world");
    } catch (const CLI::ParseError& e) {
        return app.exit(e);
    }

    std::cout << "-i,--int = " << int_option << '\n';
    std::cout << "-s,--str = " << str_option << '\n';
    std::cout << "-f,--file = " << file_option << '\n';
    std::cout << "--tuple = (" << std::get<0>(tuple_option) << ", "
              << std::get<1>(tuple_option) << ")" << '\n';
    std::cout << "--color = " << static_cast<int>(color_option) << '\n';
    std::cout << "--vec = {";
    for (const auto& v : vec_option) {
        std::cout << v << ' ';
    }
    std::cout << "}\n";
    std::cout << "--nested = {";
    for (const auto& [k, v] : nested_option) {
        std::cout << k << ":(" << v.first << "," << v.second << ") ";
    }
    std::cout << "}\n";
}
