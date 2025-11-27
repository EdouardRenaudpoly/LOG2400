#include "executeur.h"
using namespace std;

void Executeur::executerCommande(const shared_ptr<Commande>& cmd) {
    cmd->executer();
}
void Executeur::annulerDerniereCommande() {
    if (!undoStack.empty()) {
        shared_ptr<Commande> cmd = undoStack.top();
        cmd->annuler();
        undoStack.pop();
        redoStack.push(cmd);
    }
}

void Executeur::executerEtSauvergarder(const shared_ptr<Commande>& cmd)
{
    this->executerCommande(cmd);
    undoStack.push(cmd);
    redoStack = stack<shared_ptr<Commande>>();
}

void Executeur::reexecuterCommande()
{
    if(!redoStack.empty()){
        shared_ptr<Commande> cmd = redoStack.top();
        cmd->executer();
        redoStack.pop();
        undoStack.push(cmd);
    }
}