/**
  ******************************************************************************
  * @file    network_data_params.c
  * @author  AST Embedded Analytics Research Platform
  * @date    2026-06-20T21:45:24+0700
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */

#include "network_data_params.h"


/**  Activations Section  ****************************************************/
ai_handle g_network_activations_table[1 + 2] = {
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
  AI_HANDLE_PTR(NULL),
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
};




/**  Weights Section  ********************************************************/
AI_ALIGNED(32)
const ai_u64 s_network_weights_array_u64[466] = {
  0x3c9ad74d3f8dbd1fU, 0x3d035a513d7d635eU, 0x3dab7f513cfe128fU, 0x3cb91dd7bbea09b6U,
  0x3e1b807a3d1fd3dbU, 0xbe51bb803e89c1adU, 0xbe9b6666be27ab83U, 0xbd577906be1c81f0U,
  0xbe56f2843e9d876cU, 0x3e4b1c47bea73abdU, 0x3d940b76bf9dacebU, 0x3df064a8bcb40ba2U,
  0xbd0b46753ddb7289U, 0x3dcd2bb1bc725915U, 0xbe9219393da37220U, 0x3bdd4b8abe4ded3dU,
  0x3defd72cbd8a3a7aU, 0x3eda8b883d386f31U, 0x3ebaa2e63e941010U, 0x3e11c6783e5db308U,
  0xbe8ae0e5be9c838dU, 0xbe55ae313d2eba03U, 0xbeaa2dd43d4f5265U, 0xbe61e790bec22faaU,
  0x3e7a934dbe40d364U, 0xbd50d8673f9a3ca4U, 0xbdbca5963b77111aU, 0xbd4514103d035510U,
  0x3da63f8bbd56e9a9U, 0xbd2dd1273d172d73U, 0xbb588b1bbf85b5bdU, 0xbafaf2a53e8ece58U,
  0x3e2a70e13dedd456U, 0x3e1546d83ce7ea98U, 0xbdb031823ea99804U, 0xbd9a1f7bbe6c0a93U,
  0x3eedb2ba3d40d9e8U, 0xbe590c54be451d53U, 0x3ece795e3cfeec89U, 0xbe18295cbe4f43ffU,
  0x3cb8c0cebf9fed3eU, 0xbdb163bb3e436d82U, 0xbdbffdd83e65c6a5U, 0xbdef4b313e744fd5U,
  0xbe0f34f1bdef40d0U, 0xbddd239bbfb52c6fU, 0xb74ddda0bd004ffbU, 0x3e7839473d80646dU,
  0x3c510c513e91addcU, 0xbe353c0ebc014da8U, 0x3e294463bf1a82b9U, 0xbdb28d9a3ea45003U,
  0xbe106bacbe8b5540U, 0x3e93757bbe242b03U, 0x3e9a5ea63e1ab878U, 0xbc8f7661bfa0696cU,
  0x3dc548f7bcc1ea26U, 0x3e06d775bca55254U, 0x3e18b79a3dab6dfcU, 0x3d536ee43d3f6328U,
  0x3e9adae93f804a5eU, 0xbe513454be392e01U, 0x3bef5640bca51d56U, 0xbe9a8cb1bdafffbdU,
  0xbbe7d41ebe78cedeU, 0xbbcf22f03f3c36dfU, 0xbe468757bdf2116aU, 0x3e3eb1bdbdc3de26U,
  0x3e44fea93e10cc6fU, 0x3d35ba1f3e1e071cU, 0x3e22bce13e3bc583U, 0xbe5dbd1ebeb0228aU,
  0xbf37e710bf304f4cU, 0xbf096420bed37429U, 0xbd972ee7beaff7e4U, 0x3d4ad875bf843dbaU,
  0x3a1068b9bd245eebU, 0x3d25bdf1bdb2fd3aU, 0xbda1ac04bd5d0f3fU, 0x3e5ee7cbbce01acaU,
  0x3d7d2cf63e542c0cU, 0xbdc4327e3ebe787cU, 0x3e5949a73e47f428U, 0x3e1165873e932b9aU,
  0x3b1871e43c7a57f4U, 0x3daec8dfbe0a0a9aU, 0x3eeee9483df8d62fU, 0x3e7b34e93db28785U,
  0x3df64b973d4c495aU, 0xbca997253e82bdeaU, 0x3d88e7f3bca012cdU, 0x3e8b4f783cbd3e3eU,
  0x3cae58f53eb709c2U, 0x3ed3a3433eb41bb4U, 0xbe6c35203db17fc2U, 0xbc9eb1783f68febdU,
  0x3dd28c223ca8a312U, 0xbdacfd813e9f9210U, 0x3e076c8fbdeecff5U, 0xbd0ed5f23e487ab2U,
  0x3e474ff33f75f909U, 0x3e1d7f2dbdf2940fU, 0xbe8b1486bd95ebbaU, 0xbe4f76323d3fee55U,
  0x3e876944bdd927feU, 0x3c2748653f87ddccU, 0x3d0016fa3da3eeb3U, 0x3cacf2ddbd450d21U,
  0xbc7ee0663d91eef9U, 0x3dba3f3ebca9abc1U, 0xbd3e96a53ea2aea3U, 0xbe30900abe7fba8eU,
  0xbf1cd034bf32c8fcU, 0xbecdbbb6beeffa3dU, 0x3e61bc23be2272f1U, 0x3cb48e84be5a8f52U,
  0x3ecdc7153e35eea0U, 0x3ec96e7c3df768c8U, 0xbd046e4d3ee3c9fbU, 0x3e6354f43ec9aed0U,
  0x3dd9ed693e5718a2U, 0xbeb29da6be83fd3eU, 0xbef078febf130851U, 0xbe53980bbedeb5b2U,
  0x3ed34290bf01c163U, 0xbcc58b003fa30ef5U, 0xbc8c9ac33e2890bcU, 0x3de066f23b4bc919U,
  0x3c68175a3ca0e509U, 0xbdf525d43cb4caeaU, 0x3d429450bf5f40f9U, 0xbc9463bebac382e3U,
  0xbde0ff473c9d3e03U, 0xbddfceffbe0f0855U, 0x3e8a874bbd84cc6cU, 0x3d6fa7b23f7d1530U,
  0x3e0ec85fbd646582U, 0x3d26cf433d7f721bU, 0x3df62ddd3c0dd903U, 0x3de7c6a0bd0f456bU,
  0xbc667bee3faa355eU, 0x3d9d878a3c753f9aU, 0x3d61a90f3b23aa43U, 0x3d9e7a073c795d03U,
  0xbde7e6423da3e531U, 0x3e0c8b123e1dc014U, 0xbeea787bbee2af8fU, 0xbf008b78beabe30eU,
  0xbf2062e2be6eda04U, 0x3e40967abf1a911dU, 0x3da53f953f8d9a1aU, 0xbc08b1fe3dd2ee8aU,
  0xbe53c091bd9f5ef5U, 0x3c889425bda50445U, 0x3d49a879be47a44eU, 0x3db73ab03f48c08dU,
  0x3e37e10b3df43809U, 0x3d9c1c5f3e4474c6U, 0xbe8527a23d7bb314U, 0xbe7f03303db5fc27U,
  0xbda1008bbea65a5eU, 0xbdaa4dc33dadcda0U, 0xbe2210acbce74970U, 0x3adde62fbd856749U,
  0x3d9e442c3e1296d4U, 0x3d0eaf0ebd580438U, 0xbe387a523e1654f2U, 0x3eac79ed3eea18f8U,
  0xbe08958fbdffe8ebU, 0xbea2912abe21f704U, 0xbe8bbea23d4bd62eU, 0xbe3eccbf3ee25da3U,
  0xbebab93e3edf080dU, 0xbe972cb83ec61057U, 0x3eebfbc8beb32df0U, 0xbe8271333a7b202aU,
  0xbe09373abf460f33U, 0x3d923bc33f143553U, 0xbdd58eef3b97ba6eU, 0xbd0fba0ebc62d73cU,
  0x3f0dfae1bc648a52U, 0x3e7eb62d3d8e3acdU, 0xbe1529f93d8bd551U, 0x3ebb0a413fa02b79U,
  0xbe64f2163d8d277aU, 0xbe59ac4bbe01b72dU, 0xbeee08a33d35cfd0U, 0xbd5a8b903f6b0d32U,
  0xbed119c13f995198U, 0xbebbb78d3f297909U, 0x3f4607bcbed24ef8U, 0xbe311ef4be719193U,
  0xbe9b1816bf5e42e8U, 0x3cc769463efb6a4aU, 0xbda6f0c8be62498dU, 0xbde1d7c8bda2a49aU,
  0x3f16f4583eb86304U, 0x3eef75b23e98d342U, 0x3dc3bab83c40b0e9U, 0x3f47c1fd3f417862U,
  0xbdee9bf9be358924U, 0xbe81c5633cfa2d3dU, 0xbf4f92cebe25aa41U, 0xbd84a03f3f903fb0U,
  0xbe8ce3353f554b33U, 0xbf1963793ee71614U, 0x3f99bb78bf035f65U, 0xbe985f5e3d0b0357U,
  0x3e824b9abf667393U, 0x3e7742513f0782f2U, 0xbf21f80a3e7d88b1U, 0x3e51cb06bcb51e7bU,
  0x3ec899f63eb945ccU, 0x3ef857643f159358U, 0xbea7a5a8bf06994aU, 0x3f0c7fc6bf05c7caU,
  0x3d9ad6093e0b088fU, 0xbe615a303e1440e9U, 0xbf5e9b17be66252dU, 0xbc253028bf258a68U,
  0xbf002734bf1f68d8U, 0xbf01a94c3ebf48bcU, 0xbf138c84bf23c6b0U, 0xbd819861bf294279U,
  0x3e339bc3bf6b1926U, 0x3ee62a083f0e1a2aU, 0xbf31711d3bd68aa7U, 0x3c6730a23f40962eU,
  0x3f17c5dc3ee56614U, 0x3f4ee23a3ef6a4cfU, 0x3e6efbb8bc3ac33fU, 0x3ca5fbe5bf0277ceU,
  0x3f0cd02a3f0b84a1U, 0x3e905e643ebdbb5aU, 0xbf1865a1be309b45U, 0x3eb98726bed13992U,
  0xbf31db37bf45e2e9U, 0x3d2b38a2bdb94b38U, 0xbed13281bf06240dU, 0xbdcc7d61bee2e85dU,
  0x3dedcbc9bf3e9fe8U, 0x3b5267c03ecd4701U, 0xbedb5bde3c5de55fU, 0x3ee4e2633e6230d6U,
  0x3f4d21923ea47ec7U, 0x3f610d193ebd84acU, 0xbe836e37be83668cU, 0x3e6c4d21befbcf79U,
  0xbd3582ac3d50d27fU, 0xbe4c4bca3ca180b3U, 0xbf02c92bbea23e51U, 0x3e963348bf1613beU,
  0xbebd8e43bf0f73f1U, 0xbee367223e1616e1U, 0xbf1805dbbf3738f6U, 0x3d148474beb4be4bU,
  0x3dd63d53bf2f2c78U, 0x3d19722e3e9847f5U, 0xbf1241f7bdec9c27U, 0x3c1480af3e5cdca2U,
  0x3f0d76493e08e133U, 0x3eb58e793ecbb07bU, 0xbe53c4cabdcdcc9cU, 0x3e877d13bf2401deU,
  0x3e121d1c3a51c884U, 0xbd59e46e3c8b2287U, 0xbf390337bece7a0eU, 0xbcce1e28becfd3a3U,
  0xbf12daafbf320e0bU, 0xbe0edfc33e4a1f2eU, 0xbeb8492dbf156ba3U, 0xbe295149be293a37U,
  0x3e4fe5eabe199cc2U, 0xbf4b86703e4bed71U, 0x3f08579e3e4b6b31U, 0xbef26cb6bf11b0a5U,
  0xbebeaa19be35993bU, 0xbedbe1a5be53efdfU, 0xbe9929a33e44f44aU, 0x3c6c9c7f3f7a3904U,
  0xbf27b702bec95fa8U, 0xbedb68e5bf4eb237U, 0x3b4b027e3d8b0696U, 0xbf061aea3f3cb63fU,
  0xbe80e86d3f891221U, 0xbe735a903f0264f9U, 0x3f284605be32971dU, 0xbe65522f3e2cff41U,
  0x3e64b0803f2014f5U, 0x3e02c3b7be9d7dfbU, 0x3f6a782ebe830072U, 0xbd4e6e66bdea6497U,
  0xbe508fb7be379866U, 0xbefe40293dbe8e15U, 0x3e24c3193e86ab1eU, 0xbed2f0a1bf30a0caU,
  0x3d16d4e03def1ad8U, 0xbd8dc5b6bbb7513fU, 0x3f71b1fa3e5e2553U, 0xbbccd939be85b271U,
  0x3f179a88bef56910U, 0x3eb5a08fbee03b91U, 0xbeffadff3f3b2a56U, 0x3d87d3d53e947ccaU,
  0xbd472e34bef33b1dU, 0xbf2d7aefbe454ff8U, 0x3e0c733ebe9f2404U, 0xbe9adaddbf323aa2U,
  0xbefbc9ccbd3642b2U, 0xbeb9be383d2afcfaU, 0xbdcb56753ef484faU, 0x3f0ee30c3f8923cdU,
  0xbf3ff70abf522d78U, 0xbf18deb7bf46655fU, 0xbcb9344a3e957ce6U, 0xbf1a85653f44d53bU,
  0x3bbcf7d63f602aa3U, 0xbec8049f3e2ffe3eU, 0x3f6795b9bd82f2c0U, 0xbe8f78953edfe097U,
  0x3e8b18403f4a2b3eU, 0xbcab9864bea45275U, 0x3f572324bde520a4U, 0x3e07ceccbcdd63eaU,
  0xbebbc46cbeaa3228U, 0xbe140390be611feaU, 0x3e4102783ea96c4aU, 0xbe853ee6be05c20aU,
  0xbdeaba313df5e73cU, 0x3e6ff4c33d4f0c74U, 0x3f320ed13e74685eU, 0xbbb9c0343e32fd58U,
  0x3f31f02bbed8fe06U, 0x3ea9f3a9bf06b3faU, 0xbe1c0d003edeb9b6U, 0x3d0c2f3e3f009207U,
  0x3e70b1acbe949d0cU, 0xbf6083d7bdc4e48dU, 0x3dd03fd4bcc487eeU, 0xbf0d40a7bece1f19U,
  0xbe4920193e995404U, 0xbddc6da9bec95c69U, 0xbdee043c3f174f17U, 0x3eeb59803f1e5c41U,
  0xbecd53e6bf69b520U, 0xbf4003b1bf2533a5U, 0xbe57e9713e2b7ecbU, 0xbf55088c3f8cc90bU,
  0xbe7300b83f8859f0U, 0xbea901a13e2bced6U, 0x3f8d47fdbe575be3U, 0xbee9d6163e978d03U,
  0x3ea88c05bf3d5e02U, 0xbdbc002a3ea75366U, 0xbf22ff72be8b6489U, 0x3e320ee3bbf85925U,
  0x3ea1e2ac3e4d1a91U, 0x3f2d03b73ec7eed7U, 0x3cf6e88ebe7fb880U, 0x3e47e487bf0c66c6U,
  0x3e361b353e5dfefbU, 0xbe62ede13de9875cU, 0xbf09b31ebc0b1d26U, 0x3d6b513bbebf4992U,
  0xbea32f2cbf0cb54cU, 0xbec85aaa3cf88f35U, 0xbee8630dbf0f5041U, 0xbeb4ff61be0bef68U,
  0x3e843a7f3f673566U, 0x3e03857dbe4fd361U, 0x3f206a933e4c8adaU, 0x3d485b65be43735eU,
  0xbf1bf6a7bee8e221U, 0xbf27e0bbbe68379cU, 0x3e18d7143eab1e82U, 0xbf2cc1aabf07b574U,
  0x3e3aa86b3e193a54U, 0x3e526fdf3dcfd0a8U, 0x3f42489a3df5e929U, 0x3ce55c4cbf0b2ba0U,
  0x3f6a7943bf251c87U, 0x3efadaaebece2a4eU, 0xbeebac2f3f5a1db0U, 0x3cab36653f265d9aU,
  0x3e47fdc3bece571aU, 0x3f6c01563ebcc147U, 0x3d795263be2bc67cU, 0x3dfa8de33f5d301dU,
  0x3f40a949bd673ac4U, 0x3e6fea90bcf7bf98U, 0x3e97c8debd170629U, 0xbe442292bec9b47aU,
  0x3f1ebb2f3f57e16bU, 0x3eb5bb543f212c52U, 0xbe1c748fbd03e5eeU, 0x3f253dbcbef6213dU,
  0x3ecdc5c2bf00a5e8U, 0x3e5cdcfe3d5646edU, 0xbecb1f6dbd5162baU, 0x3f03d8df3d384df8U,
  0x3e3a6fcc3f5ad91fU, 0x3ee93826bb917cd3U, 0x3eed96123c6f2ee4U, 0x3efaaf973e86dc62U,
  0x3ece314d3d26fa3aU, 0xbdea62d6be34484bU, 0x3f24f076bd27920eU, 0xbbbf40a0bf254c4aU,
  0x3ef143de3f1a8faeU, 0x3f2b11d43f2bad5eU, 0x3f1e09dd3e34e028U, 0x3f19c78ebeb4d16dU,
  0x3f387592bf1036c5U, 0x3efd05d3bd76ff8dU, 0xbf11eb573f7e26e8U, 0x3e88b1e8be113ab8U,
  0xbd8b7df43dbfba31U, 0xbde9cd8fbd887f9fU, 0xbe14ebdb3e982cddU, 0xbe721257bd8f09a6U,
  0xbe17a0a83e46e8deU, 0x3cfa4b9ebe5dc1b3U, 0x3dfa953f3d827ff1U, 0xbe745132bdec85b9U,
  0x3d9a2521beaf6e23U, 0xbbb22906beae83cdU, 0xbe6f3416be28e548U, 0xbdf48af8be40f316U,
  0xbe11e8b6bc5573daU, 0xbeb712fcbeb83e96U, 0xbe2d246abdb83976U, 0xbe446a7ebe8f9621U,
  0x3ec9da993edd1508U, 0x3dea07293da224e2U, 0x3e2c6b263dfdd002U, 0xbe3257c03eb281d9U,
  0xbdcda6833ea7562dU, 0x3e25ce9a3edd88d4U, 0x3dade629be8255ddU, 0xbd87d507bda944c4U,
  0x3eb59708bac505dbU, 0x3d704a853f4c6570U, 0x3f86c57c3f2f8b35U, 0xbf58ebd7bf5ce3c9U,
  0xbf84611dbf9657f6U, 0x3f120981bed91071U, 0x3eab3550bee92661U, 0xbef7149a3ea87d9bU,
  0x3f81e4313f46d6abU, 0xbfd500f8bf2e141bU, 0xbfa3db84bfadedf8U, 0xbf2457693fbd92f9U,
  0xbdf34b773f72a5d6U, 0xbfaaa4323fc2033eU, 0xbfcdcea2bf2155b5U, 0xbe899076bfb97cb0U,
  0xbf9414ecbfb293e8U, 0xbe0eca96beb33459U, 0xbf060fd0be5b03e9U, 0x3f4e4204bf19c5fcU,
  0x3f4bc923bf6c2fd2U, 0xbf168bccbf0deed1U, 0x3ebf1b9d3f434c87U, 0xbe0e15893eff8f55U,
  0x3e8989edbe955122U, 0x3cab56f9U,
};


ai_handle g_network_weights_table[1 + 2] = {
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
  AI_HANDLE_PTR(s_network_weights_array_u64),
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
};

