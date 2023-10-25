#ifndef RSSFEEDDATA_H
#define RSSFEEDDATA_H

#include <QString>
#include <QList>


class RssFeedItem
{
public:
    RssFeedItem(const QString & title, const QString & description, const QString & link);

public:
    QString title;
    QString description;
    QString link;
};


class RssFeedData
{
public:
    RssFeedData();
    void addItem(const std::shared_ptr<RssFeedItem> & item);
    bool isEmpty()const;

public:
    QList<std::shared_ptr<RssFeedItem>> data;
};

#endif // RSSFEEDDATA_H
