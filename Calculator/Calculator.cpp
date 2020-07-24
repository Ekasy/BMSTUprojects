#include "Calculator.h"
#include "ui_mainwindow.h"

#include <cctype>
#include <cmath>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Калькулятор (обычный)");
    setFixedSize(380, 450);

    ui->lineEdit->setPlaceholderText("0");
    ui->lineEdit->setReadOnly(true);
    ui->radioButtonUsual->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ui->radioButtonEngineering->setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Preferred);
    ui->radioButtonUsual->setChecked(true);
    connect(ui->radioButtonUsual, SIGNAL(toggled(bool)), SLOT(SwitchWidget()));

    createStandartWidget();
    createUsualWidget();
    createEngineeringWidget();
    mainWidget = new QWidget(this);
    createUsualLayout();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SwitchWidget()
{
    usualWidget->setParent(this);
    engineeringWidget->setParent(this);

    if (ui->radioButtonUsual->isChecked()) {
        delete mainLayout;
        setWindowTitle("Калькулятор (обычный)");
        setFixedSize(380, 450);
        createUsualLayout();
    }
    else {
        delete mainLayout;
        setWindowTitle("Калькулятор (инженерный)");
        setFixedSize(685, 450);
        createEngineeringLayout();
    }
}

void MainWindow::createUsualLayout()
{
    mainLayout = new QGridLayout(this);
    mainLayout->setSpacing(0);
    engineeringWidget->hide();
    mainLayout->addWidget(standartWidget, 0, 0, 1, 3);
    mainLayout->addWidget(usualWidget, 1, 0, 2, 3);

    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);
    centralWidget()->layout()->setContentsMargins(0, 0, 0, 0);
}

void MainWindow::createEngineeringLayout()
{
    mainLayout = new QGridLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(standartWidget, 0, 0, 1, 9);
    mainLayout->addWidget(engineeringWidget, 1, 0, 2, 4);
    mainLayout->addWidget(usualWidget, 1, 4, 2, 5);
    engineeringWidget->show();

    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);
    centralWidget()->layout()->setContentsMargins(0, 0, 0, 0);
}

void MainWindow::createStandartWidget()
{
    QPushButton* pushButtonClear = new QPushButton(QString::fromUtf8("C"), this);

    QString StyleSheetClear = "QPushButton { color: #FF4500; background-color: white; border: none; font: 17pt 'Consolas'; outline: none; } "
                              "QPushButton:hover { background-color: #F0F0F0; } "
                              "QPushButton:pressed { background-color: #DCDCDC; }";

    QString StyleSheetRadioButton = "QRadioButton {background-color: #FFFFFF; font: 10pt 'Consolas'; padding: 0px 0px 0px 20px;} "
                                    "QRadioButton::indicator { width: 20px; height: 20px; } ";

    QString StyleSheetLine = "QLineEdit {font: 26pt 'Consolas'; qproperty-alignment: AlignRight; padding: 5px; border: none; background-color: #FFFFFF; }";

    ui->radioButtonUsual->setStyleSheet(StyleSheetRadioButton);
    ui->radioButtonEngineering->setStyleSheet(StyleSheetRadioButton);
    pushButtonClear->setStyleSheet(StyleSheetClear);
    ui->lineEdit->setStyleSheet(StyleSheetLine);

    pushButtonClear->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    standartLayout = new QGridLayout(this);
    standartLayout->setSpacing(0);
    standartLayout->setContentsMargins(0, 0, 0, 0);

    standartLayout->addWidget(ui->lineEdit, 0, 0, 2, 5);
    standartLayout->addWidget(ui->radioButtonUsual, 2, 0, 1, 4);
    standartLayout->addWidget(ui->radioButtonEngineering, 3, 0, 1, 4);
    standartLayout->addWidget(pushButtonClear, 2, 4, 2, 1);

    standartWidget = new QWidget(this);
    standartWidget->setLayout(standartLayout);

    connect(pushButtonClear, SIGNAL(clicked()), this, SLOT(ClearClicked()));
}

