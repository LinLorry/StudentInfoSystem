add_library(
    student_info_system
    student_info_system/base.c
    student_info_system/util.c
    student_info_system/init.c
    student_info_system/user.c
    student_info_system/student.c
    student_info_system/course.c
    student_info_system/grade.c
)

add_executable(main main.c user_view.c student_view.c course_view.c grade_view.c)

target_link_libraries(main student_info_system)