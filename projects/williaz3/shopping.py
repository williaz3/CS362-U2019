#Zack Williams
#Shopping.py implemetnation for Assignment 3

#open input file and output file, write input to a list for later use
fin = open("shopping.txt", "r")
fout = open("results.out", "w")
z = int(fin.readline().strip())

#while we have ints in our test cases, continue
for _ in range(z):
	#create a dictionary to store our item prices, weights, and item # based on when they were read in, cited belowi
	#dictionary[price] [weight, index #]
	dic = {}

	#strip the next value to detrermine the number of items to find data for, ind is used as our index vlaue for looping
	items = int(fin.readline().strip())
	ind = 1

	#loop while we are under our total # of items to go through
	for i in range(items):
		#take our lines with two items "X Y" and split them by price (first value listed ) and weight (second value listed) store in seperate lists
		price, weig = map(int, fin.readline().strip().split())
		#write the weight and index value in relation to the price to be used later
		dic[price] = [weig, ind]
		ind += 1#increment for the next value in the list
	#create a list for our  weights for the family members
	weights = []
	
	#fam vlaue is the # of people in teh family (F)
	fam = int(fin.readline().strip())
	#for loop to through each # of family memebers
	for i in range(fam):
		#store the value that family member can hold as it is the next item in our list
		weights.append(int(fin.readline().strip()))
	#create values RES for results and values to store data later
	RES = []
	values = []
	#next line is the weights being read in which should all be lower than the max the family membres can carry
	for weight in weights:
		#sorts our dictioanry by price from highest price to lowest price [::-1} = reverse order; m is maxVal which is a place holder if all the options are too ehavy for the family member, profit is the price value for items stored in family member's bags, and tmp is a list used to store data
		sortedDic = sorted(dic.keys())[::-1]
		maxVal = 0
		profit = 0
		tmp = []
		
		#loop while we have data in our dictionary of itmes 
		for i in range(len(dic)):
			remInd = [] #store the current index, updateds as new items are added to teh family member's bag
			bag = 0
			profit = 0
			#if the dictionary item's weight is less than or equal to the max weight the family member can hold add it to their pack
			if dic[sortedDic[i]][0] <= weight:
				bag=dic[sortedDic[i]][0] #adds the weight to this family member's bag
				profit=sortedDic[i] #adds the price of the item from the dictionary
				remInd+=dic[sortedDic[i]][1],#increments the remInd for the next iteration
			#increment as long as we are in the range of i+1 and less than the total length of our dictionary object for our test cases
			for j in range(i+1, len(dic)):
				#if we can fit another item in the bag and not overburden the family member add the new item to the bag
				if dic[sortedDic[j]][0]+bag <= weight: 
					bag+=dic[sortedDic[j]][0]#adds the item weight to this family member bag
					profit+=sortedDic[j] #adds the price of the itemform the dictionary
					remInd+=dic[sortedDic[j]][1], #increments the remInd for the next iteration
			#if our inintal max value is less than profit, which would b eture if we add anything to our bag, then change the maxVal to be our proift falue and eet temp to teh remInd value
			if maxVal<profit:
				maxVal = profit
				tmp = remInd 
		#sort our tmp array and add it to our result (RES) list, add our values to the values list
		tmp.sort()
		RES.append(tmp)
		values.append(maxVal)
	#formatted printing for our output to write to our outpile file using write()
	fout.write("test case %d\n"%(_+1)) #increment the #printed as we go through each test case
	fout.write("total price: %d\n"%(sum(values))) #sum all the values in that list before printing
	fout.write("member Items\n")
	#while we have values in our result list continue
	for i in range(len(RES)):
		fout.write("%d: %s\n"%(i+1, " ".join(map(str, RES[i]))))# print the RES(result list) as a string using map

#close our input and outpile files as all reading and writing is completed
fin.close()
fout.close()


#dictionary information from: https://www.protechtraining.com/content/python_fundamentals_tutorial-advanced_types_containers,https://www.w3schools.com/python/python_dictionaries.asp ,and https://www.geeksforgeeks.org/python-dictionary-keys-method/
