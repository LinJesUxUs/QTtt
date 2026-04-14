// Copyright (C) 2026 Radik Mirgaliev <radikru96@gmail.com>
//
// This file is part of QTtt project.
// Licensed under the GPLv3.
// See the LICENSE file in the project root for more information.

/**
 * @file settingsproxy.h
 * @brief Bridge between QSettings and QML/UI.
 * @details Provides static access to game configurations and exposes them as QML properties.
 */

#ifndef SETTINGSPROXY_H
#define SETTINGSPROXY_H

#include <QQmlEngine>
#include <QSettings>

/**
 * @class SettingsProxy
 * @brief Proxy class for managing persistent application settings.
 *
 * This class allows the QML interface to read and write game configurations
 * (like board size and player count) directly to the system's QSettings.
 */
class SettingsProxy : public QObject {
    Q_OBJECT
    QML_ELEMENT

    /** @name QML Properties
     *  Exposed to QML for reactive UI updates.
     *  @{ */
    Q_PROPERTY(uint fieldWidth READ getFieldWidth WRITE setFieldWidth NOTIFY fieldWidthChanged FINAL)
    Q_PROPERTY(uint fieldHeight READ getFieldHeight WRITE setFieldHeight NOTIFY fieldHeightChanged FINAL)
    Q_PROPERTY(uint winLength READ getWinLength WRITE setWinLength NOTIFY winLengthChanged FINAL)
    Q_PROPERTY(uint playersCount READ getPlayersCount WRITE setPlayersCount NOTIFY playersCountChanged FINAL)
    Q_PROPERTY(uint firstPlayer READ getFirstPlayer WRITE setFirstPlayer NOTIFY firstPlayerChanged FINAL)
    /** @} */

protected:
    static QSettings* m_SpSettings; ///< Static pointer to the global settings object.

    static uint fieldWidth; ///< Cached field width.
    static uint fieldHeight; ///< Cached field height.
    static uint winLength; ///< Cached winning sequence length.
    static uint playersCount; ///< Cached total players count.
    static uint firstPlayer; ///< Cached ID of the starting player.

public:
    /** @brief Sets the global QSettings pointer if it hasn't been set yet. */
    static void setSpSettings(QSettings* newSpSettings);

    /** @return Pointer to the current QSettings object. */
    static QSettings* getSpSettings();

    /** @name Getters
     *  Static methods to access current configuration values.
     *  @{ */
    static uint getFieldWidth();
    static uint getFieldHeight();
    static uint getWinLength();
    static uint getPlayersCount();
    static uint getFirstPlayer();
    /** @} */

    /** @name Setters
     *  Static methods to update configuration values.
     *  @{ */
    static void setFieldWidth(const uint val);
    static void setFieldHeight(const uint val);
    static void setWinLength(const uint val);
    static void setPlayersCount(const uint val);
    static void setFirstPlayer(const uint val);
    /** @} */

    /**
     * @brief Retrieves a string value from the "playersConf" group.
     * @param key The setting key (e.g., "1Name", "1Turn").
     * @return QString The value associated with the key.
     */
    static QString getPlayersConf(const QString& key);

    /** @brief Generic getter for any key in settings. */
    static QVariant value(const QString& key);

    /** @brief Generic setter for any key in settings. */
    static void setValue(const QString& key, const QVariant& val);

public:
    /**
     * @brief Constructs the proxy and synchronizes cached values from QSettings.
     * @param newSpSettings Pointer to QSettings (optional if already set).
     */
    SettingsProxy(QSettings* newSpSettings = nullptr);

    /**
     * @brief Destructor. Saves all cached values back to QSettings before closing.
     */
    ~SettingsProxy();

Q_SIGNALS:
    /** @name Change Notifications
     *  Signals emitted when a property value is modified.
     *  @{ */
    void fieldWidthChanged();
    void fieldHeightChanged();
    void winLengthChanged();
    void playersCountChanged();
    void firstPlayerChanged();
    /** @} */
};

#endif // SETTINGSPROXY_H
