#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QScopedPointer>
#include <QNetworkReply>
#include <QTimer>

#include <memory>

class RssFeedData;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    void onReadPushButtonClicked();
    void onReplyFinished();

private:
    void refreshRssFeed();
    void updateUi(std::shared_ptr<RssFeedData> rssFeedData);

private:
    Ui::MainWindow *ui;

    QNetworkAccessManager m_qnam;
    QScopedPointer<QNetworkReply, QScopedPointerDeleteLater> m_reply;

    QTimer m_timer;
};
#endif // MAINWINDOW_H
