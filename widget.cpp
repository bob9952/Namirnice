#include "widget.h"
#include "ui_widget.h"

#include <QFileDialog>
#include <QJsonDocument>
#include <QDebug>
#include <QStringList>


#include "recipe.h"
#include "buyerthread.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->pbUcitajSastojke, &QPushButton::clicked, this, &Widget::UcitajSastojke);
    connect(ui->pbZapocniKupovinu, &QPushButton::clicked, this, &Widget::ZapocniKupovinu);
}

Widget::~Widget()
{
    qDeleteAll(m_recipes);
    delete ui;
}


void Widget::prikaziRecepte()
{
    QStringList lista;
    foreach(const auto &r , m_recipes){
        lista << r->toString();
    }

    ui->teIspis->setText(lista.join(""));
}

void Widget::UcitajSastojke()
{
    const auto fileName = QFileDialog::getOpenFileName(nullptr, "Open JSON", "", "JSON Files (*.json)");

    QFile input(fileName);
    if (!input.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    qDeleteAll(m_recipes);
    m_recipes.clear();

    const auto data = input.readAll();
    const auto jsonDoc = QJsonDocument::fromJson(data);
    const auto v_data = jsonDoc.toVariant();
    input.close();

    QVariantList qvList = v_data.toList();
    for(const auto &v_el : qvList){
        Recipe *r = new Recipe();
        r->fromQVariant(v_el);
        m_recipes.append(r);
    }

    prikaziRecepte();
}

void Widget::ZapocniKupovinu()
{
    bool ok;
    const auto brojKupaca = ui->leBrojKupaca->text().toInt(&ok);
    if(brojKupaca <= 0 || !ok){
        qDebug() << "Unestite pozitivan broj kupaca ";
        return;
    }

    // naci sve moguce sastojke?
    QStringList sviSastojci;
    foreach (const auto& rec, m_recipes) {
        foreach (const auto& sastojak, rec->recipes()) {
            sviSastojci  << sastojak ;
        }
    }

    sviSastojci.removeDuplicates();


    for(int i =0; i < brojKupaca; i++){
        // kreirati niti
        // connect thread signala i slota iz Widget
        // connect za deletelater
        // pokrenuti niti
        BuyerThread *t = new BuyerThread(sviSastojci, &m_mutex);
        connect(t, &BuyerThread::sastojakOdabran, this, &Widget::onSastojakOdabran);
        connect(t, &BuyerThread::finished, t, &BuyerThread::deleteLater);
        t->start();

    }
}

void Widget::onSastojakOdabran(const QString &sastojak)
{
    foreach (const auto& rec, m_recipes) {
        rec->dodajKupljenSastojak(sastojak);
    }

    prikaziRecepte();
}
