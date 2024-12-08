#ifndef QCSBASELISTITEMDELEGATE_H
#define QCSBASELISTITEMDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>

class QCSBaseListItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit QCSBaseListItemDelegate(QObject *parent = nullptr);


    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;

    virtual ~QCSBaseListItemDelegate();
};

#endif // QCSBASELISTITEMDELEGATE_H
