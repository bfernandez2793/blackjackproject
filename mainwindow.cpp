#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow)
{
    setFixedSize(400, 400);
    ui->setupUi(this);
    ui->hitButton->setEnabled(false);//cannot use before a game has begun
    ui->standButton->setEnabled(false);//cannot use before a game has begun

    QObject::connect(ui->startButton,SIGNAL(clicked(bool)),this,SLOT(setGame()));//when start button is clicked initialized the game
    QObject::connect(ui->hitButton,SIGNAL(clicked(bool)),this,SLOT(setHand()));//update hand button
    QObject::connect(ui->standButton,SIGNAL(clicked(bool)),this,SLOT(setStand()));//update hand button
    QObject::connect(this,SIGNAL(bust()),this,SLOT(setStand()));//if bust dont allow the player to get more cards
    QObject::connect(this,SIGNAL(hand_changed()),this,SLOT(setOutput()));


}

MainWindow::~MainWindow()
{
    delete ui;
    delete player;
    std::cout << "player released\n";
}
void MainWindow::setGame(){
    //initializing the game for one player
    player = new RandomPlayer(100);
    ui->standButton->setEnabled(true);
    ui->hitButton->setEnabled(true);
    ui->textBrowser->insertPlainText("Player 1:");
    emit hand_changed();
    std::cout << "Start Game\n";
    std::cout << *player;
}
void MainWindow::setHand()
{
    player->update_hand();
    emit hand_changed();
    if(player->bust())
    {
        ui->textBrowser->insertPlainText("Bust!!");
        emit bust();
    }
    std::cout << *player;
}
void MainWindow::setStand()
{
    ui->hitButton->setEnabled(false);
    std::cout << "Set Stand status\n";
}
void MainWindow::setOutput()
{
    ui->textBrowser->insertPlainText(QString::number(player->value_of_hand())+" ");
}


