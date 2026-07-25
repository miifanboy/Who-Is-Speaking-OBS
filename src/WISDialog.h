#ifndef CUSTOMDIALOG_H
#define CUSTOMDIALOG_H

#include <QDialog>
#include "WISDisplay.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

class WISDialog : public QDialog {
	Q_OBJECT // Required if you plan to use custom signals or slots later

public:
	explicit WISDialog(QWidget *parent = nullptr);
	~WISDialog();

private:
	// Store pointers as private members to access them in other methods
	QLabel *m_label;
	QLineEdit *m_lineEdit;
	QPushButton *m_button;
	QVBoxLayout *m_layout;
	OBSRenderWidget *m_renderWidget;
};

#endif // CUSTOMDIALOG_H
