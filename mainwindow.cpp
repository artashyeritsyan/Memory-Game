#include "mainwindow.h"


#include <Qtimer>

namespace {
QString buttonStyleSheet = R"(QPushButton {
    background-color: rgb(220, 20, 20);
    border: 8px solid rgb(170, 20, 20);
    color: rgb(255, 255, 255);
    border-radius: 15px;
    border-bottom: 8px solid rgb(120, 20, 20);
    border-right: 8px solid rgb(120, 20, 20);
}

QPushButton:hover {
    background-color: rgb(200, 0, 0);
    border: 8px solid rgb(150, 0, 0);
    color: rgb(255, 255, 255);
    border-radius: 15px;
    border-bottom: 8px solid rgb(100, 0, 0);
    border-right: 8px solid rgb(100, 0, 0);

    background-color: qlineargradient(spread:pad, x1:0.530695, y1:0.63, x2:0.53, y2:1, stop:0 rgba(211, 7, 27, 255), stop:1 rgba(112, 0, 0, 255))

}

QPushButton:pressed {
    background-color: rgb(150, 0, 0);
    border: 8px solid rgb(120, 0, 0);
    color: rgb(255, 255, 255);
    border-radius: 15px;
    border-bottom: 6px solid rgb(90, 0, 0);
    border-right: 6px solid rgb(90, 0, 0);
}
)";

} // unnamed namespace

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // ui->centralwidget->setGeometry(0, 0, 1400, 960);
    // ui->centralwidget->setFixedSize(1000, 960)

    initMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initMenu()
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTime);
    ui->timeBoard->setText(" Time: " + QString::number(elapsedTime) + "s");

    initGameSizeButtons();
    // connectSizeMenuButtons();

    QWidget* parentWidget = qobject_cast<QWidget*>(ui->GameSizeLayout->parent());
    if (parentWidget)
    {
        parentWidget->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    }

    hideGameSizeMenu();
    hideInfoBoard();
    hideWinGameFrame();
}

void MainWindow::initializeButtons(QVector<Card> table)
{
    for (int i = 0; i < table.size(); ++i) {
        QPushButton* button = new QPushButton;
        button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        button->setFlat(true);
        button->setCheckable(true);

        connect(button, &QPushButton::clicked, this, &MainWindow::onAnyButtonClicked);

        _buttons.push_back(button);
    }

    for (int i = 0; i < _buttons.size(); ++i) {
        _buttons[i]->setStyleSheet("QPushButton {border-image: url(:/XmasPictures/Assets/advent-calendar/blows.png);}" +
            QString("QPushButton:checked {border-image: url(:/XmasPictures/Assets/advent-calendar/Xmas_%1);}").arg(table[i].getPictureNumber() - 1));
    }

    create_layout();
}

void MainWindow::setGameSize(int height, int width)
{
    _height = height;
    _width = width;
}

void MainWindow::gameStartFunction(bool isTwoPlayer) {
    hideGameSizeMenu();
    hideMenuButtons();
    showInfoBoard();
    ui->GameNameLabel->hide();
    ui->widgets_frame->setStyleSheet("QFrame {background-color: qradialgradient(spread:pad, cx:0.2, cy:0.2, radius:0.477, fx:0.499775, fy:0.5, stop:0 rgba(1, 131, 165, 255), stop:0.99061 rgba(0, 103, 129, 255)); border-radius: 25px;  }");

    if (!isTwoPlayer) {
        updateScorePanels(0, 0);
    }
    else {
        updatePlayersScores(0, 0);
        updateTurnPanel(1);
    }

    timer->start(1000);
    elapsedTime = -1;
    updateTime();
}

void MainWindow::updateGameScreen(QVector<Card> table)
{
    for (int i = 0; i < table.size(); ++i) {
        if (table[i].getIsGuessed()) {
            _buttons[i]->setDisabled(true);
            _buttons[i]->setChecked(true);

            continue;
        }

        if (table[i].getIsFlipped()) {
            _buttons[i]->setChecked(true);
        }
        else {
            _buttons[i]->setChecked(false);
        }
    }

    // TODO: Add code for timer, score, and etc.
}

void MainWindow::cardResetCooldown()
{
    disableAllButtons();
    QTimer::singleShot(CARDCOOLDOWN, this, [this]() {
                if (this->_buttons.size() > 0) {
                    this->enableAllButtons();
                    emit this->requestScreenUpdate();
                }
            });
}

