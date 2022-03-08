#include "httprequest.h"

#include <QAuthenticator>
#include <QDir>

HttpRequest::HttpRequest(QObject *parent)
    : QObject{parent}
{
    m_file = new QFile(QString("%1%2download.txt").arg( QDir::currentPath(), QDir::separator()),this);
    if (!m_file->open(QIODevice::WriteOnly | QIODevice::Text)){
        qCritical() << "file not opened";
    }
    m_manager = new QNetworkAccessManager(this);
    connect(m_manager, &QNetworkAccessManager::finished,
            this, &HttpRequest::replyFinished);

    connect(m_manager, &QNetworkAccessManager::authenticationRequired,
            this, &HttpRequest::slotAuthenticationRequired);
#ifndef QT_NO_SSL
    connect(m_manager, &QNetworkAccessManager::sslErrors,
            this, &HttpRequest::sslErrors);
#endif
}

HttpRequest::~HttpRequest()
{
    qDebug() << "Deconstructor HttpRequest";
    qDebug() << "reply" << reply.isNull();
    m_file->close();
}

void HttpRequest::get(const QUrl &url)
{
    qDebug() << "m_manager" << m_manager.isNull();
    reply = m_manager->get(QNetworkRequest(url));
    m_file->reset();
    //m_file->seek(0);

    connect(reply, &QIODevice::readyRead, this, &HttpRequest::httpReadyRead);
}

void HttpRequest::replyFinished()
{
    qDebug() << "replyFinished";
    reply->deleteLater();
    reply->manager()->deleteLater();
    qDebug() << "reply" << reply.isNull();
}

void HttpRequest::httpReadyRead()
{
    qDebug() << "httpReadyRead";
    m_file->write(reply->readAll());
    m_file->flush();
}

void HttpRequest::slotAuthenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator)
{

    qDebug() << "slotAuthenticationRequired" << QString("%1").arg(authenticator->realm());
}

void HttpRequest::sslErrors(QNetworkReply *, const QList<QSslError> &errors)
{
    QString errorString;
    for (const QSslError &error : errors) {
        if (!errorString.isEmpty())
            errorString += '\n';
        errorString += error.errorString();
    }

    qDebug() << "One or more SSL errors has occurred:\n%1" << errorString;
    reply->ignoreSslErrors();
}