void MainWindow::createUsualWidget()
{
    QPushButton* pushButton0 = new QPushButton("0", this);
    QPushButton* pushButton1 = new QPushButton("1", this);
    QPushButton* pushButton2 = new QPushButton("2", this);
    QPushButton* pushButton3 = new QPushButton("3", this);
    QPushButton* pushButton4 = new QPushButton("4", this);
    QPushButton* pushButton5 = new QPushButton("5", this);
    QPushButton* pushButton6 = new QPushButton("6", this);
    QPushButton* pushButton7 = new QPushButton("7", this);
    QPushButton* pushButton8 = new QPushButton("8", this);
    QPushButton* pushButton9 = new QPushButton("9", this);
    QPushButton* pushButtonPoint = new QPushButton(",", this);
    QPushButton* pushButtonPlus = new QPushButton("+", this);
    QPushButton* pushButtonMinus = new QPushButton(QString::fromUtf8("-"), this);
    QPushButton* pushButtonMult = new QPushButton(QString::fromUtf8("\u00D7"), this);
    QPushButton* pushButtonDiv = new QPushButton(QString::fromUtf8("\u00F7"), this);
    QPushButton* pushButtonRoot = new QPushButton(QString::fromUtf8("\u221A"), this);
    QPushButton* pushButtonReverse = new QPushButton(QString::fromUtf8("1/x"), this);
    QPushButton* pushButtonEqually = new QPushButton("=", this);

    pushButton0->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButton1->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButton2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButton3->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButton4->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButton5->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButton6->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButton7->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButton8->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButton9->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonPoint->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonPlus->setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonMinus->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonMult->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonDiv->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonReverse->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonRoot->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonEqually->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    QString StyleSheetNumbers = "QPushButton { color: black; background-color: #FAFAFA; border: none; font: 17pt 'Consolas'; outline: none;} "
                                "QPushButton:hover { background-color: #F0F0F0; } "
                                "QPushButton:pressed { background-color: #DCDCDC; }";
    QString StyleSheetEqually =  "QPushButton { color: #FAFAFA; background-color: #00BFFF; border: none; font: 17pt 'Consolas'; outline: none; } "
                                "QPushButton:hover { background-color: #00DFFF; } "
                                "QPushButton:pressed { background-color: #00EFFF; }";

    QString StyleSheetSigns =   "QPushButton { color: #00BFFF; background-color: #F5F5F5; border: none; font: 17pt 'Consolas'; outline: none; } "
                                "QPushButton:hover { background-color: #F0F0F0; } "
                                "QPushButton:pressed { background-color: #DCDCDC; }";

    pushButton0->setStyleSheet(StyleSheetNumbers);
    pushButton1->setStyleSheet(StyleSheetNumbers);
    pushButton2->setStyleSheet(StyleSheetNumbers);
    pushButton3->setStyleSheet(StyleSheetNumbers + "QPushButton { border-right: 1px solid #A9A9A9; }");
    pushButton4->setStyleSheet(StyleSheetNumbers);
    pushButton5->setStyleSheet(StyleSheetNumbers);
    pushButton6->setStyleSheet(StyleSheetNumbers + "QPushButton { border-right: 1px solid #A9A9A9; }");
    pushButton7->setStyleSheet(StyleSheetNumbers);
    pushButton8->setStyleSheet(StyleSheetNumbers);
    pushButton9->setStyleSheet(StyleSheetNumbers + "QPushButton { border-right: 1px solid #A9A9A9; }");
    pushButtonPlus->setStyleSheet(StyleSheetSigns);
    pushButtonMinus->setStyleSheet(StyleSheetSigns);
    pushButtonPoint->setStyleSheet(StyleSheetNumbers + "QPushButton { border-right: 1px solid #A9A9A9; }");
    pushButtonMult->setStyleSheet(StyleSheetSigns);
    pushButtonDiv->setStyleSheet(StyleSheetSigns);
    pushButtonEqually->setStyleSheet(StyleSheetEqually);
    pushButtonReverse->setStyleSheet(StyleSheetSigns);
    pushButtonRoot->setStyleSheet(StyleSheetSigns);

    usualLayout = new QGridLayout(this);
    usualLayout->setSpacing(0);
    usualLayout->setContentsMargins(0, 0, 0, 0);

    usualLayout->addWidget(pushButton7,       0, 0, 1, 1);
    usualLayout->addWidget(pushButton8,       0, 1, 1, 1);
    usualLayout->addWidget(pushButton9,       0, 2, 1, 1);
    usualLayout->addWidget(pushButtonDiv,     0, 3, 1, 1);
    usualLayout->addWidget(pushButtonRoot,    0, 4, 1, 1);
    usualLayout->addWidget(pushButton4,       1, 0, 1, 1);
    usualLayout->addWidget(pushButton5,       1, 1, 1, 1);
    usualLayout->addWidget(pushButton6,       1, 2, 1, 1);
    usualLayout->addWidget(pushButtonMult,    1, 3, 1, 1);
    usualLayout->addWidget(pushButtonReverse, 1, 4, 1, 1);
    usualLayout->addWidget(pushButton1,       2, 0, 1, 1);
    usualLayout->addWidget(pushButton2,       2, 1, 1, 1);
    usualLayout->addWidget(pushButton3,       2, 2, 1, 1);
    usualLayout->addWidget(pushButtonMinus,   2, 3, 1, 1);
    usualLayout->addWidget(pushButtonEqually, 2, 4, 2, 1);
    usualLayout->addWidget(pushButton0,       3, 0, 1, 2);
    usualLayout->addWidget(pushButtonPoint,   3, 2, 1, 1);
    usualLayout->addWidget(pushButtonPlus,    3, 3, 1, 1);

    usualWidget = new QWidget(this);
    usualWidget->setLayout(usualLayout);

    connect(pushButton0, SIGNAL(clicked()), this, SLOT(NumberClicked()));
    connect(pushButton1, SIGNAL(clicked()), this, SLOT(NumberClicked()));
    connect(pushButton2, SIGNAL(clicked()), this, SLOT(NumberClicked()));
    connect(pushButton3, SIGNAL(clicked()), this, SLOT(NumberClicked()));
    connect(pushButton4, SIGNAL(clicked()), this, SLOT(NumberClicked()));
    connect(pushButton5, SIGNAL(clicked()), this, SLOT(NumberClicked()));
    connect(pushButton6, SIGNAL(clicked()), this, SLOT(NumberClicked()));
    connect(pushButton7, SIGNAL(clicked()), this, SLOT(NumberClicked()));
    connect(pushButton8, SIGNAL(clicked()), this, SLOT(NumberClicked()));
    connect(pushButton9, SIGNAL(clicked()), this, SLOT(NumberClicked()));
    connect(pushButtonPoint, SIGNAL(clicked()), this, SLOT(PointClicked()));
    connect(pushButtonPlus, SIGNAL(clicked()), this, SLOT(OperationClicked()));
    connect(pushButtonMinus, SIGNAL(clicked()), this, SLOT(OperationClicked()));
    connect(pushButtonMult, SIGNAL(clicked()), this, SLOT(OperationClicked()));
    connect(pushButtonDiv, SIGNAL(clicked()), this, SLOT(OperationClicked()));
    connect(pushButtonReverse, SIGNAL(clicked()), this, SLOT(FunctionClicked()));
    connect(pushButtonRoot, SIGNAL(clicked()), this, SLOT(FunctionClicked()));
    connect(pushButtonEqually, SIGNAL(clicked()), this, SLOT(EquallyClicked()));

    pushButtonPlus->setCheckable(true);
    pushButtonMinus->setCheckable(true);
    pushButtonMult->setCheckable(true);
    pushButtonDiv->setCheckable(true);
}

