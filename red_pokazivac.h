struct osoba{
	string ime, prezime;
	char spol;
	int dan, mj, god;
	int ai, bi, ci, di;
};

struct qu{
	osoba vrijednost;
	qu *sljedeci;
};

struct que{
	qu *celo, *zacelje;
};

que *InitQ(que *Q){
	Q = new que;
	qu *novi = new qu;
	novi->sljedeci = NULL;
	Q->celo = novi;
	Q->zacelje = novi;
	return Q;
}

bool IsEmptyQ(que *Q){
	return Q->celo == Q->zacelje;
}

osoba celoQ(que *Q){
	if(IsEmptyQ(Q)) cout << "Red je prazan!\n";
	else return Q->celo->sljedeci->vrijednost;
}

void EnQueueQ(osoba x, que *Q){
	qu *novi = new qu;
	novi->vrijednost = x;
	novi->sljedeci = NULL;
	Q->zacelje->sljedeci = novi;
	Q->zacelje = novi;
}

void DeQueueQ(que *Q){
	if(IsEmptyQ(Q)) cout << "Red je prazan!\n";
	else{
		qu *brisi = Q->celo;
		Q->celo = Q->celo->sljedeci;
		delete brisi;
	}
}
