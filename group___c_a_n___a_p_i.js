var group___c_a_n___a_p_i =
[
    [ "can_bit_timing_cfg_t", "group___c_a_n___a_p_i.html#structcan__bit__timing__cfg__t", [
      [ "baud_rate_prescaler", "group___c_a_n___a_p_i.html#a33ae62d869abaf989823b7bb1563de41", null ],
      [ "time_segment_1", "group___c_a_n___a_p_i.html#aafe4728b44b6abbb0f5d540e16d0be40", null ],
      [ "time_segment_2", "group___c_a_n___a_p_i.html#a4157f4d2f2bd13acd53ebc43c557c4f8", null ],
      [ "synchronization_jump_width", "group___c_a_n___a_p_i.html#aeb8eee8b6e6ea6a433c1ff5d89f68c4b", null ]
    ] ],
    [ "can_frame_t", "group___c_a_n___a_p_i.html#structcan__frame__t", [
      [ "id", "group___c_a_n___a_p_i.html#a49d4261f37f08f5a11cc3fc12c56cdc3", null ],
      [ "id_mode", "group___c_a_n___a_p_i.html#a4144eba26f77850571fca0498bec60ef", null ],
      [ "data_length_code", "group___c_a_n___a_p_i.html#af58b9f3fe19ed69e0a635cd271c68404", null ],
      [ "type", "group___c_a_n___a_p_i.html#a79046fddb934fd7ea0d0cc70b8d7f26d", null ],
      [ "options", "group___c_a_n___a_p_i.html#a27833816de50e1ad5b16b42856653ad8", null ],
      [ "data", "group___c_a_n___a_p_i.html#ad70086e98bfe0871e3f73d1f253138db", null ]
    ] ],
    [ "can_callback_args_t", "group___c_a_n___a_p_i.html#structcan__callback__args__t", [
      [ "channel", "group___c_a_n___a_p_i.html#a08080bddad2f04a8074b995da354f259", null ],
      [ "event", "group___c_a_n___a_p_i.html#a48fa3cf4c8c7e608c25ac8b907450096", null ],
      [ "error", "group___c_a_n___a_p_i.html#a39e131d3f8e8d6d8a14e9f248c1ac1e1", null ],
      [ "p_context", "group___c_a_n___a_p_i.html#a663ed64c927057ab0ac45d02505dc758", null ],
      [ "frame", "group___c_a_n___a_p_i.html#aa8706fd62e652e6582d3c9eb155fb610", null ]
    ] ],
    [ "can_mailbox_t", "group___c_a_n___a_p_i.html#structcan__mailbox__t", [
      [ "mailbox_id", "group___c_a_n___a_p_i.html#aa0c1d24b5896560908adb0ac9761aa28", null ],
      [ "id_mode", "group___c_a_n___a_p_i.html#a9d3924b6ba4efb4c978a04d0e9a4fbc6", null ],
      [ "mailbox_type", "group___c_a_n___a_p_i.html#aa6a30551456873fb921b933bd3ddbe23", null ],
      [ "frame_type", "group___c_a_n___a_p_i.html#af01f0306a9ad2e430154d9d6a4e3404f", null ]
    ] ],
    [ "can_cfg_t", "group___c_a_n___a_p_i.html#structcan__cfg__t", [
      [ "channel", "group___c_a_n___a_p_i.html#a12f266c39b851a037b4d30ae5661e46b", null ],
      [ "p_bit_timing", "group___c_a_n___a_p_i.html#a751918f74effc746b381a75c971af879", null ],
      [ "p_callback", "group___c_a_n___a_p_i.html#a8e79eb818c5aca4f925f2323f52d08f1", null ],
      [ "p_context", "group___c_a_n___a_p_i.html#a3699700f0a08a75159483ac2825dca90", null ],
      [ "p_extend", "group___c_a_n___a_p_i.html#a0715ca299b94eea0ef2843b99e0d32e5", null ],
      [ "ipl", "group___c_a_n___a_p_i.html#a31ab501a9df967965b8085592b4d2ba1", null ],
      [ "error_irq", "group___c_a_n___a_p_i.html#ac958a7179da3a9f365a3bf55707fac6d", null ],
      [ "mailbox_rx_irq", "group___c_a_n___a_p_i.html#a70c47efed0012e4512b7d7eca31e3e58", null ],
      [ "mailbox_tx_irq", "group___c_a_n___a_p_i.html#afe91f3dd74163cacafbfb96ab2104df0", null ],
      [ "p_mailbox", "group___c_a_n___a_p_i.html#a564584ef9e48317f93f432a0b86b9af8", null ],
      [ "id_mode", "group___c_a_n___a_p_i.html#a34bf75f61795800b3df706b240fd7907", null ],
      [ "mailbox_count", "group___c_a_n___a_p_i.html#a66e92277959e9e01a6ce2105dcdcbae6", null ],
      [ "message_mode", "group___c_a_n___a_p_i.html#a0cb83f81e41146d1e688f88a69231d38", null ]
    ] ],
    [ "can_api_t", "group___c_a_n___a_p_i.html#structcan__api__t", [
      [ "open", "group___c_a_n___a_p_i.html#a44ef1a1a3726114b30f228c54b0d44ce", null ],
      [ "write", "group___c_a_n___a_p_i.html#a0dcc61e0202ace6d5b91665464415adc", null ],
      [ "read", "group___c_a_n___a_p_i.html#af6c0a7c4a078f852e7c332369f8de9e2", null ],
      [ "close", "group___c_a_n___a_p_i.html#a32ec8d31d80a709bae881f2e28d36d6c", null ],
      [ "modeTransition", "group___c_a_n___a_p_i.html#afb37a7735c6ac61a151a083b2d25153b", null ],
      [ "infoGet", "group___c_a_n___a_p_i.html#aba27908c89442250d365d4a44304e3c1", null ],
      [ "callbackSet", "group___c_a_n___a_p_i.html#a0eeb3995e651ce4b77e8860ab50597a9", null ]
    ] ],
    [ "can_instance_t", "group___c_a_n___a_p_i.html#structcan__instance__t", [
      [ "p_ctrl", "group___c_a_n___a_p_i.html#ae4d4d032f3e4f0688879027286ae4dbe", null ],
      [ "p_cfg", "group___c_a_n___a_p_i.html#a064fa2cd7b88461619693b1e2cad9530", null ],
      [ "p_api", "group___c_a_n___a_p_i.html#a7630cfae3a82f8ecd7bbce599ef992ee", null ]
    ] ],
    [ "can_ctrl_t", "group___c_a_n___a_p_i.html#ga6e2484e96eefbe59327b13e2589a0049", null ],
    [ "can_event_t", "group___c_a_n___a_p_i.html#gacc2e5bc68e8b707c069ca27f521695db", [
      [ "CAN_EVENT_ERR_WARNING", "group___c_a_n___a_p_i.html#ggacc2e5bc68e8b707c069ca27f521695dba4cf2031ec5e169907edd2bd5d0caee00", null ],
      [ "CAN_EVENT_ERR_PASSIVE", "group___c_a_n___a_p_i.html#ggacc2e5bc68e8b707c069ca27f521695dbafd0c186a8462372ff19061f8ff97160f", null ],
      [ "CAN_EVENT_ERR_BUS_OFF", "group___c_a_n___a_p_i.html#ggacc2e5bc68e8b707c069ca27f521695dbad11062356307dd2b72a96a00a4929037", null ],
      [ "CAN_EVENT_BUS_RECOVERY", "group___c_a_n___a_p_i.html#ggacc2e5bc68e8b707c069ca27f521695dba4a9b30162960edad175a755686a65a50", null ],
      [ "CAN_EVENT_MAILBOX_MESSAGE_LOST", "group___c_a_n___a_p_i.html#ggacc2e5bc68e8b707c069ca27f521695dbaacf601c286d90d108d59de289cdfd80c", null ],
      [ "CAN_EVENT_ERR_BUS_LOCK", "group___c_a_n___a_p_i.html#ggacc2e5bc68e8b707c069ca27f521695dbabd3cace64bccbd9bdc6219453b7cfbbd", null ],
      [ "CAN_EVENT_ERR_CHANNEL", "group___c_a_n___a_p_i.html#ggacc2e5bc68e8b707c069ca27f521695dbab16a5328b930c53524aecbc4d580bb24", null ],
      [ "CAN_EVENT_TX_ABORTED", "group___c_a_n___a_p_i.html#ggacc2e5bc68e8b707c069ca27f521695dba973c55ab2a29a1554f488fedf29fea8a", null ],
      [ "CAN_EVENT_RX_COMPLETE", "group___c_a_n___a_p_i.html#ggacc2e5bc68e8b707c069ca27f521695dbaa0bc5e15cee037a1d102b517ef63e161", null ],
      [ "CAN_EVENT_TX_COMPLETE", "group___c_a_n___a_p_i.html#ggacc2e5bc68e8b707c069ca27f521695dbac169b4940b7cb76562efd7439fc76949", null ],
      [ "CAN_EVENT_ERR_GLOBAL", "group___c_a_n___a_p_i.html#ggacc2e5bc68e8b707c069ca27f521695dba8adaa142ed94841f5f282232ce414333", null ]
    ] ],
    [ "can_operation_mode_t", "group___c_a_n___a_p_i.html#gac29bd7d00b06d7457ae786471c296ba7", [
      [ "CAN_OPERATION_MODE_NORMAL", "group___c_a_n___a_p_i.html#ggac29bd7d00b06d7457ae786471c296ba7abde5d9e8f5711b6fe8374671c96e6f72", null ],
      [ "CAN_OPERATION_MODE_RESET", "group___c_a_n___a_p_i.html#ggac29bd7d00b06d7457ae786471c296ba7a91f40057ea820ca0cf30a52393d5d741", null ],
      [ "CAN_OPERATION_MODE_HALT", "group___c_a_n___a_p_i.html#ggac29bd7d00b06d7457ae786471c296ba7a38a4c4896b9a14a3fa8411468b5017ee", null ],
      [ "CAN_OPERATION_MODE_SLEEP", "group___c_a_n___a_p_i.html#ggac29bd7d00b06d7457ae786471c296ba7adaf544ef1adfe3c7db5634e04f765aa3", null ]
    ] ],
    [ "can_test_mode_t", "group___c_a_n___a_p_i.html#ga93f2b2c53f782b0c21beeb1339a108b7", [
      [ "CAN_TEST_MODE_DISABLED", "group___c_a_n___a_p_i.html#gga93f2b2c53f782b0c21beeb1339a108b7ae7dee8043ba34d7a3d09f5246bd870f0", null ],
      [ "CAN_TEST_MODE_LISTEN", "group___c_a_n___a_p_i.html#gga93f2b2c53f782b0c21beeb1339a108b7a8e80b696c1567281ef11cc0d659b29bc", null ],
      [ "CAN_TEST_MODE_LOOPBACK_EXTERNAL", "group___c_a_n___a_p_i.html#gga93f2b2c53f782b0c21beeb1339a108b7a892393a146c929398882d92a7c9303eb", null ],
      [ "CAN_TEST_MODE_LOOPBACK_INTERNAL", "group___c_a_n___a_p_i.html#gga93f2b2c53f782b0c21beeb1339a108b7a53216c2055f64910bb7a47d5aa239f90", null ],
      [ "CAN_TEST_MODE_INTERNAL_BUS", "group___c_a_n___a_p_i.html#gga93f2b2c53f782b0c21beeb1339a108b7a1a181f00a1eab8aaae36031a9e403e88", null ]
    ] ],
    [ "can_id_mode_t", "group___c_a_n___a_p_i.html#gabc98e244722dcea05b5ce91bdb4c70c8", [
      [ "CAN_ID_MODE_STANDARD", "group___c_a_n___a_p_i.html#ggabc98e244722dcea05b5ce91bdb4c70c8a5d29b837d94d14fb99868c2d0a5220b0", null ],
      [ "CAN_ID_MODE_EXTENDED", "group___c_a_n___a_p_i.html#ggabc98e244722dcea05b5ce91bdb4c70c8abc5a87ed8edf218a6b44e4cceb48c0cb", null ]
    ] ],
    [ "can_global_id_mode_t", "group___c_a_n___a_p_i.html#gab798132b937282be9589b6ed177ea999", [
      [ "CAN_GLOBAL_ID_MODE_STANDARD", "group___c_a_n___a_p_i.html#ggab798132b937282be9589b6ed177ea999af93ba7d9a4356ffa8c9b49f26c4f1b3d", null ],
      [ "CAN_GLOBAL_ID_MODE_EXTENDED", "group___c_a_n___a_p_i.html#ggab798132b937282be9589b6ed177ea999a7dc9d3f494129db1c953915d1b781faa", null ],
      [ "CAN_GLOBAL_ID_MODE_MIXED", "group___c_a_n___a_p_i.html#ggab798132b937282be9589b6ed177ea999aabdf871d5bbaf279c8dcf743ca64b488", null ]
    ] ],
    [ "can_frame_type_t", "group___c_a_n___a_p_i.html#gad3ffe1ae0429fcd1053a969d96c47610", [
      [ "CAN_FRAME_TYPE_DATA", "group___c_a_n___a_p_i.html#ggad3ffe1ae0429fcd1053a969d96c47610a1da44b52c2731b02cf02ca55eec08899", null ],
      [ "CAN_FRAME_TYPE_REMOTE", "group___c_a_n___a_p_i.html#ggad3ffe1ae0429fcd1053a969d96c47610a10c7ad0f4e083496ad3a3032fc533920", null ]
    ] ],
    [ "can_message_mode_t", "group___c_a_n___a_p_i.html#ga42c6d0b24e77b50c47ec54bafcac7604", [
      [ "CAN_MESSAGE_MODE_OVERWRITE", "group___c_a_n___a_p_i.html#gga42c6d0b24e77b50c47ec54bafcac7604ad8aab020d2b6d64777a0be580f44ddb4", null ],
      [ "CAN_MESSAGE_MODE_OVERRUN", "group___c_a_n___a_p_i.html#gga42c6d0b24e77b50c47ec54bafcac7604af25ce6de3b35f5abe47186351372b8b7", null ]
    ] ],
    [ "can_clock_source_t", "group___c_a_n___a_p_i.html#ga5bf3c71a3b53b409e9ee682c69189a39", [
      [ "CAN_CLOCK_SOURCE_PCLKB", "group___c_a_n___a_p_i.html#gga5bf3c71a3b53b409e9ee682c69189a39a7c0cedacb23a57e50692191f61915cbd", null ],
      [ "CAN_CLOCK_SOURCE_CANMCLK", "group___c_a_n___a_p_i.html#gga5bf3c71a3b53b409e9ee682c69189a39a5c90a69c9ba1a8116b6ec45ff238e117", null ]
    ] ],
    [ "can_mailbox_send_receive_t", "group___c_a_n___a_p_i.html#ga99db0880f7c03215e00781d3e57db3a3", [
      [ "CAN_MAILBOX_RECEIVE", "group___c_a_n___a_p_i.html#gga99db0880f7c03215e00781d3e57db3a3a5f4004ddfe179e388be8bb240527450e", null ],
      [ "CAN_MAILBOX_TRANSMIT", "group___c_a_n___a_p_i.html#gga99db0880f7c03215e00781d3e57db3a3a1c100296f7b9384c8e09b55fd611242d", null ]
    ] ]
];