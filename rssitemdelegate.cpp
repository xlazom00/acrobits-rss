#include "rssitemdelegate.h"

#include "rssitemui.h"

RssItemDelegate::RssItemDelegate()
{

}

QWidget * RssItemDelegate::createWidget(const std::shared_ptr<RssFeedItem> & rssFeedItem, QWidget * parent)
{
    auto widget = new RssItemUi( rssFeedItem, parent );
    return widget;

}
