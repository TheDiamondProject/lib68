/*
 * Copyright (c) 2019 Tom Hancocks, The Diamond Project
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#if !defined(lib68_Endian)
#	if defined(__clang__)
#	elif defined(__GNUC__) || defined(__GNUG__)
#		if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#			define __LITTLE_ENDIAN__
#		elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#			define __BIG_ENDIAN
#		else
#			error Unsupported architecture.
#		endif
#	else
#		error Compiler not supported.	
#	endif

#	if defined(__BIG_ENDIAN__)
#		define TO_BIG_WORD(_V) (_V)
#		define TO_BIG_LONG(_V) (_V)
#		define FROM_BIG_WORD(_V) (_V)
#		define FROM_BIG_LONG(_V) (_V)
#	elif defined(__LITTLE_ENDIAN__)
#		define TO_BIG_WORD(_V) (((_V & 0xFF00) >> 8) | ((_V & 0x00FF) << 8))
#		define TO_BIG_LONG(_V) (((_V & 0xFF000000) >> 24) | ((_V & 0x000000FF) << 24) | ((_V & 0x0000FF00) << 8) | ((_V & 0x00FF0000) >> 8))
#		define FROM_BIG_WORD(_V) TO_BIG_WORD((_V))
#		define FROM_BIG_LONG(_V) TO_BIG_LONG((_V))
#	endif

#endif