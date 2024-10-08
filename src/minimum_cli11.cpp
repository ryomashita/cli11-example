#include <CLI/CLI.hpp>
#include <iostream>

int main(int argc, char **argv) {
    // CLI::App : the basis of all interactions with CLI11
    CLI::App app{"Minimum CLI11 example"};
    // show help message when an error occurs
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

    std::cout << "Parameter p: " << p << std::endl;
    return 0;
}
