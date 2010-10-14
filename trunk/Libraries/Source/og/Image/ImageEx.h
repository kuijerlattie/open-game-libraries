// ==============================================================================
//! @file
//! @brief	Image Loading
//! @author	Santo Pfingsten (TTK-Bandit)
//! @note	Copyright (C) 2007-2010 Lusito Software
// ==============================================================================
//
// The Open Game Libraries.
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
// ==============================================================================

#ifndef __OG_IMAGE_EX_H__
#define __OG_IMAGE_EX_H__

#include <og/Shared/Shared.h>
#include <og/Common/Common.h>

namespace og {
	extern FileSystemCore *imageFS;

	/*
	==============================================================================

	  ImageEx

	==============================================================================
	*/
	class ImageEx : public Image {
	public:
		// ---------------------- Public Image Interface -------------------

		void	BindTexture( void ) const;
		uInt	GetWidth( void ) const { return width; }
		uInt	GetHeight( void ) const { return height; }

		// ---------------------- Internal ImageEx Members -------------------

	public:
		ImageEx() : glTextureNum(0) {}
		~ImageEx();

	private:
		friend class ImageFileNoDXT;
		friend class ImageFileDDS;
		friend class ImageFileJPG;
		friend class Image;

		bool	UploadImage( const char *filename );
		bool	ReloadImage( bool force );

		String	fullpath;
		uInt	glTextureNum;
		uInt	width, height;
		bool	mipmap;
		time_t	time;

		static bool	denyPrecompressed;
		static int	roundDownLimit;
		static int	picmip;
		static int	minFilter;
		static int	magFilter;
		static int	maxTextureSize;
		static int	jpegQuality;
	};

	/*
	==============================================================================

	  ImageFile

	==============================================================================
	*/
	class ImageFile {
	public:
		ImageFile() {}
		virtual ~ImageFile() {}

		virtual bool	UploadFile( const char *filename, ImageEx &image ) = 0;
		virtual bool	SaveFile( const char *filename, byte *data, uInt width, uInt height, bool hasAlpha ) = 0;
	};

	/*
	==============================================================================

	  ImageFileNoDXT

	==============================================================================
	*/
	class ImageFileNoDXT : public ImageFile {
	public:
		ImageFileNoDXT() { curBuffer = 0; }

		bool	UploadFile( const char *filename, ImageEx &image );

	protected:
		uInt	width;
		uInt	height;
		bool	hasAlpha;

		DynBuffer<byte> dynBuffers[2];
		int		curBuffer;

		void	ResampleAsNeeded( void );
		void	ResampleFast( uInt newWidth, uInt newHeight );

		virtual bool	Open( const char *filename ) = 0;
	};

	/*
	==============================================================================

	  ImageFileTGA

	==============================================================================
	*/
	class ImageFileTGA : public ImageFileNoDXT {
	public:
		bool	SaveFile( const char *filename, byte *data, uInt width, uInt height, bool hasAlpha );

	private:
		bool	Open( const char *filename );
		bool	ReadType2( File *file, bool topDown );
		bool	ReadType3( File *file, bool topDown );
		bool	ReadType10( File *file, bool topDown );
	};

	/*
	==============================================================================

	  ImageFilePNG

	==============================================================================
	*/
	class ImageFilePNG : public ImageFileNoDXT {
	public:
		bool	SaveFile( const char *filename, byte *data, uInt width, uInt height, bool hasAlpha );

	private:
		bool	Open( const char *filename );
	};

	/*
	==============================================================================

	  ImageFileJPG

	==============================================================================
	*/
	class ImageFileJPG : public ImageFileNoDXT {
	public:
		bool	SaveFile( const char *filename, byte *data, uInt width, uInt height, bool hasAlpha );

	private:
		bool	Open( const char *filename );
	};

	/*
	==============================================================================

	  ImageFileDDS

	==============================================================================
	*/
	class ImageFileDDS : public ImageFile {
	public:
		bool	UploadFile( const char *filename, ImageEx &image );
		bool	SaveFile( const char *filename, byte *data, uInt width, uInt height, bool hasAlpha );

	private:
		bool	Open( const char *filename );

		uInt	width;
		uInt	height;
		uInt	dxtFormat;

		DynBuffer<byte> dynBuffer;
		uInt	numMipmaps;
	};
}
#endif