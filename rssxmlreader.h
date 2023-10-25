#ifndef RSSXMLREADER_H
#define RSSXMLREADER_H

#include <QXmlStreamReader>
#include <memory>

class RssFeedData;

class RssXmlReader
{
public:
    RssXmlReader(const QByteArray & data);
    void parseData();
    std::shared_ptr<RssFeedData> getFeedData();

private:
    void readRss();
    void readChannel();
    void readItem();
    QString readTextElement();
    void ignoreElement();

private:
    QXmlStreamReader m_xmlReader;

    std::shared_ptr<RssFeedData> m_feedData;

};

#endif // RSSXMLREADER_H
