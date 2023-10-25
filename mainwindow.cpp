#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rssxmlreader.h"
#include "rssitemdelegate.h"
#include "rssfeeddata.h"

#include <QDebug>
#include <QErrorMessage>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->rssListView->setItemDelegate(new RssItemDelegate());

    QObject::connect(ui->readPushButton, &QPushButton::clicked, this, &MainWindow::onReadPushButtonClicked);

    // refresh every 1 min
    m_timer.setInterval( 1*60*1000);
    QObject::connect(&m_timer, &QTimer::timeout, this, &MainWindow::refreshRssFeed);
    m_timer.start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onReadPushButtonClicked()
{
    refreshRssFeed();
}

void MainWindow::refreshRssFeed()
{
    qDebug() << "refreshRssFeed";

    // check if there is pending request
    if( m_reply != nullptr)
        return;

    m_reply.reset(m_qnam.get(QNetworkRequest(QUrl(ui->rssFeedUrlPlainTextEdit->toPlainText()))));
    QObject::connect(m_reply.get(), &QNetworkReply::finished, this, &MainWindow::onReplyFinished);
}

void MainWindow::onReplyFinished()
{
    QNetworkReply::NetworkError error = m_reply->error();
    if( error == QNetworkReply::NetworkError::NoError)
    {
        auto responseData = m_reply->readAll();

        RssXmlReader rssXmlReader(responseData);
        rssXmlReader.beginReading();
        auto feedData = rssXmlReader.getFeedData();
        if( feedData->isEmpty())
        {
            auto * errorMessage = new QErrorMessage(this);
            errorMessage->showMessage("Rss feed format problem!");
        }
        else
        {
            updateUi(feedData);
        }
    }
    else
    {
        auto * errorMessage = new QErrorMessage(this);
        errorMessage->showMessage("There is some network connection problems!");
    }

    m_reply.reset();
}

void MainWindow::updateUi(std::shared_ptr<RssFeedData> rssFeedData)
{
    ui->rssListView->setData(rssFeedData);
}


