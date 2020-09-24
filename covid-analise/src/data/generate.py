import random



for i in ["AC","AL","AM","AP","BA","CE","DA","DF","ES","GO","MA","MG","MS","MT","PA","PB","PE","PI","PR","RJ","RN","RO","RR","RS","SC","SE","SP"]:
	with open(i+".txt","w") as f:
		for j in range(100):
			f.write("%i\n"%random.randint(1,100))

