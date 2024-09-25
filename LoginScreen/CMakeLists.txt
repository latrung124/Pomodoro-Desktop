qt_add_library(LoginScreen STATIC)

qt_import_qml_plugins(CommonComponent)

target_link_libraries(LoginScreen PRIVATE
                        Qt6::Quick
                        CommonComponentplugin)

set_source_files_properties(LoginScreen.qml
    PROPERTIES
    QT_QML_SINGLETON_TYPE true
)

qt_add_qml_module(LoginScreen
    URI LoginScreen
    OUTPUT_DIRECTORY LoginScreen
    QML_FILES
        LoginScreen.qml
        LoginPanel.qml
    RESOURCES
        "Resources/showcase-image.png"
        "Resources/google-logo-240x240.png"
)
