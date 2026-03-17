// Copyright (C) 2026 Radik Mirgaliev <radikru96@gmail.com>
//
// This file is part of QTtt project.
// Licensed under the GPLv3.
// See the LICENSE file in the project root for more information.

#ifndef GAMESTATUSIMAGEPROVIDER_H
#define GAMESTATUSIMAGEPROVIDER_H

#include <QObject>
#include <QQuickImageProvider>

class QImage;
class SettingsProxy;

class GameStatusImageProvider : public QQuickImageProvider {
protected:
    static SettingsProxy* m_SpSettingsProxy;

public:
    static SettingsProxy* getSpSettingsProxy();
    static void setSpSettingsProxy(SettingsProxy* newSpSettingsProxy);

public:
    GameStatusImageProvider();
    ~GameStatusImageProvider();
    QImage requestImage(const QString& id, QSize* size, const QSize& requestedSize);
};

#endif // GAMESTATUSIMAGEPROVIDER_H
