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
                p.setId( currentID++) ;
                points.push_back(make_shared<Point>(p));
            }
        }
    }

    return points;
}

void NuageDePoints::relierPoints(vector<vector<char>>& grille)
{
    vector<shared_ptr<IAffichablePoint>> points;
    if(stratSurface)
    {
        stratSurface->relierPoints(grille, getPoints(points));
    }   
}

NuageDePoints::NuageDePoints(const vector<shared_ptr<ComposanteAffichageAbs>> &points, char texture)
{
    this->points = points;
    this->texture = texture;
}

void NuageDePoints::setStrategieCreationSurface(const shared_ptr<StrategieCreationSurface>& stratSurface)
{
    this->stratSurface = stratSurface;
}

string NuageDePoints::getTextures() const
{
    return string(1,texture);
}

bool NuageDePoints::contientPoint(int idPoint) const
{
    for (const auto& p : points) {
        if(typeid(*p) == typeid(IAffichablePoint) )
        {
            auto point = dynamic_pointer_cast<IAffichablePoint>(p);
            if (point->getPointDeBase()->getId() == idPoint)
            return true;
        }
        else if(typeid(*p) == typeid(NuageDePoints) )
        {
            auto nuage = dynamic_pointer_cast<NuageDePoints>(p);
            if(nuage && nuage->contientPoint(idPoint))
                return true;
        }
    }
    return false;
}

void NuageDePoints::supprimerPoint(int idPoint) {
    points.erase(
        remove_if(points.begin(), points.end(),
            [&](const shared_ptr<ComposanteAffichageAbs>& point) {
                if(typeid(*point) == typeid(NuageDePoints))
                {
                    auto nuage = dynamic_pointer_cast<NuageDePoints>(point);
                    if(nuage)
                    {
                        nuage->supprimerPoint(idPoint);
                        // Si le nuage ne contient plus de points, on le supprime aussi
                        vector<shared_ptr<IAffichablePoint>> pts;
                        nuage->getPoints(pts);
                        if(pts.empty())
                            return true;
                    }
                    return false;
                }
                auto ipoint = dynamic_pointer_cast<IAffichablePoint>(point);
                return ipoint->getPointDeBase()->getId() == idPoint;
            }),
        points.end()
    );
}

vector<shared_ptr<IAffichablePoint>>& NuageDePoints::getPoints(vector<shared_ptr<IAffichablePoint>>& vecRec) const
{
    
    for(auto&& p: points)
    {
        if(typeid(*p) == typeid(NuageDePoints))
        {
            auto nuage = dynamic_pointer_cast<NuageDePoints>(p);
            if(nuage)
            {
                nuage->getPoints(vecRec);
            }
        }
        else
        {
            auto ipoint = dynamic_pointer_cast<IAffichablePoint>(p);
            if(ipoint)
            {
                vecRec.push_back(ipoint);
            }
        }
    }
}

void NuageDePoints::ajouterComposant(const shared_ptr<ComposanteAffichageAbs>& element)
{
    if(typeid(*element) == typeid(NuageDePoints))
    {
       auto nuage = dynamic_pointer_cast<NuageDePoints>(element);
       if(nuage) 
       {
            vector<shared_ptr<IAffichablePoint>> pts;
            pts = nuage->getPoints(pts);
            for(auto&& p: pts)
            {
               p = make_shared<DecorateurTexture>(p, this->texture);
            }  
            points.push_back(nuage);
       }  
       
    }
    else
    {
        auto ipoint = dynamic_pointer_cast<IAffichablePoint>(element);
        if(ipoint)
        {
            ipoint = make_shared<DecorateurTexture>(ipoint, this->texture);
            points.push_back(ipoint);
        }
    }
   
}




ostream &operator<<(ostream& os, const NuageDePoints& nuageDePoints)
{
    cout << "Nuage '" << nuageDePoints.texture << "' contient les points:";

    for(auto&& p: nuageDePoints.points)
    {
        if(typeid(*p) == typeid(IAffichablePoint))
        {
            auto point = dynamic_pointer_cast<IAffichablePoint>(p);
            cout << " " << point->getPointDeBase()->getId();
        }
            
        if(typeid(*p) == typeid(NuageDePoints))
        {
            auto nuage = dynamic_pointer_cast<NuageDePoints>(p);
            if(nuage)
                cout << "\n" << *nuage;
        }
    }

    cout << endl;
    return os;
}

ostream& operator<<(ostream &os, const Point &p)
{
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}



string Point::getTextures() const
{
    return "";
}

DecorateurPoint::DecorateurPoint(shared_ptr<IAffichablePoint> composant)
    : composant(composant) {}


DecorateurTexture::DecorateurTexture(shared_ptr<IAffichablePoint> composant, char texture) : DecorateurPoint(composant)
{
    this->texture = texture;
}

string DecorateurTexture::getTextures() const
{
    return composant->getTextures() + texture;
}

