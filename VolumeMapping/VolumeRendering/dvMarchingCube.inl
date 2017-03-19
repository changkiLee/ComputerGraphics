
/*!
	\brief
		Constructor
*/
template<class DataType>
DvMarchingCube<DataType>::DvMarchingCube()
{

}

template<class DataType>
DvMarchingCube<DataType>::DvMarchingCube(DvVolume<DataType> *pData)
{
 	m_Data = pData;
}

/*!
	\brief
		Destructor
*/
template<class DataType>
DvMarchingCube<DataType>::~DvMarchingCube()
{

}

/*!
	\brief
		Set a data
*/
template<class DataType>
void DvMarchingCube<DataType>::SetData(DataType *pData)
{
	m_Data = pData;
}

/*!
	\brief
		Implement marching cube algorithm
*/
template<class DataType>
void DvMarchingCube<DataType>::March(DataType isoVal)
{
	cout << "[App Control] : Marching Cube Start." << endl;
	cout << "[App Control] : Iso-value is '" << (int)isoVal << "'." << endl;

	///< Process marching cube
	for(int z = 1; z < m_Data->GetExtent(2) - 2; z++)
	{
		for(int y = 1; y < m_Data->GetExtent(1) - 1; y++)
		{
			for(int x = 1; x < m_Data->GetExtent(0) -1; x++)
			{
				DvPoint3D cellpos(x, y, z);

				///< Get Cube Index
				int index = GetCubeIndex(isoVal, cellpos);

				///< Find Vertices using interpolation
				if( index != 0)
					FindVertices(isoVal, cellpos, index);				
			}
		}
	}
	cout << "[App Control] : Marching Cube End." << endl;
	cout << "[App Control] : Number of Vertices = " << m_VolumeObject.VertList.size() << endl;
	cout << "[App Control] : Number of Faces = " << m_VolumeObject.FaceList.size() << endl;

}

/*!
	\brief
		Get a Cube's Index
*/
template<class DataType>
int DvMarchingCube<DataType>::GetCubeIndex(DataType isoVal, DvPoint3D pos)
{
	int cubeInx = 0;
	int px = pos.x;		int py = pos.y;		int pz = pos.z;

	///< Compare
	if( m_Data->At(px,   py+1, pz  ) < isoVal )		cubeInx |= 1;
	if( m_Data->At(px+1, py+1, pz  ) < isoVal )		cubeInx |= 2;
	if( m_Data->At(px+1, py,   pz  ) < isoVal )		cubeInx |= 4;
	if( m_Data->At(px,   py,   pz  ) < isoVal )		cubeInx |= 8;
	if( m_Data->At(px,   py+1, pz+1) < isoVal )		cubeInx |= 16;
	if( m_Data->At(px+1, py+1, pz+1) < isoVal )		cubeInx |= 32;
	if( m_Data->At(px+1, py,   pz+1) < isoVal )		cubeInx |= 64;
	if( m_Data->At(px,   py,   pz+1) < isoVal )		cubeInx |= 128;

	return cubeInx;
}

