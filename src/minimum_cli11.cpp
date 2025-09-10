#include <CLI/CLI.hpp>
#include <iostream>

int main(int argc, char **argv) {
    // CLI::App : the basis of all interactions with CLI11
    CLI::App app{"Minimum CLI11 example"};

    // show help message when an error occurs
    // default ではエラーメッセージのみ表示し, ヘルプは表示されない
    app.failure_message(CLI::FailureMessage::help);

    // define an option `-p`.
    int p = 0;  // with default value (0)
    app.add_option("-p", p, "Parameter p");

    // The options `-h`, `--help` are implicitly defined.

    CLI11_PARSE(app, argc, argv);
    // Expands to
    // try {
    //     (app).parse(argc, argv);
    // } catch (const CLI ::ParseError &e) {
    //     return (app).exit(e);
    // }

    std::cout << "Parameter p: " << p << '\n';
    return 0;
}

/*
`./minimum_cli11 -h` と呼び出すとヘルプが表示される:
```
Minimum CLI11 example
Usage: ./build/src/minimum_cli11 [OPTIONS]

Options:
  -h,--help                   Print this help message and exit
  -p INT                      Parameter p
```
*/