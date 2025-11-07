#include "MiniDesignClient.h"
#include <iostream>
#include <cctype>
#include <sstream>
using namespace std;

void MiniDesignClient::afficherListeEtNuages()
{
    for(auto&& point : points)
    {
        char texture = '\0';
        for(auto&& nuage : nuages)
        {
            if(nuage.contientPoint(point->id))
            {
                texture = nuage.getTexture();
                break;
            }
        }

        std::cout << point->id << ": " << point << " textures: '" << texture << "'" << std::endl;
    }

    for(int i = 0; i < nuages.size(); i++)
    {
        std::cout << nuages[i];
    }
}

void MiniDesignClient::afficherGrille()
{
    // On crée une grille.
    vector<vector<char>> grille(HAUTEUR, vector<char>(LARGEUR, ' '));

    // On trace une ligne entre le point 0 et 1.
    // TODO : Remplacer par un tracé selon la commande de l'utilisateur (c1 ou c2)
    //tracerLigne(grille, points[0].x, points[0].y, points[1].x, points[1].y);

    stratSurface->relierPoints(grille, points);

    // On imprime la grille.
    for (int y = HAUTEUR - 1; y >= 0; --y) {
        for (int x = 0; x < LARGEUR; ++x)
            cout << grille[y][x];
        cout << '\n';
    }
}

void MiniDesignClient::afficherGrilleTexture()
{
}

void MiniDesignClient::afficherGrilleID()
{
}

void MiniDesignClient::creerNuage()
{
    std::vector<std::shared_ptr<Point>> pointsNuage;
    std::string input;

    std::cout << "IDs des points à fusionner dans un nuage (ex: 0 2 4): ";
    std::cin >> input;

    for(int i = 0; i < input.length(); i+=2)
    {
        if (std::isdigit(input[i])) 
        {
            int idRecherche = input[i];
            auto itPoint = std::find(points.begin(), points.end(), [&](const Point& point){ return point.id == idRecherche;});
            
            if(itPoint != points.end())
            {
                pointsNuage.push_back(std::make_shared<Point>(*itPoint));
            }
        } 
        else 
        {
            std::cout << "erreur, mauvais format" << std::endl;
        }
    }

    nuages.push_back(NuageDePoints(pointsNuage));
}

void MiniDesignClient::deplacerPoint()
{
    int idPoint;

    std::cout << "ID du point à déplacer: ";
    std::cin >> idPoint;
    std::cout << "Nouvelle position (x y): ";

    std::string input;
    std::istringstream iss(input);
    int newX, newY;

    if (iss >> newX >> newY) 
    {
        auto itPoint = std::find(points.begin(), points.end(), [&](const std::shared_ptr<Point>& point){return point->id == idPoint;});
        
        if(itPoint != points.end())
        {
            (*itPoint)->x = newX;
            (*itPoint)->y = newY;
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
        [&](const std::shared_ptr<Point>& p){ return p->id == idPoint; });
    if (it == points.end()) return;

    std::shared_ptr<Point> pointASupprimer = *it;

    for (auto& nuage : nuages) 
    {
        nuage.supprimerPoint(idPoint);
    }

    points.erase(it);
}

void MiniDesignClient::setStrategieCreationSurface(std::shared_ptr<StrategieCreationSurface> stratCreation)
{
    for(auto&& nuage: nuages)
    {
        nuage.setStrategieCreationSurface(stratCreation);
    }
}
