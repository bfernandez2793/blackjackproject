#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow),player(100),player2(100)
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
    QObject::connect(this,SIGNAL(finished()),this,SLOT(setFinished()));
    handptrs.push_back(&player);
  //srand(time(NULL));
 //   int r = 0 + rand() % 5;
    for(size_t i = 0; i < r; ++i)
    {
        handptrs.push_back(&player2);
    }
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
    player.start();
    player.bet() = QInputDialog::getInt(this, tr("Place your bet"),tr("Bet:"),0,0,player.money(),1);
    ui->textBrowser->setText("");
    ui->textBrowser->insertPlainText("\nCash: $" + QString::number(player.money()) +"\nPlayer 0:");
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
    ui->doubleButton->setEnabled(false);
    player2.start();
    player2.play();
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

    ui->textBrowser->insertPlainText("\nPlayer1: "+ QString::number(player2.value_of_hand()));
    ui->textBrowser->insertPlainText("\nDealer: " + QString::number(dealer.value_of_hand())) ;

    int i = 0;
    for(auto& x: handptrs)
    {
        if (x->bust())
        {
            x->money() -= x->bet();
            ui->textBrowser->insertPlainText("\nPlayer" + QString::number(i) +" Bust!! Dealer Wins!! Cash: $" + QString::number(x->money()));
        }
        else if (dealer.bust())
        {
            x->money() += x->bet();
            ui->textBrowser->insertPlainText("\nDealer Bust!! Player " + QString::number(i) +" Wins!! Cash: $" + QString::number(x->money()));
        }
        else if (x->value_of_hand() < dealer.value_of_hand())
        {
            x->money() -= x->bet();
            ui->textBrowser->insertPlainText("\nDealer Wins!! Cash: $" + QString::number(x->money()));
        }
        else if (x->value_of_hand() > dealer.value_of_hand())
        {
            x->money() += x->bet();
            ui->textBrowser->insertPlainText("\nPlayer " + QString::number(i) +" Wins!! Cash: $" + QString::number(x->money()));
        }
        else
            ui->textBrowser->insertPlainText("\nTie!!");
        x->reset();
        ++i;
    }
    dealer.reset();
    ui->startButton->setText("Restart");
    ui->startButton->setEnabled(true);
    if(handptrs[0]->money() == 0)
        emit finished();
}
void MainWindow::setFinished(){

    ui->hitButton->setEnabled(false);
    ui->standButton->setEnabled(false);
    ui->doubleButton->setEnabled(false);
    ui->startButton->setEnabled(false);
    /*Create lambda function to sort final cash amounts*/
}
