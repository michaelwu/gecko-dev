/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "gfxAlphaRecovery.h"
#include "gfxLockedImageSurface.h"
#include "mozilla/DebugOnly.h"

using namespace mozilla;

gfxLockedImageSurface::gfxLockedImageSurface(VolatileBuffer *vbuf,
                                             const gfxIntSize& size,
                                             gfxImageFormat format)
    : mVBufPtr(vbuf)
{
    MOZ_ASSERT(!mVBufPtr.WasBufferPurged(), "Expected image data!");

    long stride = ComputeStride(size, format);
    InitWithData(mVBufPtr, size, stride, format);
}

gfxLockedImageSurface::~gfxLockedImageSurface()
{
}

TemporaryRef<VolatileBuffer>
gfxLockedImageSurface::AllocateBuffer(const gfxIntSize& size,
                                      gfxImageFormat format)
{
    long stride = ComputeStride(size, format);
    RefPtr<VolatileBuffer> buf = new VolatileBuffer();
    if (buf->Init(stride * size.height,
                  1 << gfxAlphaRecovery::GoodAlignmentLog2()))
        return buf;

    return nullptr;
}
