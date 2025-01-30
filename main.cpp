#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv); // Initialize the Qt application

    MainWindow mainWindow; // Create the main window
    mainWindow.show();     // Display the main window

    return app.exec(); // Start the Qt event loop
}
