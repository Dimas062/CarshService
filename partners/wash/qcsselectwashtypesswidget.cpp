#include "qcsselectwashtypesswidget.h"
#include <QVBoxLayout>
#include "common.h"
#include <QUuid>
#include <QPushButton>
#include "qcswashtypedlg.h"

extern QRect screenGeometry;
extern QUuid uuidCurrentUser;



QCSSelectWashTypessWidget::QCSSelectWashTypessWidget(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout * pVMainLayout = new QVBoxLayout;
    this->setLayout(pVMainLayout);


    QString strExec = QString("select id , Тип from \"Типы задач Мойка\" where Удалено<>'true' ");

    QList<QStringList> resData = execMainBDQuery(strExec);
    for(int iResCounter = 0 ; iResCounter < resData.size() ; iResCounter++)
    {
        QCSWashTypeDlg * pTypeDlg = new QCSWashTypeDlg(resData.at(iResCounter).at(1));




        //QPushButton * pButton = createQPushButtonWithWordWrap(nullptr , pTypeDlg->getText());
            /*= new QPushButton();
        pButton->setMaximumWidth(screenGeometry.width() - 50);


        QFontMetrics metrics(pButton->font());
        QString strWrappedButtonText = metrics.elidedText(
            pTypeDlg->getText(),
            Qt::ElideRight,
            Qt::TextWordWrap,
            //pButton->width() // Ширина кнопки
            200
            );

        pButton->setText(strWrappedButtonText);*/

        QPushButton * pButton = new QPushButton(wrapText(pTypeDlg->getText() , 30));
        // pButton->setMaximumWidth(screenGeometry.width() - 50);
        // pButton->setFixedHeight(40);

        pButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        pButton->setMinimumHeight(40); // Минимальная высота для многострочного текста


        connect(pButton,SIGNAL(toggled(bool)),this,SLOT(OnButtonPress(bool)));
        pButton->setMinimumWidth(screenGeometry.width()*0.6);
        pButton->setProperty("id",QVariant(QString(resData.at(iResCounter).at(0))));
        pButton->setCheckable(true);
        pVMainLayout->addWidget(pButton);



        sWashButtonsDlgs sWashDlg;
        sWashDlg.m_pButton = pButton;
        sWashDlg.m_pWashTypeDlg = pTypeDlg;

        m_vButtonsDlgs.push_back(sWashDlg);
    }

}

void QCSSelectWashTypessWidget::OnButtonPress(bool toggled)
{
    if(toggled)
    {
        QPushButton * pButton = (QPushButton *)sender();

        foreach (sWashButtonsDlgs sWashDlg, m_vButtonsDlgs) {
            if(sWashDlg.m_pButton == pButton)
            {
                sWashDlg.m_pWashTypeDlg->exec();
                sWashDlg.m_pButton->setText(wrapText(sWashDlg.m_pWashTypeDlg->getText(), 30));
                sWashDlg.m_pButton->update();
            }
        }
    }
}

QVector<WashTypeDatas> QCSSelectWashTypessWidget::GetData()
{
    QVector<WashTypeDatas> retVal;

    foreach (sWashButtonsDlgs sWashDlg, m_vButtonsDlgs) {
        WashTypeDatas curData;

        curData.id = sWashDlg.m_pButton->property("id").toUuid();

        curData.isSelected = sWashDlg.m_pButton->isChecked();

        if(sWashDlg.m_pWashTypeDlg->m_pDayButton->isChecked())
            curData.iDay = sWashDlg.m_pWashTypeDlg->m_pDayNumberLineText->getText().toInt();
        else curData.iDay = 0;

        if(sWashDlg.m_pWashTypeDlg->m_pNigthButton->isChecked())
            curData.iNigth = sWashDlg.m_pWashTypeDlg->m_pNigthNumberLineText->getText().toInt();
        else curData.iNigth = 0;

        retVal.push_back(curData);
    }
    return retVal;
}

void QCSSelectWashTypessWidget::SetData(QVector<WashTypeDatas> datas)
{
    foreach(WashTypeDatas data , datas)
    {
        /*шщем нужную кнопку, что бы задать ей и привязанным к ней виджетам нужные настройки*/
        foreach (sWashButtonsDlgs sWashDlg, m_vButtonsDlgs) {
            if(data.id == sWashDlg.m_pButton->property("id").toUuid())
            {
                disconnect(sWashDlg.m_pButton,SIGNAL(toggled(bool)),this,SLOT(OnButtonPress(bool)));
                sWashDlg.m_pButton->setChecked(data.isSelected);
                connect(sWashDlg.m_pButton,SIGNAL(toggled(bool)),this,SLOT(OnButtonPress(bool)));
                if(data.iDay == 0)
                {
                    sWashDlg.m_pWashTypeDlg->m_pDayButton->setChecked(false);
                    sWashDlg.m_pWashTypeDlg->m_pDayNumberLineText->setText("0");
                    sWashDlg.m_pWashTypeDlg->m_pDayNumberLineText->SetEnabled(false);
                }
                else
                {
                    sWashDlg.m_pWashTypeDlg->m_pDayButton->setChecked(true);
                    sWashDlg.m_pWashTypeDlg->m_pDayNumberLineText->setText(QString("%1").arg(data.iDay));
                    sWashDlg.m_pWashTypeDlg->m_pDayNumberLineText->SetEnabled(true);
                }

                if(data.iNigth == 0)
                {
                    sWashDlg.m_pWashTypeDlg->m_pNigthButton->setChecked(false);
                    sWashDlg.m_pWashTypeDlg->m_pNigthNumberLineText->setText("0");
                    sWashDlg.m_pWashTypeDlg->m_pNigthNumberLineText->SetEnabled(false);
                }
                else
                {
                    sWashDlg.m_pWashTypeDlg->m_pNigthButton->setChecked(true);
                    sWashDlg.m_pWashTypeDlg->m_pNigthNumberLineText->setText(QString("%1").arg(data.iNigth));
                    sWashDlg.m_pWashTypeDlg->m_pNigthNumberLineText->SetEnabled(true);
                }
            }
        }
    }

    /*Обновим надписи на всех кнопках*/
    foreach (sWashButtonsDlgs sWashDlg, m_vButtonsDlgs) {
        sWashDlg.m_pButton->setText(wrapText(sWashDlg.m_pWashTypeDlg->getText() , 30));
    }

    if (layout()) {
        layout()->invalidate();
        layout()->activate();
    }
    updateGeometry();
    adjustSize();
}
