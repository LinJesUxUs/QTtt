#ifndef SETTINGSPROXY_H
#define SETTINGSPROXY_H

#include <QQmlEngine>
#include <QSettings>

class SettingsProxy : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(uint fieldWidth READ getFieldWidth WRITE setFieldWidth NOTIFY fieldWidthChanged FINAL)
    Q_PROPERTY(uint fieldHeight READ getFieldHeight WRITE setFieldHeight NOTIFY fieldHeightChanged FINAL)
    Q_PROPERTY(uint winLength READ getWinLength WRITE setWinLength NOTIFY winLengthChanged FINAL)
    Q_PROPERTY(uint playersCount READ getPlayersCount WRITE setPlayersCount NOTIFY playersCountChanged FINAL)
    Q_PROPERTY(uint firstPlayer READ getFirstPlayer WRITE setFirstPlayer NOTIFY firstPlayerChanged FINAL)

protected:
    static QSettings *m_SpSettings;

    static uint fieldWidth;
    static uint fieldHeight;
    static uint winLength;
    static uint playersCount;
    static uint firstPlayer;

public:
    static void setSpSettings(QSettings *newSpSettings);
    static QSettings* getSpSettings();

    static uint getFieldWidth();
    static uint getFieldHeight();
    static uint getWinLength();
    static uint getPlayersCount();
    static uint getFirstPlayer();

    static void setFieldWidth(const uint val);
    static void setFieldHeight(const uint val);
    static void setWinLength(const uint val);
    static void setPlayersCount(const uint val);
    static void setFirstPlayer(const uint val);

    static QString getPlayersConf(const QString &key);
    static QVariant value(const QString &key);
    static void setValue(const QString &key, const QVariant &val);

public:
    SettingsProxy(QSettings *newSpSettings = nullptr);
    ~SettingsProxy();

Q_SIGNALS:
    void fieldWidthChanged();
    void fieldHeightChanged();
    void winLengthChanged();
    void playersCountChanged();
    void firstPlayerChanged();

};

#endif // SETTINGSPROXY_H
