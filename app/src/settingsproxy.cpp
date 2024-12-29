#include "settingsproxy.h"

QSettings *SettingsProxy::m_SpSettings = nullptr;
uint SettingsProxy::fieldWidth = 3;
uint SettingsProxy::fieldHeight = 3;
uint SettingsProxy::winLength = 3;
uint SettingsProxy::playersCount = 2;
uint SettingsProxy::firstPlayer = 1;

void SettingsProxy::setSpSettings(QSettings *newSpSettings) {
    if ( m_SpSettings == nullptr)
        m_SpSettings = newSpSettings;
}

QSettings *SettingsProxy::getSpSettings() {
    return m_SpSettings;
}

uint SettingsProxy::getFieldWidth() {
    return fieldWidth;
}

uint SettingsProxy::getFieldHeight() {
    return fieldHeight;
}

uint SettingsProxy::getWinLength() {
    return winLength;
}

uint SettingsProxy::getPlayersCount() {
    return playersCount;
}

uint SettingsProxy::getFirstPlayer() {
    return firstPlayer;
}

void SettingsProxy::setFieldWidth(const uint val) {
    fieldWidth = val;
    // emit fieldWidthChanged();
}

void SettingsProxy::setFieldHeight(const uint val) {
    fieldHeight = val;
    // emit fieldHeightChanged();
}

void SettingsProxy::setWinLength(const uint val) {
    winLength = val;
    // emit winLengthChanged();
}

void SettingsProxy::setPlayersCount(const uint val) {
    playersCount = val;
    // emit playersCountChanged();
}

void SettingsProxy::setFirstPlayer(const uint val) {
    firstPlayer = val;
    // emit firstPlayerChanged();
}

QString SettingsProxy::getPlayersConf(const QString &key) {
    return m_SpSettings->value("playersConf/" + key).toString();
}

QVariant SettingsProxy::value(const QString &key) {
    return m_SpSettings->value(key);
}

void SettingsProxy::setValue(const QString &key, const QVariant &val) {
    m_SpSettings->setValue(key,val);
}

SettingsProxy::SettingsProxy(QSettings *newSpSettings) {
    if (m_SpSettings == nullptr)
        m_SpSettings = newSpSettings;
    if (m_SpSettings != nullptr) {
        fieldWidth = m_SpSettings->value("gameConfig/fieldWidth").toUInt();
        fieldHeight = m_SpSettings->value("gameConfig/fieldHeight").toUInt();
        winLength = m_SpSettings->value("gameConfig/winLength").toUInt();
        playersCount = m_SpSettings->value("gameConfig/playersCount").toUInt();
        firstPlayer = m_SpSettings->value("gameConfig/firstPlayer").toUInt();
    }
}

SettingsProxy::~SettingsProxy() {
    if (m_SpSettings != nullptr) {
        m_SpSettings->setValue("gameConfig/fieldWidth", fieldWidth);
        m_SpSettings->setValue("gameConfig/fieldHeight", fieldHeight);
        m_SpSettings->setValue("gameConfig/winLength", winLength);
        m_SpSettings->setValue("gameConfig/playersCount", playersCount);
        m_SpSettings->setValue("gameConfig/firstPlayer", firstPlayer);
        m_SpSettings == nullptr;
    }
}
