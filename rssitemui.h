#ifndef RSSITEMUI_H
#define RSSITEMUI_H

#include <QWidget>
#include <memory>

class RssFeedItem;

namespace Ui {
class RssItem;
}

class RssItemUi : public QWidget
{
    Q_OBJECT

public:
    explicit RssItemUi( const std::shared_ptr<RssFeedItem> & rssFeedItem, QWidget *parent = nullptr);
    ~RssItemUi();


private:
    void onUrlLabelClicked();

private:
    std::shared_ptr<RssFeedItem> m_rssFeedItem;

    Ui::RssItem *ui;
};

#endif // RSSITEMUI_H
