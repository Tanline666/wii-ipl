#ifndef IPL_NAND_SD_WORKER_H
#define IPL_NAND_SD_WORKER_H

#include <revolution.h>
#include "revolution/net/NETDigest.h"

namespace ipl {
    class NandSDWorker {
    public:
        NandSDWorker();
        ~NandSDWorker();

    private:
        /**
         * @brief Verifies if the banner header is valid.
         * @param pBnrData The buffer containing the banner data.
         * @param headerSize Header file size.
         * @param sum
         * @param buffer
         * @param length
         */
        BOOL check_header_base(const u8* bnrData, u32* headerSize = NULL);
        BOOL check_md5(const u8* sum, const u8* buffer, u32 length);
    };
}  // namespace ipl

#endif  // IPL_NAND_SD_WORKER_H
