#include <CLI/CLI.hpp>
#include <iostream>

// Reference: https://cliutils.github.io/CLI11/book/chapters/flags.html

int main(int argc, char **argv) {
    using std::cout;
    using std::endl;
    CLI::App app{"CLI11 flags example program"};

    // flags := parameters with no arguments

    /// [define]
    // フラグ名は `,` 区切りで指定
    // パース結果は `CLI::Option` に格納される.
    // CLI::Option methos:
    // - count() : フラグの見つかった回数
    // - empty() : フラグが見つからなかった場合 true
    // - operator bool() : フラグが見つかった場合 true
    // - clear() : パース結果をクリア
    CLI::Option *flag_plain = app.add_flag("--plain,-p", "This is a pure flag");

    /* `CLI:Option` の代わりに結果を直接格納できる */

    // bool -> true or false が格納される
    bool flag_bool = false;
    app.add_flag("--bool,-b", flag_bool, "This is a bool flag");

    // string -> "true" or "false" が格納される
    std::string flag_str = "default str";
    app.add_flag("-s,--str", flag_str, "This is a string flag");

    // int -> flag の見つかった回数が格納される
    int flag_int = 0;
    app.add_flag("-i,--int", flag_int, "This is an countable flag");

    // function -> コールバック関数を指定できる
    // (呼び出されるのは、PARSE が全て完了した後)
    auto flag_callback = [](int count) {
        cout << "Flag callback: " << count << '\n';
    };
    app.add_flag_function("-c,--callback", flag_callback,
                          "This is a callback flag");

    /* Other usages */

    // ! をつけると false 値のフラグを定義できる
    bool flag_bool_no = false;
    app.add_flag("--flag,!--no-flag", flag_bool_no, "This is a bool flag");

    // 中括弧で格納する値を指定できる
    // take_last() : 複数指定されたら最後の値を返す (e.g., `-123` -> 3)
    //  In default, 複数指定すると値が加算される (e.g., `-123` -> 6)
    // その他は MultiOptionPolicy 参照
    int flag_int2 = 0;
    app.add_flag("-1{0x1}, -2{0b2}, -3{0x3}", flag_int2, "This is an int flag")
        ->take_last();
    /// [define]

    /// [parser]
    // CLI11_PARSE(app, argc, argv); -> parse command line arguments
    // app.parse(argc, argv); も同じ.

    // parse(string) -> std::string をパースする
    // 2nd arg (program_name_included) = argv[0] に対応するプログラム名を含むか
    try {
        app.parse("-pbsic --no-flag -123", false);
    } catch (const CLI::ParseError &e) {
        return app.exit(e); // print help or error message
    }
    /// [parser]

    /// [usage]
    cout << "The flags program" << '\n';
    cout << "Flag name:" << flag_plain->get_name() << '\n'
        << "\tpassed: " << std::boolalpha <<  static_cast<bool>(flag_plain) << '\n'
        << "\tcount: " << flag_plain->count() << '\n';
    if (flag_bool) cout << "flag_bool (-b) passed" << '\n';
    cout << "flag_bool_no (--flag/--no-flag) passed: " << std::boolalpha << flag_bool_no << '\n';
    if (flag_int > 0) cout << "Flag int: " << flag_int << '\n';
    if (flag_int2 > 0) cout << "Flag int2: " << flag_int2 << '\n';
    cout << "Flag string: " << flag_str << '\n';
    /// [usage]

    // print help message
    // このプログラムでは help() の `AppFormatMode::All` を指定しても結果は Normal と同じ.
    cout << "Help message:" << '\n';
    cout << app.help() << '\n';
}
