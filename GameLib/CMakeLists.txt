project(GameLib)

set(SOURCE_FILES
        MainFrame.cpp
        MainFrame.h
        pch.h
        GameView.cpp
        GameView.h
        ids.h
        Game.cpp
        Game.h
        Item.cpp
        Item.h
        Background.cpp
        Background.h
        TaskView.cpp
        TaskView.h
        TaskManager.cpp
        TaskManager.h
        Task.cpp
        Task.h
        Plant.cpp
        Plant.h
        Bank.cpp
        Bank.h
        Sunflower.cpp
        Sunflower.h
        Rose.cpp
        Rose.h
        Cactus.cpp
        Cactus.h
        Flytrap.cpp
        Flytrap.h
        TaskDlgBox.cpp
        TaskDlgBox.h
        Fern.cpp
        Fern.h)

set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})