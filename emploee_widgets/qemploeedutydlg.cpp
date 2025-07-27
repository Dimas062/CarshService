#include "qemploeedutydlg.h"
#include <QEasingCurve>
#include <QGuiApplication>
#include <QPushButton>
#include <QScroller>
#include <QVBoxLayout>
#include <QPushButton>
#include <QUuid>
#include "common.h"
#include "service_widgets/qcsselectdialog.h"


extern QRect screenGeometry;
extern int iButtonHeight;

QEmploeeDutyDlg::QEmploeeDutyDlg()
{
    int iButtonHeight = (int)((screenGeometry.height()*0.7)/10)-10;

    QVBoxLayout * pVMainLayout = new QVBoxLayout;


    QPushButton * pSector1Button = new QPushButton("Ответственный за сектор 1");
    connect(pSector1Button,SIGNAL(pressed()),this,SLOT(OnSector1Pressed()));
    pSector1Button->setMaximumHeight(iButtonHeight*0.98);
    pSector1Button->setMinimumHeight(iButtonHeight*0.98);
    pVMainLayout->addWidget(pSector1Button);

    m_pSector1Label = new QLabel();
    pVMainLayout->addWidget(m_pSector1Label);

    pVMainLayout->addSpacing(15);

    QPushButton * pSector2Button = new QPushButton("Ответственный за сектор 2");
    connect(pSector2Button,SIGNAL(pressed()),this,SLOT(OnSector2Pressed()));
    pSector2Button->setMaximumHeight(iButtonHeight*0.98);
    pSector2Button->setMinimumHeight(iButtonHeight*0.98);
    pVMainLayout->addWidget(pSector2Button);

    m_pSector2Label = new QLabel();
    pVMainLayout->addWidget(m_pSector2Label);

    pVMainLayout->addSpacing(15);

    QPushButton * pSector3Button = new QPushButton("Ответственный за сектор 3");
    connect(pSector3Button,SIGNAL(pressed()),this,SLOT(OnSector3Pressed()));
    pSector3Button->setMaximumHeight(iButtonHeight*0.98);
    pSector3Button->setMinimumHeight(iButtonHeight*0.98);
    pVMainLayout->addWidget(pSector3Button);

    m_pSector3Label = new QLabel();
    pVMainLayout->addWidget(m_pSector3Label);

    pVMainLayout->addSpacing(15);

    QPushButton * pSector4Button = new QPushButton("Ответственный за сектор 4");
    connect(pSector4Button,SIGNAL(pressed()),this,SLOT(OnSector4Pressed()));
    pSector4Button->setMaximumHeight(iButtonHeight*0.98);
    pSector4Button->setMinimumHeight(iButtonHeight*0.98);
    pVMainLayout->addWidget(pSector4Button);

    m_pSector4Label = new QLabel();
    pVMainLayout->addWidget(m_pSector4Label);


    this->setLayout(pVMainLayout);

    m_sectorLabels = {
        {"fe4119bc-f3a0-460a-b1bb-15bef24e8c96", m_pSector1Label},
        {"8f4f0635-2f0b-4577-b895-62c8f98e4397", m_pSector2Label},
        {"2dc91773-df67-4c58-b13c-d72577eed32d", m_pSector3Label},
        {"3e4d61a4-af56-4547-976f-cb067a7c16af", m_pSector4Label}
    };

    updateDutyLabels();
}

void QEmploeeDutyDlg::OnSector1Pressed()
{
    QCSSelectDialog dlg("Пользователи", "Фамилия" ,false , true , QUuid() , "where СейчасНаРаботе <> 'false'");
    if(dlg.exec()==QDialog::Accepted)
    {
        QString strSelectedUserUuid = dlg.getCurId();

        QString strQuery = QString("update Дежурные set Сотрудник='%1' where id='fe4119bc-f3a0-460a-b1bb-15bef24e8c96'").arg(strSelectedUserUuid);
        execMainBDQueryUpdate(strQuery);

        updateDutyLabels();
    }
}

