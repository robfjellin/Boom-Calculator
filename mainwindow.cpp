#include "mainwindow.h"

#include <QIntValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), sulfurPerGP(2), sulfurPerExplosive(10), explosivesPerRocket(10), gpPerRocket(150), gpPerExplosive(50)
{
    // Setting size of window
    setGeometry(500, 200, 700, 500);

    // Creating center widget for QVBox
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Creating Vertical Box for clean centering
    layout = new QVBoxLayout(centralWidget);

    // Calculate button
    calculate = new QPushButton("Calculate", this);
    calculate->setMaximumWidth(150);

    // Input amount of sulfur
    inputSulfur = new QLineEdit(this);
    inputSulfur->setPlaceholderText("Enter sulfur amount");
    inputSulfur->setFixedWidth(130);
    inputSulfur->setValidator(new QIntValidator(0, 99999999, this));

    // Amount of resources needed
    totalRockets = new QLabel("0", this);
    totalRockets->setMaximumWidth(450);

    // Update rocket font
    QFont rocketFont = totalRockets->font();
    rocketFont.setPointSize(15);
    totalRockets->setFont(rocketFont);

    // Add inputs to layout
    layout->addWidget(totalRockets);
    layout->setAlignment(totalRockets, Qt::AlignCenter);
    layout->addWidget(inputSulfur);
    layout->setAlignment(inputSulfur, Qt::AlignCenter);
    layout->addWidget(calculate);
    layout->setAlignment(calculate, Qt::AlignCenter);

    // Lambda function to calculate total rockets

    auto calculateFunction = [this]() {
        int sulfurAmount = inputSulfur->text().toInt();
        int rockets = rocketsPerSulfur(sulfurAmount);
        int gp = gpPerTotalRockets(rockets);
        int explosives = explosivesPerTotalRockets(rockets);
        int totalGP = gpForExploAndRockets(explosives, rockets);
        int exploGP = gpForExplosives(explosives);
        int rocketGP = gpPerTotalRockets(rockets);
        totalRockets->setText(QString("You can make a total of %1 Rockets\nYou will need a total of %2 Gun Powder\n%3 will be for explosives and %4 will be for the rockets\nYou will need a total of %5 Explosives").arg(rockets).arg(totalGP).arg(exploGP).arg(rocketGP).arg(explosives));
    };

    connect(calculate, &QPushButton::clicked, this, calculateFunction);
    connect(inputSulfur, &QLineEdit::returnPressed, this, calculateFunction);
}

MainWindow::~MainWindow() {}

int MainWindow::totalSulfurPerExplosive() {
    return sulfurPerGP * 50 + sulfurPerExplosive;
}

int MainWindow::sulfurPerRocket()
{
    return (sulfurPerGP * 150) + (totalSulfurPerExplosive() * 10);
}

int MainWindow::rocketsPerSulfur(int sulfurAmount)
{
    int total;
    total = sulfurAmount / sulfurPerRocket();
    return total;
}

int MainWindow::explosivesPerTotalRockets(int rocketsAmount)
{
    return rocketsAmount * explosivesPerRocket;
}

int MainWindow::gpPerTotalRockets(int rocketsAmount)
{
    return rocketsAmount * gpPerRocket;
}

int MainWindow::gpForExplosives(int explosivesAmount)
{
    return explosivesAmount * gpPerExplosive;
}

int MainWindow::gpForExploAndRockets(int explosives, int rockets)
{
    return gpForExplosives(explosives) + gpPerTotalRockets(rockets);
}

