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
    currentRect.adjust(4,4,-4,-4);

    painter->drawRect(currentRect);

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

