#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QDebug>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    int totalSulfurPerExplosive();
    int sulfurPerRocket();
    int rocketsPerSulfur(int sulfurAmount);
    int explosivesPerTotalRockets(int rocketsAmount);
    int gpPerTotalRockets(int rocketsAmount);
    int gpForExplosives(int explosivesAmount);
    int gpForExploAndRockets(int explosives, int rockets);

private:
    QPushButton *calculate;
    QLineEdit *inputSulfur;
    QLabel *totalRockets;
    QFont *rocketFont;
    QVBoxLayout *layout;
    QWidget *centralWidget;
    QComboBox *dropDown;
    int sulfurPerGP;
    int sulfurPerExplosive;
    int gpPerExplosive;
    int explosivesPerRocket;
    int gpPerRocket;

};
#endif // MAINWINDOW_H
