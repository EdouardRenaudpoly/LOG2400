#include <memory>
#include <vector>
#include <iostream>
#include "AffichageGrille.h"
#include "affichage.h"


class Commande {
public:
    virtual ~Commande() = default;
    virtual void executer(std::string) = 0;
    virtual void annuler() = 0;
};

class CommandeCreerNuage : public Commande {
public:
    void executer(std::string) override;
    void annuler() override;
};

class CommandeDeplacerPoint : public Commande {
public:
    void executer(std::string) override;
    void annuler() override;
};

class CommandeSupprimerPoint : public Commande {    
public:
    void executer(std::string) override;
    void annuler() override;
};  

