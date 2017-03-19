#ifndef DVMARCHINGCUBE_H 
#define DVMARCHINGCUBE_H

///< System header files
#include "dvCommon.h"
#include "dvMarchingTable.h"
#include "dvVolumeData.h"

/*!
	\brief
		a class for Edge
*/
class Edge {
public:
	pair<int, int> m_edge[2];

	inline Edge &operator =(const Edge &rhs)
	{
		m_edge[0] = rhs.m_edge[0];
		m_edge[1] = rhs.m_edge[1];

		return *this;
	}
};

/*!
	\brief
		a class for Point3D
*/
class DvPoint3D{
public:
	int x;
	int y;
	int z;

	/* Constructor */
	DvPoint3D() {
		x = 0;
		y = 0;
		z = 0;
	}
	DvPoint3D( int px, int py, int pz ) {
		x = px;
		y = py;
		z = pz;
	}

	/* Operator */
	inline DvPoint3D &operator =(const DvPoint3D &rhs) {
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}
};

//< typedef struct
typedef struct {			///< Vertex
	float P[3];				///< Position
	float N[3];				///< Normal
}DvVertex;

typedef struct {			///< Face
	int vIdx[3];
}DvFace;

typedef struct  {			///< Object
	vector<DvVertex> VertList;
	vector<DvFace> FaceList;
}DvObject;

/*!
	\brief
		a class for Marching Cube
*/
template<class DataType>
class DvMarchingCube
{
public:
	/* Constructor & Destructor */  
	DvMarchingCube();
	DvMarchingCube(DvVolume<DataType> *pData);
	virtual ~DvMarchingCube();

	/* Member functions */
	inline void		March(DataType isoVal);
	inline int		GetCubeIndex(DataType isoVal, DvPoint3D pos);
	inline void		FindVertices(DataType isoVal, DvPoint3D pos, int idx);
	inline DvVertex	Lerp(DataType isoVal, DvPoint3D cell1, DvPoint3D cell2, int idx);
	inline int		GetDisplayList();
	inline DvVertex GetCenterPosition();

	inline void SetData(DataType *pData);
	inline void SetEdgeTable();

private:
	/* Member variables */
	DvVolume<DataType>		*m_Data;
	DvObject				m_VolumeObject;
};

#include "dvMarchingCube.inl"

#endif	// DVMARCHINGCUBE_H
