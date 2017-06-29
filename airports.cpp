#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <queue>

using namespace std;

class Point {
private: 
	double m_XCoord;
	double m_YCoord;
public:
	Point() {
		m_XCoord = 0.0;
		m_YCoord = 0.0;
	}
	Point(double x, double y) {
		set_Point(x, y);
	}
	Point(const Point &p) {
		m_XCoord = p.m_XCoord;
		m_YCoord = p.m_YCoord;
	}
	//SET
	void set_X(double x) {
		m_XCoord = x;
	}
	void set_Y(double y) {
		m_YCoord = y;
	}
	void set_Point(double x, double y) {
		set_X(x);
		set_Y(y);
	}
	//GET
	double get_X() const { return m_XCoord; }
	double get_Y() const { return m_YCoord; }
	//Other
	Point middle(const Point obj) const { //Middle of a line
		Point instPoint; //instance of point
		instPoint.m_XCoord = (m_XCoord + obj.m_XCoord) / 2.0;
		instPoint.m_YCoord = (m_YCoord + obj.m_YCoord) / 2.0;
		return instPoint;
	}
	double dist(const Point p) const {
		return sqrt(pow(m_XCoord - p.m_XCoord, 2) +
			pow(m_YCoord - p.m_YCoord, 2));
	}
	bool isBetweenV(Point p1, Point p2) { //Vertical comparison
		if (p1.get_X() == p2.get_X() && m_YCoord < p1.get_Y() && m_YCoord > p2.get_Y()) {
			return true;
		}
		return false;
	}
	bool isBetweenH(Point p1, Point p2) { //Horizontal comparison
		if (p1.get_Y() == p2.get_Y() && m_XCoord < p1.get_X() && m_XCoord > p2.get_Y()) {
			return true;
		}
		return false;
	}
	bool isOnPoint(Point p) {
		return m_XCoord == p.get_X() && m_YCoord == p.get_Y();
	}
	bool operator==(const Point toCompare) const {
		return m_XCoord == toCompare.m_XCoord &&
			m_YCoord == toCompare.m_YCoord;

	}
	void print() const {
		cout << "[" << m_XCoord << ", " << m_YCoord << "]";
	}
	void input(const char name[]) {
		cout << "Point " << name << endl;
		cout << "x= ";
		cin >> m_XCoord;
		cout << "y= ";
		cin >> m_YCoord;
	}
};

class Airport: public Point {
protected:
	string m_name;
	Point m_location;
	bool m_runway; //if true, a plane is using it
	int m_ramps;//стоянки на самолети
	string m_type; //Military or International
public:
	Airport() {
		m_name = "";
		m_location = Point(700.0, 200.0);
		m_runway = 0;
		m_ramps = 0;
		m_type = "International"; //Default International
	}
	Airport(string name, string type, Point location, int ramps) { 
		m_name = name;
		m_location = location;
		m_ramps = ramps;
		m_type = type; 
	}
	Airport(const Airport &airport) {
		m_name = airport.m_name;
		m_location = airport.m_location;
		m_runway = airport.m_runway;
		m_ramps = airport.m_ramps;
		m_type = airport.m_type;
	}
//SET
	void set_name(string name) {
		m_name = name;
	}
	void set_location(int x, int y) {
		m_location = Point(x, y);
	}
	void set_runway(bool runway) {
		m_runway = runway;
	}
	void set_ramps(int ramps) {
		m_ramps = ramps;
	}
	void set_type(string type) {
		m_type = type;
	}
	

//GET
	const string get_name() const {
		return m_name;
	}
	const Point get_locatin() const {
		return m_location;
	}
	const bool get_runway() const {
		return m_runway;
	}
	const int get_ramps() const {
		return m_ramps;
	}
	const string get_type() const {
		return m_type;
	}
//OTHER
	friend ostream& operator<<(ostream &output, const Airport &toStream) {
		output << "Airport of " << toStream.m_name
			//<< "Location: " << toStream.m_location
			<< "Ramps: " << toStream.m_ramps
			<< "Type: " << toStream.m_type;
		return output;
	}
	virtual bool operator==(const Airport &toCompare) const {
		return m_location == toCompare.m_location; //Military or International
	}
};

