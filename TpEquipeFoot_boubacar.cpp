#include <iostream>
using namespace std;

const unsigned short TAILLE_NOM = 31;
const unsigned short TAILLE_PRENOM = 31;
const unsigned int format_compte = 1;



enum Position {
	GARDIEN_DE_BUT = 1,
	ATTAQUANT,
	DEFENSEUR,
	MILIEU_DE_TERRAIN
};

struct joueur {
	unsigned short noDeJoueur;
	char nom[TAILLE_NOM];
	char prenom[TAILLE_PRENOM];
	unsigned short nbButs;
	Position position;
};
// Initialisation de mon tableau
joueur joueurs[15] = { 0 };
unsigned short nbJoueurs = 0;

void afficherMenu();
void ajouterJoueur(joueur joueurs[], unsigned short& nbJoueurs);
int rechercherJoueur(joueur joueurs[], unsigned short nbJoueurs);
void modifierJoueur(joueur& joueur);
void retirerJoueur(joueur joueurs[], unsigned short& nbJoueurs, int indiceJoueurARetirer);
void afficherInfoJoueur(const joueur& JOUEUR);
void ajouterButJoueur(joueur& joueur);
void retirerButJoueur(joueur& joueur);
void afficherJoueursParPosition(joueur joueurs[], unsigned short nbJoueurs);
void quitter(int param);
void afficherTotalDeButDeLEquipe(joueur joueurs[], unsigned short nbJoueurs);
// Fonctions ajoutees
joueur creerNouvelJoueur(unsigned short nbComptesActuels);
void afficherTousLesJoueurs(joueur joueurs[], unsigned short nbJoueurs);
void validerChaine(char chaine[], const unsigned short TAILLE, const char titre[]);
int saisieNumerique();
int saisieNumeriqueChoixMenu();


int main() {
	const locale LOCALE = locale::global(locale(""));

	afficherMenu();
	quitter(0);

	system("pause");
	return 0;
}

void afficherMenu() {

	int choix;

	cout << "MENU  :                " << endl;
	cout << "1 – Ajouter un joueur  " << endl;
	cout << "2 – Modifier un joueur " << endl;
	cout << "3 – Retirer un joueur" << endl;
	cout << "4 – Afficher les informations d’un joueur selon son numéro de joueur" << endl;
	cout << "5 – Ajouter un but à un joueur selon son numéro de joueur" << endl;
	cout << "6 – Retirer un but à un joueur selon son numéro de joueur" << endl;
	cout << "7 – Afficher tous les joueurs (avec option de filtre)" << endl;
	cout << "8 – Afficher le nombre total de buts comptés pour l’équipe" << endl;
	cout << "9 – Quitter l'application " << endl;
	cout << endl;
	cout << " CHOIX : ";
	choix = saisieNumeriqueChoixMenu();
	switch (choix)
	{
	case 1:
		int reponse;
		do {
			ajouterJoueur(joueurs, nbJoueurs);
			unsigned short* pointeur = &nbJoueurs;
			cout << "Ajouter encore encore un joueur" << endl;
			cout << "1 = oui " << endl;
			cout << "0 = non " << endl;
			reponse = saisieNumerique();
			*pointeur += 1;
		} while (reponse == 1 && nbJoueurs < 14);

		if (nbJoueurs == 14) {
			cout << "Nombre maximum de joueur atteints" << endl;
		}

		if (reponse == 0) {
			afficherMenu();
		}

	case 2:
		if (nbJoueurs == 0) {
			cout << endl;
			cout << "Votre liste de joueur est vide" << endl;
			cout << endl;
		}
		else if (nbJoueurs > 0) {
			int indiceJoueurAModifier;
			indiceJoueurAModifier = rechercherJoueur(joueurs, nbJoueurs);
			modifierJoueur(joueurs[indiceJoueurAModifier]);
		};
		break;
	case 3:
		int indiceJoueurARetirer;
		indiceJoueurARetirer = rechercherJoueur(joueurs, nbJoueurs);
		retirerJoueur(joueurs, nbJoueurs, indiceJoueurARetirer);
		break;
	case 4:
		int indiceJoueurAAfficher;
		indiceJoueurAAfficher = rechercherJoueur(joueurs, nbJoueurs);
		afficherInfoJoueur(joueurs[indiceJoueurAAfficher]);
		break;
	case 5:
		int indice;
		indice = rechercherJoueur(joueurs, nbJoueurs);
		ajouterButJoueur(joueurs[indice]);  
		break;
	case 6:
		int indiceJoueurButARetirer;
		indiceJoueurButARetirer = rechercherJoueur(joueurs, nbJoueurs);
		retirerButJoueur(joueurs[indiceJoueurButARetirer]);
		break;
	case 7:
		if (nbJoueurs == 0) {
			cout << endl;
			cout << "La liste est vide!! Ajoutez d'abord des joueurs" << endl;
			cout << endl;
		}
		else {
			unsigned short choixAffichage;
			cout << "Comment voulez vous afficher les joueurs :" << endl;
			cout << " 1 = affiche tous les joueurs " << endl;
			cout << " 2 = afficher par position" << endl;
			choixAffichage = saisieNumerique();
			if (choixAffichage == 1) {
				afficherTousLesJoueurs(joueurs, nbJoueurs);
			}
			else if (choixAffichage == 2) {
				afficherJoueursParPosition(joueurs, nbJoueurs);
			}
			else {
				cout << "Vous devez choisir entre 1 et 2 pour voir la joueurs" << endl;
				afficherMenu();
			}
		};
		break;
	case 8:
		afficherTotalDeButDeLEquipe(joueurs, nbJoueurs);
		break;
	case 9:
		quitter(0);
		break;
	}
	quitter(0);
}

