
#include "dvCommon.h"

class DvTrackball 
{

public:
	// »ý¼º ¼Ò¸ê
	DvTrackball();
	virtual ~DvTrackball(){};

public:
	void SetTrackballCanvasSize(const int _w, const int _h);
	void SetPreviousPosition(const int _x, const int _y);
	void SetTrackballUpdate(const int _x, const int _y);	
	void GetMatrix(float m[4][4]);
	void Clear();
protected:
	void Update();

	friend void trackball(float q[4], float p1x, float p1y, float p2x, float p2y);
	friend void negate_quat(float *q, float *qn);	
	friend void build_rotmatrix(float m[4][4], float q[4]);
	friend void axis_to_quat(float a[3], float phi, float q[4]);
	friend void add_quats(float *q1, float *q2, float *dest);

private:
	int cavas_width, canvas_height;

	int m_PreviousPosition[2];
	int m_CurrentPosition[2];

	// Member variables for trackball effects : for current matrix
	float m_CurrentQuatM[4];

	// Member variables for trackball effects : for last matrix
	float m_LastQuatM[4];


};