#include "mainwindow.h"
#include "ui_mainwindow.h"

int mano[5][3];
bool fast=false;

int valore(int carta){
    return carta%10+1;
}
int seme(int carta){
    return floor(carta/10);
}

int punti(int carta){
    int punti[]={11, 0, 10, 0, 0, 0, 0, 2, 3, 4};
    return punti[valore(carta)-1];
}
int potenza(int carta){
    int potenza[]={9, 0, 8, 1, 2, 3, 4, 5, 6, 7};
    return potenza[valore(carta)-1];
}

int CarteDisp(int *carte){
    int CarteDisp = 0;
        for(int i=0; i<40; i++)
            if(carte[i]==0)
                CarteDisp++;
    return CarteDisp;
}

void Pesca(int &slot, int *carte, int &briscola){
    if(CarteDisp(carte)==1){
        slot = briscola;
        carte[briscola]=1;
    }
    else if(CarteDisp(carte)>0){
        do{
            slot = rand()%40;
        }while(carte[slot]==1 or slot==briscola);
        carte[slot]=1;
    }
}
const char* semeW(int carta){
    const char *semi[]={"Denari", "Coppe", "Bastoni", "Spade"};
    return semi[seme(carta)];
}

const char* valoreW(int carta){
    const char *valori[]={"Asso","2","Tre","4","5","6","7","Fante","Cavallo","Re"};
    return valori[valore(carta)-1];
}

int CPU(int cpu, int *tavolo, int pt, int br, int player, bool difficile, int Dmano,  bool *Teams){
    int V[Dmano], Vmin=20, Vmax=-1, min, max, win=0;
    //Assegno un valore alle carte in mano
    for(int i=0; i<Dmano; i++){
        if(mano[cpu][i]==-1)
            V[i]=100;
        else{
            V[i]=potenza(mano[cpu][i]);
            if( seme(mano[cpu][i]) == seme(br) )
                V[i]+=6;
        }
    }
    for(int i=0; i<Dmano; i++){
        if(V[i] < Vmin){
            Vmin=V[i];
            min=i;
        }
        if(V[i] > Vmax and V[i]!=100 and seme(mano[cpu][i]) != seme(br)){
            Vmax=V[i];
            max=i;
        }
    }
    for(int i=1; i<player; i++){
        if(tavolo[i]!=-1){
            if( seme(tavolo[i]) == seme(tavolo[win]) and potenza(tavolo[i]) > potenza(tavolo[win]))
                win=i;
            if( seme(tavolo[i]) != seme(tavolo[win]) and seme(tavolo[i])==seme(br))
                    win=i;
        }
    }
    if(difficile){
        //Decido cosa giocare
        if(tavolo[0]==-1)
            return min+1;
        else if( Teams[cpu] == Teams[win] ){
            if(Vmax!=-1 and seme(mano[cpu][max])!= seme(br))
                min=max;
        }
        else if(pt<7){
            for(int i=0; i<Dmano; i++){
                if( seme(mano[cpu][i]) != seme(tavolo[win]) and seme(mano[cpu][i])==seme(br) and V[i]<11)
                    min=i;
                if( seme(mano[cpu][i]) == seme(tavolo[win]) and potenza(mano[cpu][i]) > potenza(tavolo[win]) and seme(mano[cpu][i])!=seme(br))
                    min=i;
            }
            for(int i=0; i<Dmano; i++){
                if( seme(mano[cpu][i]) == seme(tavolo[win]) and seme(mano[cpu][i])!=seme(br) and potenza(mano[cpu][i]) > potenza(tavolo[win]) and punti(i)>punti(min) )
                    min=i;
                if( seme(mano[cpu][i]) != seme(tavolo[win]) and seme(mano[cpu][i])==seme(br) and V[i]<11 )
                    min=i;
            }
        }
        else{
            for(int i=0; i<Dmano; i++){
                if( seme(mano[cpu][i]) == seme(tavolo[win]) and seme(mano[cpu][i])!=seme(br) and potenza(mano[cpu][i]) > potenza(tavolo[win]) and punti(i)>punti(min) )
                    min=i;
                if( seme(mano[cpu][i]) != seme(tavolo[win]) and seme(mano[cpu][i])==seme(br) and V[i]<V[min] )
                    min=i;
            }
        }
    }
    else{
        srand(time(NULL));
        do{
            min=rand() % Dmano;
        }while(mano[cpu][min]==-1);
    }
    return min+1;
}

