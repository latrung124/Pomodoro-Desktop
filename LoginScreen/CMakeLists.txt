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
        UserRegistrationPanel.qml
        ForgotPasswordPanel.qml
        AccountPage.qml
        PasswordPage.qml
        ThankyouPage.qml
        EnterYourEmailPage.qml
        OTPVerificationPage.qml
        ResetPasswordPage.qml
        PasswordResetSuccessPage.qml
    RESOURCES
        "Resources/arrow-left-large.png"
        "Resources/showcase-image.png"
)
