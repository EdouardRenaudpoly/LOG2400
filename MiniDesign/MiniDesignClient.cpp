#include "MiniDesignClient.h"
#include <iostream>
#include <cctype>
#include <sstream>

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
}
