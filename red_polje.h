struct osoba{
	string ime, prezime;
	char spol;
	int dan, mj, god;
	int ai, bi, ci, di;
};

struct que{
	osoba osobe[10000];
	int celo, zacelje;
};

int AddOne(int n){
	return ((n+1)%10000);
}

que *InitQ(que *Q){
	Q = new que;
	Q->celo = 0;
	Q->zacelje = 9999;
	return Q;
}

bool IsEmptyQ(que *Q){
	if(AddOne(Q->celo) == Q->zacelje) return true;
	else return false;
}

osoba celoQ(que *Q){
	if(IsEmptyQ(Q)) cout << "Red je prazan!\n";
	else return Q->osobe[Q->celo];
}

void EnQueueQ(osoba x, que *Q){
	int n;
	if(Q->zacelje==9999) n=0;
	else n = Q->zacelje+1;
	Q->osobe[n] = x;
	Q->zacelje = n;
}

void DeQueueQ(que *Q){
	if(IsEmptyQ(Q)) cout << "Red je prazan!\n";
	else {
		if(Q->celo==9999) Q->celo=0;
		else Q->celo++;
	}
}
