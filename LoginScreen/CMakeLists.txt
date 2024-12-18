qt_add_library(LoginScreen STATIC)

qt_import_qml_plugins(CommonComponent)

target_link_libraries(LoginScreen PRIVATE
                        Qt6::Quick
                        CommonComponentplugin)

set_source_files_properties(LoginScreen.qml
    PROPERTIES
    QT_QML_SINGLETON_TYPE true
)

set(panels
    Panels/UserRegistrationPanel.qml
    Panels/ForgotPasswordPanel.qml
)

foreach(panel ${panels})
    get_filename_component(panel_name ${panel} NAME)
    set_source_files_properties(${panel} PROPERTIES QT_RESOURCE_ALIAS ${panel_name})
endforeach()

set(pages
    Panels/Pages/AccountPage.qml
    Panels/Pages/PasswordPage.qml
    Panels/Pages/ThankyouPage.qml
    Panels/Pages/EnterYourEmailPage.qml
    Panels/Pages/OTPVerificationPage.qml
    Panels/Pages/ResetPasswordPage.qml
    Panels/Pages/PasswordResetSuccessPage.qml
)

foreach(pages ${pages})
    get_filename_component(pages_name ${pages} NAME)
    set_source_files_properties(${pages} PROPERTIES QT_RESOURCE_ALIAS ${pages_name})
endforeach()

qt_add_qml_module(LoginScreen
    URI LoginScreen
    OUTPUT_DIRECTORY LoginScreen
    QML_FILES
        LoginScreen.qml
        Panels/LoginPanel.qml
        Panels/UserRegistrationPanel.qml
        Panels/ForgotPasswordPanel.qml
        Panels/Pages/AccountPage.qml
        Panels/Pages/PasswordPage.qml
        Panels/Pages/ThankyouPage.qml
        Panels/Pages/EnterYourEmailPage.qml
        Panels/Pages/OTPVerificationPage.qml
        Panels/Pages/ResetPasswordPage.qml
        Panels/Pages/PasswordResetSuccessPage.qml
    RESOURCES
        "Resources/arrow-left-large.png"
        "Resources/showcase-image.png"
)
