#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow),player(100)
{
    setFixedSize(400, 400);
    ui->setupUi(this);
    ui->hitButton->setEnabled(false);//cannot use before a game has begun
    ui->standButton->setEnabled(false);//cannot use before a game has begun

    QObject::connect(ui->startButton,SIGNAL(clicked(bool)),this,SLOT(setGame()));//when start button is clicked initialized the game
    QObject::connect(ui->hitButton,SIGNAL(clicked(bool)),this,SLOT(setHand()));//update hand button
    QObject::connect(ui->standButton,SIGNAL(clicked(bool)),this,SLOT(setStand()));//update hand button
    QObject::connect(this,SIGNAL(bust()),this,SLOT(setStand()));//if bust dont allow the player to get more cards
    QObject::connect(this,SIGNAL(hand_changed()),this,SLOT(setOutput()));//update any change in the players hand
    QObject::connect(this,SIGNAL(endgame()),this,SLOT(setEndgame()));//output the results of the game
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::setGame(){
    //initializing the game for one player
    ui->standButton->setEnabled(true);
    ui->hitButton->setEnabled(true);
    ui->startButton->setEnabled(false);
    ui->textBrowser->insertPlainText("Player 1:");
    emit hand_changed();
    std::cout << "Start Game\n";
    std::cout << player;
}
void MainWindow::setHand()
{
    player.update_hand();
    emit hand_changed();
    std::cout << player;
    if(player.bust())
        emit bust();
}
void MainWindow::setStand()
{
    std::cout << "Set Stand status\n";
    ui->hitButton->setEnabled(false);
    dealer.play(player.bust());
    ui->textBrowser->insertPlainText("\nDealer: " + QString::number(dealer.value_of_hand())) ;
    std::cout << dealer;
    emit endgame();
}
void MainWindow::setOutput()
{
   ui->textBrowser->insertPlainText(QString::number(player.value_of_hand())+" ");
}
void MainWindow::setEndgame()
{
    if (player.bust())
        ui->textBrowser->insertPlainText("\nPlayer Bust!! Dealer Wins!!");
    else if (dealer.bust())
        ui->textBrowser->insertPlainText("\nDealer Bust!! Player Wins!!");
    else if (player.value_of_hand() < dealer.value_of_hand())
        ui->textBrowser->insertPlainText("\nDealer Wins!!");
    else if (player.value_of_hand() > dealer.value_of_hand())
        ui->textBrowser->insertPlainText("\nPlayer Wins!!");
    else
        ui->textBrowser->insertPlainText("\nTie!!");
}

