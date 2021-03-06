struct SuffixArray {
	const int L;
	string s;
	vector<vector<int> > P;
	vector<pair<pair<int,int>,int> > M;
	vector<int> Suf,rank,LCParr;
	// returns the length of the longest common prefix of s[i...L-1] and s[j...L-1]
	int LongestCommonPrefix(int i,int j) {
		int len = 0;
		if(i==j) return (L-i);
		for (int k=P.size()-1 ; k>=0 && i<L && j<L; k--){
			if(P[k][i]==P[k][j]){
				i+=(1<<k); j+=(1<<k);
				len+=(1<<k);
			}
		}
		return len;
	}
	//Suf[i] denotes the suffix at i^th rank
	//Rank[i] denotes the rank of the i^th suffix
	//LCP[i] the longest common prefix of the suffixes at ith and (i+1)th rank.
	SuffixArray(const string &s) : L(s.length()), s(s), P(1, vector<int>(L, 0)), M(L), rank(L), LCParr(L-1){
		vector<int> chars(L,0);
		for(int i=0 ; i<L ; i++) chars[i] = int(s[i]);
		sort(chars.begin(), chars.end());
		map<int,int> mymap;
		int ptr=0;
		for(int elem : chars) mymap[elem] = ptr++;

		for(int i=0 ; i<L ; i++) P[0][i] = mymap[int(s[i])];
		for(int skip=1,level=1 ; skip<L ; skip*=2,level++){
			P.pb(vector<int>(L, 0));
			for(int i = 0; i < L; i++) 
				M[i] = mp(mp(P[level-1][i], (i+skip)<L ? P[level-1][i+skip] : -1000), i);
			sort(M.begin(),M.end());
			for(int i = 0; i < L; i++) 
				P[level][M[i].Y] = (i > 0 && M[i].X == M[i-1].X) ? P[level][M[i-1].Y] : i;
		}
		Suf = P.back();
		for(int i=0 ; i<L ; i++) rank[Suf[i]] = i;
		for(int i=0 ; i<(L-1) ; i++) LCParr[i] = LongestCommonPrefix(rank[i],rank[i+1]); 
	}
};