class Aircraft : public Airport {
protected:
	string m_name;
	double m_speed; //скорост
	int m_weight; //тегло на натоварен самолет
	double m_maxFlightTime; //макс време на даден полет полет
	int m_rampTime; //време, обслужване на стоянка
	Point m_location; //current location of Aircraft
	Point m_fromAirport;
	Point m_toAirport;
	bool m_request;
public:

	Aircraft() {
		m_name = "";
		m_speed = 0.0;
		m_weight = 0;
		m_maxFlightTime = 0.0;
		m_rampTime = 0;
		m_location = Point(700, 200); //Varna
		m_fromAirport = Point(700, 200); //From Varna
		m_toAirport = Point(700, 200); //To Varna
		m_request = false;
	}
	Aircraft(string name, float speed, int weight, double flightTime, int rampTime,
		double x, double y, Point fromAirport, Point toAirport) {
		m_name = name;
		m_speed = speed;
		m_weight = weight;
		m_maxFlightTime = flightTime;
		m_rampTime = rampTime;
		set_location(x, y);
		m_fromAirport = fromAirport;
		m_toAirport = toAirport;
	}
	Aircraft(const Aircraft &aircraft) {
		m_name = aircraft.m_name;
		m_speed = aircraft.m_speed;
		m_weight = aircraft.m_weight;
		m_maxFlightTime = aircraft.m_maxFlightTime;
		m_rampTime = aircraft.m_rampTime;
		m_location = aircraft.m_location;
		m_fromAirport = aircraft.m_fromAirport;
		m_toAirport = aircraft.m_toAirport;
		m_request = aircraft.m_request;
	}
	//SET
	void set_name(string name) {
		m_name = name;
	}
	void set_speed(double speed) {
		m_speed = speed;
	}
	void set_weight(int weight) {
		m_weight = weight;
	}
	void set_maxFlightTime(double flightTime) {
		m_maxFlightTime = flightTime;
	}
	void set_rampTime(int rampTime) {
		m_rampTime = rampTime;
	}
	void set_location(double x, double y) {
		m_location = Point(x, y);
	}
	void set_fromAirport(Point fromAirport) {
		m_fromAirport = fromAirport;
	}
	void set_toAirport(Point toAirport) {
		m_toAirport = toAirport;
	}
	void set_request(bool request) {
		m_request = request;
	}
	//GET
	const string get_name() const {
		return m_name;
	}
	const double get_speed() const {
		return m_speed;
	}
	const int get_weight() const {
		return m_weight;
	}
	const double get_maxFlightTime() const {
		return m_maxFlightTime;
	}
	const int get_rampTime() const {
		return m_rampTime;
	}
	const Point get_location() const {
		return m_location;
	}
	const Point get_departure() const {
		return m_fromAirport;
	}
	const Point get_arrival() const {
		return m_toAirport;
	}
	const bool get_request() const {
		return m_request;
	}
	//OPERATOR 
	friend ostream& operator<<(ostream &output, const Aircraft &toStream) {
		output << "Name: " << toStream.m_name
			<< "Speed: " << toStream.m_speed
			<< "Weight: " << toStream.m_weight
			<< "Maximum flight time: " << toStream.m_maxFlightTime
			<< "Ramp time: " << toStream.m_rampTime;
			//<< "Location: " << toStream.m_location
			//<< "Depaerted from: " << toStream.m_fromAirport
			//<< "Arrives at: " << toStream.m_toAirport;
		return output;
	}
	virtual bool operator<(const Aircraft &toCompare) const {
		return m_speed < toCompare.m_speed;
	}
	//OTHER
	void roundAirport() {
		//square around airport(x,y)
		Point A = Point(m_toAirport.get_X() - 10, m_toAirport.get_Y() + 10); //(x-10; y+10)
		Point B = Point(m_toAirport.get_X() - 10, m_toAirport.get_Y() - 10); //(x-10; y-10)
		Point C = Point(m_toAirport.get_X() + 10, m_toAirport.get_Y() - 10); //(x+10; y-10)
		Point D = Point(m_toAirport.get_X() + 10, m_toAirport.get_Y() + 10); //(x+10; y+10)
		
		double x = m_location.get_X();
		double y = m_location.get_Y();

		if (m_request == false) {
			if (m_location.isBetweenV(A, B) || m_location.isOnPoint(A))
				y--;
			if (m_location.isBetweenH(B, C) || m_location.isOnPoint(B))
				x++;
			if (m_location.isBetweenV(D, C) || m_location.isOnPoint(C))
				y++;
			if (m_location.isBetweenH(A, D) || m_location.isOnPoint(D))
				x--;
		}
		m_location = Point(x, y);
	}
	void flight() {
		double x;
		double y;
		double fromX;
		double fromY;
		double toX;
		double toY;
		int choice;

		x = m_location.get_X(); //takes the X of the current plane location
		y = m_location.get_Y(); //takes the Y of the current plane location
		
		fromX = m_fromAirport.get_X(); //takes the X of the departure Airport
		fromY = m_fromAirport.get_Y(); //takes the Y of the departure Airport

		toX = m_toAirport.get_X(); //takes the X for the arical Airport
		toY = m_toAirport.get_Y(); //takes the Y for the arival Airport		

//BEGIN FLIGHT
	//the request
		if ((x == toX - 20) || (y == toY - 20)) {
			cout << this->m_name << " request landing(Y/N) ";
			cin >> choice;
			if (choice == 'y' || choice == 'Y')
				m_request = true;
		}
	//arround the airport
		roundAirport();
	//motion if outside the airport square
		if (fromX > toX && fromY > toY) {
			if(x != toX)
				x--;
			if(y != toY)
				y--;
		}
		else if (fromX < toX && fromY < toY) {
			if (x != toX)
				x++;
			if (y != toY)
				y++;
		}
		else if (fromX < toX && fromY < toY) {
			if (x != toX)
				x++;
			if (y != toY)
				y--;
		}
		else if (fromX > toX && fromY < toY) {
			if (x != toX)
				x--;
			if (y != toY)
				y++;
		}
		else {
				cout << "COORDINATES NOT CHANGED" << endl;
		}
		
		m_location = Point(x, y);
		cout << m_name + " -> ";
		m_location.print();
		if (m_location == m_toAirport)
			cout << " LANDED";
		cout << endl;
//END flight		
	}
};

