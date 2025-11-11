#include "MiniDesignClient.h"
#include <iostream>
#include <cctype>
#include <sstream>
#include <algorithm>
using namespace std;

void MiniDesignClient::afficherListeEtNuages()
{
    for(auto&& point : points)
    {
        std::string textures = point->getTextures();
        std::cout << point->getPointDeBase()->id << ": " << *(point->getPointDeBase()) << " textures: '" << textures << "'" << std::endl;
    }

    for(int i = 0; i < nuages.size(); i++)
    {
        std::cout << *nuages[i];
    }
}

void MiniDesignClient::creerNuage(char texture)
{
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
            [&](const std::shared_ptr<IAffichablePoint>& p){ return p->getPointDeBase()->id == idRecherche; });

        if (itPoint != points.end())
        {
            *itPoint = std::make_shared<DecorateurTexture>(*itPoint, texture);
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
        nuages.push_back(std::make_shared<NuageDePoints>(pointsNuage, texture));
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
            [&](const std::shared_ptr<IAffichablePoint>& p){ return p->getPointDeBase()->id == idPoint; });
        
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
        [&](const std::shared_ptr<IAffichablePoint>& p){ return p->getPointDeBase()->id == idPoint; });
    if (it == points.end()) return;

    std::shared_ptr<IAffichablePoint> pointASupprimer = *it;

    for (auto& nuage : nuages) 
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

void MiniDesignClient::choisirAffichageGrille(const std::string &cmd)
{
    if (cmd == "o1")
    {
        affichageGrille = std::make_unique<AffichageGrilleTexture>(nuages, points);
    }
    else
    {
        affichageGrille = std::make_unique<AffichageGrilleID>(nuages, points);
    }
}


void MiniDesignClient::setStrategieCreationSurface(std::shared_ptr<StrategieCreationSurface> stratCreation)
{
    for(auto&& nuage: nuages)
    {
        nuage->setStrategieCreationSurface(stratCreation);
    }
}
