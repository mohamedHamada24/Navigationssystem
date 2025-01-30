#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QRadioButton>
#include <QLabel>
#include <QTextEdit>
#include <QScrollBar>
#include <vector>
#include "Ort.h"  // Assuming Ort is defined elsewhere

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void calculateDistance();    // Slot for calculating the distance
    void showInformation();      // Slot for showing information
    void showAllLocations();     // Slot for showing all locations
    void updateMeinStandort();   // Slot to update Mein Standort

private:
    Ui::MainWindow *ui;          // Pointer to UI
    QLabel *mapLabel;            // Label for the map
    QPushButton *btnEntfernung;  // Button to calculate distance
    QPushButton *btnInformation; // Button to show information
    QPushButton *btnAlleOrte;    // Button to show all locations
    QPushButton *btnMeinStandort; // Button for Mein Standort
    QTextEdit *outputBox;        // Text box for displaying results
    QScrollBar *verticalScrollBar; // Scroll bar for map scrolling
    std::vector<QRadioButton*> locationButtons;  // Vector of radio buttons for locations
    std::vector<Ort*> orte;       // Vector of Ort objects

    Ort* meinOrt;                // Location for Mein Ort
    void addNewLocation(Ort* ort); // Function to add new location
};

#endif // MAINWINDOW_H