void ajouterJoueur(joueur joueurs[], unsigned short& nbJoueurs) {
	unsigned short* indice_joueur;
	indice_joueur = &nbJoueurs;
	joueur newjoueur;

	newjoueur = creerNouvelJoueur(*indice_joueur);

	joueurs[*indice_joueur] = newjoueur;

}

joueur creerNouvelJoueur(unsigned short nbJoueurs) {

	joueur newJoueur;
	unsigned short rep;
	unsigned short positionsaisie;

	newJoueur.noDeJoueur = (nbJoueurs + format_compte);
	newJoueur.nbButs = 0;

	cout << endl;
	cout << "-----------SAISIE NOUVEAU JOUEUR------------" << endl;
	cout << endl;

	cout << "Veuillez saisir le nom du nouveau joueur : ";
	validerChaine(newJoueur.nom, TAILLE_NOM, "nom");

	cout << "Veuillez saisir le prenom du nouveau joueur : ";
	validerChaine(newJoueur.prenom, TAILLE_PRENOM, "nom");

	cout << "Veuillez donner la position du joueur : " << endl;
	cout << " 1 = GARDIEN_DE_BUT" << endl;
	cout << " 2 = ATTAQUANT" << endl;
	cout << " 3 = DEFENSEUR" << endl;
	cout << " 4 = MILIEU_DE_TERRAIN" << endl;
	positionsaisie = saisieNumerique();
	newJoueur.position = (Position)positionsaisie;
	cout << endl;
	cout << "-----------NOUVEAU JOUEUR AJOUTÉ------------------" << endl;
	cout << "NOM : " << newJoueur.nom << endl;
	cout << "PRENOM : " << newJoueur.prenom << endl;
	cout << "NUMERO : " << newJoueur.noDeJoueur << endl;
	cout << "NOMBRE DE BUTS : " << newJoueur.nbButs << endl;
	switch (newJoueur.position)
	{
	case Position::GARDIEN_DE_BUT:
		cout << "POSITION DU JOUEUR : GARDIEN_DE_BUT " << endl;
		break;
	case Position::ATTAQUANT:
		cout << "POSITION DU JOUEUR : ATTAQUANT " << endl;
		break;
	case Position::DEFENSEUR:
		cout << "POSITION DU JOUEUR : DEFENSEUR" << endl;
	case Position::MILIEU_DE_TERRAIN:
		cout << "POSITION DU JOUEUR : MILIEU_DE_TERRAIN " << endl;
		break;
	default:
		break;
	}
	cout << "-----------------------------------------" << endl;
	return newJoueur;

}

void validerChaine(char chaine[], const unsigned short TAILLE, const char titre[]) {
	cin.getline(chaine, TAILLE);
	while (cin.fail()) {
		cin.clear();
		cin.ignore(512, '\n');
		cout << "Attention : taille maximale de " << titre << " est " << TAILLE - 1 << " : ";
		cin.getline(chaine, TAILLE);
	}
}

