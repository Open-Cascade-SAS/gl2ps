/* $Id: gl2ps.h,v 1.81 2004-03-06 02:32:34 geuzaine Exp $ */
/*
 * GL2PS, an OpenGL to PostScript Printing Library
 * Copyright (C) 1999-2004 Christophe Geuzaine <geuz@geuz.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of either:
 *
 * a) the GNU Library General Public License as published by the Free
 * Software Foundation, either version 2 of the License, or (at your
 * option) any later version; or
 *
 * b) the GL2PS License as published by Christophe Geuzaine, either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See either
 * the GNU Library General Public License or the GL2PS License for
 * more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library in the file named "COPYING.LGPL";
 * if not, write to the Free Software Foundation, Inc., 675 Mass Ave,
 * Cambridge, MA 02139, USA.
 *
 * You should have received a copy of the GL2PS License with this
 * library in the file named "COPYING.GL2PS"; if not, I will be glad
 * to provide one.
 *
 * For the latest info about gl2ps, see http://www.geuz.org/gl2ps/.
 * Please report all bugs and problems to <gl2ps@geuz.org>.
 */

#ifndef __GL2PS_H__
#define __GL2PS_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* To generate a Windows dll, define GL2PSDLL at compile time */

#ifdef _WIN32
/* Shut up warning due to bad windows header file */
#  if defined(_MSC_VER) 
#    pragma warning(disable:4115)
#  endif
#  include <windows.h>
#  ifdef GL2PSDLL
#    ifdef GL2PSDLL_EXPORTS
#      define GL2PSDLL_API __declspec(dllexport)
#    else
#      define GL2PSDLL_API __declspec(dllimport)
#    endif
#  else
#    define GL2PSDLL_API
#  endif
#else
#  define GL2PSDLL_API
#endif

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#else
#  include <GL/gl.h>
#endif

/* Support for compressed PDF */

#if defined(HAVE_ZLIB) || defined(HAVE_LIBZ) || defined(GL2PS_HAVE_ZLIB)
#  include <zlib.h>
#  ifndef GL2PS_HAVE_ZLIB
#    define GL2PS_HAVE_ZLIB
#  endif
#endif

/* Version number */

#define GL2PS_MAJOR_VERSION 1
#define GL2PS_MINOR_VERSION 2
#define GL2PS_PATCH_VERSION 0

#define GL2PS_VERSION (GL2PS_MAJOR_VERSION + \
                       0.01 * GL2PS_MINOR_VERSION + \
                       0.0001 * GL2PS_PATCH_VERSION)

/* Output file format */

#define GL2PS_PS  1
#define GL2PS_EPS 2
#define GL2PS_TEX 3
#define GL2PS_PDF 4

/* Sorting algorithms */

#define GL2PS_NO_SORT     1
#define GL2PS_SIMPLE_SORT 2
#define GL2PS_BSP_SORT    3

/* Options for gl2psBeginPage */

#define GL2PS_NONE                 0
#define GL2PS_DRAW_BACKGROUND      (1<<0)
#define GL2PS_SIMPLE_LINE_OFFSET   (1<<1)
#define GL2PS_SILENT               (1<<2)
#define GL2PS_BEST_ROOT            (1<<3)
#define GL2PS_OCCLUSION_CULL       (1<<4)
#define GL2PS_NO_TEXT              (1<<5)
#define GL2PS_LANDSCAPE            (1<<6)
#define GL2PS_NO_PS3_SHADING       (1<<7)
#define GL2PS_NO_PIXMAP            (1<<8)
#define GL2PS_USE_CURRENT_VIEWPORT (1<<9)
#define GL2PS_COMPRESS             (1<<10)

/* Arguments for gl2psEnable/gl2psDisable */

#define GL2PS_POLYGON_OFFSET_FILL 1
#define GL2PS_POLYGON_BOUNDARY    2
#define GL2PS_LINE_STIPPLE        3
#define GL2PS_BLEND               4