int Vincitore(int *tavolo, int turno, int briscola, int player){
    int win=0;
    for(int i=1; i<player; i++){
        if( seme(tavolo[i]) == seme(tavolo[win]) and potenza(tavolo[i]) > potenza(tavolo[win]))
            win=i;
        if( seme(tavolo[i]) != seme(tavolo[win]) and seme(tavolo[i])==seme(briscola))
            win=i;
    }
    return (turno+win)%player;
}

void delay(double time)
{
    if(!fast)
        time/=1000;
    else
        time=0;
    QTime dieTime= QTime::currentTime().addSecs(time);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Cards Declaration
    Card[0][0]=ui->Card00;
    Card[0][1]=ui->Card01;
    Card[0][2]=ui->Card02;
    Card[1][0]=ui->Card10;
    Card[1][1]=ui->Card11;
    Card[1][2]=ui->Card12;
    Card[2][0]=ui->Card20;
    Card[2][1]=ui->Card21;
    Card[2][2]=ui->Card22;
    Card[3][0]=ui->Card30;
    Card[3][1]=ui->Card31;
    Card[3][2]=ui->Card32;

    //Selects Declaration
    select[0]=ui->select0;
    select[1]=ui->select1;
    select[2]=ui->select2;

    //Player Boxes Declaration
    PlayerBox[0]=ui->Player1Box;
    PlayerBox[1]=ui->Player2Box;
    PlayerBox[2]=ui->Player3Box;
    PlayerBox[3]=ui->Player4Box;

    //Tavolo Declaration
    Tavolo[0]=ui->Tavolo0;
    Tavolo[1]=ui->Tavolo1;
    Tavolo[2]=ui->Tavolo2;
    Tavolo[3]=ui->Tavolo3;

    //hide menu
    ui->logoLabel_2->hide();
    ui->buttonMode1->hide();
    ui->buttonMode2->hide();
    ui->buttonOptions->hide();
    ui->modeLabel->hide();
    ui->side1->hide();
    ui->side2->hide();
    ui->buttonInfo->hide();
    ui->storicoLabel->hide();
    ui->regoleLabel->hide();

    //hide options
    ui->NPlayerLabel->hide();
    ui->SpeedLabel->hide();
    ui->checkBox->hide();
    ui->OptionsFrame->hide();
    ui->horizontalSlider->hide();
    ui->horizontalSlider_2->hide();

    //hide game
    for(int i=0; i<4; i++)
        for(int j=0; j<3; j++)
            Card[i][j]->hide();
    for(int i=0; i<3; i++)
            select[i]->hide();
    for(int i=0; i<4; i++)
           Tavolo[i]->hide();
    for(int i=0; i<4; i++)
           PlayerBox[i]->hide();
    ui->carteRimanentiLabel->hide();
    ui->puntiTavolaLabel->hide();
    ui->confirmButton->hide();
    ui->Briscola->hide();
    ui->Mazzo->hide();
    ui->communicationLabel->hide();
    ui->Mostra->hide();
    ui->menuButton->hide();
    ui->suggerimentoButton->hide();
    ui->gameEndLabel->hide();
    ui->gameEndButton->hide();

    aniTimer=new QTimer(this);
    aniTimer->setInterval(1000);
    connect(aniTimer, &QTimer::timeout, this, &MainWindow::animation);
    aniTimer->start(1000);

    speed=1.00;
    Nplayer=1;
    Dmano=3;
    toggle=true;
    difficile=false;
    opt=false;
    st=false;
    premium=false;

    animation1 = new QPropertyAnimation(ui->logoLabel, "geometry");
    animation1->setDuration(1000);
    animation1->setStartValue(ui->logoLabel->geometry());
    animation1->setEndValue(QRect(ui->logoLabel->x()-25, ui->logoLabel->y()-25, ui->logoLabel->width()+50, ui->logoLabel->height()+50));
    animation2 = new QPropertyAnimation(ui->logoLabel, "geometry");
    animation2->setDuration(1000);
    animation2->setStartValue(QRect(ui->logoLabel->x()-25, ui->logoLabel->y()-25, ui->logoLabel->width()+50, ui->logoLabel->height()+50));
    animation2->setEndValue(ui->logoLabel->geometry());

}

