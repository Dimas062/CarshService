#include "qcsbaselistitemdelegate.h"
#include <QPainter>
#include <QTextDocument>

QCSBaseListItemDelegate::QCSBaseListItemDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{}



void QCSBaseListItemDelegate::paint( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    // QStyleOptionViewItem options = option;
    // initStyleOption(&options, index);

    // painter->save();

    // options.font.setItalic(true);
    // options.font.setPixelSize(20);

    // // Получаем прямоугольник иконки
    // const QRect iconRect = options.widget->style()->subElementRect(
    //     QStyle::SE_ItemViewItemIcon, &options, options.widget
    //     );

    // QRect currentRect = option.rect;


    // painter->drawRect(currentRect);

    // const QAbstractItemModel *model = index.model();
    // if (model)
    // {
    //     QVariant varData = model->data(index,Qt::UserRole);
    //     if(varData != QVariant())
    //     {
    //         int color = varData.toInt();
    //         if(color == redColor)
    //             painter->fillRect(currentRect , QColor(240 , 50 , 50));
    //         if(color == greenColor)
    //             painter->fillRect(currentRect , QColor(50 , 240 , 50));
    //     }
    // }


    // QTextDocument doc;
    // doc.setHtml(options.text);

    // // Настройки переноса
    // QTextOption textOption;
    // textOption.setWrapMode(QTextOption::WordWrap);
    // doc.setDefaultTextOption(textOption);
    // doc.setTextWidth(options.rect.width());

    // options.text.clear();
    // options.widget->style()->drawControl(QStyle::CE_ItemViewItem, &options, painter);

    // // Смещаем текст относительно иконки
    // painter->translate(
    //     options.rect.left() + iconRect.width(),
    //     options.rect.top()
    //     );

    // // Отрисовываем текст с учетом новой позиции
    // QRect textRect(0, 0, options.rect.width() - iconRect.width(), options.rect.height());
    // doc.drawContents(painter, textRect);

    // painter->restore();

    QStyleOptionViewItem options = option;
    initStyleOption(&options, index);

    painter->save();

    // // Получаем цвет текста из текущей палитры
    // QPalette::ColorGroup cg = option.state & QStyle::State_Enabled
    //                               ? QPalette::Normal : QPalette::Disabled;
    // if (cg == QPalette::Normal && !(option.state & QStyle::State_Active))
    //     cg = QPalette::Inactive;

    // QColor textColor = option.palette.color(cg, QPalette::Text);

    // Получаем прямоугольник иконки
    const QRect decorationRect = options.widget->style()->subElementRect(
        QStyle::SE_ItemViewItemDecoration, &options, options.widget
        );

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


    QTextDocument doc;
    doc.setDocumentMargin(0); // Убираем стандартные отступы
    doc.setDocumentMargin(0);
    // doc.setHtml(QString("<span style='color:%1;'>%2</span>")
    //                 .arg(textColor.name())
    //                 .arg(options.text));
    doc.setHtml(QString("<span style='color:black;'>%1</span>")
                   // .arg(textColor.name())
                    .arg(options.text));

    // Настройки текста
    QTextOption textOption;
    textOption.setWrapMode(QTextOption::WordWrap);
    doc.setDefaultTextOption(textOption);
    doc.setTextWidth(options.rect.width() - decorationRect.width() - 8 - 40);

    // Отрисовываем стандартные элементы
    options.text.clear();
    options.widget->style()->drawControl(QStyle::CE_ItemViewItem, &options, painter);

    // Смещаем текст относительно иконки
    const int textLeft = decorationRect.right() + 4;
    painter->translate(textLeft, options.rect.top() + 2);

    // Отрисовываем текст
    QRect clip(0, 0, options.rect.width() - textLeft, options.rect.height() - 4);
    doc.drawContents(painter, clip);

    painter->restore();
}

QSize QCSBaseListItemDelegate::sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    // QStyleOptionViewItem options = option;
    // initStyleOption(&options, index);

    // options.font.setPixelSize(20);

    // // Получаем размер иконки
    // const QSize iconSize = options.icon.actualSize(options.decorationSize);

    // QTextDocument doc;
    // doc.setHtml(options.text);

    // // // Учитываем реальную ширину виджета
    // // const int widgetWidth = options.widget->width()
    // //                         - options.widget->style()->pixelMetric(QStyle::PM_ScrollBarExtent)
    // //                         - 10; // Небольшой отступ

    // // Рассчитываем доступную ширину с учетом иконки
    // const int availableWidth = options.rect.width() - iconSize.width() - 8; // + отступ

    // // Настройки переноса
    // QTextOption textOption;
    // textOption.setWrapMode(QTextOption::WordWrap);
    // doc.setDefaultTextOption(textOption);
    // doc.setTextWidth(availableWidth);

    //     return QSize(
    //         options.rect.width(),
    //         qMax(iconSize.height(), static_cast<int>(doc.size().height()))+ QSize(0, 4)); // Небольшой вертикальный отступ

    // //return QSize(doc.idealWidth(), doc.size().height() + 10);

    QStyleOptionViewItem options = option;
    initStyleOption(&options, index);

    // Размер иконки
    const QSize iconSize = options.icon.isNull()
                               ? QSize(0, 0)
                               : options.icon.actualSize(options.decorationSize);

    // Доступная ширина для текста
    const int textWidth = options.widget->contentsRect().width()
                          - iconSize.width()
                          - 12 - 40; // Суммарные отступы

    QTextDocument doc;
    doc.setDocumentMargin(0); // Важно: убираем внутренние отступы
    doc.setHtml(options.text);

    QTextOption textOption;
    textOption.setWrapMode(QTextOption::WordWrap);
    doc.setDefaultTextOption(textOption);
    doc.setTextWidth(textWidth);

    // Рассчитываем высоту текста
    const int textHeight = doc.size().height();

    // Общая высота элемента
    const int totalHeight = qMax(iconSize.height(), textHeight) + 4;

    return QSize(options.widget->width() - 40, totalHeight);
}

QCSBaseListItemDelegate::~QCSBaseListItemDelegate()
{

}

