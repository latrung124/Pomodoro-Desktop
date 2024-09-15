qt_add_library(CommonComponent STATIC)

target_link_libraries(CommonComponent PRIVATE Qt6::Quick)

# set_source_files_properties(CustomTextField.qml
#     PROPERTIES
# )

qt_add_qml_module(CommonComponent
    URI CommonComponent
    VERSION 1.0
    OUTPUT_DIRECTORY CommonComponent
    QML_FILES
        CustomTextField.qml
        CustomToggle.qml
)
