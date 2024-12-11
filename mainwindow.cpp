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

    steps = 0;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTime);
    ui->timeBoard->setText("Time: " + QString::number(elapsedTime) + "s");

    initGameSizeButtons();
    // connectSizeMenuButtons();

    QWidget* parentWidget = qobject_cast<QWidget*>(ui->GameSizeLayout->parent());
    if (parentWidget)
    {
        parentWidget->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    }

    hideGameSizeMenu();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeButtons(QVector<Card> table)
{
    for (int i = 0; i < table.size(); ++i) {
        QPushButton* button = new QPushButton;
        button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        button->setFlat(true);
        button->setCheckable(true);

        connect(button, &QPushButton::clicked, this, &MainWindow::on_anyButton_clicked);

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

void MainWindow::gameStartFunction() {
    // random_card_generation();

    ui->scoreBoard->setText("Score: " + QString::number(score));
    ui->stepsBoard->setText("Steps: " + QString::number(steps));

    timer->start(1000);
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

void MainWindow::on_anyButton_clicked(bool checked) {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if(!checked) {
        button->setChecked(true);
        return;
    }
// qt.core.qmetaobject.connectslotsbyname: QMetaObject::connectSlotsByName: No matching signal for on_anyButton_clicked(bool)
    int buttonIndex = findButtonIndex(button);
    emit buttonClicked(buttonIndex);

        qDebug() << "buttonClicked works!!";

    // bool isSecond = false;

    // if (checked) {
    //     QPushButton* secondButton;

    //     for (int i = 0; i < (_height * _width); ++i) {
    //         if (_buttons[i]->isChecked() && _buttons[i]->isEnabled() && _buttons[i] != button) {
    //             secondButton = _buttons[i];
    //             isSecond = true;

    //             break;
    //         }
    //     }

        // if (isSecond) {

        //     QVector<bool> conditions(_buttons.size());

        //     if (button->styleSheet() == secondButton->styleSheet()) {
        //         ui->scoreBoard->setText("Score: " + QString::number(++score));

        //         button->setEnabled(false);
        //         secondButton->setEnabled(false);

        //         // if (score == _buttons.size()/2) {
        //         if (score >= 14) {
        //             delete timer;
        //             auto messageBox = new QMessageBox;
        //             messageBox->setWindowTitle("Congratulations");
        //             // QPixmap iconPixmap(":/assets/images/IMG_3970.JPG");
        //             // message->setIconPixmap(iconPixmap);
        //             messageBox->setText("🎉🎉 Congratulations! You Win 🎉🎉   ");
        //             messageBox->setFixedSize(300, 200);
        //             // message->show();
        //             messageBox->exec();

        //         }
        //     }
        //     else {
                // QTimer::singleShot(cardCooldown, this, [this, button]() {
                //     this->update_button_image(button);
                // });
        //         QTimer::singleShot(cardCooldown, this, [this, secondButton]() {
        //             this->update_button_image(secondButton);
        //         });
        //     }
        //     for (int i = 0; i < _buttons.size(); ++i) {
        //         conditions[i] = _buttons[i]->isEnabled();
        //         _buttons[i]->setEnabled(false);
        //     }

        //     ui->stepsBoard->setText("Steps: " + QString::number(++steps));

        //     QTimer::singleShot(cardCooldown, this, [this, conditions]() {
        //         this->returnConditions(conditions);
        //     });

        // }
    // }
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

// void MainWindow::choose_card(int index) {

// }

// void MainWindow::compare_cards(int index_1, int index_2) {

// }

// void MainWindow::update_button_image(QPushButton* button) {
//     button->setChecked(false);
// }

// void MainWindow::returnConditions(QVector<bool> conditions) {
//     for(int i = 0; i < _buttons.size(); ++i) {
//         _buttons[i]->setEnabled(conditions[i]);
//     }
// }

void MainWindow::updateTime() {
    ++elapsedTime;
    ui->timeBoard->setText("Time: " + QString::number(elapsedTime) + "s");
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

void MainWindow::removeGameWidgets()
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
    removeGameWidgets();
    showMenuButtons();
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
    _gameMode = EGameMode::SINGLEPLAYER;
    showGameSizeMenu();

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
    // hideMenuButtons();
    // Exit game
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

    hideGameSizeMenu();
    emit startGame(_gameMode, _gameSize);
        qDebug() << "startGame works!!";
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

void MainWindow::on_BackFromSizeMenu_clicked()
{
    showMenuButtons();
    hideGameSizeMenu();
}


void MainWindow::on_HomeButton_clicked()
{
    exitToMenu();
}

