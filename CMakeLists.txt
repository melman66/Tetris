cmake_minimum_required(VERSION 3.19)
project(Tetris LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(Tetris
    src/main.cpp
    src/core/board.h src/core/board.cpp
    src/core/tetromino.h src/core/tetromino.cpp
    src/core/piece.h src/core/piece.cpp
    src/core/gameengine.h src/core/gameengine.cpp
    src/ui/boardview.h src/ui/boardview.cpp
    src/ui/nextpieceview.h src/ui/nextpieceview.cpp
    src/ui/mainwindow.h src/ui/mainwindow.cpp
)

target_link_libraries(Tetris
    PRIVATE
        Qt6::Core
        Qt6::Widgets
)

install(TARGETS Tetris
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Tetris
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
