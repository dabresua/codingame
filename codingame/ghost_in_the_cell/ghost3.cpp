#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;
#define uint unsigned int

#define DEBUG(_msg) cerr << _msg << endl
#define DEBUG_CONFIG
/* #define DEBUG_INPUT */
/* #define DEBUG_RAW */
#define TEST_VECTOR_ROUNDS 8

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

typedef enum owner_t {
	owner_adv = -1, /*< Adversary player */
	owner_neu = 0,  /*< Neutral, not a player */
	owner_me = 1    /*< Me player */
} owner_t;

owner_t get_owner(int o) {
	switch (o) {
	case -1 : return owner_adv;
	case 0  : return owner_neu;
	case 1  : return owner_me;
	}
	assert(false);
}

string owner2str(owner_t o) {
	switch (o) {
	case owner_adv: return "adversary";
	case owner_neu: return "neutral";
	case owner_me: return "player";
	}
	return "ukn";
}

class Factory {
public:
	uint id;
	owner_t owner;
	uint troops; /*< actual number */
	uint prod;   /*< troops/round */
	int closest; /*< Id of the closest factory owned by a player */

	Factory() {
		id = 0;
		troops = 0;
		prod = 0;
		owner = owner_neu;
		closest = -1;
	}

	void copy(Factory *src) {
		id = src->id;
		troops = src->troops;
		prod = src->prod;
		owner = src->owner;
	}

	void debug() {
		cerr << id << ": troops " << troops << " production " << prod << " "
		     << owner2str(owner) << " closest " << closest << endl;
	}
};

class Link {
public:
	uint id1, id2, d;

	Link() {
		id1 = 0;
		id2 = 0;
		d = 0;
	}

	Link(uint a, uint b, uint c) {
		id1 = a;
		id2 = b;
		d = c;
	}

	void set(uint f1, uint f2, uint dis) {
		id1 = f1;
		id2 = f2;
		d = dis;
	}

	void copy(Link *src) {
		id1 = src->id1;
		id2 = src->id2;
		d = src->d;
	}

	void debug() {
		cerr << id1 << " <-> " << id2 << " : " << d << endl;
	}
};

class Map {
public:
	uint size;
	uint lnum;
	Factory *factories;
	Link *links;

	Map(uint s, Factory *factos, uint l, Link *lks) {
		assert(factos);
		assert(links);
		size = s;
		factories = factos;
		lnum = l;
		links = lks;
	}

	void set_link(Link *l, uint index) {
		assert(index < lnum);
		links[index].copy(l);
	}

	void debug_links() {
		for (uint i = 0; i < lnum; i++) {
			links[i].debug();
		}
	}

	void set_factory(Factory *f, uint index) {
		assert(index < size);
		factories[index].copy(f);
	}

	void debug_factories() {
		for (uint i = 0; i < size; i++) {
			factories[i].debug();
		}
	}

	void input(int entityId, string entityType, int arg1, int arg2, int arg3,
	           int arg4, int arg5)
	{
		if (entityType == "FACTORY") {
			Factory tmp_f;
			tmp_f.id = entityId;
			tmp_f.owner = get_owner(arg1);
			tmp_f.troops = arg2;
			tmp_f.prod = arg3;
			set_factory(&tmp_f, entityId);
			#ifdef DEBUG_INPUT
			tmp_f.debug();
			#endif /* DEBUG_INPUT */
		} else if (entityType == "TROOP") {
			owner_t owner = get_owner(arg1);
			int src = arg2;
			int dst = arg3;
			int num = arg4;
			int dis = arg5;
			#ifdef DEBUG_INPUT
			cerr << owner2str(owner) << " sends " << num << " troops from "
			     << src << " to " << dst << ", will arrive in " << dis
			     << " turns" << endl;
			#endif /* DEBUG_INPUT */
		} else if (entityType == "BOMB") {
			#ifdef DEBUG_INPUT
			cerr << "The bomb has been planted at " << arg2 << endl;
			#endif /* DEBUG_INPUT */
		} else {
			cerr << " entityId: " << entityId << " entityType: " << entityType
			     << " arg1: " << arg1 << " arg2: " << arg2 << " arg3: " << arg3
			     << " arg4: " << arg4 << " arg5: " << arg5 << endl;
			assert(false);
		}
	}

	void update_voronoi() {
		for (uint i = 0; i < size; i++) {
			uint tmp_dst = 0;
			for (uint j = 0; j < lnum; j++) {
				if (links[j].id1 == i || links[j].id2 == i) {
					if (factories[links[j].id1].owner == owner_neu &&
					    factories[links[j].id2].owner == owner_neu) {
						continue;
					}
					if (factories[i].closest == -1 || links[j].d < tmp_dst) {
						tmp_dst = links[j].d;
						factories[i].closest = links[j].id1 == i ? links[j].id2:
						                                           links[j].id1;
					} else if (links[j].d == tmp_dst) {
						factories[i].closest = -2;
					}
				}
			}
		}
	}
};

int main()
{
	int factoryCount; // the number of factories
	cin >> factoryCount; cin.ignore();
	#ifdef DEBUG_RAW
	cerr << factoryCount << endl;
	#endif /* DEBUG_RAW */
	Factory factories[factoryCount];
	int linkCount; // the number of links between factories
	cin >> linkCount; cin.ignore();
	#ifdef DEBUG_RAW
	cerr << linkCount << endl;
	#endif /* DEBUG_RAW */
	Link links[linkCount];
	Map map = Map(factoryCount, factories, linkCount, links);
	Link tmp_link;
	for (int i = 0; i < linkCount; i++) {
		int factory1;
		int factory2;
		int distance;
		cin >> factory1 >> factory2 >> distance; cin.ignore();
		#ifdef DEBUG_RAW
		cerr << factory1 << " " << factory2 << " " << distance << endl;
		#endif /* DEBUG_RAW */
		tmp_link.set(factory1, factory2, distance);
		map.set_link(&tmp_link, i);
	}
	#ifdef DEBUG_CONFIG
	map.debug_links();
	#endif /* DEBUG_CONFIG */

	// game loop
	#ifdef TEST_VECTOR_ROUNDS
	uint rounds = 0;
	#endif /* TEST_VECTOR_ROUNDS */
	while (1) {
		int entityCount; // the number of entities (e.g. factories and troops)
		cin >> entityCount; cin.ignore();
		#ifdef DEBUG_RAW
		cerr << entityCount << endl;
		#endif /* DEBUG_RAW */
		for (int i = 0; i < entityCount; i++) {
			int entityId;
			string entityType;
			int arg1;
			int arg2;
			int arg3;
			int arg4;
			int arg5;
			cin >> entityId >> entityType >> arg1 >> arg2 >> arg3 >> arg4 >> arg5; cin.ignore();
			#ifdef DEBUG_RAW
			cerr << entityId << " " << entityType << " " << arg1 << " " << arg2
			     << " " << arg3 << " " << arg4 << " " << arg5 << endl;
			#endif /* DEBUG_RAW */
			map.input(entityId, entityType, arg1, arg2, arg3, arg4, arg5);
		}

		map.update_voronoi();
		#ifdef DEBUG_CONFIG
		map.debug_factories();
		#endif /* DEBUG_CONFIG */

		// Any valid action, such as "WAIT" or "MOVE source destination cyborgs"
		cout << "WAIT" << endl;
		#ifdef TEST_VECTOR_ROUNDS
		if (++rounds >= TEST_VECTOR_ROUNDS)
			break;
		#endif /* TEST_VECTOR_ROUNDS */
	}
}