void MainWindow::winGame()
{
    ui->widgets_frame->setStyleSheet("");
    removeGameCards();
    hideInfoBoard();
    showWinGameFrame();
}

void MainWindow::updateScorePanels(int steps, int score)
{
    ui->scorePanel1->setText(" Steps: " + QString::number(steps));
    // ui->scorePanel2->setText(" Score: " + QString::number(score));
}

void MainWindow::updatePlayersScores(int score1, int score2)
{
    ui->scorePanel1->setText(" 1st Player: " + QString::number(score1));
    ui->scorePanel2->setText(" 2nd Player: " + QString::number(score2));
}

void MainWindow::updateTurnPanel(int playerTurn) {
    ui->scorePanel2->show();
    ui->turnPanel->show();

    if (playerTurn == 1) {
        ui->turnPanel->setText("1st Player`s turn ");
    }
    else {
        ui->turnPanel->setText("2nd Player`s turn ");
    }

}

void MainWindow::create_layout() {
    _buttonsLayout = qobject_cast<QVBoxLayout*>(ui->widgets_frame->layout());
    if (!_buttonsLayout) {
        _buttonsLayout = new QVBoxLayout(ui->widgets_frame);
        ui->widgets_frame->setLayout(_buttonsLayout);
    }

    int k = 0;
    for (int i = 0; i < _height; ++i) {
        QHBoxLayout* tempLayout = new QHBoxLayout(ui->widgets_frame);
        for (int j = 0; j < _width; ++j) {
            tempLayout->addWidget(_buttons[k++]);
        }

        _buttonsLayout->insertLayout(i, tempLayout);
    }
}

void MainWindow::onAnyButtonClicked(bool checked) {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if(!checked) {
        button->setChecked(true);
        return;
    }
    int buttonIndex = findButtonIndex(button);
    emit buttonClicked(buttonIndex);

        qDebug() << "buttonClicked works!!";
}

int MainWindow::findButtonIndex(QPushButton *button)
{
    for (int i = 0; i < _buttons.size(); ++i) {
        if (button == _buttons[i]) {
            return i;
        }
    }
    return 0;
}

void MainWindow::updateTime() {
    ++elapsedTime;
    ui->timeBoard->setText(" Time: " + QString::number(elapsedTime) + "s");
}

void MainWindow::endGame() {
    timer->stop();
}

void MainWindow::disableAllButtons()
{
    if (_buttons.size() > 0) {
        for (int i = 0; i < _buttons.size(); ++i) {
            _buttons[i]->setDisabled(true);
        }
    }
}

void MainWindow::enableAllButtons()
{
    if (_buttons.size() > 0) {
        for (int i = 0; i < _buttons.size(); ++i) {
            _buttons[i]->setDisabled(false);
        }
    }
    // chi kara sax sarqi Enable vortev en hin disable-neru kkoren
    /// TODO: Call updateScreen function and give the table to update screen
}

void MainWindow::removeGameCards()
{
    for (int i = _buttons.size() - 1; i >= 0 ; --i) {
        _buttons[i]->deleteLater();
        _buttons.pop_back();
    }

    for (int i = 0; i < _buttonsLayout->count(); ++i) {
        auto item = _buttonsLayout->itemAt(i);
        item->layout()->deleteLater();
    }
}

void MainWindow::exitToMenu()
{
    ui->widgets_frame->setStyleSheet("");
    removeGameCards();
    hideInfoBoard();
    showMenuButtons();
    ui->GameNameLabel->show();
    hideWinGameFrame();
}

void MainWindow::gameRestartManager()
{
    exitToMenu();
    emit restartGame();
}


void MainWindow::hideMenuButtons()
{
    for (int i = 0; i < ui->MenuLayout->count(); ++i) {
        auto item = ui->MenuLayout->itemAt(i);
        item->widget()->hide();
    }
}

void MainWindow::showMenuButtons()
{
    for (int i = 0; i < ui->MenuLayout->count(); ++i) {
        auto item = ui->MenuLayout->itemAt(i);
        item->widget()->show();
    }
}


void MainWindow::on_SinglePlayerBtn_clicked()
{
    hideMenuButtons();
    showGameSizeMenu();
    _gameMode = EGameMode::SINGLEPLAYER;

    // gameStartFunction();
}

