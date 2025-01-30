#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Ort.h"
#include <QMessageBox>
#include <QRadioButton>
#include <cmath> // For distance calculation (Haversine formula)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), meinOrt(nullptr) {
    ui->setupUi(this);

    // Map initialization (background image)
    mapLabel = new QLabel(this);
    mapLabel->setPixmap(QPixmap(":/images/navigation_karte/background.png"));
    mapLabel->setGeometry(330, -30, 1041, 1341);
    mapLabel->setScaledContents(true);

    // Scrollbar initialization (if needed)
    verticalScrollBar = ui->verticalScrollBar;
    verticalScrollBar->setVisible(true);

    // Buttons initialization
    btnEntfernung = ui->distanceButton;
    btnInformation = ui->infoButton;
    btnAlleOrte = ui->allLocationsButton;
    btnMeinStandort = ui->myLocationButton;
    outputBox = new QTextEdit(this);

    // Buttons layout and setup
    btnEntfernung->setGeometry(1219, 20, 171, 32);
    btnInformation->setGeometry(1220, 80, 171, 32);
    btnAlleOrte->setGeometry(1220, 140, 171, 32);
    btnMeinStandort->setGeometry(1220, 200, 171, 32);
    outputBox->setGeometry(1220, 250, 171, 300);

    // Connect signals and slots
    connect(btnEntfernung, &QPushButton::clicked, this, &MainWindow::calculateDistance);
    connect(btnInformation, &QPushButton::clicked, this, &MainWindow::showInformation);
    connect(btnAlleOrte, &QPushButton::clicked, this, &MainWindow::showAllLocations);
    connect(btnMeinStandort, &QPushButton::clicked, this, &MainWindow::updateMeinStandort);

    // Initial MeinOrt setup
    meinOrt = new Ort(8.6512, 49.8663); // Coordinates of h_da
    addNewLocation(meinOrt);  // Display MeinOrt on map
}

MainWindow::~MainWindow() {
    delete ui;
    for (Ort* ort : orte) {
        delete ort;
    }
}

void MainWindow::addNewLocation(Ort* ort) {
    orte.push_back(ort);

    // Create a new radio button for the location
    QRadioButton *button = new QRadioButton(this);
    button->setText(QString("ID: %1, Koordinaten: (%2, %3)")
                        .arg(ort->getId())
                        .arg(ort->getLängengrad())
                        .arg(ort->getBreitengrad()));
    locationButtons.push_back(button);

    // Mapping coordinates to the map (pixel coordinates)
    int x = static_cast<int>((ort->getLängengrad() - 5.8663) * 615 / (15.0427 - 5.8663));
    int y = static_cast<int>((ort->getBreitengrad() - 47.2701) * 830 / (54.9079 - 47.2701));
    button->move(x, y);
    button->show();
}

void MainWindow::calculateDistance() {
    // Check if two radio buttons are selected
    QVector<QRadioButton*> selectedButtons;
    for (QRadioButton *button : locationButtons) {
        if (button->isChecked()) {
            selectedButtons.push_back(button);
        }
    }

    if (selectedButtons.size() != 2) {
        QMessageBox::warning(this, "Fehler", "Bitte genau zwei Orte auswählen!");
        return;
    }

    // Retrieve the IDs of the selected locations
    Ort *ort1 = orte.at(selectedButtons.at(0)->property("id").toInt());
    Ort *ort2 = orte.at(selectedButtons.at(1)->property("id").toInt());

    // Haversine formula for distance calculation
    double lat1 = ort1->getBreitengrad();
    double lon1 = ort1->getLängengrad();
    double lat2 = ort2->getBreitengrad();
    double lon2 = ort2->getLängengrad();

    const double R = 6371.0; // Earth radius in km
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    double a = sin(dLat / 2) * sin(dLat / 2) +
               cos(lat1 * M_PI / 180.0) * cos(lat2 * M_PI / 180.0) *
                   sin(dLon / 2) * sin(dLon / 2);

    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double distance = R * c;

    outputBox->append(QString("Entfernung zwischen ID %1 und ID %2: %3 km")
                          .arg(ort1->getId())
                          .arg(ort2->getId())
                          .arg(distance));
}

void MainWindow::showInformation() {
    // Display information of selected location
    for (QRadioButton *button : locationButtons) {
        if (button->isChecked()) {
            int id = button->property("id").toInt();
            Ort *ort = orte.at(id);
            outputBox->append(QString("ID: %1\nKoordinaten: (%2, %3)")
                                  .arg(ort->getId())
                                  .arg(ort->getLängengrad())
                                  .arg(ort->getBreitengrad()));
            return;
        }
    }

    QMessageBox::warning(this, "Fehler", "Bitte einen Ort auswählen!");
}

void MainWindow::showAllLocations() {
    // Show all locations in the output box
    outputBox->clear();
    for (Ort *ort : orte) {
        outputBox->append(QString("ID: %1, Koordinaten: (%2, %3)")
                              .arg(ort->getId())
                              .arg(ort->getLängengrad())
                              .arg(ort->getBreitengrad()));
    }
}

void MainWindow::updateMeinStandort() {
    // Display symbol for MeinOrt on the map
    int x = static_cast<int>((meinOrt->getLängengrad() - 5.8663) * 615 / (15.0427 - 5.8663));
    int y = static_cast<int>((meinOrt->getBreitengrad() - 47.2701) * 830 / (54.9079 - 47.2701));
    QLabel *symbol = new QLabel(this);
    symbol->setGeometry(x, y, 10, 10);
    symbol->setStyleSheet("background-color: red; border-radius: 5px;");
    symbol->show();
}