void MainWindow::createEngineeringWidget()
{
    QPushButton* pushButtonSinh = new QPushButton("sinh", this);
    QPushButton* pushButtonSin = new QPushButton("sin", this);
    QPushButton* pushButtonExp = new QPushButton(QString::fromUtf8("e\u207F"), this);
    QPushButton* pushButtonSquaring = new QPushButton(QString::fromUtf8("x\u00B2"), this);
    QPushButton* pushButtonCosh = new QPushButton("cosh", this);
    QPushButton* pushButtonCos = new QPushButton("cos", this);
    QPushButton* pushButtonLn = new QPushButton("ln", this);
    QPushButton* pushButtonCubing = new QPushButton(QString::fromUtf8("x\u00B3"), this);
    QPushButton* pushButtonTanh = new QPushButton("tanh", this);
    QPushButton* pushButtonTan = new QPushButton("tan", this);
    QPushButton* pushButtonLog = new QPushButton("log", this);
    QPushButton* pushButtonErectionInX = new QPushButton(QString::fromUtf8("x\u207F"), this);
    QPushButton* pushButtonFact = new QPushButton("n!", this);
    QPushButton* pushButtonPi = new QPushButton(QString::fromUtf8("\u03C0"), this);
    QPushButton* pushButtonCubeRoot = new QPushButton(QString::fromUtf8("\u00B3\u221A"), this);
    QPushButton* pushButtonNRoot = new QPushButton(QString::fromUtf8("\u207F\u221A"), this);

    pushButtonSinh->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonSin->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonExp->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonSquaring->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonCosh->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonCos->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonLn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonCubing->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonTanh->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonTan->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonLog->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonErectionInX->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonFact->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonPi->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonCubeRoot->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonNRoot->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    QString StyleSheetSpecSigns = "QPushButton {color: black; background-color: #F5F5F5; border: none; font: 14pt 'Consolas'; outline: none; } "
                                  "QPushButton:hover { background-color: #F0F0F0; } "
                                  "QPushButton:pressed { background-color: #DCDCDC; }";
    QString StyleSheetSpecRoot =  "QPushButton {color: black; background-color: #FAFAFA; border: none; font: 14pt 'Consolas'; outline: none; } "
                                  "QPushButton:hover { background-color: #F0F0F0; } "
                                  "QPushButton:pressed { background-color: #DCDCDC; }";

    pushButtonCosh->setStyleSheet(StyleSheetSpecSigns);
    pushButtonCos->setStyleSheet(StyleSheetSpecSigns);
    pushButtonSinh->setStyleSheet(StyleSheetSpecSigns);
    pushButtonSin->setStyleSheet(StyleSheetSpecSigns);
    pushButtonExp->setStyleSheet(StyleSheetSpecSigns);
    pushButtonPi->setStyleSheet(StyleSheetSpecSigns);
    pushButtonCubeRoot->setStyleSheet(StyleSheetSpecSigns);
    pushButtonNRoot->setStyleSheet(StyleSheetSpecSigns + "QPushButton { border-right: 1px solid #A9A9A9; }");
    pushButtonTanh->setStyleSheet(StyleSheetSpecSigns);
    pushButtonTan->setStyleSheet(StyleSheetSpecSigns);
    pushButtonFact->setStyleSheet(StyleSheetSpecSigns);
    pushButtonLn->setStyleSheet(StyleSheetSpecSigns);
    pushButtonLog->setStyleSheet(StyleSheetSpecSigns);
    pushButtonSquaring->setStyleSheet(StyleSheetSpecSigns + "QPushButton { border-right: 1px solid #A9A9A9; }");
    pushButtonCubing->setStyleSheet(StyleSheetSpecSigns + "QPushButton { border-right: 1px solid #A9A9A9; }");
    pushButtonErectionInX->setStyleSheet(StyleSheetSpecSigns + "QPushButton { border-right: 1px solid #A9A9A9; }");

    engineeringLayout = new QGridLayout(this);
    engineeringLayout->setSpacing(0);
    engineeringLayout->setContentsMargins(0, 0, 0, 0);

    engineeringLayout->addWidget(pushButtonSinh,        0, 0, 1, 1);
    engineeringLayout->addWidget(pushButtonSin,         0, 1, 1, 1);
    engineeringLayout->addWidget(pushButtonExp,         0, 2, 1, 1);
    engineeringLayout->addWidget(pushButtonSquaring,    0, 3, 1, 1);
    engineeringLayout->addWidget(pushButtonCosh,        1, 0, 1, 1);
    engineeringLayout->addWidget(pushButtonCos,         1, 1, 1, 1);
    engineeringLayout->addWidget(pushButtonLn,          1, 2, 1, 1);
    engineeringLayout->addWidget(pushButtonCubing,      1, 3, 1, 1);
    engineeringLayout->addWidget(pushButtonTanh,        2, 0, 1, 1);
    engineeringLayout->addWidget(pushButtonTan,         2, 1, 1, 1);
    engineeringLayout->addWidget(pushButtonLog,         2, 2, 1, 1);
    engineeringLayout->addWidget(pushButtonErectionInX, 2, 3, 1, 1);
    engineeringLayout->addWidget(pushButtonFact,        3, 0, 1, 1);
    engineeringLayout->addWidget(pushButtonPi,          3, 1, 1, 1);
    engineeringLayout->addWidget(pushButtonCubeRoot,    3, 2, 1, 1);
    engineeringLayout->addWidget(pushButtonNRoot,       3, 3, 1, 1);

    engineeringWidget = new QWidget(this);
    engineeringWidget->setLayout(engineeringLayout);

    connect(pushButtonSinh, SIGNAL(clicked()), this, SLOT(FunctionClicked()));
    connect(pushButtonSin, SIGNAL(clicked()), this, SLOT(FunctionClicked()));
    connect(pushButtonCosh, SIGNAL(clicked()), this, SLOT(FunctionClicked()));
    connect(pushButtonCos, SIGNAL(clicked()), this, SLOT(FunctionClicked()));
    connect(pushButtonTanh, SIGNAL(clicked()), this, SLOT(FunctionClicked()));
    connect(pushButtonTan, SIGNAL(clicked()), this, SLOT(FunctionClicked()));
    connect(pushButtonFact, SIGNAL(clicked()), this, SLOT(FunctionClicked()));
    connect(pushButtonPi, SIGNAL(clicked()), this, SLOT(FunctionClicked()));
    connect(pushButtonExp, SIGNAL(clicked()), this, SLOT(FunctionClicked()));
    connect(pushButtonLn, SIGNAL(clicked()), this, SLOT(FunctionClicked()));
    connect(pushButtonLog, SIGNAL(clicked()), this, SLOT(FunctionClicked()));
    connect(pushButtonCubeRoot, SIGNAL(clicked()), this, SLOT(FunctionClicked()));
    connect(pushButtonSquaring, SIGNAL(clicked()), this, SLOT(FunctionClicked()));
    connect(pushButtonCubing, SIGNAL(clicked()), this, SLOT(FunctionClicked()));
    connect(pushButtonErectionInX, SIGNAL(clicked()), this, SLOT(OperationClicked()));
    connect(pushButtonNRoot, SIGNAL(clicked()), this, SLOT(OperationClicked()));
}

