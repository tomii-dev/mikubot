add_executable(mikubot
    src/main.cpp
    src/mikubot.cpp
)

target_compile_features(mikubot PRIVATE cxx_std_17)

target_include_directories(mikubot
    PUBLIC include
)

target_link_libraries(mikubot
    dpp
)
