#include <string>
#include <vector>
#include "../Utilities/utilities.h"

using namespace std;

class Trajectory
{
public:
	string trajectoryType;
	string direction;
	bool forward;
	int iterationCount;
	float speed;
	vector<Vector3> points;
	int currentPoint;
	Vector3 lastPosition;
	float radius;
	float alpha;
	//float beta = 0;
	//int sign = 1;
	Vector3 offsetPosition;

	Trajectory();
	~Trajectory();

	//void Update(Vector3*, Vector3*, float);
	void Update(Vector3*, Vector3*, float);
};