void MainWindow::NumberClicked()
{
    QPushButton *button = (QPushButton*) sender();

    if (MainWindow::equally == true) {
        ui->lineEdit->setText("0");
        MainWindow::equally = false;
    }

    QString str_number = ui->lineEdit->text();
    double number = 0;

    if (str_number.contains('.') && button->text() == "0") {
        str_number = str_number + button->text();
    }
    else {
        number = (str_number + button->text()).toDouble();
        str_number = QString::number(number);
    }

    ui->lineEdit->setText(str_number);
}

void MainWindow::PointClicked()
{
    if (!ui->lineEdit->text().contains('.'))
        ui->lineEdit->setText(ui->lineEdit->text() + ".");
}

void MainWindow::OperationClicked()
{
    QPushButton *button = (QPushButton*) sender();
    MainWindow::num_first = (ui->lineEdit->text()).toDouble();
    ui->lineEdit->setText("0");

    MainWindow::bool_plus = false;
    MainWindow::bool_minus = false;
    MainWindow::bool_mult = false;
    MainWindow::bool_div = false;
    MainWindow::bool_er_in_x = false;
    MainWindow::bool_root_n = false;

    if (button->text() == "+") {
        MainWindow::bool_plus = true;
    }
    else if (button->text() == "-") {
        MainWindow::bool_minus = true;
    }
    else if (button->text() == "\u00D7") {
        MainWindow::bool_mult = true;
    }
    else if (button->text() == "\u00F7") {
        MainWindow::bool_div = true;
    }
    else if (button->text() == "x\u207F") {
        MainWindow::bool_er_in_x = true;
    }
    else if (button->text() == "\u207F\u221A") {
        MainWindow::bool_root_n = true;
    }
}

