/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

uint32_t const DomainParam_NIST_P256[] =
{
#ifndef __ARMEB__   /* Little endian */
    0x5b95ed03, 0x8c43430f, 0x1efdfb18, 0x80d18976,
    0x68abe94b, 0x917c7d63, 0xb12b3783, 0xe1867865,
    0x755370ec, 0xa48f61f3, 0x020e374b, 0x86ecc995,
    0xda090d3c, 0xffef8149, 0x6e84fda5, 0x5f438e28,
    0xb7fcaef9, 0xf5919f8d, 0x5b23011f, 0xf0c683fb,
    0xebc8f491, 0xd2d52da6, 0x97903ece, 0x6042f732,
    0x904bc919, 0xd17305ce, 0x7c91ab32, 0xdba71ce5,
    0xd6be9696, 0x7c1ec304, 0x87ab90e0, 0x566af7bf,
    0x2a7ff1d3, 0x2171e670, 0xe7da191b, 0x3d4140f7,
    0x4a2020e5, 0xc6efb74d, 0x0f04a935, 0x2d40923a,
    0x1cd8a1cd, 0x99fc64be, 0x0b5135cf, 0x78320866,
    0x2e57d40e, 0x52ddc2a1, 0x43285699, 0x28288ef7,
    0xae1fb128, 0x0f85cdc2, 0x4f8f4842, 0x6c5aa393,
    0x54a5620f, 0x94571ec6, 0x987e6f74, 0x8b00683f,
    0x4add137f, 0x396fa4ce, 0xc9896ed1, 0xc399c12c,
    0xe493c74e, 0xd1fbc23f, 0x619bba77, 0xe3d8961f,
    0x868114a7, 0x917c16bd, 0x7570524f, 0x8d373059,
    0x783a4d58, 0x25ad1485, 0xc17d29e7, 0xe2ae36d7

#else               /* Big endian */
    0x03ed955b, 0x0f43438c, 0x18fbfd1e, 0x7689d180,
    0x4be9ab68, 0x637d7c91, 0x83372bb1, 0x657886e1,
    0xec705375, 0xf3618fa4, 0x4b370e02, 0x95c9ec86,
    0x3c0d09da, 0x4981efff, 0xa5fd846e, 0x288e435f,
    0xf9aefcb7, 0x8d9f91f5, 0x1f01235b, 0xfb83c6f0,
    0x91f4c8eb, 0xa62dd5d2, 0xce3e9097, 0x32f74260,
    0x19c94b90, 0xce0573d1, 0x32ab917c, 0xe51ca7db,
    0x9696bed6, 0x04c31e7c, 0xe090ab87, 0xbff76a56,
    0xd3f17f2a, 0x70e67121, 0x1b19dae7, 0xf740413d,
    0xe520204a, 0x4db7efc6, 0x35a9040f, 0x3a92402d,
    0xcda1d81c, 0xbe64fc99, 0xcf35510b, 0x66083278,
    0x0ed4572e, 0xa1c2dd52, 0x99562843, 0xf78e2828,
    0x28b11fae, 0xc2cd850f, 0x42488f4f, 0x93a35a6c,
    0x0f62a554, 0xc61e5794, 0x746f7e98, 0x3f68008b,
    0x7f13dd4a, 0xcea46f39, 0xd16e89c9, 0x2cc199c3,
    0x4ec793e4, 0x3fc2fbd1, 0x77ba9b61, 0x1f96d8e3,
    0xa7148186, 0xbd167c91, 0x4f527075, 0x5930378d,
    0x584d3a78, 0x8514ad25, 0xe7297dc1, 0xd736aee2
#endif  /* defined __ARMEB__ */
};

