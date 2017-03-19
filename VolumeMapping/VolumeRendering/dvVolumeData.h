#ifndef DVVOLUMEDATA_H 
#define DVVOLUMEDATA_H

///< System header files
#include "dvCommon.h"

///< templete declaration
template<class DataType> class DvVolume;

/*!
	\brief
		a class for Volume data (raw data)
*/
template<class DataType>
class DvVolume
{
public:
	typedef DataType value_type;

	/* Constructor & Destructor */  
	DvVolume();
	virtual ~DvVolume();

	/* Member functions */
	inline void		Init(int width, int height, int depth, int dim);
	inline void		ReadRawFile(const char *filename);
	inline int		GetExtent(int index) const;
	inline int		GetSize()   const;
	inline int		GetWidth()  const;
	inline int		GetHeight() const;
	inline int		GetDepth()  const;
	inline DataType	&At(int px, int py, int pz, int pn = 0) const;

	/* Operator */
	inline operator DataType &();
	inline operator const DataType &() const;
	inline operator DataType *() ;
	inline operator const DataType *() const;

private:
	/* Member variables */
	DataType	*m_Data;				///< data pointer
	int			m_Dimension;			///< demesion of element
	int			m_Width;				///< size of width
	int			m_Height;				///< size of height
	int			m_Depth;				///< size of depth
	int			m_VolumeExtent[3];		///< size of volume
};

#include "dvVolumeData.inl"

#endif	//DVVOLUMEDATA_H
