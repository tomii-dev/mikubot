add_executable(mikubot
    src/main.cpp
    src/mikubot.cpp
    src/client.cpp

    src/util/num.cpp

    src/command/commandregistry.cpp
    src/command/command.cpp
    src/command/option.cpp

    src/module/modulemanager.cpp
    src/module/module.cpp
    src/module/help.cpp
    src/module/voice.cpp
    src/module/storage.cpp
)

target_compile_features(mikubot PRIVATE cxx_std_17)

target_include_directories(mikubot
    PUBLIC include
    PUBLIC ${RAPIDJSON_INCLUDE_DIR}
)

target_link_libraries(mikubot
    dpp
    curl
    curlpp
)