int main() {
	//City Coordinates
	Point Berlin = Point(200, 560);
	Point Paris = Point(100, 360);
	Point Rome = Point(460, 100);
	Point Kiev = Point(800, 560);
	Point Varna = Point(700, 200);

	//Airports
	Airport Germany = Airport("Berlin", "International", Berlin, 5);
	Airport France = Airport("Paris", "International", Paris, 5);
	Airport Italy = Airport("Rome", "International", Rome, 5);
	Airport Ukraine = Airport("Kiev", "International", Kiev, 5);
	Airport Bulgaria = Airport("Varna", "International", Bulgaria, 5);

	//Planes
	Aircraft Boeing_737 = Aircraft("Boeing 737", 1100.0, 41.0, 410, 6, 700, 200, Varna, Berlin); //Bulgaria - Germany
	Aircraft Airbus_A320 = Aircraft("Airbus A320", 904.0, 37.230, 400, 5, 100, 360, Paris, Kiev); //France - Ukraine

	int time = 0;

	//FLIGHT SIMULATOR
	while (true) {
		//Time
		cout << "Time: " << time << endl;
		time++;

		Boeing_737.flight();
		Airbus_A320.flight();

		cout << "\n";
		cout << "*********************************" << endl;
		system("pause");
		cout << "\n";
	}
	system("pause");
	return 0;
}