/*!
	\brief
		Find the vertices where the surface intersects the cube
*/
template<class DataType>
void DvMarchingCube<DataType>::FindVertices(DataType isoVal, DvPoint3D pos, int idx)
{	
	if(EDGE_TABLE[idx] == 0)		
		return;

	DvPoint3D cellpos[8];
	DvVertex  vertices[12];
	int px = pos.x;		int py = pos.y;		int pz = pos.z;
	
 	cellpos[0] = DvPoint3D(px,py+1,pz);
 	cellpos[1] = DvPoint3D(px+1,py+1,pz);
 	cellpos[2] = DvPoint3D(px+1,py,pz);
 	cellpos[3] = DvPoint3D(px,py,pz);
 
 	cellpos[4] = DvPoint3D(px,py+1,pz+1);
 	cellpos[5] = DvPoint3D(px+1,py+1,pz+1);
 	cellpos[6] = DvPoint3D(px+1,py,pz+1);
 	cellpos[7] = DvPoint3D(px,py,pz+1);

	///< Find vertices through edge table
	if(EDGE_TABLE[idx] & 1)		
		vertices[0] = Lerp(isoVal, cellpos[0], cellpos[1], idx);
	if(EDGE_TABLE[idx] & 2)
		vertices[1] = Lerp(isoVal, cellpos[1], cellpos[2], idx);
	if(EDGE_TABLE[idx] & 4)
		vertices[2] = Lerp(isoVal, cellpos[2], cellpos[3], idx);
	if(EDGE_TABLE[idx] & 8)
		vertices[3] = Lerp(isoVal, cellpos[3], cellpos[0], idx);

	if(EDGE_TABLE[idx] & 16)
		vertices[4] = Lerp(isoVal, cellpos[4], cellpos[5], idx);
	if(EDGE_TABLE[idx] & 32)
		vertices[5] = Lerp(isoVal, cellpos[5], cellpos[6], idx);
	if(EDGE_TABLE[idx] & 64)
		vertices[6] = Lerp(isoVal, cellpos[6], cellpos[7], idx);
	if(EDGE_TABLE[idx] & 128)
		vertices[7] = Lerp(isoVal, cellpos[7], cellpos[4], idx);
	
	if(EDGE_TABLE[idx] & 256)
		vertices[8] = Lerp(isoVal, cellpos[0], cellpos[4], idx);
	if(EDGE_TABLE[idx] & 512)
		vertices[9] = Lerp(isoVal, cellpos[1], cellpos[5], idx);
	if(EDGE_TABLE[idx] & 1024)
		vertices[10] = Lerp(isoVal, cellpos[2], cellpos[6], idx);
	if(EDGE_TABLE[idx] & 2048)
		vertices[11] = Lerp(isoVal, cellpos[3], cellpos[7], idx);

	///< Triangulation
	static int facenum = 0;
	for(int i = 0; TRIANGLE_TABLE[idx][i] != 255; i+=3)
	{
		///< Set face
		DvFace f;
		f.vIdx[0] = TRIANGLE_TABLE[idx][i];
		f.vIdx[1] = TRIANGLE_TABLE[idx][i+1];
		f.vIdx[2] = TRIANGLE_TABLE[idx][i+2];

		///< Set Position
		DvVertex q[3];
		q[0] = vertices[f.vIdx[0]];
		q[1] = vertices[f.vIdx[1]];
		q[2] = vertices[f.vIdx[2]];
		
		f.vIdx[0] = facenum;
		f.vIdx[1] = facenum + 1;
		f.vIdx[2] = facenum + 2;
		facenum += 3;

		///< Push
		m_VolumeObject.FaceList.push_back( f );
		m_VolumeObject.VertList.push_back( q[0] );
		m_VolumeObject.VertList.push_back( q[1] );
		m_VolumeObject.VertList.push_back( q[2] );
	}
}

/*!
	\brief
		Linear interpolation
*/
template<class DataType>
DvVertex DvMarchingCube<DataType>::Lerp(DataType isoVal, DvPoint3D cell1, DvPoint3D cell2, int idx)
{
	DvVertex q;

	float val1 = (float) (m_Data->At(cell1.x, cell1.y, cell1.z));
	float val2 = (float) (m_Data->At(cell2.x, cell2.y, cell2.z));

	float t = ((float)isoVal - val1) / (val2 - val1);

	q.P[0] = (float)cell1.x + t * ((float)cell2.x - (float)cell1.x);
	q.P[1] = (float)cell1.y + t * ((float)cell2.y - (float)cell1.y);
	q.P[2] = (float)cell1.z + t * ((float)cell2.z - (float)cell1.z);

	///< Find normals - cell1 normal
	float normals1[3];
	normals1[0] = (float) (m_Data->At(cell1.x+1, cell1.y, cell1.z)) - (float) (m_Data->At(cell1.x-1, cell1.y, cell1.z));
	normals1[1] = (float) (m_Data->At(cell1.x, cell1.y+1, cell1.z)) - (float) (m_Data->At(cell1.x, cell1.y-1, cell1.z));
	normals1[2] = (float) (m_Data->At(cell1.x, cell1.y, cell1.z+1)) - (float) (m_Data->At(cell1.x, cell1.y, cell1.z-1));

	///< Find normals - cell2 normal
	float normals2[3];
	normals2[0] = (float) (m_Data->At(cell2.x+1, cell2.y, cell2.z)) - (float) (m_Data->At(cell2.x-1, cell2.y, cell2.z));
	normals2[1] = (float) (m_Data->At(cell2.x, cell2.y+1, cell2.z)) - (float) (m_Data->At(cell2.x, cell2.y-1, cell2.z));
	normals2[2] = (float) (m_Data->At(cell2.x, cell2.y, cell2.z+1)) - (float) (m_Data->At(cell2.x, cell2.y, cell2.z-1));
	
	//< Interpolation normal
	q.N[0] = normals1[0] + t * (normals2[0] - normals1[0]);
	q.N[1] = normals1[1] + t * (normals2[1] - normals1[1]);
	q.N[2] = normals1[2] + t * (normals2[2] - normals1[2]);
//	cout << q.N[0] << "," << q.N[1] << "," << q.N[2] << endl;

	///< Normalized
	float norm = sqrt(q.N[0] * q.N[0] + q.N[1] * q.N[1] + q.N[2] * q.N[2]);
	q.N[0] /= norm;
	q.N[1] /= norm;
	q.N[2] /= norm;

//	if(cell2.z != m_Data->GetExtent(2) - 1 || cell2.z != m_Data->GetExtent(2) - 1){
		q.N[0] *= -1.0;
		q.N[1] *= -1.0;
		q.N[2] *= -1.0;
//	}
	
	return q;
}

