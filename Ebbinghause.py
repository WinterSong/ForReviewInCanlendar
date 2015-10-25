import time
import datetime

def func(days):
	threeDayAgo = (datetime.datetime.now() + datetime.timedelta(days))
	timeStamp = int(time.mktime(threeDayAgo.timetuple()))
	otherStyleTime = threeDayAgo.strftime("%Y-%m-%d %H:%M:%S")
	return time.strptime(otherStyleTime,"%Y-%m-%d %X")

def main():
	name = raw_input()
	if isinstance(name,unicode):
		name = name.encode('gbk')
	else:
		name = name.decode('utf-8').encode('gbk')
	name+=','
	f = file('forcalendar.csv','w')
	#Ebbinghause-curve days to review
	a = [0,1,3, 6, 20, 40]
	s = "Subject,Start Date,All Day\n"
	s = s.decode('gbk').encode('utf-8')
	f.write(s)
	for i in a:
		struct_time = func(i)
		tm = str(struct_time.tm_year)
		tm+='-'+str(struct_time.tm_mon)+'-'+str(struct_time.tm_mday)+',TRUE\n'
		tm = tm.decode('gbk').encode('utf-8')
		f.write(name.decode('gbk').encode('utf-8'))
		f.write(tm)
	f.close()





if __name__ == '__main__':
	main()
