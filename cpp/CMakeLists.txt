add_executable(test_zlog
    test/src/main.cpp 
    log/test/log_test.cpp
)
target_compile_options(test_zlog PRIVATE -Werror -Wall -Wextra -Wconversion)

add_subdirectory(log)

# Link the test executable
target_link_libraries(test_zlog 
    PRIVATE 
        gtest 
        gmock
        log
)