uint32_t const DomainParam_NIST_P384[] =
{
#ifndef __ARMEB__   /* Little endian */
    0xc1208b71, 0x04bab7c6, 0xada6d981, 0xf58061a9,
    0x4b38fe8c, 0x26dc457d, 0x6deb0d90, 0xfb300e47,
    0x7429d33c, 0xda82d455, 0xc4ea7b35, 0x29fd1b2b,
    0xebcd95f6, 0x7fec518c, 0x7701b27d, 0x36c43bec,
    0x514102f1, 0x07d8c82e, 0xb70c670f, 0x364117b5,
    0x860afb8d, 0xc907187c, 0x861180f7, 0x54ba39e1,
    0xcca53ff8, 0x1d20aee8, 0xb61a4aec, 0x7de840e8,
    0xe92b2bc8, 0xef11c790, 0x42d6a6b5, 0xcc46e370,
    0xe14c1a26, 0x378832d8, 0x538e61a4, 0x48273d1d,
    0x5096d864, 0x56c33b32, 0xe0baf5c4, 0x8580958e,
    0x15d12a27, 0x114689d9, 0x9398776d, 0x4b4bbeb2,
    0xaec1eb16, 0x408780ad, 0x11ff59b5, 0x64a68380,
    0x389ff4bd, 0x41223131, 0xe0ffe36a, 0xdaa4897c,
    0x4ee571fb, 0xdd2b3571, 0x933d0d36, 0x96eab797,
    0xda27eb94, 0x02c5effe, 0xa66e4d0a, 0xab3d14ff,
    0xa69475c0, 0x49cb2fa4, 0x9d206b08, 0x696e3158,
    0xf25e9485, 0xdbb78301, 0x0395a324, 0x7bf66a1d,
    0x515b126c, 0x1a4c1d98, 0x250792dd, 0xc438241b,
    0x10b707cc, 0x39cd40de, 0x1573327a, 0x4a2cd20a,
    0xf7c3fcff, 0x309a467e, 0x7bc08f27, 0x431fcbef,
    0x041c95e2, 0xad3eef0e, 0x77b3a6fa, 0x65199326,
    0xdf571b9d, 0xaf55e174, 0xbd85cd9d, 0xbc0f7117,
    0xb0c455d5, 0x309b1934, 0x068f2487, 0xe593a891,
    0x9996a673, 0x22dc46a8, 0x64fb4e42, 0xdc75500e,
    0x482abf68, 0x4afb3a48, 0x560c0f65, 0x9e7ac1a1,
    0xfdf3fe43, 0xbf3c370d, 0x28764006, 0xc880ad94

#else               /* Big endian */
    0x718b20c1, 0xc6b7ba04, 0x81d9a6ad, 0xa96180f5,
    0x8cfe384b, 0x7d45dc26, 0x900deb6d, 0x470e30fb,
    0x3cd32974, 0x55d482da, 0x357beac4, 0x2b1bfd29,
    0xf695cdeb, 0x8c51ec7f, 0x7db20177, 0xec3bc436,
    0xf1024151, 0x2ec8d807, 0x0f670cb7, 0xb5174136,
    0x8dfb0a86, 0x7c1807c9, 0xf7801186, 0xe139ba54,
    0xf83fa5cc, 0xe8ae201d, 0xec4a1ab6, 0xe840e87d,
    0xc82b2be9, 0x90c711ef, 0xb5a6d642, 0x70e346cc,
    0x261a4ce1, 0xd8328837, 0xa4618e53, 0x1d3d2748,
    0x64d89650, 0x323bc356, 0xc4f5bae0, 0x8e958085,
    0x272ad115, 0xd9894611, 0x6d779893, 0xb2be4b4b,
    0x16ebc1ae, 0xad808740, 0xb559ff11, 0x8083a664,
    0xbdf49f38, 0x31312241, 0x6ae3ffe0, 0x7c89a4da,
    0xfb71e54e, 0x71352bdd, 0x360d3d93, 0x97b7ea96,
    0x94eb27da, 0xfeefc502, 0x0a4d6ea6, 0xff143dab,
    0xc07594a6, 0xa42fcb49, 0x086b209d, 0x58316e69,
    0x85945ef2, 0x0183b7db, 0x24a39503, 0x1d6af67b,
    0x6c125b51, 0x981d4c1a, 0xdd920725, 0x1b2438c4,
    0xcc07b710, 0xde40cd39, 0x7a327315, 0x0ad22c4a,
    0xfffcc3f7, 0x7e469a30, 0x278fc07b, 0xefcb1f43,
    0xe2951c04, 0x0eef3ead, 0xfaa6b377, 0x26931965,
    0x9d1b57df, 0x74e155af, 0x9dcd85bd, 0x17710fbc,
    0xd555c4b0, 0x34199b30, 0x87248f06, 0x91a893e5,
    0x73a69699, 0xa846dc22, 0x424efb64, 0x0e5075dc,
    0x68bf2a48, 0x483afb4a, 0x650f0c56, 0xa1c17a9e,
    0x43fef3fd, 0x0d373cbf, 0x06407628, 0x94ad80c8
#endif  /* defined __ARMEB__ */
};

