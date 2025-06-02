#include "qstringlistdlg.h"
#include <QLabel>
#include <QPushButton>
#include <QScrollerProperties>
#include <QScroller>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QEasingCurve>
#include <QListWidgetItem>
#include "service_widgets/qcsbaselistitemdelegate.h"
#include "service_widgets/qinputtextdlg.h"
#include "common.h"

extern QRect screenGeometry;
extern int iButtonHeight;

QStringListDlg::QStringListDlg(QStringList strList , QString strTitle , QWidget *parent, Qt::WindowFlags f ):QCSBaseDialog(parent , f )
{
    m_strList = strList;

    QVBoxLayout * pVMainLayout = new QVBoxLayout;

    QLabel * pTopLabel = new QLabel(QString("<b>%1<\b>").arg(strTitle));
    pVMainLayout->addWidget(pTopLabel);

    if(strTitle == "Номера")
        m_bIsGRZ = true;
    else m_bIsGRZ = false;

    m_pStrsListWidget = new QCSBaseListWidget();
#ifdef Q_OS_ANDRIOD
    m_pStrsListWidget->setFixedHeight(screenGeometry.height() - 340 - iButtonHeight*2);
#endif
#if defined Q_OS_IOS || defined Q_OS_WINDOWS
    m_pStrsListWidget->setFixedHeight(screenGeometry.height() - 240 - iButtonHeight*2);
#endif
    m_pStrsListWidget->setItemDelegate(new QCSBaseListItemDelegate(m_pStrsListWidget));

    QScrollerProperties sp;
    sp.setScrollMetric( QScrollerProperties::DragStartDistance, 0.001 );
    sp.setScrollMetric( QScrollerProperties::ScrollingCurve, QEasingCurve::Linear );
    QScroller* qs = QScroller::scroller( m_pStrsListWidget );
    qs->setScrollerProperties( sp );

    QScroller::grabGesture(m_pStrsListWidget, QScroller::TouchGesture);
    m_pStrsListWidget->setWordWrap(true);
    pVMainLayout->addWidget(m_pStrsListWidget);
    m_pStrsListWidget->addItems(strList);

    QHBoxLayout * pButtonsLayout = new QHBoxLayout;

    QPushButton * pAddButton = new QPushButton("Добавить");
    connect(pAddButton,SIGNAL(pressed()),this,SLOT(OnAddPressed()));
    pAddButton->setIcon(QIcon(":/icons/add_plus_insert_more_icon.png"));
    pButtonsLayout->addWidget(pAddButton);

    QPushButton * pRemButton = new QPushButton("Удалить");
    connect(pRemButton,SIGNAL(pressed()),this,SLOT(OnRemPressed()));
    pRemButton->setIcon(QIcon(":/icons/minus_orange_icon.png"));
    pButtonsLayout->addWidget(pRemButton);

    pVMainLayout->addLayout(pButtonsLayout);
    pVMainLayout->addSpacing(10);

    QPushButton * pApplyButton = new QPushButton("Внести");
    pApplyButton->setIcon(QIcon(":/icons/done_icon.png"));
    pApplyButton->setFixedWidth(screenGeometry.width()* 0.5);
    pApplyButton->setIconSize(QSize(iButtonHeight*0.75 , iButtonHeight*0.75));

    pVMainLayout->addWidget(pApplyButton, 0 , Qt::AlignHCenter);
    connect(pApplyButton,SIGNAL(released()),this,SLOT(OnApplyPressedSlot()));

    QPushButton * pCancelButton = new QPushButton("Отменить");
    pCancelButton->setIcon(QIcon(":/icons/remove_icon.png"));
    pCancelButton->setFixedWidth(screenGeometry.width()* 0.5);
    pCancelButton->setIconSize(QSize(iButtonHeight*0.75 , iButtonHeight*0.75));

    pVMainLayout->addWidget(pCancelButton, 0 , Qt::AlignHCenter);
    connect(pCancelButton,SIGNAL(released()),this,SLOT(reject()));

    this->setLayout(pVMainLayout);
}

void QStringListDlg::OnAddPressed()
{
    QInputTextDlg dlg;
    if(dlg.exec()==QDialog::Accepted)
    {
        if(dlg.GetText().length()>0)
        {
            if(m_bIsGRZ)
            {
                QStringList strGRZList = extractCarNumbers(dlg.GetText());
                foreach (QString strGrz, strGRZList) {
                    m_pStrsListWidget->addItem(strGrz);
                }
            }
            else
                m_pStrsListWidget->addItem(dlg.GetText());
        }
    }
}

void QStringListDlg::OnRemPressed()
{
    // Получить текущий выбранный элемент
    QList<QListWidgetItem*> selectedItems = m_pStrsListWidget->selectedItems();

    // Если есть выбранные элементы
    if (!selectedItems.isEmpty()) {
        // Удалить первый выбранный элемент (для множественного выбора потребуется цикл)
        QListWidgetItem* item = selectedItems.first();

        // Удалить через takeItem + delete
        int row = m_pStrsListWidget->row(item);
        delete m_pStrsListWidget->takeItem(row); // Освобождает память
    }
}

void QStringListDlg::OnApplyPressedSlot()
{
    m_strList.clear();
    QList<QListWidgetItem*> items = m_pStrsListWidget->findItems(QString(), Qt::MatchContains);
    for (QListWidgetItem* item : items) {
        m_strList << item->text();
    }
    accept();
}