/* Magic numbers */

#define GL2PS_EPSILON             5.0e-3F
#define GL2PS_DEPTH_FACT          1000.0F
#define GL2PS_SIMPLE_OFFSET       0.05F
#define GL2PS_SIMPLE_OFFSET_LARGE 1.0F
#define GL2PS_ZERO(arg)           (fabs(arg)<1.e-20)
#define GL2PS_FIXED_XREF_ENTRIES  7 

/* Message levels and error codes */

#define GL2PS_SUCCESS       0
#define GL2PS_INFO          1
#define GL2PS_WARNING       2
#define GL2PS_ERROR         3
#define GL2PS_NO_FEEDBACK   4
#define GL2PS_OVERFLOW      5
#define GL2PS_UNINITIALIZED 6

/* Primitive types */

#define GL2PS_NOTYPE     -1
#define GL2PS_TEXT       1
#define GL2PS_POINT      2
#define GL2PS_LINE       3
#define GL2PS_QUADRANGLE 4
#define GL2PS_TRIANGLE   5
#define GL2PS_PIXMAP     6

/* Text alignment */

#define GL2PS_TEXT_C     1
#define GL2PS_TEXT_CL    2
#define GL2PS_TEXT_CR    3
#define GL2PS_TEXT_B     4
#define GL2PS_TEXT_BL    5
#define GL2PS_TEXT_BR    6
#define GL2PS_TEXT_T     7
#define GL2PS_TEXT_TL    8
#define GL2PS_TEXT_TR    9

/* BSP tree primitive comparison */

#define GL2PS_COINCIDENT  1
#define GL2PS_IN_FRONT_OF 2
#define GL2PS_IN_BACK_OF  3
#define GL2PS_SPANNING    4

/* 2D BSP tree primitive comparison */

#define GL2PS_POINT_COINCIDENT 0
#define GL2PS_POINT_INFRONT    1
#define GL2PS_POINT_BACK       2

/* Pass through options */

#define GL2PS_BEGIN_POLYGON_OFFSET_FILL 1
#define GL2PS_END_POLYGON_OFFSET_FILL   2
#define GL2PS_BEGIN_POLYGON_BOUNDARY    3
#define GL2PS_END_POLYGON_BOUNDARY      4
#define GL2PS_BEGIN_LINE_STIPPLE        5
#define GL2PS_END_LINE_STIPPLE          6
#define GL2PS_SET_POINT_SIZE            7
#define GL2PS_SET_LINE_WIDTH            8
#define GL2PS_BEGIN_BLEND               9
#define GL2PS_END_BLEND                10
#define GL2PS_SRC_BLEND                11
#define GL2PS_DST_BLEND                12

typedef enum {
  T_UNDEFINED    = -1,
  T_CONST_COLOR  = 1,
  T_VAR_COLOR    = 1<<1,
  T_ALPHA_1      = 1<<2,
  T_ALPHA_LESS_1 = 1<<3,
  T_VAR_ALPHA    = 1<<4
} GL2PS_TRIANGLE_PROPERTY;

typedef GLfloat GL2PSrgba[4];
typedef GLfloat GL2PSxyz[3];
typedef GLfloat GL2PSplane[4];

typedef struct _GL2PSbsptree2d GL2PSbsptree2d;

struct _GL2PSbsptree2d {
  GL2PSplane plane;
  GL2PSbsptree2d *front, *back;
};

typedef struct {
  GLint nmax, size, incr, n;
  char *array;
} GL2PSlist;

typedef struct _GL2PSbsptree GL2PSbsptree;

struct _GL2PSbsptree {
  GL2PSplane plane;
  GL2PSlist *primitives;
  GL2PSbsptree *front, *back;
};

typedef struct {
  GL2PSxyz xyz;
  GL2PSrgba rgba;
} GL2PSvertex;

typedef struct {
  GL2PSvertex vertex[3];
  GL2PS_TRIANGLE_PROPERTY prop;
} GL2PStriangle;

