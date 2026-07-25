#include "WISDialog.h"
#include "WISDisplay.h"
// Include the full headers needed for implementation

WISDialog::WISDialog(QWidget *parent) : QDialog(parent)
{
	setWindowTitle("My Custom Dialog");

	// 1. Create the UI elements
	m_renderWidget = new OBSRenderWidget(this);
	m_label = new QLabel("Enter your name:", this);
	m_lineEdit = new QLineEdit(this);
	m_button = new QPushButton("Submit", this);

	// 2. Create the layout manager
	m_layout = new QVBoxLayout(this);

	// 3. Add elements to the layout
	m_layout->addWidget(m_renderWidget);
	m_layout->addWidget(m_label);
	m_layout->addWidget(m_lineEdit);
	m_layout->addWidget(m_button);

	// 4. Apply the layout to the dialog
	setLayout(m_layout);
}

WISDialog::~WISDialog()
{
	// Qt handles memory cleanup automatically for child widgets,
	// so leaving this empty is safe.
}