void MainWindow::imposta(char mod, int *carte, int player, int &briscola, int &turno, int *punti, int Nplayer, bool *Cplayers, int &Dmano){
    QString edit;
    turno=0;
    int k=Nplayer;
    for(int i=0; i<5; i++)
        punti[i]=0;
    for(int i = 0; i<40; i++)
        carte[i]=0;
    for(int i=0; i<player; i++)
        if(k==0)
            Cplayers[i]=0;
        else{
            Cplayers[i]=1;
            k--;
        }
    for(int i=0; i<4; i++){
        if(CPlayers[i]){
            edit="Player ";
            QTextStream(&edit)<<i+1<<" Punti: "<< PuntiP[i%2];
        }
        else{
            edit="CPU ";
            QTextStream(&edit)<<i-Nplayer+1<<" Punti: "<< PuntiP[i%2];
        }
        PlayerBox[i]->setText(edit);
    }
    if(mod=='f'){
        Dmano=8;
        for(int i=0; i<player; i++)
            for(int j=0; j<Dmano; j++){
                do{
                    mano[i][j] = rand()%40;
                }while(carte[mano[i][j]]==1);
                carte[mano[i][j]]=1;
            }
        ui->communicationLabel->setText("Decisione Briscola in corso...");
    }
    else{
        Dmano=3;
        briscola = rand()%40;
        for(int i=0; i<player; i++)
            for(int j=0; j<Dmano; j++){
                do{
                    mano[i][j] = rand()%40;
                }while(carte[mano[i][j]]==1 or mano[i][j]==briscola);
                carte[mano[i][j]]=1;
            }
        ui->Briscola->setStyleSheet("");
        ui->Briscola->setPixmap(immagini[seme(briscola)][valore(briscola)-1]);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::animation()
{
    if(toggle){
        animation1 ->start();
        toggle=false;
    }
    else{
        animation2 ->start();
        toggle=true;
    }
}

void MainWindow::sideAnimation(){
    if(toggle){
        sideAni1 = new QPropertyAnimation(ui->side1, "geometry");
        sideAni1->setDuration(1000);
        sideAni1->setStartValue(QRect(ui->side1->x(), ui->side1->y(), ui->side1->width(), ui->side1->height()));
        sideAni1->setEndValue(QRect(ui->side1->x(), ui->side1->y()+100, ui->side1->width(), ui->side1->height()));

        sideAni2 = new QPropertyAnimation(ui->side2, "geometry");
        sideAni2->setDuration(1000);
        sideAni2->setStartValue(QRect(ui->side2->x(), ui->side2->y(), ui->side2->width(), ui->side2->height()));
        sideAni2->setEndValue(QRect(ui->side2->x(), ui->side2->y()+100, ui->side2->width(), ui->side2->height()));
        toggle=false;
    }
    else{
        sideAni1 = new QPropertyAnimation(ui->side1, "geometry");
        sideAni1->setDuration(1000);
        sideAni1->setStartValue(QRect(ui->side1->x(), ui->side1->y(), ui->side1->width(), ui->side1->height()));
        sideAni1->setEndValue(QRect(ui->side1->x(), ui->side1->y()-100, ui->side1->width(), ui->side1->height()));

        sideAni2 = new QPropertyAnimation(ui->side2, "geometry");
        sideAni2->setDuration(1000);
        sideAni2->setStartValue(QRect(ui->side2->x(), ui->side2->y(), ui->side2->width(), ui->side2->height()));
        sideAni2->setEndValue(QRect(ui->side2->x(), ui->side2->y()-100, ui->side2->width(), ui->side2->height()));
        toggle=true;
    }
    sideAni1->start();
    sideAni2->start();
    hide_game();
}

void MainWindow::hide_menu()
{
    aniTimer->stop();
    sideAni1->stop();
    sideAni2->stop();
    ui->modeLabel->hide();
    ui->side1->hide();
    ui->side2->hide();
    ui->logoLabel_2->hide();
    ui->buttonMode1->hide();
    ui->buttonMode2->hide();
    ui->buttonOptions->hide();
    ui->backgroundLabel->setStyleSheet("image: url(:/gameBG4resized.jpg);");
    ui->NPlayerLabel->hide();
    ui->SpeedLabel->hide();
    ui->checkBox->hide();
    ui->OptionsFrame->hide();
    ui->horizontalSlider->hide();
    ui->horizontalSlider_2->hide();
    ui->buttonInfo->hide();
    ui->storicoLabel->hide();
    ui->regoleLabel->hide();
    ui->side1->setGeometry(50, -100, 355, 1000);
    ui->side2->setGeometry(795, -100, 355, 1000);
    opt=false;
}

void MainWindow::show_menu()
{
    ui->modeLabel->show();
    ui->side1->show();
    ui->side2->show();
    ui->logoLabel_2->show();
    ui->buttonMode1->show();
    if(premium)
        ui->buttonMode2->show();
    ui->buttonOptions->show();
    ui->backgroundLabel->setStyleSheet("image: url(:/menuresized.png);");
    ui->buttonInfo->show();
    //ui->buttonInfo->setGeometry(500, 425+premium*35, 200, 49);
    ui->buttonMode1->setGeometry(500, 390-premium*70, 200, 49);
    ui->modeLabel->setGeometry(485, 345-premium*55, 230, 20);
    ui->horizontalSlider->setMaximum(2+premium*2);
    if(st)
        ui->storicoLabel->show();
}

void MainWindow::show_game(){
    for(int i=0; i<player; i++)
        for(int j=0; j<3; j++)
           Card[i][j]->show();
    for(int i=0; i<4; i++)
           Tavolo[i]->show();
    for(int i=0; i<player; i++)
        PlayerBox[i]->show();
    ui->carteRimanentiLabel->show();
    ui->puntiTavolaLabel->show();
    ui->Briscola->show();
    ui->Mazzo->show();
    ui->communicationLabel->show();
    ui->menuButton->show();
}

void MainWindow::hide_game(){
        for(int i=0; i<4; i++)
            for(int j=0; j<3; j++)
               Card[i][j]->hide();
        for(int i=0; i<4; i++)
               Tavolo[i]->hide();
        for(int i=0; i<3; i++)
               select[i]->hide();
        for(int i=0; i<4; i++)
               PlayerBox[i]->hide();
        ui->carteRimanentiLabel->hide();
        ui->puntiTavolaLabel->hide();
        ui->confirmButton->hide();
        ui->Briscola->hide();
        ui->Mazzo->hide();
        ui->communicationLabel->hide();
        ui->menuButton->hide();
        ui->Mostra->hide();
        ui->suggerimentoButton->hide();
        ui->gameEndLabel->hide();
        ui->gameEndButton->hide();
}

void MainWindow::on_pushButton_clicked()
{
    QPixmap cards (":/Piacentine.jpg");
        for(int a=0; a<10; a++){
            for(int j=0; j<4; j++){
                QRect rect(8+a*87.9, 7+j*149, 66, 125);
                QPixmap cropped  =cards.copy(rect);
                cropped.setDevicePixelRatio(0.9);
                immagini[j][a]=cropped;
            }
        }
    aniTimer->stop();
    animation1 ->stop();
    animation2 ->stop();
    ui->checkBox_2->hide();
    ui->logoLabel->hide();
    ui->pushButton->hide();
    aniTimer=new QTimer(this);
    aniTimer->setInterval(1000);
    connect(aniTimer, &QTimer::timeout, this, &MainWindow::sideAnimation);
    aniTimer->start(1000);
    ui->side1->setGeometry(50, -100, 355, 1000);
    ui->side2->setGeometry(795, -100, 355, 1000);
    show_menu();
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    difficile=arg1;
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
   Nplayer=value;
   text="Numero Player: ";
   QTextStream(&text)<<value;
   ui->NPlayerLabel->setText(text);
}

void MainWindow::on_buttonOptions_clicked()
{
    if(opt){
        ui->SpeedLabel->hide();
        ui->checkBox->hide();
        ui->OptionsFrame->hide();
        ui->horizontalSlider->hide();
        ui->horizontalSlider_2->hide();
        opt=false;
    }
    else{
        ui->NPlayerLabel->show();
        ui->SpeedLabel->show();
        ui->checkBox->show();
        ui->OptionsFrame->show();
        ui->horizontalSlider->show();
        ui->horizontalSlider_2->show();
        opt=true;
    }
}

void MainWindow::on_buttonMode1_clicked()
{
    if(Nplayer<=2){
        game=true;
        mod='s';
        player=2;
        Play(false);
    }
    else{
        QMessageBox Warn;
        Warn.setText("Attenzione, Non si può giocare 1v1 con più di 2 player!");
        Warn.exec();
    }
}

void MainWindow::on_buttonMode2_clicked()
{
    game=true;
    mod='d';
    player=4;
    Play(false);
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    speed=float(value)/100;
    text="Velocità di Gioco: ";
    QTextStream(&text)<<speed;
    ui->SpeedLabel->setText(text);
}

void MainWindow::setPos(){
    if(mod=='s'){
        for(int i=0; i<3; i++)
            Card[1][i]->setGeometry(448+108*i, 50, 88, 149);
        PlayerBox[1]->setGeometry(330, 50, 101, 71);
    }
    if(mod=='d'){
        for(int i=0; i<3; i++)
            Card[1][i]->setGeometry(992, 400-170*i, 88, 149);
        PlayerBox[1]->setGeometry(1089, 60, 101, 71);
    }
}

void MainWindow::Play(bool state){
    if(state==true)
        goto start;
    hide_menu();
    show_game();
    for(int i=0; i<player; i++)
        for(int j=0; j<Dmano; j++)
         Card[i][j]->setStyleSheet("image:url(:/CardBack.jpeg);");
    ui->Mazzo->setStyleSheet("image:url(:/CardBack.jpeg);");
    imposta(mod, carte, player, briscola, turno, PuntiP, Nplayer, CPlayers, Dmano);
    setPos();
    for(int i=0; i<4; i++){
        tavolo[i]=-1;
        Tavolo[i]->setPixmap(vacuo);
    }
    game = true;
    puntiTavola=0;
    round=0;
    start:
    QString edit="Carte Rimamenti: ";
    QTextStream(&edit)<<CarteDisp(carte);
    ui->carteRimanentiLabel->setText(edit);
    if(round==player){
        turno = Vincitore(tavolo, turno, briscola, player);
        if(turno%2==0)
            PuntiP[0]+=puntiTavola;
        else
            PuntiP[1]+=puntiTavola;
        if(CPlayers[turno]){
            edit="Giocatore ";
            QTextStream(&edit)<<turno+1<<" ha preso questa mano!" ;
        }
        else{
            edit="CPU ";
            QTextStream(&edit)<<turno-Nplayer+1<<" ha preso questa mano!" ;
        }
        ui->communicationLabel->setText(edit);
        time=4000/speed;
        delay(time);
        if(CarteDisp(carte)>0)
            for(int i=turno; i<player+turno; i++)
                for(int j=0; j<Dmano; j++)
                    if(mano[i%player][j]==-1)
                        Pesca(mano[i%player][j], carte, briscola);
        for(int i=0; i<4; i++)
            for(int j=0; j<3; j++)
                if(mano[i][j]!=-1){
                Card[i][j]->setPixmap(vacuo);
                Card[i][j]->setStyleSheet("image: url(:/CardBack.jpeg);");
                }
        if(CarteDisp(carte)<=0){
            ui->Mazzo->setStyleSheet("image: url(:/MTslot.jpg);");
        }
        for(int i=0; i<4; i++){
            tavolo[i]=-1;
            Tavolo[i]->setPixmap(vacuo);
        }
        round = 0;
        puntiTavola=0;
        ui->puntiTavolaLabel->setText("Punti in tavola: 0");
        for(int i=0; i<player; i++){
            if(CPlayers[i]){
                edit="Player ";
                QTextStream(&edit)<<i+1<<" Punti: "<< PuntiP[i%2];
            }
            else{
                edit="CPU ";
                QTextStream(&edit)<<i-Nplayer+1<<" Punti: "<< PuntiP[i%2];
            }
            PlayerBox[i]->setText(edit);
        }
        bool check=true;
        for(int i=0; i<Dmano; i++)
            if(mano[0][i]!=-1)
                check=false;
        if(check){
            game = false;
            continuePlay();
            return;
        }
        goto start;
        }
        if(CPlayers[turno]){
            if(CPlayers[(turno-1)%player]){
                for(int i=0; i<player; i++)
                    for(int j=0; j<Dmano; j++)
                        if(mano[i][j]!=-1){
                            Card[i][j]->setPixmap(vacuo);
                            Card[i][j]->setStyleSheet("image:url(:/CardBack.jpeg);");
                        }
                        else{
                            Card[i][j]->setPixmap(vacuo);
                            Card[i][j]->setStyleSheet("image:url(:/MTslot.jpg);");
                        }
                edit="Giocatore ";
                QTextStream(&edit)<<turno+1<< ", premi Mostra per mostrare le carte...";
                ui->communicationLabel->setText(edit);
                ui->Mostra->show();
            }
            else
                on_Mostra_clicked();
        }
        else
            continuePlay();
}

void MainWindow::on_Mostra_clicked()
{
    ui->Mostra->hide(); 
    if(CPlayers[turno]){
        for(int i=0; i<Dmano; i++)
            if(mano[turno][i]!=-1){
                Card[turno][i]->setStyleSheet("");
                Card[turno][i]->setPixmap(immagini[seme(mano[turno][i])][valore(mano[turno][i])-1]);
            }
            else{
                Card[turno][i]->setPixmap(vacuo);
                Card[turno][i]->setStyleSheet("image:url(:/MTslot.jpg);");
            }
        clearSelect();
        QString edit="Tocca al Giocatore ";
        QTextStream(&edit)<<turno+1<<", Scegli cosa giocare: ";
        ui->communicationLabel->setText(edit);
        move_selects();
        for(int i=0; i<Dmano; i++)
            if(mano[turno][i]!=-1)
                select[i]->show();
        ui->confirmButton->show();
        ui->suggerimentoButton->show();
        azione=0;

    }

}

void MainWindow::clearSelect()
{
    for(int i=0; i<Dmano; i++)
            select[i]->setStyleSheet("");
    QString edit="Selezione attuale: Carta ";
    QTextStream(&edit)<<azione;
    if(azione!=0)
        ui->communicationLabel->setText(edit);
    else
       ui->communicationLabel->setText("Scegli una carta...");

}

void MainWindow::move_selects()
{
    for(int i=0; i<3; i++)
        select[i]->setGeometry( Card[turno][i]->x(),Card[turno][i]->y()+145, select[i]->width(), select[i]->height() );
}

void MainWindow::on_select0_clicked()
{
    azione=1;
    clearSelect();
    ui->select0->setStyleSheet("background-color: rgb(0, 132, 0);");
}

void MainWindow::on_select1_clicked()
{
    azione=2;
    clearSelect();
    ui->select1->setStyleSheet("background-color: rgb(0, 132, 0);");
}

void MainWindow::on_select2_clicked()
{
    azione=3;
    clearSelect();
    ui->select2->setStyleSheet("background-color: rgb(0, 132, 0);");
}

void MainWindow::on_confirmButton_accepted()
{
    if(azione==0){
        QMessageBox Warn;
        Warn.setText("Attenzione, devi selezionare una carta prima di giocare!");
        Warn.exec();
    }
    else{
        for(int i=0; i<Dmano; i++)
                select[i]->hide();
        ui->confirmButton->hide();
        ui->suggerimentoButton->hide();
        continuePlay();
        return;
    }
}

void MainWindow::on_confirmButton_rejected()
{
    azione=0;
    clearSelect();
}

void MainWindow::continuePlay(){
    QString edit;
    if(game){
        if(CPlayers[turno]){
            edit= "Giocatore ";
            QTextStream(&edit)<<turno+1 << " Ha Giocato "<<valoreW(mano[turno][azione-1])<<" di "<< semeW(mano[turno][azione-1]);
            ui->communicationLabel->setText(edit);
        }
        else{
            azione = CPU(turno, tavolo, puntiTavola, briscola, player, difficile, Dmano, Teams);
            edit= "CPU ";
            QTextStream(&edit)<<turno-Nplayer+1 << " Ha Giocato "<<valoreW(mano[turno][azione-1])<<" di "<< semeW(mano[turno][azione-1]);
            ui->communicationLabel->setText(edit);
        }
        tavolo[round] = mano[turno][azione-1];
        Card[turno][azione-1]->setStyleSheet("image: url(:/MTslot.jpg)");
        Card[turno][azione-1]->setPixmap(vacuo);
        puntiTavola=0;
        for(int i = 0; i<=round; i++){
            puntiTavola+=punti(tavolo[i]);
        }
        for(int i=0; i<=round; i++)
            if(tavolo[i]!=-1)
                Tavolo[i]->setPixmap(immagini[seme(tavolo[i])][valore(tavolo[i])-1]);
            else
                Tavolo[i]->setPixmap(vacuo);
        edit="Punti in tavola: ";
        QTextStream(&edit)<<puntiTavola;
        ui->puntiTavolaLabel->setText(edit);
        mano[turno][azione-1] = -1;
        turno++;
        if(turno==player)
            turno = 0;
        round++;
        time=2000/speed;
        delay(time);
        Play(true);
        return;
    }
    else{
        if(PuntiP[0]>PuntiP[1]){
            ui->communicationLabel->setText("La Squadra 1 HA VINTO!!!");
            ui->gameEndLabel->setStyleSheet("background-image: url(:/Team1win.jpeg);");
            QTextStream(&editStorico)<<"Partita "<<Npartite+1<<": Vittoria Team 1 " << PuntiP[0]<< " - "<<PuntiP[1]<<"<br>";
        }
        else if(PuntiP[0]==PuntiP[1]){
            ui->communicationLabel->setText("PAREGGIO (60-60)");
            ui->gameEndLabel->setStyleSheet("background-image: url(:/TeamDraw.jpeg);");
            QTextStream(&editStorico)<<"Partita "<<Npartite+1<<": Vittoria Team 1 " << PuntiP[0]<< " - "<<PuntiP[1]<<"<br>";
        }
        else if(PuntiP[0]<PuntiP[1]){
            ui->communicationLabel->setText("La Squadra 2 HA VINTO!!!");
            ui->gameEndLabel->setStyleSheet("background-image: url(:/Team2win.jpeg);");
            QTextStream(&editStorico)<<"Partita "<<Npartite+1<<": Vittoria Team 2 " << PuntiP[0]<< " - "<<PuntiP[1]<<"<br>";
        }
        Npartite++;
        edit="Partite Giocate: ";
        QTextStream(&edit)<<Npartite<<"<br><br>"<<editStorico;
        ui->storicoLabel->setText(edit);
        ui->gameEndLabel->show();
        ui->gameEndButton->show();
    }
}

void MainWindow::on_menuButton_clicked()
{
    hide_game();
    aniTimer->start();
    ui->side1->setGeometry(50, -100, 355, 1000);
    ui->side2->setGeometry(795, -100, 355, 1000);
    show_menu();
}

void MainWindow::on_suggerimentoButton_clicked()
{
    clearSelect();
    QString edit;
    edit="|-|Suggerimento --> Gioca la carta: ";
    QTextStream(&edit)<<valoreW(mano[turno][CPU(turno, tavolo, puntiTavola, briscola, player, 1, Dmano, Teams)-1])<<" di "<< semeW(mano[turno][CPU(turno, tavolo, puntiTavola, briscola, player, 1, Dmano, Teams)-1]) << " |-|";
    ui->communicationLabel->setText(edit);
}

void MainWindow::on_gameEndButton_clicked()
{
    on_menuButton_clicked();
}

void MainWindow::on_checkBoxStorico_stateChanged(int arg1)
{
    st=arg1;
    if(st)
        ui->storicoLabel->show();
    else
        ui->storicoLabel->hide();
}

void MainWindow::on_buttonInfo_clicked()
{
    if(ui->regoleLabel->isVisible())
        ui->regoleLabel->hide();
    else
        ui->regoleLabel->show();
}

void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    premium=arg1;
}

void MainWindow::on_checkBoxSpeed_stateChanged(int arg1)
{
    fast=arg1;
}
