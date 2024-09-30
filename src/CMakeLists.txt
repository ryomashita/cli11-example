add_library(Add add.cpp)
set_normal_compile_options(Add)
set_warnings_as_errors(Add)

add_executable(minimum_cli11 minimum_cli11.cpp)
link_cli11(minimum_cli11)