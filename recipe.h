#ifndef RECIPE_H
#define RECIPE_H
#include <QString>
#include <QVector>
#include <QVariant>

class Recipe
{
public:
    Recipe();
    Recipe(const QString &naziv, const QVector<QString> &recipes, const QVector<QString> &boughtRecipes);
    void fromQVariant(const QVariant &var);
    QString toString() const;
    const QVector<QString> &recipes() const;
    const QVector<QString> &boughtRecipes() const;
    void dodajKupljenSastojak(const QString &sastojak);
private:
    QString m_naziv;
    QVector<QString> m_recipes;
    QVector<QString> m_boughtRecipes;

};

#endif // RECIPE_H
