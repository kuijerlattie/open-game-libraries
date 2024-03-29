// ==============================================================================
//! @file
//! @brief	FileSystemCore Interface
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

#ifndef __OG_FILESYSTEM_CORE_H__
#define __OG_FILESYSTEM_CORE_H__

#include <time.h>
#include <og/Shared.h>
#include <og/Shared/File.h>

//! Open Game Libraries
namespace og {
//! @defgroup Shared Shared (Library)
//! @{

	// ==============================================================================
	//! List of files
	//!
	//! returned by FS->GetFileList()
	// ==============================================================================
	class FileList {
	public:
		// ==============================================================================
		//! Get the filename of the specified index
		//!
		//! @param index The file index
		//!
		//! @return	The filename
		// ==============================================================================
		virtual const char *GetName( int index ) = 0;

		// ==============================================================================
		//! Get Number of files
		//!
		//! @return	number of files
		// ==============================================================================
		virtual int			Num( void ) = 0;
	};

	// ==============================================================================
	//! File list flags
	// ==============================================================================
	enum ListFlags {
		LF_DIRS				= BIT(0),	//!< List directories (directories will have a trailing "/").
		LF_FILES			= BIT(1),	//!< List files.
		LF_CHECK_SUBDIRS	= BIT(2),	//!< Dive into subdirectories.
		LF_CHECK_LOCAL		= BIT(3),	//!< List local files.
		LF_CHECK_ARCHIVED	= BIT(4),	//!< List archived files.
		LF_CHECK_UNPURE		= BIT(5),	//!< List also pure files.
		LF_REMOVE_DIR		= BIT(6),	//!< Removes only first directory, not sub dirs.

		LF_DEFAULT			= (LF_FILES | LF_CHECK_SUBDIRS | LF_CHECK_LOCAL
								| LF_CHECK_ARCHIVED), //!< Default flags
	};

	// ==============================================================================
	//! FileSystemCore interface.
	//!
	//! Global file access
	//! @note	og::ThreadSafetyClass = og::TSC_MULTIPLE
	//! @note	These methods must be callable from multiple threads at the same time.
	//!			Make sure that is possible if you provide your own filesystem.
	// ==============================================================================
	class FileSystemCore {
	public:
		// ==============================================================================
		//! Open a file for writing
		//!
		//! @param	filename		The file path
		//! @param	pure			Use internal file management
		//! @param	buffered		Read whole file into memory for faster reading.
		//!
		//! @return	Pointer to a new File object on success, otherwise NULL
		// ==============================================================================
		virtual File *	OpenRead( const char *filename, bool pure=true, bool buffered=false ) = 0;

		// ==============================================================================
		//! Open a file for writing ( in save path if pure is true )
		//!
		//! @param	filename		The file path
		//! @param	pure			Use internal file management
		//!
		//! @return	Pointer to a new File object on success, otherwise NULL
		// ==============================================================================
		virtual File *	OpenWrite( const char *filename, bool pure=true ) = 0;

		// ==============================================================================
		//! Open a file for appending ( in save path if pure is true )
		//!
		//! @param	filename		The file path
		//! @param	pure			Use internal file management
		//!
		//! @return	Pointer to a new File object on success, otherwise NULL
		// ==============================================================================
		virtual File *	OpenAppend( const char *filename, bool pure=true ) = 0;

		// ==============================================================================
		//! Remove a file ( from save path if pure is true )
		//!
		//! @param	filename		The file path
		//! @param	pure			Use internal file management
		//!
		//! @return	true on success, otherwise false
		// ==============================================================================
		virtual bool	Remove( const char *filename, bool pure=true ) = 0;

		// ==============================================================================
		//! Rename a file ( in save path if pure is true )
		//!
		//! @param	from			The old file path
		//! @param	to				The new file path
		//! @param	pure			Use internal file management
		//!
		//! @return	true on success, otherwise false
		// ==============================================================================
		virtual bool	Rename( const char *from, const char *to, bool pure=true ) = 0;

		// ==============================================================================
		//! Get the size of a given file
		//!
		//! @param	filename		The file path
		//! @param	pure			Use internal file management
		//!
		//! @return	Size of the file if exists, otherwise -1
		// ==============================================================================
		virtual int		FileSize( const char *filename, bool pure=true ) = 0;

		// ==============================================================================
		//! Find out if a given file exists
		//!
		//! @param	filename		The file path
		//! @param	pure			Use internal file management
		//!
		//! @return	true if it exists, otherwise false
		// ==============================================================================
		virtual bool	FileExists( const char *filename, bool pure=true ) = 0;

		// ==============================================================================
		//! Find out if a given file exists in the save path ( for use before writing a file )
		//!
		//! @param	filename		The file path
		//!
		//! @return	true if it exists, otherwise false
		// ==============================================================================
		virtual bool	FileExistsInSavePath( const char *filename ) = 0;

		// ==============================================================================
		//! Get the file modification time
		//!
		//! @param	filename		The file path
		//! @param	pure			Use internal file management
		//!
		//! @return	The time in seconds (since 1.1.1970), when the file has been modified last
		// ==============================================================================
		virtual time_t	FileTime( const char *filename, bool pure=true ) = 0;

		// ==============================================================================
		//! Load the file into a buffer
		//!
		//! @param	path		The file path
		//! @param	buffer		The buffer to write
		//! @param	size		The size of the buffer
		//! @param	pure		Use internal file management
		//!
		//! @return	true on success, otherwise false
		//!
		//!	@note	You need to free it when you're done.
		// ==============================================================================
		virtual bool	StoreFile( const char *path, byte *buffer, int size, bool pure=true ) = 0;

		// ==============================================================================
		//! Load the file into a buffer
		//!
		//! @param	path		The file path
		//! @param	buffer		Pointer to a byte array, gets set by the function
		//! @param	pure		Use internal file management
		//! @param	pakFileName	A destination string for the pak file name the found file is in (optional, can be NULL)
		//!
		//! @return	The files size on success, otherwise -1
		//!
		//!	@note	You need to free it when you're done.
		// ==============================================================================
		virtual int		LoadFile( const char *path, byte **buffer, bool pure=true, String *pakFileName=NULL ) = 0;

		// ==============================================================================
		//! Free a file buffer previously created by LoadFile
		//!
		//! @param	buffer	The buffer to free
		// ==============================================================================
		virtual void	FreeFile( byte *buffer ) = 0;

		// ==============================================================================
		//! Create a path, if it doesn't exist already
		//!
		//! @param	path		Path
		//! @param	pure		Use internal file management
		//!
		//! @return	true if it succeeds, false if it fails
		// ==============================================================================
		virtual bool	MakePath( const char *path, bool pure=true ) = 0;

		// Retrieve file lists
		// ==============================================================================
		//! Find files and or directories in the local filesystem
		//!
		//! @param	dir			The directory to search in
		//! @param	extension	The file extension to look for
		//! @param	flags		The flags to use
		//!
		//! @return	NULL if it fails, else the file list. 
		//!
		//! @see	ListFlags
		// ==============================================================================
		virtual FileList *GetFileList( const char *dir, const char *extension, int flags=LF_DEFAULT ) = 0;

		// ==============================================================================
		//! Free a file list previously created by GetFileList
		//!
		//! @param	list	The list to free
		// ==============================================================================
		virtual void	FreeFileList( FileList *list ) = 0;
	};

//! @}
}
#endif
