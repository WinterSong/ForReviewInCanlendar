#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>

using namespace std;
class Date{
	 
	public:
	    Date():year(0),month(1),day(1){};
	    Date(const unsigned year,
	        const unsigned month,
	        const unsigned day):
	                            year(year),
	                            month(month),
	                            day(day){};
	    ~Date(){};
	 
	    unsigned getDays()const;
	    const Date& setFromDays(unsigned);
	    void clear();
	    bool isRunNian()const;
	 
	    const Date& operator+=(const int);
	    friend istream& operator>>(istream& in,Date& date);
	    friend ostream& operator<<(ostream& out,const Date& date);
	 
	public:
	    unsigned year;
	    unsigned month;
	    unsigned day;
	 
	    // 每个月开始时是这年的第几天,0月不用
	    static const unsigned int daysInEveryMonth[13];
};
const unsigned int Date::daysInEveryMonth[13] = {0,0,31,59,90,120,151,181,212,243,273,304,334};
// 输入输出
istream& operator>>(istream& in,Date& date){
 
    in>>date.year>>date.month>>date.day;
 
    return in;
}

// 加
const Date& Date::operator+=(const int days){
    setFromDays(getDays() + days);
 
    return *this;
}
 
// 清空
void Date::clear(){
    year = 0;
    month = 1;
    day = 1;
}
 
// 是否为闰年
bool Date::isRunNian()const{
    return (year % 400 == 0) || (year % 100 != 0 && year % 4 == 0);
}
 
// 将格式化的时间转化为以天数表示的时间戳
unsigned Date::getDays()const{
    unsigned days(0);
 
    // 每100年有24个闰年
    days += year / 100 * 24;
    // 每400年是闰年
    days += year / 400;
    // 年数小于100时,每4年是闰年
    days += (year % 100) / 4;
 
    days += year * 365;
    days += daysInEveryMonth[month];
    days += day;
 
    return days;
}
 
// 将天数表示的时间戳转化为时间结构
const Date& Date::setFromDays(unsigned days){
    clear();
 
    // 年份
    while (days > 365){
        ++year;
        days -= 365;
 
        // 闰年
        isRunNian() && --days;
    }
 
    // 月份
    month = 12;
    while (days < daysInEveryMonth[month])
        --month;
    days -= daysInEveryMonth[month];
 
    // 日期
    day = days;
 
    return *this;
}


int main()
{
	time_t tt = time(NULL);
	tm* t = localtime(&tt);
	int year = t->tm_year+1900;
	int mon = t->tm_mon+1;
	int day = t->tm_mday;
	ofstream out;
	out.open("ForWords.csv");

	string name;
	cin>>name;
	Date now(year,mon,day);
	out<<"Subject,Start Date,All Day\n";
	out<<name<<','<<year<<'-'<<mon<<'-'<<day<<",TURE\n";
	int days[5] = {1,3,6,18,35};
	for (int i = 0; i<5;i++)
	{
		now += days[i];
		out<<name<<','<<now.year<<'-'<<now.month<<'-'<<now.day<<",TURE\n";
	}
	out.close();
}
