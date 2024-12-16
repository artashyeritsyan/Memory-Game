#include "controller.h"

Controller::Controller() {
    _board = nullptr;
    _window = new MainWindow();

    _window->setFixedSize(1420, 940);

    connect(_window, &MainWindow::startGame, this, &Controller::handleStartCmd);
    connect(_window, &MainWindow::restartGame, this, &Controller::handleGameRestartCmd);
    connect(_window, &MainWindow::buttonClicked, this, &Controller::handleClick);
    connect(_window, &MainWindow::requestScreenUpdate, this, &Controller::handleScreenUpdateRequest);

    _window->show();

    // connect(_board, &Board::waitForCooldown, this, &Controller::handleCooldown);
    // connect(_board, &Board::sendSteps, this, &Controller::updateStepsValue);
}

Controller::~Controller()
{
    delete _window;
}

void Controller::startGame()
{
    if (_board != nullptr) {
        delete _board;
    }
    _board = new Board(_height, _width, _isTwoPlayer);

    _window->setGameSize(_height, _width);
    _window->initializeButtons(_board->getTable());

    _window->gameStartFunction(_isTwoPlayer);
}

void Controller::handleStartCmd(EGameMode gameMode, EGameSize gameSize)
{
    switch (gameSize)
    {
    case SIZE_4x3:
        _height = 3;
        _width = 4;
        break;
    case SIZE_4x4:
        _height = 4;
        _width = 4;
        break;
    case SIZE_4x5:
        _height = 4;
        _width = 5;
        break;
    case SIZE_4x6:
        _height = 4;
        _width = 6;
        break;
    case SIZE_4x7:
        _height = 4;
        _width = 7;
        break;
    default:
        _height = 4;
        _width = 5;
    }

    if (gameMode == EGameMode::SINGLEPLAYER) {
        _isTwoPlayer = false;
    }
    else {
        _isTwoPlayer = true;
    }

    startGame();
}

void Controller::handleGameRestartCmd()
{
    startGame();
}

void Controller::handleClick(int buttonIndex)
{
    if (_board->checkCard(buttonIndex)) {
        _window->cardResetCooldown();
    }

    if (_isTwoPlayer) {
        _window->updatePlayersScores(_board->firstPlayerScore(), _board->secondPlayerScore());
        _window->updateTurnPanel(_board->getPlayerTurn());
    }
    else {
        _window->updateScorePanels(_board->getSteps(), _board->getScore());
    }

    if(_board->winCheck()) {
        _window->winGame();
    }
}

void Controller::handleScreenUpdateRequest()
{
    _window->updateGameScreen(_board->getTable());
}

void Controller::handleCooldown()
{
    _window->cardResetCooldown();
}




