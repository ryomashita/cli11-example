#include <CLI/CLI.hpp>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    CLI::App app{"CLI11 Subcommands example"};
    app.failure_message(CLI::FailureMessage::help);

    // サブコマンドを追加する
    CLI::App& app_sub = *app.add_subcommand("sub", "Some subcommand");

    // Option の追加 (通常のオプションと同じ)
    std::string sub_opt1;
    app_sub.add_option("sub_opt1", sub_opt1, "Argument for subcommand")
        ->required();
    
    // Add more subcommands
    CLI::App& app_dub = *app.add_subcommand("dub", "Some dubcommand");
    std::string dub_opt1;
    app_dub.add_option("dub_opt1", dub_opt1, "Argument for dubcommand")
        ->required();

    CLI11_PARSE(app, argc, argv);

    std::cout << "sub passed? : " << std::boolalpha << app_sub.parsed() << '\n';
    std::cout << "sub_opt1: " << sub_opt1 << '\n';

    // サブコマンドを指定した場合, help() はそのサブコマンドのヘルプを表示する
    std::cout << app.help() << '\n';
    return 0;
}