/*!
	\brief
		Get the Display List
*/
template<class DataType>
int DvMarchingCube<DataType>::GetDisplayList()
{	
	GLint objID = glGenLists(1);
	glNewList(objID, GL_COMPILE);

	///< Compute center position
	GetCenterPosition();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);
	for(int i = 0; i < m_VolumeObject.FaceList.size(); i++)
	{
		int idx0, idx1, idx2;
		idx0 = m_VolumeObject.FaceList[i].vIdx[0];
		idx1 = m_VolumeObject.FaceList[i].vIdx[1];
		idx2 = m_VolumeObject.FaceList[i].vIdx[2];

		glNormal3fv( m_VolumeObject.VertList[idx0].N );
		glVertex3fv( m_VolumeObject.VertList[idx0].P );
		glNormal3fv( m_VolumeObject.VertList[idx1].N );
		glVertex3fv( m_VolumeObject.VertList[idx1].P );
		glNormal3fv( m_VolumeObject.VertList[idx2].N );
		glVertex3fv( m_VolumeObject.VertList[idx2].P );
	}
	glEnd();

	glEndList();
	
	return objID;
}

/*!
	\brief
		Get a Center Position
*/
template<class DataType>
DvVertex DvMarchingCube<DataType>::GetCenterPosition()
{
	float min[3];
	min[0] = m_VolumeObject.VertList[0].P[0];
	min[1] = m_VolumeObject.VertList[0].P[1];
	min[2] = m_VolumeObject.VertList[0].P[2];

	float max[3];
	max[0] = m_VolumeObject.VertList[0].P[0];
	max[1] = m_VolumeObject.VertList[0].P[1];
	max[2] = m_VolumeObject.VertList[0].P[2];

	for(int i = 0; i < m_VolumeObject.VertList.size(); i++) {
		if(min[0] >= m_VolumeObject.VertList[i].P[0])	min[0] =m_VolumeObject.VertList[i].P[0];
		if(min[1] >= m_VolumeObject.VertList[i].P[1])	min[1] =m_VolumeObject.VertList[i].P[1];
		if(min[2] >= m_VolumeObject.VertList[i].P[2])	min[2] =m_VolumeObject.VertList[i].P[2];

		if(max[0] < m_VolumeObject.VertList[i].P[0])	max[0] = m_VolumeObject.VertList[i].P[0];
		if(max[1] < m_VolumeObject.VertList[i].P[1])	max[1] = m_VolumeObject.VertList[i].P[1];
		if(max[2] < m_VolumeObject.VertList[i].P[2])	max[2] = m_VolumeObject.VertList[i].P[2];
	}

	DvVertex centerPos;
	centerPos.P[0] = (min[0] + max[0]) * 0.5f;
	centerPos.P[1] = (min[1] + max[1]) * 0.5f;
	centerPos.P[2] = (min[2] + max[2]) * 0.5f;

	cout << "[App Control] : Bounding Box Min : " << min[0] << ", " << min[1] << ", " << min[2] << endl;
	cout << "[App Control] : Bounding Box Max : " << max[0] << ", " << max[1] << ", " << max[2] << endl;

	glTranslatef(-centerPos.P[0], -centerPos.P[1], -centerPos.P[2]);

	///< Bounding Cube
	glDisable(GL_LIGHTING);
	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(min[0], min[1], min[2]);		// 0
	glVertex3f(max[0], min[1], min[2]);		// 1
	glVertex3f(max[0], max[1], min[2]);		// 2
	glVertex3f(min[0], max[1], min[2]);		// 3
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3f(min[0], min[1], max[2]);		// 4
	glVertex3f(max[0], min[1], max[2]);		// 5
	glVertex3f(max[0], max[1], max[2]);		// 6
	glVertex3f(min[0], max[1], max[2]);		// 7
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(min[0], min[1], min[2]);		// 0
	glVertex3f(min[0], min[1], max[2]);		// 4
	glVertex3f(max[0], min[1], min[2]);		// 1
	glVertex3f(max[0], min[1], max[2]);		// 5
	glVertex3f(max[0], max[1], min[2]);		// 2
	glVertex3f(max[0], max[1], max[2]);		// 6
	glVertex3f(min[0], max[1], min[2]);		// 3
	glVertex3f(min[0], max[1], max[2]);		// 7
	glEnd();
	glEnable(GL_LIGHTING);

	return centerPos;
}