void MainWindow::EquallyClicked()
{
    MainWindow::equally = true;
    double num_second, labelNumber;
    QString newlabel;
    num_second = (ui->lineEdit->text()).toDouble();

    if (MainWindow::bool_plus) {
        labelNumber = MainWindow::num_first + num_second;
        newlabel = QString::number(labelNumber);
        ui->lineEdit->setText(newlabel);
        MainWindow::bool_plus = false;
    }
    else if (MainWindow::bool_minus) {
        labelNumber = MainWindow::num_first - num_second;
        newlabel = QString::number(labelNumber);
        ui->lineEdit->setText(newlabel);
        MainWindow::bool_minus = false;
    }
    else if (MainWindow::bool_mult) {
        labelNumber = MainWindow::num_first * num_second;
        newlabel = QString::number(labelNumber);
        ui->lineEdit->setText(newlabel);
        MainWindow::bool_mult = false;
    }
    else if (MainWindow::bool_div) {
        if (num_second == 0)
            ui->lineEdit->setText("Error");
        else {
            labelNumber = MainWindow::num_first / num_second;
            newlabel = QString::number(labelNumber);
            ui->lineEdit->setText(newlabel);
        }
        MainWindow::bool_div = false;
    }
    else if (MainWindow::bool_er_in_x) {
        ui->lineEdit->setText(QString::number(pow(MainWindow::num_first, num_second)));
        MainWindow::bool_er_in_x = false;
    }
    else if (MainWindow::bool_root_n) {
        ui->lineEdit->setText(QString::number(pow(MainWindow::num_first, 1.0 / num_second)));
        MainWindow::bool_root_n = false;
    }

    MainWindow::num_first = 0;
}

