#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow),player(100)
{
    setFixedSize(400, 400);
    ui->setupUi(this);
    ui->hitButton->setEnabled(false);//cannot use before a game has begun
    ui->standButton->setEnabled(false);//cannot use before a game has begun
    ui->doubleButton->setEnabled(false);//cannot use before a game has begun
    QObject::connect(ui->startButton,SIGNAL(clicked(bool)),this,SLOT(setGame()));//when start button is clicked initialized the game
    QObject::connect(ui->hitButton,SIGNAL(clicked(bool)),this,SLOT(setHand()));//update hand button
    QObject::connect(ui->standButton,SIGNAL(clicked(bool)),this,SLOT(setStand()));//update hand button
    QObject::connect(ui->doubleButton,SIGNAL(clicked(bool)),this,SLOT(setDouble()));//allow player double down
    QObject::connect(this,SIGNAL(bust()),this,SLOT(setStand()));//if bust dont allow the player to get more cards
    QObject::connect(this,SIGNAL(hand_changed()),this,SLOT(setOutput()));//update any change in the players hand
    QObject::connect(this,SIGNAL(endgame()),this,SLOT(setEndgame()));//output the results of the game
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::setGame()
{
    //initializing the game for one player
    ui->standButton->setEnabled(true);
    ui->hitButton->setEnabled(true);
    ui->doubleButton->setEnabled(true);
    ui->startButton->setEnabled(false);
    player.bet() = QInputDialog::getInt(this, tr("Place your bet"),tr("Bet:"),0,0,player.money(),1);
    ui->textBrowser->insertPlainText("Cash: $" + QString::number(player.money()) +"\nPlayer 1:");
    emit hand_changed();
    if(player.blackjack())
        emit endgame();
    std::cout << "Start Game\n";
    std::cout << player;
}
void MainWindow::setHand()
{
    player.update_hand();
    emit hand_changed();
    std::cout << player;
    if (player.size() != 2)
        ui->doubleButton->setEnabled(false);
    if(player.bust())
        emit bust();
}
void MainWindow::setStand()
{
    std::cout << "Set Stand status\n";
    ui->hitButton->setEnabled(false);
    ui->standButton->setEnabled(false);
    dealer.play(player.bust());
    std::cout << dealer;
    emit endgame();
}
void MainWindow::setOutput()
{
   ui->textBrowser->insertPlainText(QString::number(player.value_of_hand())+" ");
}
void MainWindow::setDouble()
{
    std::cout << player;
    player.update_hand();
    player.bet() = 2*player.bet();
    emit hand_changed();
    emit endgame();
}
void MainWindow::setEndgame()
{
    ui->textBrowser->insertPlainText("\nDealer: " + QString::number(dealer.value_of_hand())) ;
    if (player.bust())
    {
        player.money() -= player.bet();
        ui->textBrowser->insertPlainText("\nPlayer Bust!! Dealer Wins!! \nCash: $" + QString::number(player.money()));
    }
    else if (dealer.bust())
    {
        player.money() += player.bet();
        ui->textBrowser->insertPlainText("\nDealer Bust!! Player Wins!! \nCash: $" + QString::number(player.money()));
    }
    else if (player.value_of_hand() < dealer.value_of_hand())
    {
        player.money() -= player.bet();
        ui->textBrowser->insertPlainText("\nDealer Wins!! \nCash: $" + QString::number(player.money()));
    }
    else if (player.value_of_hand() > dealer.value_of_hand())
    {
        player.money() += player.bet();
        ui->textBrowser->insertPlainText("\nPlayer Wins!! \nCash: $" + QString::number(player.money()));
    }
    else
        ui->textBrowser->insertPlainText("\nTie!!");
}
