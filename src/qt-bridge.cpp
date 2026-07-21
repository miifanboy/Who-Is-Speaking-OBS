#include "qt-bridge.h"


#include <QCoreApplication>
#include <QMetaObject>
#include <QDialog>
#include <QWidget>
#include <obs-frontend-api.h>

void open_qt_settings_dialog(void)
{
    QMetaObject::invokeMethod(
        qApp,
        []() {
            QWidget *main_win = static_cast<QWidget*>(obs_frontend_get_main_window());
            QDialog dialog(main_win);
            dialog.setWindowTitle("Settings");
            dialog.resize(400, 300);
            dialog.exec();
        
        },
        Qt::QueuedConnection
    );
}