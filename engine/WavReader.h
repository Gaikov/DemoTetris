// Copyright (c) 2003-2007, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file WavReader.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_WavReader_H_
#define	_WavReader_H_

#include "nsLib/comm_types.h"
#include "Core/Package.h"
#include "Core/headers.h"

class nsWavReader
{
public:
	nsWavReader();
	virtual ~nsWavReader();
	
	bool				Read( const char *fileName );
	void				Free();

	const WAVEFORMATEX*	GetFormat();
	const void*			GetSamples();
	uint				GetSamplesSize();

private:
	nsFile				*m_file;
	uint				m_samplesSize;

private:
	bool				Check( const char *data );

};

#endif //_WavReader_H_