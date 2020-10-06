var group___c_a_n___a_p_i =
[
    [ "can_bit_timing_cfg_t", "group___c_a_n___a_p_i.html#structcan__bit__timing__cfg__t", [
      [ "baud_rate_prescaler", "group___c_a_n___a_p_i.html#a33ae62d869abaf989823b7bb1563de41", null ],
      [ "time_segment_1", "group___c_a_n___a_p_i.html#a7127ea5ba7d0c09da9c5c7db44682b99", null ],
      [ "time_segment_2", "group___c_a_n___a_p_i.html#a51d2d4165d59650327ef2aef3b001390", null ],
      [ "synchronization_jump_width", "group___c_a_n___a_p_i.html#af1ad9a2ea8a49defb11650e854f213b9", null ]
    ] ],
    [ "can_frame_t", "group___c_a_n___a_p_i.html#structcan__frame__t", [
      [ "id", "group___c_a_n___a_p_i.html#a423c72dcd9f1926280e2180c7e7342cd", null ],
      [ "data_length_code", "group___c_a_n___a_p_i.html#af58b9f3fe19ed69e0a635cd271c68404", null ],
      [ "data", "group___c_a_n___a_p_i.html#a09d478fc07973c861c149147b842d4e6", null ],
      [ "type", "group___c_a_n___a_p_i.html#a79046fddb934fd7ea0d0cc70b8d7f26d", null ]
    ] ],
    [ "can_mailbox_t", "group___c_a_n___a_p_i.html#structcan__mailbox__t", [
      [ "mailbox_id", "group___c_a_n___a_p_i.html#aee84684f6d8674760af518e659ff9d98", null ],
      [ "mailbox_type", "group___c_a_n___a_p_i.html#aa6a30551456873fb921b933bd3ddbe23", null ],
      [ "frame_type", "group___c_a_n___a_p_i.html#af01f0306a9ad2e430154d9d6a4e3404f", null ]
    ] ],
    [ "can_callback_args_t", "group___c_a_n___a_p_i.html#structcan__callback__args__t", [
      [ "channel", "group___c_a_n___a_p_i.html#a08080bddad2f04a8074b995da354f259", null ],
      [ "event", "group___c_a_n___a_p_i.html#a48fa3cf4c8c7e608c25ac8b907450096", null ],
      [ "mailbox", "group___c_a_n___a_p_i.html#a92b2bae44686b544b24fb9f05647ad01", null ],
      [ "p_frame", "group___c_a_n___a_p_i.html#a34fbfff40d0155fb8016db8195b48f98", null ],
      [ "p_context", "group___c_a_n___a_p_i.html#a663ed64c927057ab0ac45d02505dc758", null ]
    ] ],
    [ "can_cfg_t", "group___c_a_n___a_p_i.html#structcan__cfg__t", [
      [ "channel", "group___c_a_n___a_p_i.html#a12f266c39b851a037b4d30ae5661e46b", null ],
      [ "p_bit_timing", "group___c_a_n___a_p_i.html#a751918f74effc746b381a75c971af879", null ],
      [ "id_mode", "group___c_a_n___a_p_i.html#a666e6f43f48d582c43890e41b9016a41", null ],
      [ "mailbox_count", "group___c_a_n___a_p_i.html#a66e92277959e9e01a6ce2105dcdcbae6", null ],
      [ "p_mailbox", "group___c_a_n___a_p_i.html#a564584ef9e48317f93f432a0b86b9af8", null ],
      [ "message_mode", "group___c_a_n___a_p_i.html#a0cb83f81e41146d1e688f88a69231d38", null ],
      [ "operation_mode", "group___c_a_n___a_p_i.html#a9de129329d3e68ac80594666a66769ba", null ],
      [ "test_mode", "group___c_a_n___a_p_i.html#abf7341399c6a294232dec9c78c6ade42", null ],
      [ "p_callback", "group___c_a_n___a_p_i.html#a8e79eb818c5aca4f925f2323f52d08f1", null ],
      [ "p_context", "group___c_a_n___a_p_i.html#a3699700f0a08a75159483ac2825dca90", null ],
      [ "p_extend", "group___c_a_n___a_p_i.html#a0715ca299b94eea0ef2843b99e0d32e5", null ],
      [ "ipl", "group___c_a_n___a_p_i.html#a31ab501a9df967965b8085592b4d2ba1", null ],
      [ "error_irq", "group___c_a_n___a_p_i.html#ac958a7179da3a9f365a3bf55707fac6d", null ],
      [ "mailbox_rx_irq", "group___c_a_n___a_p_i.html#a70c47efed0012e4512b7d7eca31e3e58", null ],
      [ "mailbox_tx_irq", "group___c_a_n___a_p_i.html#afe91f3dd74163cacafbfb96ab2104df0", null ]
    ] ],
    [ "can_api_t", "group___c_a_n___a_p_i.html#structcan__api__t", [
      [ "open", "group___c_a_n___a_p_i.html#a44ef1a1a3726114b30f228c54b0d44ce", null ],
      [ "write", "group___c_a_n___a_p_i.html#a795522061dd3240005aba0e6b936132f", null ],
      [ "close", "group___c_a_n___a_p_i.html#a32ec8d31d80a709bae881f2e28d36d6c", null ],
      [ "modeTransition", "group___c_a_n___a_p_i.html#afb37a7735c6ac61a151a083b2d25153b", null ],
      [ "infoGet", "group___c_a_n___a_p_i.html#aba27908c89442250d365d4a44304e3c1", null ],
      [ "callbackSet", "group___c_a_n___a_p_i.html#a0eeb3995e651ce4b77e8860ab50597a9", null ],
      [ "versionGet", "group___c_a_n___a_p_i.html#aa3a9393d2130549479111743b1750b41", null ]
    ] ],
    [ "can_instance_t", "group___c_a_n___a_p_i.html#structcan__instance__t", [
      [ "p_ctrl", "group___c_a_n___a_p_i.html#ae4d4d032f3e4f0688879027286ae4dbe", null ],
      [ "p_cfg", "group___c_a_n___a_p_i.html#a064fa2cd7b88461619693b1e2cad9530", null ],
      [ "p_api", "group___c_a_n___a_p_i.html#a7630cfae3a82f8ecd7bbce599ef992ee", null ]
    ] ],
    [ "can_id_t", "group___c_a_n___a_p_i.html#gad4cb716102402e9be0b5919cd2dd6ead", null ],
    [ "can_ctrl_t", "group___c_a_n___a_p_i.html#ga6e2484e96eefbe59327b13e2589a0049", null ],
    [ "can_event_t", "group___c_a_n___a_p_i.html#gacc2e5bc68e8b707c069ca27f521695db", [
      [ "CAN_EVENT_ERR_WARNING", "group___c_a_n___a_p_i.html#ggacc2e5bc68e8b707c069ca27f521695dba4cf2031ec5e169907edd2bd5d0caee00", null ],
      [ "CAN_EVENT_ERR_PASSIVE", "group___c_a_n___a_p_i.html#ggacc2e5bc68e8b707c069ca27f521695dbafd0c186a8462372ff19061f8ff97160f", null ],
      [ "CAN_EVENT_ERR_BUS_OFF", "group___c_a_n___a_p_i.html#ggacc2e5bc68e8b707c069ca27f521695dbad11062356307dd2b72a96a00a4929037", null ],
      [ "CAN_EVENT_BUS_RECOVERY", "group___c_a_n___a_p_i.html#ggacc2e5bc68e8b707c069ca27f521695dba4a9b30162960edad175a755686a65a50", null ],
      [ "CAN_EVENT_MAILBOX_MESSAGE_LOST", "group___c_a_n___a_p_i.html#ggacc2e5bc68e8b707c069ca27f521695dbaacf601c286d90d108d59de289cdfd80c", null ],
      [ "CAN_EVENT_RX_COMPLETE", "group___c_a_n___a_p_i.html#ggacc2e5bc68e8b707c069ca27f521695dbaa0bc5e15cee037a1d102b517ef63e161", null ],
      [ "CAN_EVENT_TX_COMPLETE", "group___c_a_n___a_p_i.html#ggacc2e5bc68e8b707c069ca27f521695dbac169b4940b7cb76562efd7439fc76949", null ]
    ] ],
    [ "can_status_t", "group___c_a_n___a_p_i.html#ga507b4ed3fc531e0c40aa8812174e3e1d", [
      [ "CAN_STATUS_NEW_DATA", "group___c_a_n___a_p_i.html#gga507b4ed3fc531e0c40aa8812174e3e1da44b1af154963d1f81a99d80cb68f279f", null ],
      [ "CAN_STATUS_SENT_DATA", "group___c_a_n___a_p_i.html#gga507b4ed3fc531e0c40aa8812174e3e1dad62a6cf78bc6f7eab84dcbb2a3401acd", null ],
      [ "CAN_STATUS_RECEIVE_FIFO", "group___c_a_n___a_p_i.html#gga507b4ed3fc531e0c40aa8812174e3e1daee4425fae03c9c915eea5c2a4fda609f", null ],
      [ "CAN_STATUS_TRANSMIT_FIFO", "group___c_a_n___a_p_i.html#gga507b4ed3fc531e0c40aa8812174e3e1dab2dda75d9dec6f4f6780e2f968dc177d", null ],
      [ "CAN_STATUS_NORMAL_MBOX_MESSAGE_LOST", "group___c_a_n___a_p_i.html#gga507b4ed3fc531e0c40aa8812174e3e1dad7fbdfdfe8636dbc45739fda699b8fa2", null ],
      [ "CAN_STATUS_FIFO_MBOX_MESSAGE_LOST", "group___c_a_n___a_p_i.html#gga507b4ed3fc531e0c40aa8812174e3e1dab6a11467700aa53191e9ae8c7c4ab23f", null ],
      [ "CAN_STATUS_TRANSMISSION_ABORT", "group___c_a_n___a_p_i.html#gga507b4ed3fc531e0c40aa8812174e3e1dace73309e8a8c0937ecf442f1a90ecc14", null ],
      [ "CAN_STATUS_ERROR", "group___c_a_n___a_p_i.html#gga507b4ed3fc531e0c40aa8812174e3e1da6367584ac42dd8a820dc5245f9ef8e89", null ],
      [ "CAN_STATUS_RESET_MODE", "group___c_a_n___a_p_i.html#gga507b4ed3fc531e0c40aa8812174e3e1da1abf51e6347229f3a093e22670b828b0", null ],
      [ "CAN_STATUS_HALT_MODE", "group___c_a_n___a_p_i.html#gga507b4ed3fc531e0c40aa8812174e3e1dad3b110d4bf8f06c66f59e45eb2adc317", null ],
      [ "CAN_STATUS_SLEEP_MODE", "group___c_a_n___a_p_i.html#gga507b4ed3fc531e0c40aa8812174e3e1daae9c41b396ddf88f003b83f68095c323", null ],
      [ "CAN_STATUS_ERROR_PASSIVE", "group___c_a_n___a_p_i.html#gga507b4ed3fc531e0c40aa8812174e3e1dadba914ee82427aea2fc1ebfef1624bef", null ],
      [ "CAN_STATUS_BUS_OFF", "group___c_a_n___a_p_i.html#gga507b4ed3fc531e0c40aa8812174e3e1da82ce02b7988100673b68d4d8097c479f", null ]
    ] ],
    [ "can_error_t", "group___c_a_n___a_p_i.html#ga6d777202844afdced277cb7edb5f659c", [
      [ "CAN_ERROR_STUFF", "group___c_a_n___a_p_i.html#gga6d777202844afdced277cb7edb5f659ca83689dbb5c4ea9b3ef351f64b40155fa", null ],
      [ "CAN_ERROR_FORM", "group___c_a_n___a_p_i.html#gga6d777202844afdced277cb7edb5f659ca225beca2274575939d123e3c4512c49f", null ],
      [ "CAN_ERROR_ACK", "group___c_a_n___a_p_i.html#gga6d777202844afdced277cb7edb5f659cabd43a054ac70bc0999a7a480bb795d5a", null ],
      [ "CAN_ERROR_CRC", "group___c_a_n___a_p_i.html#gga6d777202844afdced277cb7edb5f659cad4604379becaa13df2444c3bb84934dc", null ],
      [ "CAN_ERROR_BIT_RECESSIVE", "group___c_a_n___a_p_i.html#gga6d777202844afdced277cb7edb5f659ca6695c5611227ddd4bd29bd5f965a3cde", null ],
      [ "CAN_ERROR_BIT_DOMINANT", "group___c_a_n___a_p_i.html#gga6d777202844afdced277cb7edb5f659caaa624ddb5e00f243bb07c3bd1530af30", null ],
      [ "CAN_ERROR_ACK_DELIMITER", "group___c_a_n___a_p_i.html#gga6d777202844afdced277cb7edb5f659ca3f50326451e594774edaaf5ec3d86102", null ],
      [ "CAN_ERROR_ERROR_DISPLAY_MODE", "group___c_a_n___a_p_i.html#gga6d777202844afdced277cb7edb5f659ca1107ee480bb64f0f5dd4907253fc0fbe", null ]
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
      [ "CAN_TEST_MODE_LOOPBACK_INTERNAL", "group___c_a_n___a_p_i.html#gga93f2b2c53f782b0c21beeb1339a108b7a53216c2055f64910bb7a47d5aa239f90", null ]
    ] ],
    [ "can_id_mode_t", "group___c_a_n___a_p_i.html#gabc98e244722dcea05b5ce91bdb4c70c8", [
      [ "CAN_ID_MODE_STANDARD", "group___c_a_n___a_p_i.html#ggabc98e244722dcea05b5ce91bdb4c70c8a5d29b837d94d14fb99868c2d0a5220b0", null ],
      [ "CAN_ID_MODE_EXTENDED", "group___c_a_n___a_p_i.html#ggabc98e244722dcea05b5ce91bdb4c70c8abc5a87ed8edf218a6b44e4cceb48c0cb", null ]
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
    [ "can_time_segment1_t", "group___c_a_n___a_p_i.html#ga8cd82cb0068dd4193599e5ef03457af5", [
      [ "CAN_TIME_SEGMENT1_TQ4", "group___c_a_n___a_p_i.html#gga8cd82cb0068dd4193599e5ef03457af5aae3969682d8df111098a8565f88d0295", null ],
      [ "CAN_TIME_SEGMENT1_TQ5", "group___c_a_n___a_p_i.html#gga8cd82cb0068dd4193599e5ef03457af5a59b83c6c7818be79f3be91ac509d2bca", null ],
      [ "CAN_TIME_SEGMENT1_TQ6", "group___c_a_n___a_p_i.html#gga8cd82cb0068dd4193599e5ef03457af5af3245f714dfae709bdee745dff2fdd52", null ],
      [ "CAN_TIME_SEGMENT1_TQ7", "group___c_a_n___a_p_i.html#gga8cd82cb0068dd4193599e5ef03457af5a313cf6c8d036ca124ffd683a4d62eb8a", null ],
      [ "CAN_TIME_SEGMENT1_TQ8", "group___c_a_n___a_p_i.html#gga8cd82cb0068dd4193599e5ef03457af5aed1daad68bef5596c41c236f8b601dd1", null ],
      [ "CAN_TIME_SEGMENT1_TQ9", "group___c_a_n___a_p_i.html#gga8cd82cb0068dd4193599e5ef03457af5a04aff84519646e3183da4a30f7dfb932", null ],
      [ "CAN_TIME_SEGMENT1_TQ10", "group___c_a_n___a_p_i.html#gga8cd82cb0068dd4193599e5ef03457af5a985a7d84c5f5d6c61732b07a620405fc", null ],
      [ "CAN_TIME_SEGMENT1_TQ11", "group___c_a_n___a_p_i.html#gga8cd82cb0068dd4193599e5ef03457af5a1cf5d3658622a3642e159068da32ee9a", null ],
      [ "CAN_TIME_SEGMENT1_TQ12", "group___c_a_n___a_p_i.html#gga8cd82cb0068dd4193599e5ef03457af5a3a9798939b288c033a0a746d48aff8ab", null ],
      [ "CAN_TIME_SEGMENT1_TQ13", "group___c_a_n___a_p_i.html#gga8cd82cb0068dd4193599e5ef03457af5ac5e1db2bc7acd7cbf228cc1d14cf2c80", null ],
      [ "CAN_TIME_SEGMENT1_TQ14", "group___c_a_n___a_p_i.html#gga8cd82cb0068dd4193599e5ef03457af5a3384cfdde6ce3b8c5096ed229cc12156", null ],
      [ "CAN_TIME_SEGMENT1_TQ15", "group___c_a_n___a_p_i.html#gga8cd82cb0068dd4193599e5ef03457af5a23b245409e185001548f01fce95c1334", null ],
      [ "CAN_TIME_SEGMENT1_TQ16", "group___c_a_n___a_p_i.html#gga8cd82cb0068dd4193599e5ef03457af5af3ec9c066f13ef7923af90b3c78b15c9", null ]
    ] ],
    [ "can_time_segment2_t", "group___c_a_n___a_p_i.html#ga8fe54dfc53ae7746f947826be715e8ba", [
      [ "CAN_TIME_SEGMENT2_TQ2", "group___c_a_n___a_p_i.html#gga8fe54dfc53ae7746f947826be715e8baa8ecd3147340260b84452c93b3c19a9b5", null ],
      [ "CAN_TIME_SEGMENT2_TQ3", "group___c_a_n___a_p_i.html#gga8fe54dfc53ae7746f947826be715e8baa26ac1ecc10fc024bbf9c6f617551c691", null ],
      [ "CAN_TIME_SEGMENT2_TQ4", "group___c_a_n___a_p_i.html#gga8fe54dfc53ae7746f947826be715e8baa415745dc6fcddae619994b2f3e185f86", null ],
      [ "CAN_TIME_SEGMENT2_TQ5", "group___c_a_n___a_p_i.html#gga8fe54dfc53ae7746f947826be715e8baabe20f18aaa64ab2e7e5799e8734ccaa1", null ],
      [ "CAN_TIME_SEGMENT2_TQ6", "group___c_a_n___a_p_i.html#gga8fe54dfc53ae7746f947826be715e8baa3a1cb0e7baae5c30117a483fe71279d9", null ],
      [ "CAN_TIME_SEGMENT2_TQ7", "group___c_a_n___a_p_i.html#gga8fe54dfc53ae7746f947826be715e8baa32e1d2a8c30947f57a68a42558d12a0d", null ],
      [ "CAN_TIME_SEGMENT2_TQ8", "group___c_a_n___a_p_i.html#gga8fe54dfc53ae7746f947826be715e8baa6e3b82e2f55a89c3ec82d1c166c70ce9", null ]
    ] ],
    [ "can_sync_jump_width_t", "group___c_a_n___a_p_i.html#ga22b79812c12d9bc63daeb01ff85c6622", [
      [ "CAN_SYNC_JUMP_WIDTH_TQ1", "group___c_a_n___a_p_i.html#gga22b79812c12d9bc63daeb01ff85c6622a9aa706b09e35bc1ffdd0f88a16574af3", null ],
      [ "CAN_SYNC_JUMP_WIDTH_TQ2", "group___c_a_n___a_p_i.html#gga22b79812c12d9bc63daeb01ff85c6622a808a1591d10bb2a143d2d5d8622f9854", null ],
      [ "CAN_SYNC_JUMP_WIDTH_TQ3", "group___c_a_n___a_p_i.html#gga22b79812c12d9bc63daeb01ff85c6622a0f527c3014ff1ca3ec367424fafc1cc5", null ],
      [ "CAN_SYNC_JUMP_WIDTH_TQ4", "group___c_a_n___a_p_i.html#gga22b79812c12d9bc63daeb01ff85c6622a2e3c056793d51a4e2a24347b20b11ea9", null ]
    ] ],
    [ "can_mailbox_send_receive_t", "group___c_a_n___a_p_i.html#ga99db0880f7c03215e00781d3e57db3a3", [
      [ "CAN_MAILBOX_RECEIVE", "group___c_a_n___a_p_i.html#gga99db0880f7c03215e00781d3e57db3a3a5f4004ddfe179e388be8bb240527450e", null ],
      [ "CAN_MAILBOX_TRANSMIT", "group___c_a_n___a_p_i.html#gga99db0880f7c03215e00781d3e57db3a3a1c100296f7b9384c8e09b55fd611242d", null ]
    ] ]
];