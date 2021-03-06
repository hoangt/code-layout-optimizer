//#include <google/sparse_hash_map>
#include <tr1/unordered_map>
#include <boost/functional/hash.hpp>
#include <deque>

//using google::sparse_hash_map;
short totalFuncs;

typedef std::pair<short,short> shortpair;

bool CGECmp(const shortpair&, const shortpair&);

struct shortpair_hash{
  size_t operator()(const shortpair& s) const{
	    return std::tr1::hash<short>()(totalFuncs*s.first + s.second);
	}
};

shortpair make_pair(short s1,short s2){
	return (s1<s2)?(shortpair(s1,s2)):(shortpair(s2,s1));
}
struct eqshortpair{
	bool operator()(shortpair s1, shortpair s2) const {
		if ((s1.first == s2.first) && (s1.second == s2.second))
			return true;
		if ((s1.second == s2.first) && (s1.first == s2.second))
			return true;
		return false;
	}
};

typedef std::tr1::unordered_map < shortpair, int, shortpair_hash, eqshortpair> CGMap;
typedef std::pair< shortpair, int> CGE;

struct disjointSet {
	static disjointSet ** sets;
	std::deque<short> elements;
	size_t size(){ return elements.size();}
	static void mergeSets(disjointSet *, disjointSet *);
	static void mergeSets(short id1, short id2){
		if(sets[id1]!=sets[id2])
			mergeSets(sets[id1],sets[id2]);
	}
	
	static void init_new_set(short id){
		sets[id]= new disjointSet();
		sets[id]->elements.push_back(id);
	}
	
};

disjointSet ** disjointSet::sets = 0;



