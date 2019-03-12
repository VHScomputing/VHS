// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2017-2018 The XDNA Core developers
// Copyright (c) 2018-2018 The VHS Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <mutex>
#include <assert.h>
#include <limits>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of(0, uint256("00000e766077229965499049eb2b8c05e776048555e9b2768d253e3a0a3ba4e0"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1552053990, // * UNIX timestamp of last checkpoint block
    0,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("00000e766077229965499049eb2b8c05e776048555e9b2768d253e3a0a3ba4e0"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1552053990,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("000003b994bb5b9c0c07f9ae6646710766a8e00ee1df9ede2d4ad34cdf462f0a"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1552053992,
    0,
    100};


void MineGenesis(CBlock genesis)
{
    printf("Searching for genesis block...\n");
    // This will figure out a valid hash and Nonce if you're
    // creating a different genesis block:
    uint256 hashTarget = ~uint256(0) >> 20;
    uint256 thash;
    while(true)
    {
        thash = genesis.GetHash();
        if (thash <= hashTarget)
            break;
        if ((genesis.nNonce & 0xFFF) == 0)
        {
            printf("nonce %u: hash = %s \n", genesis.nNonce, thash.ToString().c_str());
        }
        ++genesis.nNonce;
        if (genesis.nNonce == 0)
        {
            printf("NONCE WRAPPED, incrementing time\n");
            ++genesis.nTime;
        }
    }
    printf("block.nTime = %u \n", genesis.nTime);
    printf("block.nNonce = %u \n", genesis.nNonce);
    printf("block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
    printf("block.merkle = %s\n", genesis.hashMerkleRoot.ToString().c_str());
    std::fflush(stdout);
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x6F;
        pchMessageStart[1] = 0x70;
        pchMessageStart[2] = 0x71;
        pchMessageStart[3] = 0x73;
        vAlertPubKey = ParseHex("04c6d5b3d44ddb1d4b2e7b8cd54e474704e9c5f6c9b20a1054ebd2354f8ac62426cb2d30c918c91a426eff46c3dcfe4cdaa8a12798df10c2bd693bcfa3ec11fe26");
        vVHSDevKey = ParseHex("044c0066bda6a59c2f395e95906fdb34dc76e838e953ed8c8f1b3291a57dff5cd3bfe7e98f490941407f82931e4250cdc18334a2bb2847a1eb1bd199e5368f8f8b"); // TEAMPubKey for fees
        vVHSFundKey = ParseHex("0440e4276373938ce8a5f8bbfc6c99927149aecd69b2a6f3da5dd424a347699b5da3bd30cab427f23666c60714dab6c182787f5d699800ba2efb5174d4c0ccdbb5"); // SWAPPubKey for fees
        nDevFee = 5; // TEAMFee %
        nFundFee = 5; // SWAPFee %
        nDefaultPort = 13200;
        bnProofOfWorkLimit = ~uint256(0) >> 20;
        bnStartWork = ~uint256(0) >> 24;


        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetSpacing = 2 * 60;  // VHS: 2 minute
        nAntiInstamineTime = 10; // 10 blocks with 1 reward for instamine prevention
        nMaturity = 50;
        nMasternodeCountDrift = 3;
        nMaxMoneyOut = 1432200 * COIN;

        nStartMasternodePaymentsBlock = 250;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 64800;
        nModifierUpdateBlock = std::numeric_limits<decltype(nModifierUpdateBlock)>::max();

        const char* pszTimestamp = "Social Investment Platform Etoro Launches in 30 US States";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 10000 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04f51beb87c2c47d0142e2aa8088003c00b60d0c71a7a40cf6042b57da37c00633e20e2de18b61ed4f734e25b61048f3864a668508bcece58b21f0c23fb1ee20fc") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1552053990;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 3730032;

       // MineGenesis(genesis);
       // std::cout << genesis.ToString() << std::endl;

	    hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("00000e766077229965499049eb2b8c05e776048555e9b2768d253e3a0a3ba4e0"));
        assert(genesis.hashMerkleRoot == uint256("e3ad2e01cfb0483f1c36bc769fcf6945be791a1fb0d9d359a6d0892bb1092b65"));

        vSeeds.push_back(CDNSSeedData("92.63.103.206", "92.63.103.206"));
		vSeeds.push_back(CDNSSeedData("80.87.197.162", "80.87.197.162"));
		vSeeds.push_back(CDNSSeedData("37.143.9.193", "37.143.9.193"));
		vSeeds.push_back(CDNSSeedData("37.143.10.155", "37.143.10.155"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 71);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 18);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 233);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x3D)(0x35)(0x37).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x31)(0x51)(0x2A).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x07)(0x99).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04600ae18baf7e32a2cd8caba8081e5b696af20fc11e7de17f0a3365f10853a47ef413a3dae10fed7ed8c1e0b0ce508f9b328a242679dc506fbd9ba078ebd287f8";
        strObfuscationPoolDummyAddress = "VPGfxo1fS8hrsowprmo8gpJAvmAd1N35cp";
        nStartMasternodePayments = 1552053990;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xa2;
        pchMessageStart[1] = 0x59;
        pchMessageStart[2] = 0xa9;
        pchMessageStart[3] = 0x9a;

        bnProofOfWorkLimit = ~uint256(0) >> 1;
        bnStartWork = bnProofOfWorkLimit;


        vAlertPubKey = ParseHex("04dd42c7eb18273f3c68887f922b035a6a21465d79dd4a92373814d9a94c116b58174630ea4b2dd5bd36b454efd7b82e47a3bc0a140a9f4731695cbeeb5f1715d7");
        nDefaultPort = 51112;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetSpacing = 1 * 60;  // VHS: 1 minute
        nLastPOWBlock = std::numeric_limits<decltype(nLastPOWBlock)>::max();
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = std::numeric_limits<decltype(nModifierUpdateBlock)>::max();
        nMaxMoneyOut = 1000000000 * COIN;


        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1552053990;
        genesis.nNonce = 3730032;

	//MineGenesis(genesis);
       // std::cout << genesis.ToString() << std::endl;

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("00000e766077229965499049eb2b8c05e776048555e9b2768d253e3a0a3ba4e0"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 128); // Testnet VHS addresses start with 't'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 11);  
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 240);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x51)(0xc0).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x81)(0x88)(0xf7).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04d52f7564e5e86d07f17b11da7936c1f721d4a82f51eaaf0b9c1f7dad47c524235a3dce703a61aa1b7556099cbecb7b4d08f32cb041492057152d8e84d4998748";
        strObfuscationPoolDummyAddress = "tk7oN9aE8Foa8gqoJCYx4UcrWnEaFvr3Co";
        nStartMasternodePayments = 1536512409;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xa4;
        pchMessageStart[1] = 0x5f;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0x2c;

        bnStartWork = ~uint256(0) >> 20;


        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetSpacing = 1 * 60;        // VHS: 1 minute
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1552053992;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 4456827;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 61112;

	//MineGenesis(genesis);
        //std::cout << genesis.ToString() << std::endl;

        assert(hashGenesisBlock == uint256("000003b994bb5b9c0c07f9ae6646710766a8e00ee1df9ede2d4ad34cdf462f0a"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 31112;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fMineBlocksOnDemand = true;

 /* subsidySwitchPoints = {
            {0         ,   4 * COIN},
            {20   * 1e9,   5 * COIN},
            {30   * 1e9,   7 * COIN},
            {50   * 1e9,  10 * COIN},
            {80   * 1e9,  14 * COIN},
            {130  * 1e9,  19 * COIN},
            {210  * 1e9,  25 * COIN},
            {340  * 1e9,  32 * COIN},
            {550  * 1e9,  40 * COIN},
            {890  * 1e9,  49 * COIN},
            {1440 * 1e9,  59 * COIN},
            {2330 * 1e9,  70 * COIN},
            {3770 * 1e9,  82 * COIN},
            {6100 * 1e9,  95 * COIN},
            {9870 * 1e9, 109 * COIN},
        };
        assert(subsidySwitchPoints.size());*/

    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