void MainWindow::initGameSizeButtons()
{

    for (int i = 0; i < 5; ++i) {
        QPushButton* button = new QPushButton;
        button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        button->setText(QString("4 x %1").arg(i + 3));

        QFont font;
        font.setFamily("FreeStyle Script");
        font.setPointSize(30);
        font.setBold(true);
        button->setFont(font);
        button->setStyleSheet(buttonStyleSheet);

        connect(button, &QPushButton::clicked, this, &MainWindow::onAnyGameSizeButtonClicked);

        ui->GameSizeLayout->addWidget(button);
    }
}

void MainWindow::on_TwoPlayerBtn_clicked()
{
    hideMenuButtons();
    _gameMode = EGameMode::TWOPLAYER;
    showGameSizeMenu();
}

void MainWindow::on_ExitButton_clicked()
{
    exit(0);
}


// Game size choosing menu
// void MainWindow::connectSizeMenuButtons()
// {
//     for (int i = 0; i < ui->GameSizeLayout->count(); ++i) {
//         auto item = ui->GameSizeLayout->itemAt(i);
//         QPushButton* button = qobject_cast<QPushButton*>(item->widget());
//         connect(button, &QPushButton::clicked, this, &MainWindow::onAnyGameSizeButtonClicked);
//     }
// }

void MainWindow::onAnyGameSizeButtonClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());

    for (int i = 0; i < ui->GameSizeLayout->count(); ++i) {
        auto item = ui->GameSizeLayout->itemAt(i);
        if (auto buttonInLayout = qobject_cast<QPushButton*>(item->widget())) {
            if (button == buttonInLayout) {
                _gameSize = EGameSize(i);
                break;
            }
        }
    }

    // hideGameSizeMenu();
    // showScoreBoard();
    emit startGame(_gameMode, _gameSize);
}

void MainWindow::hideGameSizeMenu()
{
    QWidget* parentWidget = qobject_cast<QWidget*>(ui->GameSizeLayout->parent());
    if (parentWidget)
    {
        parentWidget->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    }

    for (int i = 0; i < ui->GameSizeLayout->count(); ++i) {
        auto item = ui->GameSizeLayout->itemAt(i);
        item->widget()->hide();
    }
    ui->BackFromSizeMenu->hide();

}

void MainWindow::showGameSizeMenu()
{
    for (int i = 0; i < ui->GameSizeLayout->count(); ++i) {
        auto item = ui->GameSizeLayout->itemAt(i);
        item->widget()->show();
    }
    ui->BackFromSizeMenu->show();

    QWidget* parentWidget = qobject_cast<QWidget*>(ui->GameSizeLayout->parent());
    if (parentWidget)
    {
        parentWidget->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    }
}

void MainWindow::hideInfoBoard()
{
    ui->Info_board_frame->hide();
    ui->scorePanel2->hide();
    ui->turnPanel->hide();

    // ui->infoPanelLayout->
}

void MainWindow::showInfoBoard()
{
    // hideWidgetsInLayout(ui->Info_board_frame, false);
    ui->Info_board_frame->show();
}

void MainWindow::hideWinGameFrame()
{
    ui->WinFrame->hide();
}

void MainWindow::showWinGameFrame()
{
    ui->WinFrame->move(320, 100);
    ui->WinFrame->show();
    ui->WinFrame->raise();
    ui->TimeSign->setText(ui->timeBoard->text());
    ui->WinSign->setText("You Win");
    ui->StepsSign->setText(ui->scorePanel1->text());
}

void MainWindow::setWinnerInfo(int winnerId, int score)
{
    if (winnerId == 0) {
        ui->WinSign->setText("Draw");
    }
    else if (winnerId == 1) {
        ui->WinSign->setText("1st Player Win");
    }
    else {
        ui->WinSign->setText("2nd Player Win");
    }

    ui->StepsSign->setText(" Score: " + QString::number(score));
}


void MainWindow::on_BackFromSizeMenu_clicked()
{
    showMenuButtons();
    hideGameSizeMenu();
}

void MainWindow::on_RestartButton_clicked()
{
    gameRestartManager();
}


void MainWindow::on_RestartButton_2_clicked()
{
    gameRestartManager();
}

void MainWindow::on_HomeButton_clicked()
{
    exitToMenu();
}

void MainWindow::on_HomeButton_2_clicked()
{
    exitToMenu();
}



