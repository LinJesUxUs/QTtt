TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += \
    Directions \
    GameCore

GameCore.depends = Directions
