import sys
import os
from pprint import pprint

fileName = "wrestler.txt"

def designate_wrestlers(wrestlers):
	fin = open(fileName, "r")
	count = int(fin.readline().strip())
	fin.close();
#	print("count")
#	print(count)	


#	print("in designate wrestlers\n")
	def rival_type(type):
		if type == 'babyface':
			return 'heel'
		return 'babyface'

	def mark_rivals(node):
	#	fin = open("wrestler2.txt", "r")
	#	count = int(fin.readline().strip())
	#	fin.close();
	#	print("count")
	#	print(count)	

#		print("in markrivals\n")
		good_guys = wrestlers[node]['type']
		bad_guys = rival_type(good_guys)
		#print(good_guys)
		#print(bad_guys)
		#print(wrestlers[node])

		for r in wrestlers[node]['rivals']:
			#print(wrestlers[node]['type'])
#			print("\n")
			#current_type = wrestlers[r] 
			line = wrestlers[node]['rivals']	
#			print (r)	
			for s in range(count):
				if r == wrestlers[s]['name']:
					checkMe = wrestlers[s]['index']
					
#			print( checkMe)
#			print (wrestlers[checkMe]['type'])
			if wrestlers[checkMe]['type'] is not None and wrestlers[checkMe]['type'] != bad_guys:
#				print("Error: conflicting alignments")
				sys.exit()
			else:
				wrestlers[checkMe]['type'] = bad_guys

	node_list = [x for x in list(wrestlers.keys()) if wrestlers[x]['state']!='visited']

	while len(node_list):
	#indent back out	
		n = node_list[0]
#		print ("n\n")
#		print (n)
		wrestlers[n]['type'] = 'babyface'
		wrestlers[n]['state'] = 'visited'
		unvisited_nodes = list(wrestlers[n]['rivals'])
#		print("unvisited nodes")
#		print (unvisited_nodes)
		mark_rivals(n)
	
		while unvisited_nodes:
			u = unvisited_nodes.pop(0)
#			print("u")
#			print(u)
			for s in range(count):
				if u == wrestlers[s]['name']:
					checkMe = wrestlers[s]['index']
#			print("checkMe")		
#			print( checkMe)

			wrestlers[checkMe]['state'] = 'visited'
	
			for t in wrestlers[checkMe]['rivals']:
				for y in range(count):
					if t == wrestlers[y]['name']:
						check3 = wrestlers[y]['index']
#						print("check 3")
#						print( check3)	
					if wrestlers[check3]['state'] != 'visited':
						unvisited_nodes.append(t)
						unvisited = list(set(unvisited_nodes))
			mark_rivals(wrestlers[checkMe]['index'])

		node_list = [x for x in list(wrestlers.keys()) if wrestlers[x]['state'] != 'visited']
#		print(node_list)


#def print_wrestler(wrestlers):
#	print("\n")
#	print("Babyfaces: " + str(' '.join([x for x in list(wrestlers.keys()) if wrestlers[x]['type'] == 'babyface'])))
#	print("Heels: " + str(' '.join([x for x in list(wrestlers.keys()) if wrestlers[x]['type'] == 'heel'])))
#	print("\n")

def main():
	fin = open(fileName, "r")
	wh = int(fin.readline().strip())
	#print(z)
	z = wh
	wrestlers = {}
	ind = 1
	
	for i in range(z):
		name = fin.readline().strip()
		wrestlers[i] = {
		'index': i,
		'name': name,
		'rivals': [],
		'type': None,
		'state': 'unchecked'
		}
		ind = ind + 1

	

#	print(wrestlers)

	y = int(fin.readline().strip())
	for _ in range(y):
		r = fin.readline().strip()
		if len(r.split(" ")) != 2:
			break
		w1, w2 = r.split(" ")
		#print(wrestlers)
		#print(w1,w2)			
		for j  in range(z):
			if w1 == wrestlers[j]['name']:
	#			print wrestlers[j]['index']
				setW1 = j
				break
		for k  in range(z):
			if w2 == wrestlers[k]['name']:
	#			print wrestlers[k]['index']
				setW2 = k
				break
	#	print (j)	
	#	print(k)
		if wrestlers[k]['name'] not in wrestlers[j]['rivals']:
			wrestlers[j]['rivals'].append(wrestlers[k]['name'])
		if wrestlers[j]['name'] not in wrestlers[k]['rivals']:
			wrestlers[k]['rivals'].append(wrestlers[j]['name'])

#	for l in range (z):
#		print (wrestlers[l])
#		print("\n")




	designate_wrestlers(wrestlers)
#	print_wrestler(wrestlers)

	heellist = []

	babyfacelist =[] 
	for p in range (z):
		tp = wrestlers[p]['type']		
		if tp == 'heel':
			heellist.append(wrestlers[p]['name'])
		if tp == 'babyface':
			babyfacelist.append(wrestlers[p]['name'])
	print ("heellist:")
	print(  heellist )
	print ("babyfacelist:")
	print(  babyfacelist)


if __name__ == '__main__':
	main()	
	



