#include "MiniDesignClient.h"
#include <iostream>
#include <cctype>
#include <sstream>
#include <algorithm>
using namespace std;

void MiniDesignClient::afficherListeEtNuages()
{
    for (auto &&element : elements)
    {
        if (typeid(*element) == typeid(NuageDePoints))
        {
            auto nuage = dynamic_pointer_cast<NuageDePoints>(element);
            if (nuage)
            {
                std::cout << "Nuage ID " << nuage->getId() << " avec texture '" << nuage->getTextures() << "' contenant les points :" << std::endl;
    
            }
        }
        else
        {
            auto point = dynamic_pointer_cast<IAffichablePoint>(element);
            if (point)
            {
                std::string textures = point->getTextures();
                std::cout << "Point ID " << point->getPointDeBase()->getId() << ": " << *(point->getPointDeBase()) << " textures: '" << textures << "'" << std::endl;
            }
        }
    }

   
}

void MiniDesignClient::creerNuage()
{
    if(nuages.size() == texturesNuages.size())
    {
        cout << "Nombre maximal de nuages atteint";
        return;
    }
    
    std::vector<std::shared_ptr<IAffichablePoint>> pointsNuage;

    std::cout << "IDs des points à fusionner dans un nuage (ex: 0 2 4): ";
    std::string line;
    std::getline(std::cin >> std::ws, line);

    std::istringstream iss(line);
    int idRecherche;
    bool erreur = false;

    while (iss >> idRecherche)
    {
        auto itPoint = std::find_if(points.begin(), points.end(),
                                    [&](const std::shared_ptr<IAffichablePoint> &p)
                                    { return p->getPointDeBase()->getId() == idRecherche; });

        if (itPoint != points.end())
        {
            *itPoint = std::make_shared<DecorateurTexture>(*itPoint,texturesNuages[nuages.size()] );
            pointsNuage.push_back(*itPoint);
        }
        else
        {
            std::cout << "Aucun point avec l'ID " << idRecherche << std::endl;
            erreur = true;
        }
    }

    if (!erreur && !pointsNuage.empty())
    {

        std::vector<std::shared_ptr<ComposanteAffichageAbs>> converted;
        for (auto &p : pointsNuage)
        {
            converted.push_back(p); // Works if IAffichablePoint inherits ComposanteAffichageAbs
        }

        nuages.push_back(std::make_shared<NuageDePoints>(converted, texturesNuages[nuages.size()]));
        std::cout << "Nuage créé avec " << pointsNuage.size() << " points." << std::endl;
    }
    else if (pointsNuage.empty())
    {
        std::cout << "Aucun point valide fourni." << std::endl;
    }
}

void MiniDesignClient::deplacerPoint()
{
    int idPoint;

    std::cout << "ID du point à déplacer: ";
    std::cin >> idPoint;

    std::cout << "Nouvelle position (x y): ";
    int newX, newY;
    if (std::cin >> newX >> newY)
    {
        auto itPoint = std::find_if(points.begin(), points.end(),
                                    [&](const std::shared_ptr<IAffichablePoint> &p)
                                    { return p->getPointDeBase()->getId() == idPoint; });

        if (itPoint != points.end())
        {
            (*itPoint)->getPointDeBase()->x = newX;
            (*itPoint)->getPointDeBase()->y = newY;
        }
        else
        {
            std::cout << "Ce point n'existe pas" << std::endl;
        }
    }
    else
    {
        std::cout << "Entrée invalide" << std::endl;
    }
}

void MiniDesignClient::supprimerPoint()
{
    int idPoint;
    std::cout << "ID du point à supprimer: ";
    std::cin >> idPoint;

    auto it = std::find_if(points.begin(), points.end(),
                           [&](const std::shared_ptr<IAffichablePoint> &p)
                           { return p->getPointDeBase()->getId() == idPoint; });
    if (it == points.end())
        return;

    std::shared_ptr<IAffichablePoint> pointASupprimer = *it;

    for (auto &nuage : nuages)
    {
        nuage->supprimerPoint(idPoint);
    }

    points.erase(it);
}

void MiniDesignClient::afficherGrille()
{
    if (affichageGrille)
    {
        affichageGrille->afficherGrille();
    }
}

void MiniDesignClient::choisirAffichageGrilleTexture()
{
    
    affichageGrille = std::make_unique<AffichageGrilleTexture>(nuages, points);
    this->afficherGrille();
}

void MiniDesignClient::choisirAffichageGrilleID()
{
    affichageGrille = std::make_unique<AffichageGrilleID>(nuages, points);
    this->afficherGrille();
}

void MiniDesignClient::setStrategieCreationSurface(std::shared_ptr<StrategieCreationSurface> stratCreation)
{
    for (auto &&nuage : nuages)
    {
        nuage->setStrategieCreationSurface(stratCreation);
    }
}

std::vector<std::shared_ptr<IAffichablePoint>> MiniDesignClient::getPoints() const
{
    return points;
}

std::vector<std::shared_ptr<NuageDePoints>> MiniDesignClient::getNuages() const
{
    return nuages;
}
