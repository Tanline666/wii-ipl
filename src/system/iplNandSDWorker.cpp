#include <decomp.h>

#include "system/iplNandSDWorker.h"

#include "iplSystem.h"
#include "revolution/net/NETDigest.h"
#include "revolution/types.h"

#include <revolution.h>

typedef struct SMetaBlockHeader {
    char sig[4];   // 0x00
    u32 headSize;  // 0x04
    u32 version;   // 0x08 (always 3)
} SMetaBlockHeader;

namespace ipl {
    BOOL NandSDWorker::check_header_base(const u8* bnrData, u32* headerSize) {
        SMetaBlockHeader* header = (SMetaBlockHeader*)(bnrData);

        u32 headSize = header->headSize;
        if (headerSize != NULL) {
            *headerSize = headSize;
        }

        // Check signature
        if (!NAND_CHECK_MAGIC4(header->sig, 'I', 'M', 'E', 'T') || headSize < sizeof(channel::SMetaBlockHeader)) {
            OSReport("BANNER WARNING: invalid signature or header size %d\n", headSize);
            return FALSE;
        }

        // Check version
        if (header->version != channel::META_CURRENT_VERSION) {
            OSReport("BANNER WARNING: different version v.%d ( now v.%d)\n", header->version, channel::META_CURRENT_VERSION);
            return FALSE;
        }

        return TRUE;
    }
    BOOL NandSDWorker::check_md5(const u8* sum, const u8* buffer, u32 length) {
        NETMD5Sum md5;
        NETCalcMD5(md5, buffer, length);

        for (int i = 0; i < NET_MD5_DIGEST_SIZE; i++) {
            if (md5[i] != sum[i]) {
                OSReport("BANNER WARNING: invalid md5 value ( data )\n");
                return FALSE;
            }
        }
        return TRUE;
        }
}  // namespace ipl
