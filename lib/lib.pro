TEMPLATE = subdirs

SUBDIRS += \
    Directions \
    GameCore

GameCore.depends = Directions
