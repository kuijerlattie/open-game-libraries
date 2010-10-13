/*
===========================================================================
The Open Game Libraries.
Copyright (C) 2007-2010 Lusito Software

Author:  Santo Pfingsten (TTK-Bandit)
Purpose: Basic Library stuff
-----------------------------------------

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.

3. This notice may not be removed or altered from any source distribution.
===========================================================================
*/

#ifndef __OG_COMMON_H__
#define __OG_COMMON_H__

#include <og/Shared/Shared.h>
#include <og/Shared/FileSystemCore.h>
#include <og/Shared/Thread/ThreadLocalStorage.h>

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// Public Library Includes
#include "Math/Random.h"
#include "Color.h"
#include "Hash/SecureHash.h"
#include "Hash/Hash.h"
#include "Math/Math.h"
#include "Math/Vector.h"
#include "Math/Rectangle.h"
#include "Math/Matrix.h"
#include "Math/Quat.h"
#include "Math/Angles.h"
#include "Math/Bounds.h"
#include "Text/String.h"
#include "Containers/List.h"
#include "Containers/LinkedList.h"
#include "Containers/Stack.h"
#include "Containers/HashIndex.h"
#include "Containers/StringPool.h"
#include "Containers/Dict.h"
#include "Containers/Pair.h"
#include "Containers/CmdArgs.h"
#include "Containers/DynBuffer.h"
#include "Containers/Allocator.h"
#include "Text/Lexer.h"
#include "Text/DeclParser.h"
#include "Text/XDeclParser.h"

namespace og {
	extern FileSystemCore *commonFS;
	OG_INLINE void	CommonSetFileSystem( FileSystemCore *fileSystem ) { commonFS = fileSystem; }
	
	Format &operator << ( Format &fmt, const String &value );
	Format &operator << ( Format &fmt, const Vec2 &value );
	Format &operator << ( Format &fmt, const Vec3 &value );
	Format &operator << ( Format &fmt, const Vec4 &value );
	Format &operator << ( Format &fmt, const Angles &value );
	Format &operator << ( Format &fmt, const Rect &value );
	Format &operator << ( Format &fmt, const Quat &value );
	Format &operator << ( Format &fmt, const Mat2 &value );
	Format &operator << ( Format &fmt, const Mat3 &value );
	Format &operator << ( Format &fmt, const Color &value );
}

// We include .inl files last, so we can access all classes here.
#include "Math/Random.inl"
#include "Color.inl"
#include "Math/Math.inl"
#include "Math/Vector.inl"
#include "Math/Rectangle.inl"
#include "Math/Matrix.inl"
#include "Math/Quat.inl"
#include "Math/Angles.inl"
#include "Math/Bounds.inl"
#include "Text/String.inl"
#include "Containers/List.inl"
#include "Containers/LinkedList.inl"
#include "Containers/Stack.inl"
#include "Containers/HashIndex.inl"
#include "Containers/Dict.inl"
#include "Containers/Pair.inl"
#include "Containers/DynBuffer.inl"
#include "Containers/Allocator.inl"

#endif