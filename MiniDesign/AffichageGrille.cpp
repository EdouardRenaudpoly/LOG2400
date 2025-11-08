#include "AffichageGrille.h"
#include <iostream>
#include <vector>
using namespace std;

void AffichageGrilleTexture::afficherPoints(std::vector<std::vector<char>>& grille)
{
    for(auto&& point : points)
    {
        int nTextures = 0;
        
        for(auto&& nuage : nuages)
        {
            if(nuage->contientPoint(point->id))
            {
                grille[point->y][point->x+nTextures] = nuage->getTexture();
                nTextures++;
            }
        }

        if(nTextures == 0)
        {
            grille[point->y][point->x+nTextures] = '.';
        }
    }
}

void AffichageGrilleID::afficherPoints(std::vector<std::vector<char>>& grille)
{
    for (auto&& point : points)
        grille[point->y][point->x] = '0' + (point->id % 10);
}

AffichageGrille::AffichageGrille(const std::vector<std::shared_ptr<NuageDePoints>>& nuages, const std::vector<std::shared_ptr<Point>> &points)
{
    this->nuages = nuages;
    this->points = points;
}

void AffichageGrille::afficherGrille()
{
    // On crée une grille.
    vector<vector<char>> grille(HAUTEUR, vector<char>(LARGEUR, ' '));

    // On trace une ligne entre le point 0 et 1.
    // TODO : Remplacer par un tracé selon la commande de l'utilisateur (c1 ou c2)
    //tracerLigne(grille, points[0].x, points[0].y, points[1].x, points[1].y);


    for(auto&& nuage : nuages)
    {
        nuage->relierPoints(grille);
    }

    afficherPoints(grille);

    // On imprime la grille.
    for (int y = HAUTEUR - 1; y >= 0; --y) {
        for (int x = 0; x < LARGEUR; ++x)
            cout << grille[y][x];
        cout << '\n';
    }
}