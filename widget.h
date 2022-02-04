#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVector>
#include <QMutex>

class Recipe;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void UcitajSastojke();
    void ZapocniKupovinu();
    void onSastojakOdabran(const QString &sastojak);

private:
    QVector<Recipe*> m_recipes;
    Ui::Widget *ui;
    QMutex m_mutex;
    void prikaziRecepte();
};
#endif // WIDGET_H
