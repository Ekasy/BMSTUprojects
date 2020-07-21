#include <QApplication>
#include <QQmlApplicationEngine>
#include <QWindow>
#include <QQmlContext>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>
#include "fileSystemModel.h"
#include "playlistHandler.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    app.setWindowIcon(QIcon(":/images/window_icon.png"));
    qmlRegisterUncreatableType<DisplayFileSystemModel>("io.qt.examples.quick.controls.filesystembrowser", 1, 0,
                                                           "FileSystemModel", "Cannot create a FileSystemModel instance."); //тип не может быть создан, предназначен только для предоставления вложенных свойств
    qmlRegisterUncreatableType<DisplayFileSystemModel>("my.mo.filesystembrowser", 1, 0, "FileSystemModel", "Cannot create a FileSystemModel instance.");
    qmlRegisterType<playlistHandler>("my.mo.playlisthandler", 1, 0, "PlaylistHandler");
    QQmlApplicationEngine engine;

    QFileSystemModel* displayModel = new DisplayFileSystemModel;
    displayModel->setRootPath("/");
    displayModel->setRootPath("c:/Users/MiAir/");
    displayModel->setResolveSymlinks(true);

    engine.rootContext()->setContextProperty("fileSystemModel", displayModel);
    engine.rootContext()->setContextProperty("rootPathIndex", displayModel->index(displayModel->rootPath()));

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
