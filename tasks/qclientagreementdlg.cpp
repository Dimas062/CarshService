#include "qclientagreementdlg.h"
#include <QGuiApplication>
#include <QVBoxLayout>
#include "common.h"

extern QRect screenGeometry;
extern QUuid uuidCurrentUser;
extern int iButtonHeight;
extern UserTypes CurrentUserType;
extern QColor currentWorkdayColor;

QClientAgreementDlg::QClientAgreementDlg(QWidget *parent, Qt::WindowFlags f ):QCSBaseDialog(parent , f /*, false*/)
{

    QVBoxLayout * pVMainLayout = new QVBoxLayout;

    m_pTopLabel = new QLabel(QString("<b>Клиент<\b>"));
    pVMainLayout->addWidget(m_pTopLabel);

    m_pFIOLineText = new QLineText("ФИО:");
    pVMainLayout->addWidget(m_pFIOLineText);

    m_pGRZLineText = new QLineText("ГРЗ:");
    pVMainLayout->addWidget(m_pGRZLineText);

    m_pLoadPassportWidget= new QLoadDocLineWidget("Па");
    pVMainLayout->addWidget(m_pLoadPassportWidget);

    QLoadDocLineWidget * m_pLoadPTSWidget;
    QLoadDocLineWidget * m_pLoadLicWidget;


    this->setLayout(pVMainLayout);
}