uint32_t const DomainParam_Brainpool_256r1[] =
{
#ifndef __ARMEB__   /* Little endian */
    0x817ee07a, 0x30906960, 0xc9106902, 0x07e7a7e5,
    0x02faaf71, 0x339f0019, 0x7d9f1cdf, 0xa1f32348,
    0x505fe9bb, 0xbfce7c43, 0x8bdba09a, 0xd28d1e33,
    0xd6794619, 0x8cadebf2, 0xe1eed8b5, 0x0714802a,
    0x3fdfabc7, 0x7756a6f3, 0xd1342086, 0x00f043b7,
    0x85f58c04, 0xe20f802d, 0x238171a5, 0x4b9f9175,
    0xcdb090f4, 0xb52c4c81, 0xbd4b5dca, 0xf08e4a57,
    0xc79c1f0a, 0xb94e7e5a, 0x8807ef0a, 0x9cfbf470,
    0x8eb7924f, 0x06aeb48d, 0x99fa09b5, 0x204de8d6,
    0x85624943, 0xc9332ba5, 0xb11c0bf4, 0x5bca1307,
    0xea4f92d3, 0x90ccd675, 0xba5d12df, 0xfd8c41a8,
    0xb2439dd0, 0x43935c75, 0x764838d1, 0xc63df14f,
    0xdc536cdf, 0xa43ebb2b, 0x12db6bc0, 0x3bacb72e,
    0x362b3336, 0x619d891a, 0xe9dc4dee, 0xf853ed82,
    0x9028e9af, 0x8b903797, 0xd03df007, 0xc30c2dbc,
    0xf0209230, 0xc7301f76, 0xddabbb93, 0xdcb5930e,
    0x777d8d4d, 0x47be67bf, 0xc809ab62, 0x2d42bd1f,
    0xd4f96008, 0x179c8240, 0xab72fe15, 0xb54e44cf

#else               /* Big endian */
    0x7ae07e81, 0x60699030, 0x026910c9, 0xe5a7e707,
    0x71affa02, 0x19009f33, 0xdf1c9f7d, 0x4823f3a1,
    0xbbe95f50, 0x437ccebf, 0x9aa0db8b, 0x331e8dd2,
    0x194679d6, 0xf2ebad8c, 0xb5d8eee1, 0x2a801407,
    0xc7abdf3f, 0xf3a65677, 0x862034d1, 0xb743f000,
    0x048cf585, 0x2d800fe2, 0xa5718123, 0x75919f4b,
    0xf490b0cd, 0x814c2cb5, 0xca5d4bbd, 0x574a8ef0,
    0x0a1f9cc7, 0x5a7e4eb9, 0x0aef0788, 0x70f4fb9c,
    0x4f92b78e, 0x8db4ae06, 0xb509fa99, 0xd6e84d20,
    0x43496285, 0xa52b33c9, 0xf40b1cb1, 0x0713ca5b,
    0xd3924fea, 0x75d6cc90, 0xdf125dba, 0xa8418cfd,
    0xd09d43b2, 0x755c9343, 0xd1384876, 0x4ff13dc6,
    0xdf6c53dc, 0x2bbb3ea4, 0xc06bdb12, 0x2eb7ac3b,
    0x36332b36, 0x1a899d61, 0xee4ddce9, 0x82ed53f8,
    0xafe92890, 0x9737908b, 0x07f03dd0, 0xbc2d0cc3,
    0x309220f0, 0x761f30c7, 0x93bbabdd, 0x0e93b5dc,
    0x4d8d7d77, 0xbf67be47, 0x62ab09c8, 0x1fbd422d,
    0x0860f9d4, 0x40829c17, 0x15fe72ab, 0xcf444eb5
#endif  /* defined __ARMEB__ */
};

