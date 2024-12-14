#include "controller.h"


// Controller::Controller() {}


Controller::Controller() {
    _window = new MainWindow();

    connect(_window, &MainWindow::startGame, this, &Controller::handleStartCmd);
    connect(_window, &MainWindow::restartGame, this, &Controller::handleGameRestartCmd);
    connect(_window, &MainWindow::buttonClicked, this, &Controller::handleClick);
    connect(_window, &MainWindow::requestScreenUpdate, this, &Controller::handleScreenUpdateRequest);

    _window->show();

    // connect(_board, &Board::waitForCooldown, this, &Controller::handleCooldown);
    // connect(_board, &Board::sendSteps, this, &Controller::updateStepsValue);
}

void Controller::startSinglePlayer()
{
    // if (_board != nullptr) {
    //     delete _board;
    // }
    _board = new Board(_height, _width);

    // connect(_board, &Board::waitCardCooldown, this, &Controller::handleCooldown);

    _window->setGameSize(_height, _width);
    _window->initializeButtons(_board->getTable());
    _window->gameStartFunction();
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

    _gameMode = gameMode;
    if (_gameMode == EGameMode::SINGLEPLAYER) {
        startSinglePlayer();
    }
    else {

    }
}

void Controller::handleGameRestartCmd()
{
    if (_gameMode == EGameMode::SINGLEPLAYER) {
        startSinglePlayer();
    }
    else {

    }
}

void Controller::handleClick(int buttonIndex)
{
    if (_board->checkCard(buttonIndex)) {
        _window->cardResetCooldown();

    }
    _window->updateStepsAndScore(_board->getSteps(), _board->getScore());

}

void Controller::handleScreenUpdateRequest()
{
    _window->updateGameScreen(_board->getTable());
}

void Controller::handleCooldown()
{
    _window->cardResetCooldown();
}


