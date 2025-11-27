#pragma once
#include <memory>
#include <vector>
#include <iostream>
#include "AffichageGrille.h"
#include "affichage.h"
#include "MiniDesignClient.h"
#include <iostream>
#include <cctype>
#include <sstream>
#include <algorithm>


class Commande {
public:
    Commande(std::shared_ptr<MiniDesignClient>& recepteur) : recepteur(recepteur) {};
    virtual ~Commande() = default;
    virtual void executer() = 0;
    virtual void annuler() = 0;
protected:
    std::shared_ptr<MiniDesignClient> recepteur;
};

class CommandeCreerNuage : public Commande {
public:
    using Commande::Commande;
    void executer() override;
    void annuler() override;
private:
    
};

class CommandeDeplacerPoint : public Commande {
public:
    using Commande::Commande;
    void executer() override;
    void annuler() override;
};

class CommandeSupprimerPoint : public Commande {    
public:
    using Commande::Commande;
    void executer() override;
    void annuler() override;
};  


class CommandeAfficherListeEtNuages : public Commande {
public:
    using Commande::Commande;
    void executer() override;
    void annuler() override;
};

class CommandeAffichageTexture : public Commande {
public:
    using Commande::Commande;
    void executer() override;
    void annuler() override;
};

class CommandeAffichageID : public Commande {
public: 
    using Commande::Commande;
    void executer() override;
    void annuler() override;
};

class CommandeCreerSurfaceOrdreID : public Commande {
public:
    using Commande::Commande;
    void executer() override;
    void annuler() override;
};
class CommandeCreerSurfaceDistanceMin : public Commande {
public:
    using Commande::Commande;
    void executer() override;
    void annuler() override;
};




