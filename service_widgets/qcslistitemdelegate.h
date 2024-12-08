#ifndef QCSListItemDelegate_H
#define QCSListItemDelegate_H

#include <QStyledItemDelegate>

class QCSListItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    QCSListItemDelegate(QObject *parent);

    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;

    virtual ~QCSListItemDelegate();
};

#endif // QCSListItemDelegate_H
