add_library(
    student_info_system
    student_info_system/util.c
    student_info_system/init.c
)

add_executable(main main.c)

target_link_libraries(main student_info_system)