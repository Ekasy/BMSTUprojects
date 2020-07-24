#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QFrame>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QWidget* mainWidget;
    QWidget* standartWidget;
    QWidget* usualWidget;
    QWidget* engineeringWidget;

    QGridLayout* mainLayout;
    QGridLayout* standartLayout;
    QGridLayout* usualLayout;
    QGridLayout* engineeringLayout;

    void createStandartWidget();
    void createUsualWidget();
    void createEngineeringWidget();

    void createUsualLayout();
    void createEngineeringLayout();

    bool digits_only = true;
    bool equally = false;
    bool bool_plus = false;
    bool bool_minus = false;
    bool bool_mult = false;
    bool bool_div = false;
    bool bool_er_in_x = false;
    bool bool_root_n = false;
    double num_first = 0;

private slots:
    void SwitchWidget();
    void NumberClicked();
    void PointClicked();
    void OperationClicked();
    void EquallyClicked();
    void FunctionClicked();
    void ClearClicked();
};

#endif // CALCULATOR_H
