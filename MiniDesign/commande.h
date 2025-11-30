#pragma once
#include <memory>
#include <vector>
#include <iostream>

class MiniDesignClient;
class IAffichablePoint;
class NuageDePoints;

class Commande {
public:
    Commande(std::shared_ptr<MiniDesignClient>& recepteur) : recepteur(recepteur) {};
    virtual ~Commande() = default;
    virtual void executer() = 0;
    virtual void annuler() = 0;
protected:
    std::shared_ptr<MiniDesignClient> recepteur;
};

class CommandeAnnulable : public Commande{
public:
    using Commande::Commande;
    virtual void annuler() override = 0;
};

class CommandeNonAnnulable : public Commande {
public:
    using Commande::Commande;
    void annuler() override {
        std::cout << "Cette commande ne peut pas être annulée." << std::endl;
    }
};
class CommandeCreerNuage : public CommandeNonAnnulable {
public:
    using CommandeNonAnnulable::CommandeNonAnnulable;
    void executer() override;
};

class CommandeDeplacerPoint : public CommandeAnnulable, public std::enable_shared_from_this<CommandeDeplacerPoint> {
public:
    using CommandeAnnulable::CommandeAnnulable;
    void executer() override;
    void annuler() override;
    void setSavedData(std::shared_ptr<IAffichablePoint> point, int idPoint, int oldX, int oldY)
    {
        pointDeplace = point;
        ancienId = idPoint;
        ancienneX = oldX;
        ancienneY = oldY;
    }
    const int getIdPoint() const { return ancienId; }
    const int getancienneX() const { return ancienneX; } 
    const int getancienneY() const { return ancienneY; }
private:
    std::shared_ptr<IAffichablePoint> pointDeplace;
    int ancienId = -1;
    int ancienneX = -1;
    int ancienneY= -1;
};

class CommandeSupprimerPoint : public CommandeAnnulable , public std::enable_shared_from_this<CommandeSupprimerPoint> {    
public:
    using CommandeAnnulable::CommandeAnnulable;
    void executer() override;
    void annuler() override;
    void setSavedData(std::shared_ptr<IAffichablePoint> point, const std::vector<std::shared_ptr<NuageDePoints>>& nuages);
    std::shared_ptr<IAffichablePoint> getPointSupprime() const { return pointSupprime; }
    std::vector<std::shared_ptr<NuageDePoints>> getNuagesContenantPoint() const { return nuagesContenantPoint; }
private:
    std::shared_ptr<IAffichablePoint> pointSupprime;
    std::vector<std::shared_ptr<NuageDePoints>> nuagesContenantPoint;
};  


class CommandeAfficherListeEtNuages : public CommandeNonAnnulable {
public:
    using CommandeNonAnnulable::CommandeNonAnnulable;
    void executer() override;
};

class CommandeAffichageTexture : public CommandeNonAnnulable {
public:
    using CommandeNonAnnulable::CommandeNonAnnulable;
    void executer() override;
};

class CommandeAffichageID : public CommandeNonAnnulable {
public:
    using CommandeNonAnnulable::CommandeNonAnnulable;
    void executer() override;
};

class CommandeCreerSurfaceOrdreID : public CommandeNonAnnulable {
public:
    using CommandeNonAnnulable::CommandeNonAnnulable;
    void executer() override;
};

class CommandeCreerSurfaceDistanceMin : public CommandeNonAnnulable {
public:
    using CommandeNonAnnulable::CommandeNonAnnulable;
    void executer() override;
};