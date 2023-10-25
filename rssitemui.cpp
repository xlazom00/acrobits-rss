#include "RssItemUi.h"
#include "ui_rssitemui.h"

#include <QDesktopServices>

#include "rssfeeddata.h"


RssItemUi::RssItemUi(const std::shared_ptr<RssFeedItem> & rssFeedItem, QWidget *parent) :
    QWidget(parent),
    m_rssFeedItem(rssFeedItem),
    ui(new Ui::RssItem)
{
    ui->setupUi(this);

    ui->titleLabel->setText(rssFeedItem->title);
    ui->descriptionLabel->setText(rssFeedItem->description);
    ui->urlLabel->setText(rssFeedItem->link);

    QObject::connect(ui->urlLabel, &ClickableLabel::clicked, this, &RssItemUi::onUrlLabelClicked);

}

RssItemUi::~RssItemUi()
{
    delete ui;
}


void RssItemUi::onUrlLabelClicked()
{
    QDesktopServices::openUrl( QUrl{m_rssFeedItem->link} );
}
