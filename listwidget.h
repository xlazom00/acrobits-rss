#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QScrollArea>

#include <memory>

class RssFeedData;
class RssItemDelegate;
class QAbstractListModel;

class ListWidget : public QScrollArea
{
    Q_OBJECT

public:
    explicit ListWidget( QWidget * parent = nullptr );
    ~ListWidget();

    void setItemDelegate( RssItemDelegate * newItemDelegate );

    void setData(std::shared_ptr<RssFeedData> feedData);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
    bool event( QEvent * event ) override;

private:
    void resetListWidget();

private:
    RssItemDelegate * m_itemDelegate = nullptr;

    mutable QSize m_widgetSize;
};

#endif // LISTWIDGET_H
