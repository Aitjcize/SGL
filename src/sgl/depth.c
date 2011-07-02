/**
 * @file   depth.c
 *
 * Copyright (C) 2011 - SGL Authors <aitjcize@gmail.com>
 * All Rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "depth.h"

#include <string.h>

#include "context.h"
#include "logging.h"
#include "macros.h"

void _sgl_init_depth(struct sgl_context* ctx)
{
  ctx->depth.test = GL_FALSE;
  ctx->depth.clear = 1.0;
  ctx->depth.func = GL_LESS;
  ctx->depth.mask = GL_TRUE;

  int i = 0;
  for (i = 0; i < ctx->buffer.width * ctx->buffer.height; ++i)
    *((GLfloat*)ctx->drawbuffer->clear_depth_buf.data + i) = ctx->depth.clear;

  memcpy(ctx->drawbuffer->depth_buf.data,
         ctx->drawbuffer->clear_depth_buf.data,
         ctx->buffer.width * ctx->buffer.height * sizeof(GLfloat));
}

void glClearDepth(GLclampd depth)
{
  GET_CURRENT_CONTEXT(ctx);
  ASSERT_OUTSIDE_BEGIN_END(ctx);

  depth = CLAMP(depth, 0.0, 1.0);

  if (ctx->depth.clear == depth)
    return;

  ctx->depth.clear = depth;

  int i = 0;
  for (i = 0; i < ctx->buffer.width * ctx->buffer.height; ++i)
    *((GLfloat*)ctx->drawbuffer->clear_depth_buf.data + i) = ctx->depth.clear;
}

void glClearDepthf(GLclampf depth)
{
  glClearDepth(depth);
}

void glDepthFunc(GLenum func)
{
  GET_CURRENT_CONTEXT(ctx);
  ASSERT_OUTSIDE_BEGIN_END(ctx);

  switch (func) {
  case GL_LESS:    /* (default) pass if incoming z < stored z */
  case GL_GEQUAL:
  case GL_LEQUAL:
  case GL_GREATER:
  case GL_NOTEQUAL:
  case GL_EQUAL:
  case GL_ALWAYS:
  case GL_NEVER:
    break;
  default:
    _sgl_error(ctx, GL_INVALID_ENUM, "glDepth.Func");
    return;
  }

  if (ctx->depth.func == func)
    return;

  ctx->depth.func = func;
}

void glDepthMask(GLboolean flag)
{
  GET_CURRENT_CONTEXT(ctx);
  ASSERT_OUTSIDE_BEGIN_END(ctx);
  ctx->depth.mask = flag;
}