void QEmploeeDutyDlg::OnSector2Pressed()
{
    QCSSelectDialog dlg("Пользователи", "Фамилия" ,false , true , QUuid() , "where СейчасНаРаботе <> 'false'");
    if(dlg.exec()==QDialog::Accepted)
    {
        QString strSelectedUserUuid = dlg.getCurId();

        QString strQuery = QString("update Дежурные set Сотрудник='%1' where id='8f4f0635-2f0b-4577-b895-62c8f98e4397'").arg(strSelectedUserUuid);
        execMainBDQueryUpdate(strQuery);

        updateDutyLabels();
    }
}

void QEmploeeDutyDlg::OnSector3Pressed()
{
    QCSSelectDialog dlg("Пользователи", "Фамилия" ,false , true , QUuid() , "where СейчасНаРаботе <> 'false'");
    if(dlg.exec()==QDialog::Accepted)
    {
        QString strSelectedUserUuid = dlg.getCurId();

        QString strQuery = QString("update Дежурные set Сотрудник='%1' where id='2dc91773-df67-4c58-b13c-d72577eed32d'").arg(strSelectedUserUuid);
        execMainBDQueryUpdate(strQuery);

        updateDutyLabels();
    }
}

void QEmploeeDutyDlg::OnSector4Pressed()
{
    QCSSelectDialog dlg("Пользователи", "Фамилия" ,false , true , QUuid() , "where СейчасНаРаботе <> 'false'");
    if(dlg.exec()==QDialog::Accepted)
    {
        QString strSelectedUserUuid = dlg.getCurId();

        QString strQuery = QString("update Дежурные set Сотрудник='%1' where id='3e4d61a4-af56-4547-976f-cb067a7c16af'").arg(strSelectedUserUuid);
        execMainBDQueryUpdate(strQuery);

        updateDutyLabels();
    }
}

void QEmploeeDutyDlg::updateDutyLabels()
{

    // Создаем временный контейнер для данных
    QMap<QString, QString> dutyInfo;

    QString strQuery("SELECT d.id, u.\"Фамилия\", u.\"Имя\", u.\"Отчество\" "
        "FROM \"Дежурные\" d "
        "LEFT JOIN \"Пользователи\" u ON d.\"Сотрудник\" = u.id "
        "WHERE d.id IN ("
        "    'fe4119bc-f3a0-460a-b1bb-15bef24e8c96',"
        "    '8f4f0635-2f0b-4577-b895-62c8f98e4397',"
        "    '2dc91773-df67-4c58-b13c-d72577eed32d',"
        "    '3e4d61a4-af56-4547-976f-cb067a7c16af'"
        ")");

    qDebug()<<"QEmploeeDutyDlg::updateDutyLabels()";

    QList<QStringList> resEmpl = execMainBDQuery(strQuery);

    for(int iEmplCounter = 0 ; iEmplCounter < resEmpl.size() ; iEmplCounter++)
    {

        QString sectorId = resEmpl.at(iEmplCounter).at(0);
        QString lastName = resEmpl.at(iEmplCounter).at(1);
        QString firstName = resEmpl.at(iEmplCounter).at(2);
        QString patronymic = resEmpl.at(iEmplCounter).at(3);

        qDebug()<<sectorId<<" "<<firstName;

        QString displayText;
        if (lastName.isEmpty() || firstName.isEmpty()) {
            displayText = "Не задан";
        } else {
            displayText = QString("%1 %2.%3.")
                .arg(lastName)
                .arg(firstName.left(1))
                .arg(patronymic.isEmpty() ? "" : patronymic.left(1));
        }

        dutyInfo[sectorId] = displayText;
    }

    // Обновляем метки
    for (auto it = m_sectorLabels.constBegin(); it != m_sectorLabels.constEnd(); ++it) {
        const QString& sectorId = it.key();
        QLabel* label = it.value();

        qDebug()<<"Обновляем метки ";

        if (dutyInfo.contains(sectorId)) {
            label->setText(dutyInfo[sectorId]);
        } else {
            label->setText("Не задан");
        }

        // Дополнительное форматирование
        label->setAlignment(Qt::AlignCenter);

        if (label->text() == "Не задан") {
            label->setStyleSheet("color: #999999; font-style: italic;");
        } else {
            label->setStyleSheet("color: #000000; font-weight: bold;");
        }
    }

    qDebug() << "Duty labels updated successfully";
}