uint32_t const DomainParam_Brainpool_384r1[] =
{
#ifndef __ARMEB__   /* Little endian */
    0xd2568e17, 0x2f85dc4d, 0x5aee1bbe, 0x2ce94022,
    0xbac92d3d, 0xcc3226ba, 0x97ef3851, 0xb161d542,
    0x954976e1, 0x2ddd96aa, 0xad6ff75f, 0x3d704752,
    0x4957c607, 0xe7896e13, 0x9ddab34e, 0x2bd6f33b,
    0x53721dc5, 0x765a7860, 0xd1a324c6, 0x42f370ed,
    0xd3b51268, 0xe2b2b933, 0xee6e17ad, 0x9b04fbef,
    0x419ca7e2, 0x0d43594b, 0xf6d5e3d1, 0x251e6634,
    0xafdaebcd, 0x8f1443cd, 0x52efa45d, 0x272f35bc,
    0x07529d98, 0x40c304e6, 0xf3479993, 0xcc6d0a46,
    0x036ed829, 0x1bdda6b4, 0x87f0a503, 0xb84900cf,
    0x8377cdfd, 0xab0917b5, 0x57f58eeb, 0xe57b89cd,
    0x665f244d, 0x99c46de5, 0xb06a32dd, 0xf5efe29a,
    0x50692c6c, 0xa8477a60, 0x55c9a613, 0x66be1a56,
    0x2a3c46cd, 0x611e968e, 0x895bdf65, 0xab44dee6,
    0xf764c4db, 0x447d6afc, 0x0fde6e77, 0xa92278a5,
    0x6c60f15b, 0xa2b4283d, 0xf8a4fc7d, 0x05308147,
    0x5cbc7785, 0x6d388016, 0xccd5ab58, 0x80f97965,
    0x0dd6acbc, 0xb2e55c32, 0x10d32760, 0x218998ff,
    0xe666949a, 0x9f9e0b19, 0x4dac249c, 0x5f5bab65,
    0xa4325fe1, 0x0d5209e5, 0x71381728, 0x210486d0,
    0x834de045, 0x4ded79a2, 0x06ba9655, 0x5b9fd9da,
    0x65ed502b, 0x440b0ab7, 0x0c6d9aee, 0x002b7389,
    0x46614840, 0xbe3848d7, 0x294c8c55, 0x0dfa8068,
    0x5bc00cf5, 0x152d04cf, 0xdf182892, 0x0ce3973a,
    0x34650544, 0x441a55f2, 0xd72ae902, 0x6e8bd4d1,
    0xe1b95e2f, 0xe831a76e, 0x2f8ff458, 0x40c3653c

#else               /* Big endian */
    0x178e56d2, 0x4ddc852f, 0xbe1bee5a, 0x2240e92c,
    0x3d2dc9ba, 0xba2632cc, 0x5138ef97, 0x42d561b1,
    0xe1764995, 0xaa96dd2d, 0x5ff76fad, 0x5247703d,
    0x07c65749, 0x136e89e7, 0x4eb3da9d, 0x3bf3d62b,
    0xc51d7253, 0x60785a76, 0xc624a3d1, 0xed70f342,
    0x6812b5d3, 0x33b9b2e2, 0xad176eee, 0xeffb049b,
    0xe2a79c41, 0x4b59430d, 0xd1e3d5f6, 0x34661e25,
    0xcdebdaaf, 0xcd43148f, 0x5da4ef52, 0xbc352f27,
    0x989d5207, 0xe604c340, 0x939947f3, 0x460a6dcc,
    0x29d86e03, 0xb4a6dd1b, 0x03a5f087, 0xcf0049b8,
    0xfdcd7783, 0xb51709ab, 0xeb8ef557, 0xcd897be5,
    0x4d245f66, 0xe56dc499, 0xdd326ab0, 0x9ae2eff5,
    0x6c2c6950, 0x607a47a8, 0x13a6c955, 0x561abe66,
    0xcd463c2a, 0x8e961e61, 0x65df5b89, 0xe6de44ab,
    0xdbc464f7, 0xfc6a7d44, 0x776ede0f, 0xa57822a9,
    0x5bf1606c, 0x3d28b4a2, 0x7dfca4f8, 0x47813005,
    0x8577bc5c, 0x1680386d, 0x58abd5cc, 0x6579f980,
    0xbcacd60d, 0x325ce5b2, 0x6027d310, 0xff988921,
    0x9a9466e6, 0x190b9e9f, 0x9c24ac4d, 0x65ab5b5f,
    0xe15f32a4, 0xe509520d, 0x28173871, 0xd0860421,
    0x45e04d83, 0xa279ed4d, 0x5596ba06, 0xdad99f5b,
    0x2b50ed65, 0xb70a0b44, 0xee9a6d0c, 0x89732b00,
    0x40486146, 0xd74838be, 0x558c4c29, 0x6880fa0d,
    0xf50cc05b, 0xcf042d15, 0x922818df, 0x3a97e30c,
    0x44056534, 0xf2551a44, 0x02e92ad7, 0xd1d48b6e,
    0x2f5eb9e1, 0x6ea731e8, 0x58f48f2f, 0x3c65c340
#endif  /* defined __ARMEB__ */
};

