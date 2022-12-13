add_executable(test_zlog
    test/src/main.cpp 
    zlog/test/zlog_test.cpp
)
target_compile_options(test_zlog PRIVATE -Werror -Wall -Wextra -Wconversion)

add_subdirectory(zlog)

# Link the test executable
target_link_libraries(test_zlog 
    PRIVATE 
        gtest 
        gmock
        zlog
)
