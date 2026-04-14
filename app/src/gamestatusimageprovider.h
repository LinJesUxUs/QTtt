// Copyright (C) 2026 Radik Mirgaliev <radikru96@gmail.com>
//
// This file is part of QTtt project.
// Licensed under the GPLv3.
// See the LICENSE file in the project root for more information.

/**
 * @file gamestatusimageprovider.h
 * @brief Custom image provider for player avatars and game status icons.
 * @details Enables QML to load images stored in QSettings via the "image://GameStatus/" prefix.
 */

#ifndef GAMESTATUSIMAGEPROVIDER_H
#define GAMESTATUSIMAGEPROVIDER_H

#include <QObject>
#include <QQuickImageProvider>

class QImage;
class SettingsProxy;

/**
 * @class GameStatusImageProvider
 * @brief Dynamic image loader for the game's UI components.
 *
 * Inherits from QQuickImageProvider to serve QImage objects to the QML engine
 * based on the current game state, such as player turns or the "Game Over" screen.
 */
class GameStatusImageProvider : public QQuickImageProvider {
protected:
    static SettingsProxy* m_SpSettingsProxy; ///< Shared pointer to settings for image data retrieval.

public:
    /** @brief Returns the global settings proxy used by the provider. */
    static SettingsProxy* getSpSettingsProxy();

    /** @brief Sets the global settings proxy to access image resources. */
    static void setSpSettingsProxy(SettingsProxy* newSpSettingsProxy);

public:
    /** @brief Constructs the provider and registers it as a QQuickImageProvider::Image type. */
    GameStatusImageProvider();

    /** @brief Destructor. Cleans up the static proxy reference. */
    ~GameStatusImageProvider();

    /**
     * @brief Core method that handles image requests from QML.
     * @details Parses the @p id string to determine which image to return:
     * - If id contains "Game Over!", returns the "over" image.
     * - If id matches a player name, returns that player's turn icon.
     * @param id The string after "image://GameStatus/".
     * @param size Output parameter for the original image size.
     * @param requestedSize The size requested by the QML Image element.
     * @return QImage The requested image or an empty QImage if not found.
     */
    QImage requestImage(const QString& id, QSize* size, const QSize& requestedSize) override;
};

#endif // GAMESTATUSIMAGEPROVIDER_H
