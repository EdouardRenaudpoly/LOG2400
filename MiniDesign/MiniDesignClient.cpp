#include "MiniDesignClient.h"
#include <iostream>
#include <cctype>

void MiniDesignClient::afficherListeEtNuages()
{
    for(auto&& point : points)
    {
        char texture = '\0';
        for(auto&& nuage : nuages)
        {
            if(nuage.contientPoint(point.id))
            {
                texture = nuage.getTexture();
                break;
            }
        }

        std::cout << point.id << ": " << point << " textures: '" << texture << "'" << std::endl;
    }

    for(int i = 0; i < nuages.size(); i++)
    {
        std::cout << nuages[i];
    }
}

void MiniDesignClient::creerNuage()
{
    std::vector<Point> pointsNuage;
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
                pointsNuage.push_back(*itPoint);
            }
        } 
        else 
        {
            std::cout << "erreur, mauvais format" << std::endl;
        }
    }

    
}
