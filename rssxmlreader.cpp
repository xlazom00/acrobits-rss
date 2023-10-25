#include "rssxmlreader.h"

#include "rssfeeddata.h"

RssXmlReader::RssXmlReader(const QByteArray & data) : m_feedData(std::make_shared<RssFeedData>())
{
    m_xmlReader.addData(data);
}

std::shared_ptr<RssFeedData> RssXmlReader::getFeedData()
{
    return m_feedData;
}

void RssXmlReader::beginReading()
{


    while(m_xmlReader.readNextStartElement())
    {
        auto name = m_xmlReader.name();
        if(name == QStringLiteral("rss"))
        {
            readRss();
            return;
        }
        else
        {
            ignoreElement();
        }
    }
}

void RssXmlReader::readRss()
{
    while(m_xmlReader.readNextStartElement())
    {
        auto name = m_xmlReader.name();
        if(name == QStringLiteral("channel"))
        {
            readChannel();
            return;
        }
        else
        {
            ignoreElement();
        }
    }
}

void RssXmlReader::readChannel()
{
    while(m_xmlReader.readNextStartElement())
    {
        auto name = m_xmlReader.name();
        if(name == QStringLiteral("item"))
        {
            readItem();
        }
        else
        {
            ignoreElement();
        }
    }
}

void RssXmlReader::readItem()
{
    QString title;
    QString description;
    QString link;

    while(m_xmlReader.readNextStartElement())
    {
        auto name = m_xmlReader.name();
        if(name == QStringLiteral("title"))
        {
            title = readTextElement();
        }
        else if(name == QStringLiteral("description"))
        {
            description = readTextElement();
        }
        else if(name == QStringLiteral("link"))
        {
            link = readTextElement();
        }
        else
        {
            ignoreElement();
        }
    }

    m_feedData->addItem(std::make_shared<RssFeedItem>(title, description, link));
}

QString RssXmlReader::readTextElement()
{
    QString text;

    while( m_xmlReader.readNext() )
    {
        if( m_xmlReader.tokenType() == QXmlStreamReader::Characters )
        {
            text += m_xmlReader.text();
        }
        else if( m_xmlReader.tokenType() == QXmlStreamReader::EndElement )
        {
            break;
        }
        else
        {
            break;
        }
    }

    return text;
}

void RssXmlReader::ignoreElement()
{
    while( m_xmlReader.readNextStartElement() )
    {
        ignoreElement();
    }
}
