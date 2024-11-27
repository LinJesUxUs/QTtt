CONFIG += c++17

BUILDDIR = $$PWD/build/$$TARGET
BINDIR = $$PWD/bin

contains(CONFIG, testcase) {
    DESTDIR = $${BUILDDIR}
} else {
    DESTDIR = $${BINDIR}
}

contains(TEMPLATE, lib) {
    CONFIG += staticlib
}

OBJECTS_DIR = $${BUILDDIR}
MOC_DIR = $${BUILDDIR}
RCC_DIR = $${BUILDDIR}
UI_DIR = $${BUILDDIR}