typedef struct {
  GLshort fontsize;
  char *str, *fontname;
  GLint alignment;
} GL2PSstring;

typedef struct {
  GLsizei width, height;
  GLenum format, type;
  GLfloat *pixels;
} GL2PSimage;

typedef struct {
  GLshort type, numverts;
  char boundary, dash, culled;
  GLfloat width, depth;
  GL2PSvertex *verts;
  union {
    GL2PSstring *text;
    GL2PSimage *image;
  } data;
} GL2PSprimitive;

typedef struct {
#ifdef GL2PS_HAVE_ZLIB
  Bytef *dest, *src, *start;
  uLongf destLen, srcLen;
#else
  int dummy;
#endif
} GL2PScompress;

typedef struct{
  GL2PSlist* ptrlist;
  int gsno, fontno, imno, shno, maskshno, trgroupno;
  int gsobjno, fontobjno, imobjno, shobjno, maskshobjno, trgroupobjno;
} GL2PSpdfgroup;

typedef struct {
  /* General */
  GLint format, sort, options, colorsize, colormode, buffersize;
  char *title, *producer, *filename;
  GLboolean boundary;
  GLfloat *feedback, offset[2], lastlinewidth;
  GLint viewport[4];
  GLenum blendfunc[2];
  GLboolean blending;
  GL2PSrgba *colormap, lastrgba, threshold;
  GL2PSlist *primitives;
  FILE *stream;
  GL2PScompress *compress;

  /* BSP-specific */
  GLint maxbestroot;

  /* Occlusion culling-specific */
  GLboolean zerosurfacearea;
  GL2PSbsptree2d *imagetree;
  GL2PSprimitive *primitivetoadd;
  
  /* PDF-specific */
  int streamlength;
  GL2PSlist *pdfprimlist, *pdfgrouplist;
  int *xreflist;
  int objects_stack; /* available objects */
  int extgs_stack; /* graphics state object number */
  int font_stack; /* font object number */
  int im_stack; /* image object number */
  int trgroupobjects_stack; /* xobject numbers */
  int shader_stack; /* shader object numbers */
  int mshader_stack; /* mask shader object numbers */
} GL2PScontext;

/* Private prototypes */

GLint gl2psPrintPrimitives(void);

/* Public functions */

#ifdef __cplusplus
extern "C" {
#endif

GL2PSDLL_API GLint gl2psBeginPage(const char *title, const char *producer, 
                                  GLint viewport[4], GLint format, GLint sort,
                                  GLint options, GLint colormode,
                                  GLint colorsize, GL2PSrgba *colormap, 
                                  GLint nr, GLint ng, GLint nb, GLint buffersize,
                                  FILE *stream, const char *filename);
GL2PSDLL_API GLint gl2psEndPage(void);
GL2PSDLL_API GLint gl2psBeginViewport(GLint viewport[4]);
GL2PSDLL_API GLint gl2psEndViewport(void);
GL2PSDLL_API GLint gl2psText(const char *str, const char *fontname, GLshort fontsize);
GL2PSDLL_API GLint gl2psDrawPixels(GLsizei width, GLsizei height,
                                   GLint xorig, GLint yorig,
                                   GLenum format, GLenum type, const void *pixels);
GL2PSDLL_API GLint gl2psEnable(GLint mode);
GL2PSDLL_API GLint gl2psDisable(GLint mode);
GL2PSDLL_API GLint gl2psPointSize(GLfloat value);
GL2PSDLL_API GLint gl2psLineWidth(GLfloat value);
GL2PSDLL_API GLint gl2psBlendFunc(GLenum sfactor, GLenum dfactor);

/* Undocumented */
GL2PSDLL_API GLint gl2psTextOpt(const char *str, const char *fontname, GLshort fontsize,
                                GLint align, GL2PSrgba color);

#ifdef __cplusplus
};
#endif

#endif /* __GL2PS_H__ */
