// Copyright (C) 2026 Radik Mirgaliev <radikru96@gmail.com>
//
// This file is part of QTtt project.
// Licensed under the GPLv3.
// See the LICENSE file in the project root for more information.
/**
 * @file main.cpp
 * @brief The entry point to the QTtt game.
 * @details Initializes the Qt application and starts the main event loop.
 */
#include "gamepainteditem.h"
#include "gamestatusimageprovider.h"
#include "settingsproxy.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSettings>

/**
 * @brief Find max size of square
 * @details The largest square that will fit on the largest available screen.
 * @param screens List of all connected screens to device
 * @return QSize Defined Square size
 */
inline QSize getMaxSquareSize(const QList<QScreen*>& screens)
{
    QSize maxSize;
    for (auto i : std::as_const(screens)) {
        if (maxSize.isEmpty())
            maxSize = i->size();
        else {
            maxSize.setWidth(qMax(maxSize.width(), i->size().width()));
            maxSize.setHeight(qMax(maxSize.height(), i->size().height()));
        }
    }
    if (maxSize.width() < maxSize.height()) {
        maxSize.setHeight(maxSize.width());
    } else {
        maxSize.setWidth(maxSize.height());
    }
    return maxSize;
}

/**
 * @brief Initialyse settings
 * @details Fills empty fields with default parameters
 * @param settings Pointer to apps QSettings object
 * @param maxSize Image size limitation for optimise storage
 */
inline void initSettings(QSettings* settings, const QSize& maxSize)
{
    settings->beginGroup("gameConfig");
    if (settings->value("fieldWidth").isNull())
        settings->setValue("fieldWidth", 3);
    if (settings->value("fieldHeight").isNull())
        settings->setValue("fieldHeight", 3);
    if (settings->value("winLength").isNull())
        settings->setValue("winLength", 3);
    if (settings->value("playersCount").isNull())
        settings->setValue("playersCount", 2);
    if (settings->value("firstPlayer").isNull())
        settings->setValue("firstPlayer", 1);
    settings->endGroup();

    QImage imgBuf;
    QList<QString> lst = { "Alice",
        "AliceWin",
        "Bob",
        "BobWin",
        "Chuck",
        "BackGround" };
    settings->beginGroup("images");
    for (auto const& i : qAsConst(lst)) {
        if (settings->value(i).isNull()) {
            imgBuf = QImage(QString(":/images/") + i + ".jpg");
            if (imgBuf.size().width() > maxSize.width())
                imgBuf = imgBuf.scaled(maxSize);
            settings->setValue(i, imgBuf);
        }
    }
    settings->endGroup();

    settings->beginGroup("playersConf");
    if (settings->value("1Turn").isNull())
        settings->setValue("1Turn", "Alice");
    if (settings->value("1Win").isNull())
        settings->setValue("1Win", "AliceWin");
    if (settings->value("1Name").isNull())
        settings->setValue("1Name", "Alice");
    if (settings->value("2Turn").isNull())
        settings->setValue("2Turn", "Bob");
    if (settings->value("2Win").isNull())
        settings->setValue("2Win", "BobWin");
    if (settings->value("2Name").isNull())
        settings->setValue("2Name", "Bob");
    if (settings->value("background").isNull())
        settings->setValue("background", "BackGround");
    if (settings->value("over").isNull())
        settings->setValue("over", "Chuck");
    settings->endGroup();
    settings->sync();
}

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    app.setApplicationName("QTtt");
    app.setOrganizationName("LinJesUxUs");

    QSize maxSize = getMaxSquareSize(app.screens());
    auto* settings = new QSettings();
    initSettings(settings, maxSize);
    auto* settingsProxy = new SettingsProxy(settings);

    GamePaintedItem::setSpSettingsProxy(settingsProxy);
    GameStatusImageProvider::setSpSettingsProxy(settingsProxy);

    QQmlApplicationEngine engine;

    qmlRegisterType<SettingsProxy>("linjesuxus.settingsProxy", 1, 0, "SettingsProxy");
    qmlRegisterType<GamePaintedItem>("linjesuxus.game", 1, 0, "Game");

    engine.addImageProvider(QLatin1String("GameStatus"), new GameStatusImageProvider);
    engine.load(QUrl("qrc:/linjesuxus/settingsProxy/src/ViewsComposer.qml"));

    int ret = app.exec();

    if (settingsProxy != nullptr)
        delete settingsProxy;
    settingsProxy = nullptr;

    if (settings != nullptr)
        delete settings;
    settings = nullptr;

    return ret;
}
