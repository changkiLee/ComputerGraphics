
/*!
	\brief
		Constructor
*/
template<class DataType>
DvVolume<DataType>::DvVolume()
	: m_Data( 0 )
{

}

/*!
	\brief
		Destructor
*/
template<class DataType>
DvVolume<DataType>::~DvVolume()
{
	if( m_Data != 0 )	delete [] m_Data;
}

/*!
	\brief
		Initialize member variables and memory
*/
template<class DataType>
void DvVolume<DataType>::Init(int width, int height, int depth, int dim)
{
	///< initialize variables
	m_Width		= width;
	m_Height	= height;
	m_Depth		= depth;
	m_Dimension	= dim;

	m_VolumeExtent[0] = width;
	m_VolumeExtent[1] = height;
	m_VolumeExtent[2] = depth;

	///< allocate memory
	int memSize = width * height * depth * dim;
	m_Data		= new DataType[memSize];
	memset( m_Data, 0, sizeof(DataType) * memSize );
}

/*!
	\brief
		Read the raw data from file
	\param
		filename - const file name
*/
template<class DataType>
void DvVolume<DataType>::ReadRawFile(const char *filename)
{
	assert( m_Data );

	///< read the binary file(.raw)    
	ifstream filein( filename, ios::in | ios::binary);
	if( !filein ) {
		cerr << "Unable to open raw file." << endl;
		exit(0);
	}
	filein.read( (char *)m_Data, sizeof(DataType) * m_Width * m_Height * m_Depth * m_Dimension );
	filein.close();

	cout << "[App Control] : Load '" << filename << "' !"<< endl;
	cout << "[App Control] : " << m_Width << " * " << m_Height << " * " << m_Depth << endl << endl;
}

/*!
	\brief
		Get a element at given index
*/
template<class DataType>
DataType &DvVolume<DataType>::At(int px, int py, int pz, int pn /* = 0 */) const
{
	return m_Data[ (pz * m_Width * m_Height * m_Dimension) + 
		(py * m_Width * m_Dimension) + 
		(px * m_Dimension) + pn];
}

/*!
	\brief
		Get a length at given index
*/
template<class DataType>
int DvVolume<DataType>::GetExtent( int index ) const
{
	assert( 0 <= index && index < 3 );
	return m_VolumeExtent[index];
}

/*!
	\brief
		Get a size
*/
template<class DataType>
int DvVolume<DataType>::GetSize() const
{
	return (m_Width * m_Height * m_Depth);
}

template<class DataType>
int DvVolume<DataType>::GetWidth() const
{
	return m_Width;
}

template<class DataType>
int DvVolume<DataType>::GetHeight() const
{
	return m_Height;
}

template<class DataType>
int DvVolume<DataType>::GetDepth() const
{
	return m_Depth;
}

/*!
	\brief
		Type cast operator
	\return
		a address to the data of array 
*/
template<class DataType>
DvVolume<DataType>::operator DataType &()
{
	return &m_Data;
}
template<class DataType>
DvVolume<DataType>::operator const DataType &() const
{
	return &m_Data;
}

/*!
	\brief
		Type cast operator
	\return
		a pointer to the data of array 
*/
template<class DataType>
DvVolume<DataType>::operator DataType *()
{
	return m_Data;
}
template<class DataType>
DvVolume<DataType>::operator const DataType *() const
{
	return m_Data;
}