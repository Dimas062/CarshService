#ifndef QCSSELECTWASHTYPESSWIDGET_H
#define QCSSELECTWASHTYPESSWIDGET_H

#include <QWidget>
#include <QPushButton>
#include "qcswashtypedlg.h"
#include <QUuid>
#include <QVector>

struct sWashButtonsDlgs
{
    QPushButton * m_pButton;
    QCSWashTypeDlg * m_pWashTypeDlg;
};

struct WashTypeDatas
{
    bool isSelected;
    QUuid id;
    int iDay;
    int iNigth;
};



class QCSSelectWashTypessWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QCSSelectWashTypessWidget(QWidget *parent = nullptr);
    QVector<sWashButtonsDlgs> m_vButtonsDlgs;

    QVector<WashTypeDatas> GetData();
    void SetData(QVector<WashTypeDatas>);

signals:

public slots:
    void OnButtonPress(bool);
};

#endif // QCSSELECTWASHTYPESSWIDGET_H
