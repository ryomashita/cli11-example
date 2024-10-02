#include <CLI/CLI.hpp>
#include <iostream>

int main(int argc, char **argv) {
    using std::cout;
    using std::endl;
    CLI::App app{"Flag example program"};

    /// [define]
    // CLI::Option フラグオプションの設定、取得を行うクラス
    CLI::Option *flag_plain = app.add_flag("--plain,-p", "This is a pure flag");

    bool flag_bool = false;
    app.add_flag("--bool,-b", flag_bool, "This is a bool flag")
        ->take_last();  // allow only once. `-b -b ...` becomes invalid.

    // will be set to count of times this flag was found.
    int flag_int = 0;
    app.add_flag("-i,--int", flag_int, "This is an countable flag");

    // フラグ変数にはbool型以外も使える (int, string, vector, ...)
    // ただし格納されるのは true/false のみ
    std::string flag_str = "default str";
    app.add_flag("-s,--str", flag_str, "This is a string flag");

    // ! をつけるとデフォルト値を false にできる
    bool flag_bool2 = false;
    app.add_flag("--flag,!--no-flag", flag_bool, "This is a bool flag");

    // bool 以外の場合は、中括弧でデフォルト値を指定できる
    int flag_int2 = 0;
    app.add_flag("-1{1}, -2{2}, -3{3}", flag_int2, "This is an int flag")
        ->take_last();  // デフォルトでは 複数指定 (`-123`)
                        // すると値が加算されていく

    // コールバック関数を指定できる
    // (呼び出されるのは、PARSE が全て完了した後)
    auto flag_callback = [](int count) {
        cout << "Flag callback: " << count << endl;
    };
    app.add_flag_function("-c,--callback", flag_callback,
                          "This is a callback flag");
    /// [define]

    /// [parser]
    CLI11_PARSE(app, argc, argv);
    /// [parser]

    /// [usage]
    cout << "The flags program" << endl;
    if (*flag_plain) cout << "Flag plain: " << flag_plain->count() << endl;
    if (flag_bool) cout << "flag_bool (-b) passed" << endl;
    if (flag_int > 0) cout << "Flag int: " << flag_int << endl;
    if (flag_int2 > 0) cout << "Flag int2: " << flag_int2 << endl;
    cout << "Flag string: " << flag_str << endl;
    /// [usage]
}
