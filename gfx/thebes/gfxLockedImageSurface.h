/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef GFXLOCKEDIMAGESURFACE_H
#define GFXLOCKEDIMAGESURFACE_H

#include "gfxImageSurface.h"
#include "mozilla/VolatileBuffer.h"

/*
 * This is just a gfxImageSurface which will unlock the buffer on destruction
 */

class gfxLockedImageSurface : public gfxImageSurface
{
public:
    gfxLockedImageSurface(mozilla::VolatileBuffer *vbuf,
                          const gfxIntSize& size,
                          gfxImageFormat format);
    virtual ~gfxLockedImageSurface();

    static mozilla::TemporaryRef<mozilla::VolatileBuffer>
    AllocateBuffer(const gfxIntSize& size, gfxImageFormat format);
private:
    mozilla::VolatileBufferPtr<unsigned char> mVBufPtr;
};

#endif /* GFXLOCKEDIMAGESURFACE_H */
