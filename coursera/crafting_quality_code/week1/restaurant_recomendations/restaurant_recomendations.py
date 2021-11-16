"""
A restaurant recommendation system.

Here are some example dictionaries.  These correspond to the information in
restaurants_small.txt.

Restaurant name to rating:
# dict of {str: int}
{'Georgie Porgie': 87,
 'Queen St. Cafe': 82,
 'Dumplings R Us': 71,
 'Mexican Grill': 85,
 'Deep Fried Everything': 52}

Price to list of restaurant names:
# dict of {str, list of str}
{'$': ['Queen St. Cafe', 'Dumplings R Us', 'Deep Fried Everything'],
 '$$': ['Mexican Grill'],
 '$$$': ['Georgie Porgie'],
 '$$$$': []}

Cuisine to list of restaurant names:
# dict of {str, list of str}
{'Canadian': ['Georgie Porgie'],
 'Pub Food': ['Georgie Porgie', 'Deep Fried Everything'],
 'Malaysian': ['Queen St. Cafe'],
 'Thai': ['Queen St. Cafe'],
 'Chinese': ['Dumplings R Us'],
 'Mexican': ['Mexican Grill']}

With this data, for a price of '$' and cuisines of ['Chinese', 'Thai'], we
would produce this list:

	[[82, 'Queen St. Cafe'], [71, 'Dumplings R Us']]
"""

# The file containing the restaurant data.
FILENAME = 'restaurants_small.txt'


def recommend(file, price, cuisines_list):
	"""(file open for reading, str, list of str) -> list of [int, str] list

	Find restaurants in file that are priced according to price and that are
	tagged with any of the items in cuisines_list.  Return a list of lists of
	the form [rating%, restaurant name], sorted by rating%.
	"""

	# Read the file and build the data structures.
	# - a dict of {restaurant name: rating%}
	# - a dict of {price: list of restaurant names}
	# - a dict of {cusine: list of restaurant names}
	name_to_rating, price_to_names, cuisine_to_names = read_restaurants(file)
	#print(price_to_names)

	# Look for price or cuisines first?
	# Price: look up the list of restaurant names for the requested price.
	names_matching_price = price_to_names[price]
	#print(names_matching_price)

	# Now we have a list of restaurants in the right price range.
	# Need a new list of restaurants that serve one of the cuisines.
	names_final = filter_by_cuisine(names_matching_price, cuisine_to_names, cuisines_list)
	#print(names_final)

	# Now we have a list of restaurants that are in the right price range and serve the requested cuisine.
	# Need to look at ratings and sort this list.
	result = build_rating_list(name_to_rating, names_final)
	#print(result)

	# We're done!  Return that sorted list.
	return result

def build_rating_list(name_to_rating, names_final):
	""" (dict of {str: int}, list of str) -> list of list of [int, str]

	Return a list of [rating%, restaurant name], sorted by rating%

	>>> name_to_rating = {'Georgie Porgie': 87,
	                      'Queen St. Cafe': 82,
	                      'Dumplings R Us': 71,
	                      'Mexican Grill': 85,
	                      'Deep Fried Everything': 52}
	>>> names = ['Queen St. Cafe', 'Dumplings R Us']
	[[82, 'Queen St. Cafe'], [71, 'Dumplings R Us']]
	"""
	final_unsorted = {}
	for ntr in name_to_rating:
		#print(ntr)
		for nf in names_final:
			if ntr == nf:
				#print(name_to_rating[ntr])
				final_unsorted.update({name_to_rating[ntr] : ntr})
	final_sorted = sorted(final_unsorted.items(), reverse=True)
	return final_sorted

def filter_by_cuisine(names_matching_price, cuisine_to_names, cuisines_list):
	""" (list of str, dict of {str: list of str}, list of str) -> list of str

	>>> names = ['Queen St. Cafe', 'Dumplings R Us', 'Deep Fried Everything']
	>>> cuis = {'Canadian': ['Georgie Porgie'],
	            'Pub Food': ['Georgie Porgie', 'Deep Fried Everything'],
	            'Malaysian': ['Queen St. Cafe'],
	            'Thai': ['Queen St. Cafe'],
	            'Chinese': ['Dumplings R Us'],
	            'Mexican': ['Mexican Grill']}
	>>> cuisines = ['Chinese', 'Thai']
	>>> filter_by_cuisine(names, cuis, cuisines)
	['Queen St. Cafe', 'Dumplings R Us']
	"""
	restaurants = []
	for cl in cuisines_list:
		for ctn in cuisine_to_names.get(cl):
			restaurants.append(ctn)
	print(restaurants)
	result = []
	for r1 in restaurants:
		for r2 in names_matching_price:
			if r1 == r2:
				result.append(r1)
	return result

def read_restaurants(file):
	""" (file) -> (dict, dict, dict)

	Return a tuple of three dictionaries based on the information in the file:

	- a dict of {restaurant name: rating%}
	- a dict of {price: list of restaurant names}
	- a dict of {cusine: list of restaurant names}
	"""

	name_to_rating = {}
	price_to_names = {'$': [], '$$': [], '$$$': [], '$$$$': []}
	cuisine_to_names = {}

	f = open(file, "r")
	index = 0
	tmp_name=""
	tmp_rat=0
	tmp_dol=""
	tmp_cui=""
	for x in f:
		if index == 0:
			tmp_name = x.replace('\n', '')
			#print(tmp_name)
		elif index == 1:
			tmp_rat = int(x[:x.index("%")])
			#print(tmp_rat)
		elif index == 2:
			tmp_dol = x.replace('\n', '')
			#print(tmp_dol)
		elif index == 3:
			tmp_cui = x.replace('\n', '').split(",");
			#print(tmp_cui)
			name_to_rating.update({tmp_name: tmp_rat})
			name = price_to_names[tmp_dol]
			name.append(tmp_name)
			price_to_names.update({tmp_dol: name})
			for cui in tmp_cui:
				name = []
				other_name = cuisine_to_names.get(cui)
				if other_name is not None:
					name = other_name
				name.append(tmp_name)
				cuisine_to_names.update({cui: name})
		else:
			index = -1
		index = index + 1
	f.close()

	#print(name_to_rating)
	#print(price_to_names)
	#print(cuisine_to_names)
	return (name_to_rating, price_to_names, cuisine_to_names)

if __name__ == "__main__":
	args = sys.argv
	# args[0] = current file
	# args[1] = function name
	# args[2:] = function args : (*unpacked)
	globals()[args[1]](*args[2:])
