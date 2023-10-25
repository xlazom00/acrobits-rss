#include "rssfeeddata.h"



RssFeedItem::RssFeedItem(const QString & title, const QString & description, const QString & link) : title(title), description(description), link(link)
{
}

RssFeedData::RssFeedData() = default;

void RssFeedData::addItem(const std::shared_ptr<RssFeedItem> & item)
{
    data.append(item);
}

bool RssFeedData::isEmpty()const
{
    return data.isEmpty();
}
