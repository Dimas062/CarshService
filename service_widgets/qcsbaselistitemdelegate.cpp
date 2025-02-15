#include "qcsbaselistitemdelegate.h"
#include <QPainter>

QCSBaseListItemDelegate::QCSBaseListItemDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{}



void QCSBaseListItemDelegate::paint( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    QStyleOptionViewItem newOption(option);
    initStyleOption(&newOption, index);

    newOption.font.setItalic(true);
    newOption.font.setPixelSize(20);

    QRect currentRect = option.rect;


    painter->drawRect(currentRect);

    const QAbstractItemModel *model = index.model();
    if (model)
    {
        QVariant varData = model->data(index,Qt::UserRole);
        if(varData != QVariant())
        {
            int color = varData.toInt();
            if(color == redColor)
                painter->fillRect(currentRect , QColor(240 , 50 , 50));
            if(color == greenColor)
                painter->fillRect(currentRect , QColor(50 , 240 , 50));
        }
    }
    // QBrush brushBackground;

    // brushBackground.setColor(Qt::red);

    // painter->fillRect(currentRect , brushBackground.color());

    //  newOption.decorationAlignment = Qt::AlignRight;


    return QStyledItemDelegate ::paint(painter , /*option*/ newOption , index);
}

QSize QCSBaseListItemDelegate::sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    QStyleOptionViewItem newOption(option);

    newOption.font.setPixelSize(20);

    QSize retVal = QStyledItemDelegate ::sizeHint(newOption , index);

    retVal.setHeight(retVal.height()+10);

    return (retVal);
}

QCSBaseListItemDelegate::~QCSBaseListItemDelegate()
{

}

