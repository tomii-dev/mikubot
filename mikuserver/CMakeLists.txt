add_executable(mikuserver
    src/main.cpp
    src/mikuserver.cpp

    src/system/system.cpp
    src/system/systemmanager.cpp
    src/system/storage.cpp
)

target_compile_features(mikuserver PRIVATE cxx_std_17)

target_include_directories(mikuserver
    PUBLIC include
)

target_link_libraries(mikuserver
    httpserver
)