uint32_t const DomainParam_Koblitz_secp256k1[] =
{
#ifndef __ARMEB__   /* Little endian */
    0x802dda51, 0x8445e14b, 0x6a51b5d8, 0xcbc7390d,
    0x10c17a39, 0x0de194be, 0xd5d04fb3, 0xbeff6cbf,
    0x68ea3254, 0x8fee4e35, 0x6c7674a6, 0x644451ea,
    0x99e2211e, 0x2306c4b0, 0x07a90fc9, 0x67ab6eaa,
    0x7a4c26d9, 0xcf294d92, 0xdcf3a81f, 0xc354bb01,
    0x9fc1e322, 0x0565cc1e, 0xfd8ac23c, 0x19e07ae6,
    0x6785e73d, 0xc26a809b, 0xc7355776, 0x70d4d810,
    0x9b8d95eb, 0xc066190a, 0xf089bbe2, 0x7b29a705,
    0x6eb6fd8e, 0x5f42498c, 0xac75b4e2, 0xa9624f30,
    0x46045533, 0x92dbf1bd, 0x080b43de, 0xaac29193,
    0xfdd2cf7a, 0xe13c666e, 0x13a18c29, 0xba904dbe,
    0x1b21cda6, 0x2e4bacf5, 0xfe2dd45f, 0x5aaf9877,
    0x05534017, 0x7cba3aed, 0x84f723f8, 0x0dc25f26,
    0xb4f336e6, 0xb194fb79, 0x3653f041, 0x82613106,
    0x2ff0f567, 0xd7f7935d, 0x5f2f554f, 0x94ba222b,
    0x3151b17f, 0xd7388697, 0x0d696aa7, 0x4a03f5e5,
    0x8e937fb7, 0x23e5c430, 0x579701e5, 0x5fc5ae2b,
    0xc3a8738a, 0x83a868da, 0xe16d3b29, 0xf70702a9

#else               /* Big endian */
    0x51da2d80, 0x4be14584, 0xd8b5516a, 0x0d39c7cb,
    0x397ac110, 0xbe94e10d, 0xb34fd0d5, 0xbf6cffbe,
    0x5432ea68, 0x354eee8f, 0xa674766c, 0xea514464,
    0x1e21e299, 0xb0c40623, 0xc90fa907, 0xaa6eab67,
    0xd9264c7a, 0x924d29cf, 0x1fa8f3dc, 0x01bb54c3,
    0x22e3c19f, 0x1ecc6505, 0x3cc28afd, 0xe67ae019,
    0x3de78567, 0x9b806ac2, 0x765735c7, 0x10d8d470,
    0xeb958d9b, 0x0a1966c0, 0xe2bb89f0, 0x05a7297b,
    0x8efdb66e, 0x8c49425f, 0xe2b475ac, 0x304f62a9,
    0x33550446, 0xbdf1db92, 0xde430b08, 0x9391c2aa,
    0x7acfd2fd, 0x6e663ce1, 0x298ca113, 0xbe4d90ba,
    0xa6cd211b, 0xf5ac4b2e, 0x5fd42dfe, 0x7798af5a,
    0x17405305, 0xed3aba7c, 0xf823f784, 0x265fc20d,
    0xe636f3b4, 0x79fb94b1, 0x41f05336, 0x06316182,
    0x67f5f02f, 0x5d93f7d7, 0x4f552f5f, 0x2b22ba94,
    0x7fb15131, 0x978638d7, 0xa76a690d, 0xe5f5034a,
    0xb77f938e, 0x30c4e523, 0xe5019757, 0x2baec55f,
    0x8a73a8c3, 0xda68a883, 0x293b6de1, 0xa90207f7
#endif  /* defined __ARMEB__ */
};

