#include "recipe.h"

Recipe::Recipe()
{

}

Recipe::Recipe(const QString &naziv, const QVector<QString> &recipes, const QVector<QString> &boughtRecipes) : m_naziv(naziv),
    m_recipes(recipes),
    m_boughtRecipes(boughtRecipes)
{}

void Recipe::fromQVariant(const QVariant &var)
{
    const auto map = var.toMap();
    m_naziv = map.find("title")->toString();

    // mora da se ocisti
    m_recipes.clear();

    const auto varinatIngred = map.find("ingredients")->toList();
    for(const auto &v : varinatIngred){
        m_recipes.append(v.toString());
    }
    m_boughtRecipes = QVector<QString>();
}

QString Recipe::toString() const
{
    const auto line1 = m_naziv;
    std::string line2;

    for(const auto &sastojak : m_recipes){
        if(m_boughtRecipes.contains(sastojak)){
            line2 += 'O';
        }else{
            line2 += 'X';
        }
    }
    const auto line = line1 + "\n" + QString::fromStdString(line2) + "\n";
    return line;
}

const QVector<QString> &Recipe::recipes() const
{
    return m_recipes;
}

const QVector<QString> &Recipe::boughtRecipes() const
{
    return m_boughtRecipes;
}

void Recipe::dodajKupljenSastojak(const QString &sastojak)
{
    m_boughtRecipes.append(sastojak);
}
