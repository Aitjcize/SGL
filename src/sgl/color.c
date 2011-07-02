/**
 * @file   color.c
 *
 * Copyright (C) 2011 - SGL Authors <aitjcize@gmail.com>
 * All Rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * BRIAN PAUL BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "color.h"

#include <string.h>

#include "macros.h"

void _sgl_init_color(struct sgl_context* ctx)
{
  ctx->color.clear = 0;

  int i = 0;
  for (i = 0; i < ctx->buffer.width * ctx->buffer.height; ++i)
    *((GLuint*)ctx->drawbuffer->clear_color_buf.data + i) = ctx->color.clear;
}


void glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
  GET_CURRENT_CONTEXT(ctx);
  ctx->color.clear = COLOR_FE(red, green, blue, alpha);

  int i = 0;
  for (i = 0; i < ctx->buffer.width * ctx->buffer.height; ++i)
    *((GLuint*)ctx->drawbuffer->clear_color_buf.data + i) = ctx->color.clear;
}
