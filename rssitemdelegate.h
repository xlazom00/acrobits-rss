#ifndef RSSITEMDELEGATE_H
#define RSSITEMDELEGATE_H

#include <memory>


class QWidget;
class RssFeedItem;

class RssItemDelegate
{
public:
    RssItemDelegate();

    QWidget * createWidget(const std::shared_ptr<RssFeedItem> & rssFeedItem, QWidget * parent);
};

#endif // RSSITEMDELEGATE_H
