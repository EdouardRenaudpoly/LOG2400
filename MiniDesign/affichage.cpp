#include "affichage.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

void tracerLigne(vector<vector<char>> &grille, int x0, int y0, int x1, int y1)
{
    // Distance verticale
    int lignes = abs(y1 - y0);
    // Si la ligne est horizontale 
    if (lignes == 0) {
        // On prend distance horizontale 
        lignes = abs(x1 - x0);
        for (int i = 0; i <= lignes; ++i) {
            // On trace chaque point de la ligne, de gauche à droite ou de droite à gauche selon la direction.
            int x = (x0 < x1) ? x0 + i : x0 - i;
            if (y1 >= 0 && y1 < HAUTEUR && x >= 0 && x < LARGEUR)
                grille[y1][x] = '/';
        }
    } else {
        // Si la ligne est verticale ou diagonale 
        for (int i = 0; i <= lignes; ++i) {
            double t = (double)i / lignes;
            // On fait une interpolation lineaire
            int x = round(x0 + t * (x1 - x0));
            int y = round(y0 + t * (y1 - y0));
            if (x >= 0 && x < LARGEUR && y >= 0 && y < HAUTEUR)
                grille[y][x] = '/';
        }
    }
}

vector<shared_ptr<IAffichablePoint>> PointFactory::creerPoints(const string& ligne) {
    vector<shared_ptr<IAffichablePoint>> points;
    // On crée un flux de lecture (istringstream) à partir de la chaîne ligne.
    istringstream iss(ligne);
    string token;
    int currentID = 0;
    // On lit chaque point de la ligne (séparé par des espaces).
    while (iss >> token) {
        // On vérifie que le point est entre parenthèses
        if (token.size() >= 3 && token.front() == '(' && token.back() == ')') {
            // On enlève les parenthèses au début et à la fin.
            token = token.substr(1, token.size() - 2);
            // On remplace la virgule par un espace.
            replace(token.begin(), token.end(), ',', ' ');
            // On crée un flux de lecture pour chaque point
            istringstream pair(token);
            int x, y;
            // On ajoute un point {x, y} au vecteur de points.
            if (pair >> x >> y) {
                Point p {x,y};
                p.id = currentID++;
                points.push_back(make_shared<Point>(p));
            }
        }
    }

    return points;
}

void NuageDePoints::relierPoints(vector<vector<char>>& grille)
{
    if(stratSurface)
    {
        stratSurface->relierPoints(grille, points);
    }   
}

NuageDePoints::NuageDePoints(const std::vector<std::shared_ptr<IAffichablePoint>> &points, char texture)
{
    this->points = points;
    this->texture = texture;
}

void NuageDePoints::setStrategieCreationSurface(const std::shared_ptr<StrategieCreationSurface>& stratSurface)
{
    this->stratSurface = stratSurface;
}

char NuageDePoints::getTexture() const
{
    return texture;
}

bool NuageDePoints::contientPoint(int idPoint) const
{
    for (const auto& p : points) {
        if (p->getPointDeBase()->id == idPoint)
            return true;
    }
    return false;
}

void NuageDePoints::supprimerPoint(int idPoint) {
    points.erase(
        std::remove_if(points.begin(), points.end(),
            [&](const std::shared_ptr<IAffichablePoint>& point) {
                return point->getPointDeBase()->id == idPoint;
            }),
        points.end()
    );
}


std::ostream &operator<<(std::ostream& os, const NuageDePoints& nuageDePoints)
{
    std::cout << "Nuage '" << nuageDePoints.texture << "' contient les points:";

    for(auto&& point: nuageDePoints.points)
    {
        cout << " " << point->getPointDeBase()->id;
    }

    std::cout << endl;
    return os;
}

std::ostream& operator<<(std::ostream &os, const Point &p)
{
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}



std::string Point::getTextures() const
{
    return "";
}

DecorateurPoint::DecorateurPoint(std::shared_ptr<IAffichablePoint> composant)
    : composant(composant) {}


DecorateurTexture::DecorateurTexture(std::shared_ptr<IAffichablePoint> composant, char texture) : DecorateurPoint(composant)
{
    this->texture = texture;
}

std::string DecorateurTexture::getTextures() const
{
    return composant->getTextures() + std::string(1, texture);
}

