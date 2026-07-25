#include "qt-bridge.h"


#include <QCoreApplication>
#include <QMetaObject>
#include <QDialog>
#include <QWidget>
#include <obs-frontend-api.h>
#include "WISDialog.h"
void open_qt_settings_dialog(void)
{
    QMetaObject::invokeMethod(
        qApp,
        []() {
            QWidget *main_win = static_cast<QWidget*>(obs_frontend_get_main_window());
            WISDialog dialog(main_win);
            dialog.setWindowTitle("Settings");
            dialog.resize(960, 540);
            dialog.exec();
        
        },
        Qt::QueuedConnection
    );
}