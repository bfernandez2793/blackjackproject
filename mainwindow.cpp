#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmapCache>


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
    QObject::connect(this,SIGNAL(dealer_hand_changed()),this,SLOT(setDealerHand()));
    QObject::connect(this,SIGNAL(dealerStart()),this,SLOT(setDealerStart()));
    QObject::connect(this,SIGNAL(hand_changed()),this,SLOT(setOutput()));//update any change in the players hand
    QObject::connect(this,SIGNAL(endgame()),this,SLOT(setEndgame()));//output the results of the game
    QObject::connect(this,SIGNAL(finished()),this,SLOT(setFinished()));
    handptrs.push_back(&player);
    handptrs.push_back(&player2);

    verticalPicsLayout=new QHBoxLayout(ui->cardLabel);
    verticalPicsLayout2=new QHBoxLayout(ui->cardLabel_2);

    i = 0;
    k = 0;
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
    ui->textBrowser->setText("");
    player.bet() = QInputDialog::getInt(this, tr("Place your bet"),tr("Bet:"),0,0,player.money(),1);
    player.update_hand();
    emit hand_changed();
    player.update_hand();
    emit hand_changed();
    dealer.update_hand();
    emit dealer_hand_changed();
    dealer.update_hand();
    emit dealer_hand_changed();
    ui->textBrowser->insertPlainText("\nCash: $" + QString::number(player.money()) +"\nPlayer 0:");
    if(player.blackjack())
        emit endgame();
}
void MainWindow::setHand()
{
    player.update_hand();
    emit hand_changed();
    if (player.size() != 2)
        ui->doubleButton->setEnabled(false);
    if(player.bust())
        emit bust();
}
void MainWindow::setStand()
{
    ui->hitButton->setEnabled(false);
    ui->standButton->setEnabled(false);
    ui->doubleButton->setEnabled(false);
    player2.play();
    emit dealerStart();
    emit endgame();
}
void MainWindow::setOutput()
{
    picture.load(QString::fromStdString(player.get_card_name())+".png");
    ++i;
    QLabel *picLabel = new QLabel(ui->cardLabel);
    picLabel->setScaledContents(true);
    picLabel->setPixmap(picture);
    ui->cardLabel->resize(i*75,100);
    verticalPicsLayout->addWidget(picLabel);
    ui->textBrowser->insertPlainText(QString::number(player.value_of_hand())+" ");
}
void MainWindow::setDealerHand()
{
    if(dealer.size() == 1)
    {
        picture.load("back.png");
        ++k;
        dealerinitcard = dealer.get_card_name();
        Dealerinit = new QLabel(ui->cardLabel_2);
        Dealerinit->setScaledContents(true);
        Dealerinit->setPixmap(picture);
        ui->cardLabel_2->resize(k*75,100);
        verticalPicsLayout2->addWidget(Dealerinit);
    }
    else
    {
        picture.load(QString::fromStdString(dealer.get_card_name())+".png");
        ++k;
        QLabel *picLabel = new QLabel(ui->cardLabel_2);
        picLabel->setScaledContents(true);
        picLabel->setPixmap(picture);
        ui->cardLabel_2->resize(k*75,100);
        verticalPicsLayout2->addWidget(picLabel);
    }

}
void MainWindow::setDealerStart()
{
    picture.load(QString::fromStdString(dealerinitcard)+".png");
    Dealerinit->setPixmap(picture);
    dealer.play(player.bust());
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
   // delete verticalPicsLayout->layout();
    QPixmapCache::clear();


}
void MainWindow::setFinished(){

    ui->hitButton->setEnabled(false);
    ui->standButton->setEnabled(false);
    ui->doubleButton->setEnabled(false);
    ui->startButton->setEnabled(false);
    /*Create lambda function to sort final cash amounts*/
}