int saisieNumerique() {
	int valeur;
	cin >> valeur;
	while (cin.fail() || cin.peek() != '\n') {
		cin.clear();
		cin.ignore(512, '\n');
		cout << "Attention : saisir une valeur numerique seulement : ";
		cin >> valeur;
	}
	cin.ignore(512, '\n');
	return valeur;
}

int saisieNumeriqueChoixMenu() {
	int valeur;
	cin >> valeur;
	while (cin.fail() || cin.peek() != '\n' || valeur < 0 || valeur >9) {
		cin.clear();
		cin.ignore(512, '\n');
		cout << "Attention : saisir une valeur numerique seulement entre 1 et 9 : ";
		cin >> valeur;
	}
	cin.ignore(512, '\n');
	return valeur;
}


int rechercherJoueur(joueur joueurs[], unsigned short nbJoueurs) {
	int i;
	int numeroSaisie;
	bool trouve;
	int valretour;

	trouve = false;
	i = 0;
	cout << "Veuillez saisir le numero du joueur :" << endl;
	numeroSaisie = saisieNumerique();

	valretour = -1;

	while ((i < nbJoueurs) && (trouve == false))
	{
		if ((joueurs[i].noDeJoueur == numeroSaisie))
		{
			valretour = i;
			trouve = true;
		}
		else {
			i++;
		}
	}
	if (trouve)
	{
		return valretour;
	}
	else {
		cout << "Ce joueur n'existe pas dans la liste!" << endl;
		return valretour;
	}	
}

void modifierJoueur(joueur& joueur) {
	cout << "Informations actuelles du joueur" << endl;
	cout << "Nom : " << joueur.nom << endl;
	cout << "Prenom : " << joueur.prenom << endl;
	cout << "Position : " << joueur.position << endl;
	cout << "Numero  :" << joueur.noDeJoueur << endl;
	cout << "Nombre de bute : " << joueur.nbButs << endl;
	cout << endl;
	cout << "----------------------------------" << endl;
	cout << "Modification des infos du joueur" << endl;
	cout << "Nouveau Nom : ";
	validerChaine(joueur.nom, TAILLE_NOM, "nom");

	cout << "Nouveau Prenom : ";
	validerChaine(joueur.prenom, TAILLE_PRENOM, "prenom");

	cout << "Nouvelle Position : " << endl;
	cout << " 1 = GARDIEN_DE_BUT" << endl;
	cout << " 2 = ATTAQUANT" << endl;
	cout << " 3 = DEFENSEUR" << endl;
	cout << " 4 = MILIEU_DE_TERRAIN" << endl;
	unsigned short positionsaisie = saisieNumerique();
	joueur.position = (Position)positionsaisie;
	cout << endl;
	cout << " -- Réussi, joueur numéro " << joueur.noDeJoueur << " modifié ! --" << endl;
		
}

void retirerJoueur(joueur joueurs[], unsigned short& nbJoueurs, int indiceJoueurARetirer) {
	for (int i = indiceJoueurARetirer; i < nbJoueurs; i++)
	{
		joueurs[i] = joueurs[i + 1];
		joueurs[i].noDeJoueur = joueurs[i].noDeJoueur - 1;
	}
}

void afficherInfoJoueur(const joueur& JOUEUR) {
	cout << "Nom : " << JOUEUR.nom << endl;
	cout << "Prenom : " << JOUEUR.prenom << endl;
	cout << "Nombre de buts : " << JOUEUR.nbButs << endl;
	cout << "Numero du joueur : " << JOUEUR.nbButs << endl;
	switch (JOUEUR.position)
	{
	case Position::GARDIEN_DE_BUT:
		cout << "  POSITION DU JOUEUR : GARDIEN_DE_BUT " << endl;
		break;
	case Position::ATTAQUANT:
		cout << "  POSITION DU JOUEUR : ATTAQUANT " << endl;
		break;
	case Position::DEFENSEUR:
		cout << "  POSITION DU JOUEUR : DEFENSEUR" << endl;
		break;
	case Position::MILIEU_DE_TERRAIN:
		cout << "  POSITION DU JOUEUR : MILIEU_DE_TERRAIN " << endl;
		break;
	default:
		break;
	}
	cout << endl;
}

void ajouterButJoueur(joueur& joueur) {
	joueur.nbButs += 1;
	cout << "Un but a ete ajoute au joueur numero " << joueur.noDeJoueur << endl;
}


