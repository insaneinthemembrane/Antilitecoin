// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    // How many times we expect transactions after the last checkpoint to
    // be slower. This number is a compromise, as it can't be accurate for
    // every system. When reindexing from a fast disk with a slow CPU, it
    // can be up to 20, while when downloading from a slow network with a
    // fast multicore CPU, it won't be much higher than 1.
    static const double fSigcheckVerificationFactor = 5.0;

    struct CCheckpointData {
        const MapCheckpoints *mapCheckpoints;
        int64 nTimeLastCheckpoint;
        int64 nTransactionsLastCheckpoint;
        double fTransactionsPerDay;
    };

    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (     0, uint256("0x743de1f713cc7e6ee4d5ff38f907b9047f29afe46ca1e6abe0223dcc1b6ca2f7"))
        (     1, uint256("0x7d34262bc9dd865dbf4ce3d2733fc7f4ad956f99d3b3d699ca511e14875c5d45"))
        (     2, uint256("0x6e26b8c11f21d15a9555fc3e19492979f5fad888da94109505e82a79f741a202"))
        (     3, uint256("0xdb7617163bcd343d6d5874931a01f8a1df68a16d37bf78c04030178c1ee9f08a"))
        (     4, uint256("0xa2c9803c26dd4fee837419e1a5f5382b8f3a3bc4893260c4571b11ae65dadb0e"))
        (  4999, uint256("0xfa9265181cb6e2fe05cc5b4daf32d9c2e96d55627f976ef5d81b73c09b1fdc20"))
        (  5000, uint256("0x8c9dd42edc212f8c381864e9212d1ce2245a98b5d1507caeafcb539c57a345b1"))
        (  5001, uint256("0xfb18d997cbc850eaeb3f62b987e8320cb41d2caae6fb9f09b1fd84a89b906705"))
        (  5002, uint256("0x490e2403be7d42b8e3f8d407fc5008cb79438a09d8d6167c7b57d9eb85534109"))
        (  8000, uint256("0xe835440610d70fa8c544ef3b9fde2d3aa77d004d5a759ab63a0bd4c935c23783"))
        (  9999, uint256("0x2d899771d10f7d5b59c52c07a456cf8175a605e5803a49a654a13765708089fa"))
        ( 10000, uint256("0xc150f0639c9548dd1e1be195d22c2d4b640d94cd7a3bda98dc7fe281c2927175"))
        ( 10001, uint256("0x54a488727587a8e7cdff0cc2157c4eecee70b33482f8c473ecc147e7c7cdbc1c"))
        ( 22847, uint256("0xa6b1e66917daf8ed75b4c99420fab027a7f9613d6342af7787755fef02e11d77"))
        ( 22850, uint256("0x229fe4a04fbd46e8723f013cc9b202290eea622597e80a961f7fe9fe50ff82dd"))
        ( 22854, uint256("0xdfd77d5c3df3ed96dee2b2518b78adb56b1910dbf6f935e07b016495ca483fa0"))
        ( 22855, uint256("0xf94c43d0047d6a5022c31f96a7db29b434848de8ad585851c6e534de17284e6d"))
        ( 25050, uint256("0x0df0f7d987dc2fa5c84dcb9a481d6f8c85ddbff5978315fdb4cd2f05ebbcdba6"))
        ( 32845, uint256("0xc96f44b43944b154f993d863fb145b7d25fc773322d02fd533f861709c2bb766"))
        ( 32850, uint256("0x0c953756f9aaaa3e805e5cf195baa34662fdf925e96f577fd2bc9b49c58edd1c"))
        ( 38630, uint256("0x741cfa39dc74f24c80a6f5b3ee920dc69dd640b8114f0996dd79d01d77229d0b"))
        ( 39999, uint256("0xebaaa3c2a91d545c0402e6a5989a48082b167de0ae5f9098ce391c83248cbecc"))
        ( 46741, uint256("0x13e37c080843bf0bbe22c951dbbcb38bfde70be5a442f8d7816b5c16baa21cb4"))
        ( 47100, uint256("0xfa7d6e75af53e04a17e79b6765367d25fbe8a62daf00e10951461425828e43eb"))
        ( 52000, uint256("0xcaf9f5843b61637069802aa570264168cc5c6e3a13291676e04009a68111c677"))
        ( 55150, uint256("0x4bdeb2a8674aac7ebfc77d05647d366494b93c81eee73429b3b25edf7ca60c70"))
        ( 57922, uint256("0x74afc1befaf54c55faebf676d114ccfd2f1cb50f6d9db27f23bed09cc3a645a1"))
        ;
    static const CCheckpointData data = { 
        &mapCheckpoints,
        1459568042, // * UNIX timestamp of last checkpoint 
        0,    // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        2000.0     // * estimated number of transactions per day after checkpoint
    };

    static MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
        (   0, uint256("0x743de1f713cc7e6ee4d5ff38f907b9047f29afe46ca1e6abe0223dcc1b6ca2f7"))
        ;
    static const CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        1456999184,
        0,
        2000
    };

    const CCheckpointData &Checkpoints() {
        if (fTestNet)
            return dataTestnet;
        else
            return data;
    }

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (!GetBoolArg("-checkpoints", true))
            return true;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    // Guess how far we are in the verification process at the given block index
    double GuessVerificationProgress(CBlockIndex *pindex) {
        if (pindex==NULL)
            return 0.0;

        int64 nNow = time(NULL);

        double fWorkBefore = 0.0; // Amount of work done before pindex
        double fWorkAfter = 0.0;  // Amount of work left after pindex (estimated)
        // Work is defined as: 1.0 per transaction before the last checkoint, and
        // fSigcheckVerificationFactor per transaction after.

        const CCheckpointData &data = Checkpoints();

        if (pindex->nChainTx <= data.nTransactionsLastCheckpoint) {
            double nCheapBefore = pindex->nChainTx;
            double nCheapAfter = data.nTransactionsLastCheckpoint - pindex->nChainTx;
            double nExpensiveAfter = (nNow - data.nTimeLastCheckpoint)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore;
            fWorkAfter = nCheapAfter + nExpensiveAfter*fSigcheckVerificationFactor;
        } else {
            double nCheapBefore = data.nTransactionsLastCheckpoint;
            double nExpensiveBefore = pindex->nChainTx - data.nTransactionsLastCheckpoint;
            double nExpensiveAfter = (nNow - pindex->nTime)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore + nExpensiveBefore*fSigcheckVerificationFactor;
            fWorkAfter = nExpensiveAfter*fSigcheckVerificationFactor;
        }

        return fWorkBefore / (fWorkBefore + fWorkAfter);
    }

    int GetTotalBlocksEstimate()
    {
        if (!GetBoolArg("-checkpoints", true))
            return 0;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (!GetBoolArg("-checkpoints", true))
            return NULL;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
