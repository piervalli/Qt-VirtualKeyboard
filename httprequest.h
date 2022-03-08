#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QNetworkAccessManager>
#include <QObject>
#include <QDebug>
#include <QNetworkReply>
#include <QPointer>
#include <QFile>

class HttpRequest : public QObject
{
    Q_OBJECT
public:
    explicit HttpRequest(QObject *parent = nullptr);
    ~HttpRequest();
public slots:
    void get(const QUrl &url);
private slots:
    void replyFinished();
    void httpReadyRead();
    void slotAuthenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator);
#ifndef QT_NO_SSL
    void sslErrors(QNetworkReply *, const QList<QSslError> &errors);
#endif
signals:
private:
    QPointer<QNetworkAccessManager> m_manager;
    QPointer<QNetworkReply> reply;
    QPointer<QFile> m_file;
};

#endif // HTTPREQUEST_H