void retirerButJoueur(joueur& joueur) {
	if (joueur.nbButs > 0) {
		joueur.nbButs -= 1;
		cout << "1 but a ete retirer au joueur numero " << joueur.noDeJoueur << endl;
	}
	else if (joueur.nbButs == 0) {
		cout << "Ce joueur n'a pas enregistrer de but d'abord";
	}
}

void afficherJoueursParPosition(joueur joueurs[], unsigned short nbJoueurs) {
	unsigned int positionJoueurAfficher;
	cout << endl;
	cout << "Quelle est la position des joueurs a afficher : " << endl;
	cout << " 1 = GARDIEN_DE_BUT" << endl;
	cout << " 2 = ATTAQUANT" << endl;
	cout << " 3 = DEFENSEUR" << endl;
	cout << " 4 = MILIEU_DE_TERRAIN" << endl;
	positionJoueurAfficher = saisieNumerique();
	for (int i = 0; i < nbJoueurs; i++)
	{
		if (joueurs[i].position == positionJoueurAfficher) {
			cout << endl;
			cout << "Les joueurs a la position demande sont : " << endl;
			cout << endl;
			cout << "  NUMERO : " << joueurs[i].noDeJoueur << endl;
			cout << "  NOM : " << joueurs[i].nom << endl;
			cout << "  PRENOM : " << joueurs[i].nom << endl;
			cout << "  NOMBRE DE BUTS : " << joueurs[i].nbButs << endl;
			switch (joueurs[i].position)
			{
			case Position::GARDIEN_DE_BUT:
				cout << "  POSITION DU JOUEUR : GARDIEN_DE_BUT " << endl;
				break;
			case Position::ATTAQUANT:
				cout << "POSITION DU JOUEUR : ATTAQUANT " << endl;
				break;
			case Position::DEFENSEUR:
				cout << "POSITION DU JOUEUR : DEFENSEUR" << endl;
				break;
			case Position::MILIEU_DE_TERRAIN:
				cout << "POSITION DU JOUEUR : MILIEU_DE_TERRAIN " << endl;
				break;
			default:
				break;
			}
			cout << endl;
		}
	}
}
void afficherTousLesJoueurs(joueur joueurs[], unsigned short nbJoueurs) {

	cout << "------------------------------------- : " << endl;
	cout << "LA LISTE TOTALE DES JOUEURS EST : " << endl;
	cout << "------------------------------------- " << endl;
	for (int i = 0; i < nbJoueurs; i++)
	{
		if (joueurs[i].noDeJoueur >= 1 && joueurs[i].noDeJoueur <= 14) {
			cout << endl;
			cout << "  NUMERO : " << joueurs[i].noDeJoueur << endl;
			cout << "  NOM : " << joueurs[i].nom << endl;
			cout << "  PRENOM : " << joueurs[i].prenom << endl;
			cout << "  NOMBRE DE BUTS : " << joueurs[i].nbButs << endl;
			switch (joueurs[i].position)
			{
			case Position::GARDIEN_DE_BUT:
				cout << "  POSITION DU JOUEUR : GARDIEN_DE_BUT " << endl;
				break;
			case Position::ATTAQUANT:
				cout << "POSITION DU JOUEUR : ATTAQUANT " << endl;
				break;
			case Position::DEFENSEUR:
				cout << "POSITION DU JOUEUR : DEFENSEUR" << endl;
				break;
			case Position::MILIEU_DE_TERRAIN:
				cout << "POSITION DU JOUEUR : MILIEU_DE_TERRAIN " << endl;
				break;
			default:
				break;
			}
			cout << endl;
		}
	}
}

void afficherTotalDeButDeLEquipe(joueur joueurs[], unsigned short nbJoueurs) {
	if(nbJoueurs > 0) {
	unsigned short nmbreTotalButsEquipe =0;
	for (int i = 0; i < nbJoueurs; i++)
	{
		nmbreTotalButsEquipe += joueurs[i].nbButs;
	}
	cout << "Nombre total de but de toute l'equipe est : " << nmbreTotalButsEquipe << endl;
	}
	else if (nbJoueurs == 0) {
		cout << "La liste de joueurs est vide !!!!" << endl;
	}
}


void quitter(int param) {
	string reponse;
	cerr << "\n" << "Quitter? O/N :" << endl; cin >> reponse;
	if (reponse == "o" || reponse == "O") {
		exit(0);
	}
	if (reponse == "n" || reponse == "N")
	{
		if (param == 0) {
			afficherMenu();
		}
	}
}
