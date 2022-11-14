add_executable(mikubot
    src/main.cpp
    src/mikubot.cpp

    src/command/commandregistry.cpp
    src/command/command.cpp
    src/command/option.cpp

    src/module/modulemanager.cpp
    src/module/help.cpp
)

target_compile_features(mikubot PRIVATE cxx_std_17)

target_include_directories(mikubot
    PUBLIC include
)

target_link_libraries(mikubot
    dpp
)
