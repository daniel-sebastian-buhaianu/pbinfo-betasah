#include <fstream>
#define MAX_LINII 1000
#define MAX_DAME 100
#define VALOARE_PATRAT_ACCESIBIL 0
#define VALOARE_PATRAT_INACCESIBIL -1
#define VALOARE_PATRAT_DAMA 1
#define NR_DIRECTII 8
using namespace std;
struct Pozitie { int nrLinie, nrColoana; };
Pozitie pozitieDama[MAX_DAME];
int directieLinie[] = {-1, -1, -1, 0, 1, 1, 1, 0};
int directieColoana[] = {-1, 0, 1, 1, 1, 0, -1, -1};
int tabla[MAX_LINII+2][MAX_LINII+2];
int nrLinii, nrColoane, nrDame, nrMaximPatrateAlbe, nrPatrateAccesibile;
void citesteDateleDeIntrare();
void marcheazaPatrateleInaccesibile(); 
void calculeazaNumarulMaximDePatrateAlbePeUnRand();
void calculeazaNumarulDePatrateAccesibile();
void afiseazaDateleDeIesire();
int main()
{
	citesteDateleDeIntrare();
	marcheazaPatrateleInaccesibile();
	calculeazaNumarulMaximDePatrateAlbePeUnRand();
	calculeazaNumarulDePatrateAccesibile();
	afiseazaDateleDeIesire();
	return 0;
}
void calculeazaNumarulDePatrateAccesibile()
{
	for (int i = 0; i < nrDame; i++)
		for (int k = 0; k < NR_DIRECTII; k++)
		{
			Pozitie p;
			p.nrLinie = pozitieDama[i].nrLinie + directieLinie[k];
			p.nrColoana = pozitieDama[i].nrColoana + directieColoana[k];
			while (tabla[p.nrLinie][p.nrColoana] != VALOARE_PATRAT_DAMA
			       && tabla[p.nrLinie][p.nrColoana] != VALOARE_PATRAT_INACCESIBIL)
			{
				if (tabla[p.nrLinie][p.nrColoana] == VALOARE_PATRAT_ACCESIBIL)
				{
					nrPatrateAccesibile++;
					tabla[p.nrLinie][p.nrColoana] = nrPatrateAccesibile+1;
				}
				p.nrLinie += directieLinie[k];
				p.nrColoana += directieColoana[k];
			}
		}
}
void calculeazaNumarulMaximDePatrateAlbePeUnRand()
{
	nrMaximPatrateAlbe = 0;
	for (int i = 1; i <= nrLinii; i++)
	{
		int nr = 0;
		for (int j = 1; j <= i; j++)
			if (tabla[i][j] == VALOARE_PATRAT_ACCESIBIL)
				nr++;
		if (nr > nrMaximPatrateAlbe)
			nrMaximPatrateAlbe = nr;
	}
}
void marcheazaPatrateleInaccesibile()
{
	int i, j;
	// bordez matricea
	for (j = 0; j <= nrColoane+1; j++)
		tabla[0][j] = tabla[nrLinii+1][j] = VALOARE_PATRAT_INACCESIBIL;
	for (i = 1; i <= nrLinii; i++)
		tabla[i][0] = tabla[i][nrColoane+1] = VALOARE_PATRAT_INACCESIBIL;
	// marchez celelalte patrate inaccesibile
	for (i = 1; i <= nrLinii; i++)
		for (j = i+1; j <= nrColoane; j++)
			tabla[i][j] = VALOARE_PATRAT_INACCESIBIL;
}
void citesteDateleDeIntrare()
{
	ifstream citeste("betasah.in");
	int nrPatrateGri, linie, coloana, i;
	citeste >> nrLinii >> nrDame >> nrPatrateGri;
	nrColoane = nrLinii;
	for (i = 0; i < nrDame; i++)
	{
		citeste >> linie >> coloana;
		tabla[linie][coloana] = VALOARE_PATRAT_DAMA;
		pozitieDama[i].nrLinie = linie;
		pozitieDama[i].nrColoana = coloana;
	}
	for (i = 0; i < nrPatrateGri; i++)
	{
		citeste >> linie >> coloana;
		tabla[linie][coloana] = VALOARE_PATRAT_INACCESIBIL;
	}
	citeste.close();
}
void afiseazaDateleDeIesire()
{
	ofstream scrie("betasah.out");
	scrie << nrMaximPatrateAlbe << '\n' << nrPatrateAccesibile;
	scrie.close();
}

