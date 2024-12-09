#include "controller.h"

// Controller::Controller() {}


Controller::Controller(QObject* parent) : QObject(parent) {
    menu = new Menu();

    // Connect menu signals to Controller slots
    connect(menu, &Menu::singlePlayerSelected, this, &Controller::startSinglePlayer);
    connect(menu, &Menu::twoPlayerSelected, this, &Controller::startTwoPlayer);
    connect(menu, &Menu::difficultySelected, this, &Controller::showDifficultyMenu);
    connect(menu, &Menu::scoresSelected, this, &Controller::showScores);
    connect(menu, &Menu::exitSelected, this, &Controller::exitGame);

    menu->show();
}

void Controller::start()
{

}