void MainWindow::ClearClicked()
{
    ui->lineEdit->setText("0");
    MainWindow::bool_plus = false;
    MainWindow::bool_minus = false;
    MainWindow::bool_mult = false;
    MainWindow::bool_div = false;
}

void MainWindow::FunctionClicked()
{
    QPushButton *button = (QPushButton*) sender();
    double number = (ui->lineEdit->text()).toDouble();
    MainWindow::equally = true;

    if (button->text() == "\u221A") {
        ui->lineEdit->setText(QString::number(sqrt(number)));
    }
    else if (button->text() == "1/x") {
        if (number == 0) {
            ui->lineEdit->setText("Error");
        } else {
            ui->lineEdit->setText(QString::number(1 / number));
        }
    }
    else if (button->text() == "sinh") {
        ui->lineEdit->setText(QString::number(sinh(number)));
        MainWindow::equally = true;
    }
    else if (button->text() == "sin") {
        ui->lineEdit->setText(QString::number(sin(number)));
    }
    else if (button->text() == "cosh") {
        ui->lineEdit->setText(QString::number(cosh(number)));
    }
    else if (button->text() == "cos") {
        ui->lineEdit->setText(QString::number(cos(number)));
    }
    else if (button->text() == "tanh") {
        ui->lineEdit->setText(QString::number(tanh(number)));
    }
    else if (button->text() == "tan") {
        ui->lineEdit->setText(QString::number(tan(number)));
    }
    else if (button->text() == "\u03C0") {
        double pi = 3.1415926535897932;
        ui->lineEdit->setText(QString::number(pi));
    }
    else if (button->text() == "e\u207F") {
        ui->lineEdit->setText(QString::number(exp(number)));
    }
    else if (button->text() == "log") {
        ui->lineEdit->setText(QString::number(log10(number)));
    }
    else if (button->text() == "ln") {
        ui->lineEdit->setText(QString::number(log(number) / log(exp(1))));
    }
    else if (button->text() == "x\u00B2") {
        ui->lineEdit->setText(QString::number(number * number));
    }
    else if (button->text() == "x\u00B3") {
        ui->lineEdit->setText(QString::number(number * number * number));
    }
    else if (button->text() == "\u00B3\u221A") {
        ui->lineEdit->setText(QString::number(pow(number, 1.0 / 3.0)));
    }
    else if (button->text() == "n!") {
        double result = 1;
        if (number < 0 || (int)number != number)
            ui->lineEdit->setText("0");
        else {
            while (number > 0) {
                result = result * number;
                --number;
            }
            ui->lineEdit->setText(QString::number(result));
        }
    }
}
