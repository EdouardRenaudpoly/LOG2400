#include "StrategieCreationSurface.h"
#include "affichage.h"
#include <iostream>
#include <cmath>
#include <memory>

void StrategieSurfaceOrdreID::relierPoints(std::vector<std::vector<char>>& grille, std::vector<std::shared_ptr<Point>>& points)
{
    int size = points.size();
    for(int i = 0; i < size; i++)
    {
        tracerLigne(grille, points[i]->x, points[i]->y, points[(i+1)%size]->x, points[(i+1)%size]->y);
    }
}

void StrategieSurfaceDistanceMin::relierPoints(std::vector<std::vector<char>>& grille, std::vector<std::shared_ptr<Point>>& points) 
{
    
    std::vector<bool> visite(points.size(), false);
    int indexCourant = 0;
    visite[indexCourant] = true;
    int nbVisites = 1;

    while (nbVisites < points.size()) 
    {
        int suivant = -1;
        double distMin = 1e9;

        for (int i = 0; i < points.size(); i++) 
        {
            if (!visite[i]) 
            {
                double dx = points[i]->x - points[indexCourant]->x;
                double dy = points[i]->y - points[indexCourant]->y;
                double dist = sqrt(dx*dx + dy*dy);
                
                if (dist < distMin) 
                {
                    distMin = dist;
                    suivant = i;
                }
            }
        }

        tracerLigne(grille, points[indexCourant]->x, points[indexCourant]->y, points[suivant]->x, points[suivant]->y);
        visite[suivant] = true;
        indexCourant = suivant;
        ++nbVisites;
    }

    tracerLigne(grille, points[indexCourant]->x, points[indexCourant]->y, points[0]->x, points[0]->y);
}
