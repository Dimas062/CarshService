#include "qwashpartnerpendlg.h"
#include <QVBoxLayout>
#include <QLabel>
#include "pictures/qpictureswidget.h"
#include "common.h"

QWashPartnerPenDlg::QWashPartnerPenDlg(QUuid idPen , QWidget *parent, Qt::WindowFlags f ):QCSBaseDialog(parent , f)
{
    QVBoxLayout * pVMainLayout = new QVBoxLayout;

    pVMainLayout->addSpacing(5);
    QLabel * pTopLabel = new QLabel(QString("<b>Рекламация.</b>"));
    pTopLabel->setStyleSheet("font-size: 20px;\
                                     color: black;");
    pVMainLayout->addWidget(pTopLabel);

    QString strExec= QString("select \"Отмена Мойки\".id, \"Отмена Мойки\".Количество, \"Отмена Мойки\".Ночь , \"Типы задач Мойка\".Тип from \"Отмена Мойки\" , \"Типы задач Мойка\" where \"Отмена Мойки\".Тип = \"Типы задач Мойка\".id and \"Отмена Мойки\".id = '%1' and \"Отмена Мойки\".Удалено=false").arg(idPen.toString());

    QList<QStringList> resPens = execMainBDQuery(strExec);

    QLabel * pPenLabel = new QLabel(QString("<b>Рекламация.</b>"));
    pPenLabel->setStyleSheet("font-size: 16px;\
                                     color: black;");

    for(int iPensCounter = 0 ; iPensCounter < resPens.size() ; iPensCounter++)
    {
        QString strNigth("День");
        if(resPens.at(iPensCounter).at(2) == "true") strNigth="Ночь";
        QString strPens  = QString("%1(%2)\n Количество: %3.").arg(resPens.at(iPensCounter).at(3)).arg(strNigth).arg(resPens.at(iPensCounter).at(1));
        pPenLabel->setText(strPens);
    }

    pVMainLayout->addWidget(pPenLabel);

    QPicturesWidget * pPicturesWidget = new QPicturesWidget(this , true);
   // pPicturesWidget->setMinimumHeight(400);
    pVMainLayout->addWidget(pPicturesWidget);

    /*Загрузка картинок задачи*/
    QString strPicExec = QString("select Документы.Изображение from Документы, \"Задача-Документы задач\" where Документы.id=\"Задача-Документы задач\".Документ and \"Задача-Документы задач\".Задача='%1'").arg(idPen.toString());

    qDebug()<<   strPicExec;
    QList<QStringList> resPicTasks = execMainBDQuery(strPicExec);
    for(int iPicTasksCounter = 0 ; iPicTasksCounter < resPicTasks.size() ; iPicTasksCounter++)
    {
        QString tmpStr = resPicTasks.at(iPicTasksCounter).at(0);
        QImage tmpImg = Base64ToImage(tmpStr);
        pPicturesWidget->AddImage(tmpImg);
    }

    this->setLayout(pVMainLayout);
}
