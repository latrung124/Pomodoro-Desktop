qt_add_library(HomeScreen STATIC)

target_link_libraries(HomeScreen PRIVATE Qt6::Quick)

set_source_files_properties(HomeScreen.qml
    PROPERTIES
    QT_QML_SINGLETON_TYPE true
)

qt_add_qml_module(HomeScreen
    URI HomeScreen
    OUTPUT_DIRECTORY HomeScreen
    QML_FILES
        HomeScreen.qml
)
