var group___p_t_p___a_p_i =
[
    [ "ptp_clock_properties_t", "group___p_t_p___a_p_i.html#structptp__clock__properties__t", [
      [ "priority1", "group___p_t_p___a_p_i.html#a130322bddd2c41518677de7786b02826", null ],
      [ "cclass", "group___p_t_p___a_p_i.html#acca961410d7e83947f8507e8cc15cd28", null ],
      [ "accuracy", "group___p_t_p___a_p_i.html#a55f86a5d01e1d8a24307ea7182c1696c", null ],
      [ "variance", "group___p_t_p___a_p_i.html#a822688c8785df6d910f92051ff558f5a", null ],
      [ "priority2", "group___p_t_p___a_p_i.html#a8e9c9e9ae237d1aec9bffc72d9511929", null ]
    ] ],
    [ "ptp_time_t", "group___p_t_p___a_p_i.html#structptp__time__t", [
      [ "seconds_upper", "group___p_t_p___a_p_i.html#a0a56c617bdfbf239bb1c4bd7aab438d5", null ],
      [ "seconds_lower", "group___p_t_p___a_p_i.html#ab4fe3125f0ac05f6956438cb0cc348a1", null ],
      [ "nanoseconds", "group___p_t_p___a_p_i.html#a1b51aaa1cc5d99d8721c53e96d611ec9", null ]
    ] ],
    [ "ptp_message_flags_t", "group___p_t_p___a_p_i.html#structptp__message__flags__t", null ],
    [ "ptp_message_header_t", "group___p_t_p___a_p_i.html#structptp__message__header__t", [
      [ "message_type", "group___p_t_p___a_p_i.html#aec1dad61d1dcce0e13690e7f3c70615b", null ],
      [ "sdoid_major", "group___p_t_p___a_p_i.html#a26a982f4668004afbbe3d039b8e5bdf1", null ],
      [ "version", "group___p_t_p___a_p_i.html#a5d9dd652591f35448cc1fbb93eeb7698", null ],
      [ "minor_version", "group___p_t_p___a_p_i.html#aa0e93e5e3552d227264ee9073059d743", null ],
      [ "message_length", "group___p_t_p___a_p_i.html#a5f59ab0b3aad174817b679b0cf33efeb", null ],
      [ "domain", "group___p_t_p___a_p_i.html#a7ae8248a4e69c003ff55bdc311677931", null ],
      [ "sdoid_minor", "group___p_t_p___a_p_i.html#a794da8fd7743b605fc6e7d942b906345", null ],
      [ "flags", "group___p_t_p___a_p_i.html#a3b87e2ac2e924ea89a9272b7b8c34692", null ],
      [ "correction_field", "group___p_t_p___a_p_i.html#a2b149b04dab6a3eeb43c31ba4c8c0626", null ],
      [ "clock_id", "group___p_t_p___a_p_i.html#ad16718c4538ce910c86d4ec2c9972e28", null ],
      [ "source_port_id", "group___p_t_p___a_p_i.html#ac2e2ee9435d560a3abfdfd893dc54654", null ],
      [ "sequence_id", "group___p_t_p___a_p_i.html#a6ca77807f296491b97b64f2750eb3412", null ],
      [ "control_field", "group___p_t_p___a_p_i.html#a65f738413281757f52f57111a065bc6a", null ],
      [ "log_message_interval", "group___p_t_p___a_p_i.html#ac6a940a418fb7330b6b3a072c9548b3a", null ]
    ] ],
    [ "ptp_message_sync_t", "group___p_t_p___a_p_i.html#structptp__message__sync__t", [
      [ "origin_timestamp", "group___p_t_p___a_p_i.html#af252b6a3b66eb8cb351b292034762d4f", null ]
    ] ],
    [ "ptp_message_pdelay_req_t", "group___p_t_p___a_p_i.html#structptp__message__pdelay__req__t", [
      [ "origin_timestamp", "group___p_t_p___a_p_i.html#a48d834a446c9610a464545e862ef76f0", null ]
    ] ],
    [ "ptp_message_pdelay_resp_t", "group___p_t_p___a_p_i.html#structptp__message__pdelay__resp__t", [
      [ "origin_timestamp", "group___p_t_p___a_p_i.html#addaae805d83d5b66a941d64d421ab261", null ],
      [ "source_port_identity", "group___p_t_p___a_p_i.html#a2344a86cb5aa12e439ac7da53c95f28c", null ]
    ] ],
    [ "ptp_message_announce_t", "group___p_t_p___a_p_i.html#structptp__message__announce__t", [
      [ "origin_timestamp", "group___p_t_p___a_p_i.html#a769942ce3b25d99a22f91b47a62a4ec8", null ],
      [ "current_utc_offset", "group___p_t_p___a_p_i.html#adfa2fd53ba4fba18a8df9f5b0cfe400f", null ],
      [ "clock_properties", "group___p_t_p___a_p_i.html#a5a50eef7881b40397a82bc186adb7258", null ],
      [ "clock_id", "group___p_t_p___a_p_i.html#af94f76ab8aef7cb3bb148bccaf3c2882", null ],
      [ "steps_removed", "group___p_t_p___a_p_i.html#aae21fdccb0a895f592f88353e84f41d8", null ],
      [ "time_source", "group___p_t_p___a_p_i.html#ae18a47fab9b4aa34403787823c5cd7b2", null ]
    ] ],
    [ "ptp_message_signaling_t", "group___p_t_p___a_p_i.html#structptp__message__signaling__t", [
      [ "target_clock_id", "group___p_t_p___a_p_i.html#a3b0ae861c2e9ae82db6671b1e74b711d", null ],
      [ "target_port_id", "group___p_t_p___a_p_i.html#a08700666a7ee46414b67d9bcc43e10d3", null ]
    ] ],
    [ "ptp_message_management_t", "group___p_t_p___a_p_i.html#structptp__message__management__t", [
      [ "target_clock_id", "group___p_t_p___a_p_i.html#ac282cd23874d782c90f44ad6c68f4204", null ],
      [ "target_port_id", "group___p_t_p___a_p_i.html#a6b322a99624fdaa7f6ba75f600b17323", null ],
      [ "starting_boundary_hops", "group___p_t_p___a_p_i.html#aa8d1c5eb1c6abf5644421bc1e4db92fc", null ],
      [ "boundary_hops", "group___p_t_p___a_p_i.html#a47027dee0e55b9e761338dce10980514", null ],
      [ "action", "group___p_t_p___a_p_i.html#a75ee5f506bede0d9060eddbc2d78be82", null ]
    ] ],
    [ "ptp_message_t", "group___p_t_p___a_p_i.html#structptp__message__t", [
      [ "header", "group___p_t_p___a_p_i.html#a9fc56e8a4c02e45355b28387b6f4f8d7", null ]
    ] ],
    [ "ptp_callback_args_t", "group___p_t_p___a_p_i.html#structptp__callback__args__t", [
      [ "event", "group___p_t_p___a_p_i.html#a85b99f7657cc3c6be615f6aab23a990a", null ],
      [ "p_message", "group___p_t_p___a_p_i.html#a223a52551c562f3b009301aed9805a39", null ],
      [ "p_tlv_data", "group___p_t_p___a_p_i.html#a3ec8cd6fa9f6536a0366e74dc2b6bc40", null ],
      [ "tlv_data_size", "group___p_t_p___a_p_i.html#a4479e95a75cf12039d631ff58c7e6b65", null ],
      [ "pulse_timer_channel", "group___p_t_p___a_p_i.html#adbbab3647453c2c5471f7f418c299bc1", null ],
      [ "p_context", "group___p_t_p___a_p_i.html#a56d5ccc8e56e6d0be7185d861ba9a1bb", null ]
    ] ],
    [ "ptp_pulse_timer_common_cfg_t", "group___p_t_p___a_p_i.html#structptp__pulse__timer__common__cfg__t", [
      [ "ipls_rising_irq", "group___p_t_p___a_p_i.html#a383fc5e11165b3450ec796105cc77084", null ],
      [ "ipls_falling_irq", "group___p_t_p___a_p_i.html#a709a235973db7400350c0d607ac17e4b", null ],
      [ "ipls_rising_irq_auto_clear", "group___p_t_p___a_p_i.html#adc8889e40b5e96e3d491f8d8b8d8bf11", null ],
      [ "ipls_falling_irq_auto_clear", "group___p_t_p___a_p_i.html#ac6c5dc2f3278fac9d671ac28913b8a17", null ]
    ] ],
    [ "ptp_pulse_timer_cfg_t", "group___p_t_p___a_p_i.html#structptp__pulse__timer__cfg__t", [
      [ "start_time", "group___p_t_p___a_p_i.html#aea3de9bcaefbd1295c68cdc51e3e8d29", null ],
      [ "period", "group___p_t_p___a_p_i.html#a5d86e4e11cbfaf287462cae9af53e0b7", null ],
      [ "pulse", "group___p_t_p___a_p_i.html#a5c510b7dd38a3196f80a272849cb4e32", null ],
      [ "mint_rising_irq", "group___p_t_p___a_p_i.html#ae5a5ec3cc891dab0eaf01e74be80fa44", null ],
      [ "ipls_rising_event", "group___p_t_p___a_p_i.html#afd33c613706bf6994609198cf9ed1660", null ],
      [ "ipls_falling_event", "group___p_t_p___a_p_i.html#aeb06857b8c3ea483e366c6f7155be790", null ],
      [ "ipls_rising_event_auto_clear", "group___p_t_p___a_p_i.html#a9770944cbb664f9f3cc981fb81b37ef6", null ],
      [ "ipls_falling_event_auto_clear", "group___p_t_p___a_p_i.html#a8ae29ad4315f13a17606fcc2bf2de586", null ],
      [ "ipls_irq_source", "group___p_t_p___a_p_i.html#a5854faf9f7a8cc05d655396ba4212510", null ]
    ] ],
    [ "ptp_sync_state_cfg_t", "group___p_t_p___a_p_i.html#structptp__sync__state__cfg__t", [
      [ "threshold", "group___p_t_p___a_p_i.html#a60e92da581112a1113313119565bdce0", null ],
      [ "count", "group___p_t_p___a_p_i.html#aef6b4221fcbfdb27f77ef9fff9daef73", null ]
    ] ],
    [ "ptp_synfp_cfg_t", "group___p_t_p___a_p_i.html#structptp__synfp__cfg__t", [
      [ "ethernet_phy_interface", "group___p_t_p___a_p_i.html#a08a1a771170cfe1396f3275a3f9be994", null ],
      [ "frame_format", "group___p_t_p___a_p_i.html#a8dabf3b79220d66d3951bc4fc42ad40d", null ],
      [ "frame_filter", "group___p_t_p___a_p_i.html#afd2f1c5332bdeb73f22c2793fa47fbc9", null ],
      [ "clock_domain", "group___p_t_p___a_p_i.html#ae05d8c654f8f059119273e6a9069d962", null ],
      [ "clock_domain_filter", "group___p_t_p___a_p_i.html#a76bc771a7b21e290848061bd4bf44e08", null ],
      [ "announce_interval", "group___p_t_p___a_p_i.html#a6c9cd01acddd9c14eae3bc94347d5582", null ],
      [ "sync_interval", "group___p_t_p___a_p_i.html#af37b1ce369c98d53a662632171cea6a0", null ],
      [ "delay_req_interval", "group___p_t_p___a_p_i.html#acf0e59bc01f625f69191c1ae51a248c6", null ],
      [ "message_timeout", "group___p_t_p___a_p_i.html#a21ec3cfaa60eaff97d0bdbf00005b0b8", null ],
      [ "clock_properties", "group___p_t_p___a_p_i.html#a61b7009af3a05be4961d55f5c7fc40a1", null ],
      [ "timesource", "group___p_t_p___a_p_i.html#abb8328bc2ec847755c59d9508152c455", null ],
      [ "p_multicast_addr_filter", "group___p_t_p___a_p_i.html#a80d387b424e8e014e168acbfccad06e4", null ],
      [ "ether", "group___p_t_p___a_p_i.html#a8ca935fb79b8aac68b21c0d188c0d782", null ],
      [ "ipv4", "group___p_t_p___a_p_i.html#a694dfeb02811ea3dd80a8660dba87691", null ]
    ] ],
    [ "ptp_synfp_cfg_t.ether", "group___p_t_p___a_p_i.html#structptp__synfp__cfg__t_8ether", [
      [ "p_primary_mac_addr", "group___p_t_p___a_p_i.html#a0f927a373824bd7c043a987878931431", null ],
      [ "p_pdelay_mac_addr", "group___p_t_p___a_p_i.html#a4ba8379e5d7d136e7b1ec8c230a13ff9", null ]
    ] ],
    [ "ptp_synfp_cfg_t.ipv4", "group___p_t_p___a_p_i.html#structptp__synfp__cfg__t_8ipv4", [
      [ "primary_ip_addr", "group___p_t_p___a_p_i.html#ae8f88b9e33d50edadce7bfd49213f83b", null ],
      [ "pdelay_ip_addr", "group___p_t_p___a_p_i.html#aab1135dd7468dffdef07c3970be6d748", null ],
      [ "event_tos", "group___p_t_p___a_p_i.html#a586b79d65f450846df46cc1bc5156b2b", null ],
      [ "general_tos", "group___p_t_p___a_p_i.html#a1b36379c7fd9b2846dc3f49ce03e4ef7", null ],
      [ "primary_ttl", "group___p_t_p___a_p_i.html#aa2815f8357258fd20f763d62b08286d9", null ],
      [ "pdelay_ttl", "group___p_t_p___a_p_i.html#af139cd2c8105e5df026e08aa6d71abb6", null ],
      [ "event_udp_port", "group___p_t_p___a_p_i.html#a74653199001bc57f05fb1dd2b67bec99", null ],
      [ "general_udp_port", "group___p_t_p___a_p_i.html#aacd7ad6ef510d15ca81a58edad9c15f0", null ]
    ] ],
    [ "ptp_stca_cfg_t", "group___p_t_p___a_p_i.html#structptp__stca__cfg__t", [
      [ "clock_freq", "group___p_t_p___a_p_i.html#aa68e323afb8835572c2430432a09f6f5", null ],
      [ "clock_sel", "group___p_t_p___a_p_i.html#af0b7856331bba3d8d0b6475314c662ca", null ],
      [ "clock_correction_mode", "group___p_t_p___a_p_i.html#a491655652252dab40dec6f444b10950e", null ],
      [ "gradient_worst10_interval", "group___p_t_p___a_p_i.html#a6a29b1beb38a9e80b6d945c8c37c9e8e", null ],
      [ "sync_threshold", "group___p_t_p___a_p_i.html#a2dc323f84ad42a09f82399bacb0d76c4", null ],
      [ "sync_loss_threshold", "group___p_t_p___a_p_i.html#aa6ae28b290cc11a7b354bb9264b7d0aa", null ]
    ] ],
    [ "ptp_cfg_t", "group___p_t_p___a_p_i.html#structptp__cfg__t", [
      [ "synfp", "group___p_t_p___a_p_i.html#a6a55f739d029cf392039b8cfce3f5d5c", null ],
      [ "stca", "group___p_t_p___a_p_i.html#ab26b00393c3adea960ae86dcd6df0610", null ],
      [ "p_edmac_instance", "group___p_t_p___a_p_i.html#adb43f93d8285f9601a273dc9d486c144", null ],
      [ "buffer_size", "group___p_t_p___a_p_i.html#a49fcfc222a7c7fe69865bb363fdcb3cc", null ],
      [ "p_rx_buffers", "group___p_t_p___a_p_i.html#aa8d00091378f66836f8f4971b83d3291", null ],
      [ "p_tx_buffers", "group___p_t_p___a_p_i.html#aa7f26533efb6458d06f9fd60533fa345", null ],
      [ "mint_irq", "group___p_t_p___a_p_i.html#a6967d60b95d1817e1653c0992ae89e73", null ],
      [ "ipls_irq", "group___p_t_p___a_p_i.html#ab94a111d491b1614960c7c1b7bcd0e5a", null ],
      [ "mint_ipl", "group___p_t_p___a_p_i.html#a5beed4e4bba8e7b152024f4bee0c84a9", null ],
      [ "ipls_ipl", "group___p_t_p___a_p_i.html#a10c5fe366e891a5b93608867c0bc1c62", null ],
      [ "p_callback", "group___p_t_p___a_p_i.html#a7f2e9b56803f1cb3d2fb06997537532b", null ]
    ] ],
    [ "ptp_api_t", "group___p_t_p___a_p_i.html#structptp__api__t", [
      [ "open", "group___p_t_p___a_p_i.html#ab5c5a3285336842f7c44a8e8954a6382", null ],
      [ "macAddrSet", "group___p_t_p___a_p_i.html#a807b189c7987b1f2d972f4f1fb5af55b", null ],
      [ "ipAddrSet", "group___p_t_p___a_p_i.html#ad5f07a92c3563dd682ee13f548f2bb76", null ],
      [ "localClockIdSet", "group___p_t_p___a_p_i.html#a06e922d35f8c477b1d929a1847d2d273", null ],
      [ "masterClockIdSet", "group___p_t_p___a_p_i.html#a412c4ca0c0f16a2c447bac098cd07184", null ],
      [ "messageFlagsSet", "group___p_t_p___a_p_i.html#abe50284d5ff38e62e2702c135f0674d2", null ],
      [ "currentUtcOffsetSet", "group___p_t_p___a_p_i.html#ac56ac84b683491b29b92e5fd33e3c70e", null ],
      [ "portStateSet", "group___p_t_p___a_p_i.html#a55d6e455b502644258e4bfb55152dea1", null ],
      [ "messageSend", "group___p_t_p___a_p_i.html#a3e765c401379982e08ef2c5786343280", null ],
      [ "localClockValueSet", "group___p_t_p___a_p_i.html#a98d7e44f46454c96d43831ee7e66455e", null ],
      [ "localClockValueGet", "group___p_t_p___a_p_i.html#a72ba77657f891c2253678b87526cb206", null ],
      [ "pulseTimerCommonConfig", "group___p_t_p___a_p_i.html#a3a4f87618ed1e25abe7d61a569d7dac3", null ],
      [ "pulseTimerEnable", "group___p_t_p___a_p_i.html#a28a8fdf928bb7595d3f5b131bdfe1d8d", null ],
      [ "pulseTimerDisable", "group___p_t_p___a_p_i.html#a1f6219692e39e4fdda71100ab92dba9e", null ],
      [ "close", "group___p_t_p___a_p_i.html#affa30a9c253e0a32d42e35a90fddc1e8", null ]
    ] ],
    [ "ptp_instance_t", "group___p_t_p___a_p_i.html#structptp__instance__t", [
      [ "p_ctrl", "group___p_t_p___a_p_i.html#a9133bdac2e7390cd18c7eb7d4c45766c", null ],
      [ "p_cfg", "group___p_t_p___a_p_i.html#af7915b2813899a8c9753d5bdcda0f53c", null ],
      [ "p_api", "group___p_t_p___a_p_i.html#a9586ac3de39ea3c8e4aa9183572f1d15", null ]
    ] ],
    [ "ptp_ctrl_field_t", "group___p_t_p___a_p_i.html#ga302d95067285fb7c391e30a4f9294154", null ],
    [ "ptp_message_delay_req_t", "group___p_t_p___a_p_i.html#gab820cbbb006af92f1979a7d6b3a5668b", null ],
    [ "ptp_message_follow_up_t", "group___p_t_p___a_p_i.html#ga9b79b3b86a834490cde859d556b1b86e", null ],
    [ "ptp_message_delay_resp_t", "group___p_t_p___a_p_i.html#gadcf5ca10235d0caf05f44726719b11f9", null ],
    [ "ptp_message_pdelay_resp_follow_up_t", "group___p_t_p___a_p_i.html#ga238f188f1535add576ae1ece2087fe39", null ],
    [ "ptp_message_type_t", "group___p_t_p___a_p_i.html#gad488af97304ef1466637952ecb35ea37", [
      [ "PTP_MESSAGE_TYPE_SYNC", "group___p_t_p___a_p_i.html#ggad488af97304ef1466637952ecb35ea37ada5fbad390f28196dee5c8e0260cb182", null ],
      [ "PTP_MESSAGE_TYPE_DELAY_REQ", "group___p_t_p___a_p_i.html#ggad488af97304ef1466637952ecb35ea37a96994166624c427d11e04e2e3bddb2fe", null ],
      [ "PTP_MESSAGE_TYPE_PDELAY_REQ", "group___p_t_p___a_p_i.html#ggad488af97304ef1466637952ecb35ea37ad1c4e806a480591d131dcd0c7df89646", null ],
      [ "PTP_MESSAGE_TYPE_PDELAY_RESP", "group___p_t_p___a_p_i.html#ggad488af97304ef1466637952ecb35ea37a14c2fa08557663a5fd9b8546e8b7ad06", null ],
      [ "PTP_MESSAGE_TYPE_FOLLOW_UP", "group___p_t_p___a_p_i.html#ggad488af97304ef1466637952ecb35ea37abdc0441e058f68302792b24076e426e3", null ],
      [ "PTP_MESSAGE_TYPE_DELAY_RESP", "group___p_t_p___a_p_i.html#ggad488af97304ef1466637952ecb35ea37a1ae571a0f57cad3571b9bd448cd52cb0", null ],
      [ "PTP_MESSAGE_TYPE_PDELAY_RESP_FOLLOW_UP", "group___p_t_p___a_p_i.html#ggad488af97304ef1466637952ecb35ea37a61fe5de16df58276f94adc0c96106eb5", null ],
      [ "PTP_MESSAGE_TYPE_ANNOUNCE", "group___p_t_p___a_p_i.html#ggad488af97304ef1466637952ecb35ea37ad26c9ce538d7d315f7e7c35265696e27", null ],
      [ "PTP_MESSAGE_TYPE_SIGNALING", "group___p_t_p___a_p_i.html#ggad488af97304ef1466637952ecb35ea37a9f6867705113c94f153259c8ee0981b8", null ],
      [ "PTP_MESSAGE_TYPE_MANAGEMENT", "group___p_t_p___a_p_i.html#ggad488af97304ef1466637952ecb35ea37a0666dd235df49faca6c7ea25a31d6107", null ]
    ] ],
    [ "ptp_port_state_t", "group___p_t_p___a_p_i.html#ga5093799b09bcf8a2ec5865d38f1c46a1", [
      [ "PTP_PORT_STATE_GENERATE_ANNOUNCE", "group___p_t_p___a_p_i.html#gga5093799b09bcf8a2ec5865d38f1c46a1abeeac9ed8a3f28c09feab7308bca1040", null ],
      [ "PTP_PORT_STATE_GENERATE_SYNC", "group___p_t_p___a_p_i.html#gga5093799b09bcf8a2ec5865d38f1c46a1a0761daeb91158f9884695941fa312635", null ],
      [ "PTP_PORT_STATE_GENERATE_DELAY_REQ", "group___p_t_p___a_p_i.html#gga5093799b09bcf8a2ec5865d38f1c46a1a23319c05d6bbf371f8020b8c855377e5", null ],
      [ "PTP_PORT_STATE_GENERATE_PDELAY_REQ", "group___p_t_p___a_p_i.html#gga5093799b09bcf8a2ec5865d38f1c46a1a4da3efd7e454da845d9b4f22677b7149", null ],
      [ "PTP_PORT_STATE_RECEIVE_ANNOUNCE", "group___p_t_p___a_p_i.html#gga5093799b09bcf8a2ec5865d38f1c46a1ac67a492f052ec96dbee8462437c4fe25", null ],
      [ "PTP_PORT_STATE_RECEIVE_SYNC", "group___p_t_p___a_p_i.html#gga5093799b09bcf8a2ec5865d38f1c46a1a856df6171238f906cd07a8ba8215e770", null ],
      [ "PTP_PORT_STATE_RECEIVE_FOLLOW_UP", "group___p_t_p___a_p_i.html#gga5093799b09bcf8a2ec5865d38f1c46a1ac386a341840162b5c0311f34d5897b3a", null ],
      [ "PTP_PORT_STATE_RECEIVE_DELAY_REQ", "group___p_t_p___a_p_i.html#gga5093799b09bcf8a2ec5865d38f1c46a1ad7e2f1d0504adbbd1c66237705c7bf76", null ],
      [ "PTP_PORT_STATE_RECEIVE_DELAY_RESP", "group___p_t_p___a_p_i.html#gga5093799b09bcf8a2ec5865d38f1c46a1ab93f410b9b8cfd86405bc6f7a8504400", null ],
      [ "PTP_PORT_STATE_RECEIVE_PDELAY_REQ", "group___p_t_p___a_p_i.html#gga5093799b09bcf8a2ec5865d38f1c46a1a78e4077b9b21ffa9c16f8a3d0547041f", null ],
      [ "PTP_PORT_STATE_RECEIVE_PDELAY_RESP", "group___p_t_p___a_p_i.html#gga5093799b09bcf8a2ec5865d38f1c46a1a593b3514bed3e4b02a85341287b2fc07", null ],
      [ "PTP_PORT_STATE_RECEIVE_PDELAY_RESP_FOLLOW_UP", "group___p_t_p___a_p_i.html#gga5093799b09bcf8a2ec5865d38f1c46a1a7c8ca1a9d55855f6470bfec92fd2f108", null ],
      [ "PTP_PORT_STATE_RECEIVE_MANAGEMENT", "group___p_t_p___a_p_i.html#gga5093799b09bcf8a2ec5865d38f1c46a1a0f6fa1467e9c1faa61dfaedee703148c", null ],
      [ "PTP_PORT_STATE_RECEIVE_SIGNALING", "group___p_t_p___a_p_i.html#gga5093799b09bcf8a2ec5865d38f1c46a1aac15956cd0570fed534bdfe7ca392ff4", null ],
      [ "PTP_PORT_STATE_PROCESS_SYNC", "group___p_t_p___a_p_i.html#gga5093799b09bcf8a2ec5865d38f1c46a1a7e7c7e5fe5f32e5f8001d79ec646fcb7", null ],
      [ "PTP_PORT_STATE_PROCESS_FOLLOW_UP", "group___p_t_p___a_p_i.html#gga5093799b09bcf8a2ec5865d38f1c46a1a5e5d5721b2c3e375f2c6c6a8cac1655c", null ],
      [ "PTP_PORT_STATE_PROCESS_DELAY_REQ", "group___p_t_p___a_p_i.html#gga5093799b09bcf8a2ec5865d38f1c46a1a685de45bced1ee884014fd3e14485d35", null ],
      [ "PTP_PORT_STATE_PROCESS_DELAY_RESP", "group___p_t_p___a_p_i.html#gga5093799b09bcf8a2ec5865d38f1c46a1a7808b3d5c8e81fcce425dbde5cb129d6", null ],
      [ "PTP_PORT_STATE_PROCESS_PDELAY_REQ", "group___p_t_p___a_p_i.html#gga5093799b09bcf8a2ec5865d38f1c46a1ad0ee2d91b1f2ee171537bfaf0fdab934", null ],
      [ "PTP_PORT_STATE_PROCESS_PDELAY_RESP", "group___p_t_p___a_p_i.html#gga5093799b09bcf8a2ec5865d38f1c46a1a7ee34fc1be9115e002d740cfc6894b7c", null ],
      [ "PTP_PORT_STATE_PROCESS_PDELAY_RESP_FOLLOW_UP", "group___p_t_p___a_p_i.html#gga5093799b09bcf8a2ec5865d38f1c46a1a232cabc0f931dd5734c1f8f2a0d34c45", null ],
      [ "PTP_PORT_STATE_PASSIVE", "group___p_t_p___a_p_i.html#gga5093799b09bcf8a2ec5865d38f1c46a1a2c8978d9c8c24739632e4ff8c736aed1", null ],
      [ "PTP_PORT_STATE_E2E_MASTER", "group___p_t_p___a_p_i.html#gga5093799b09bcf8a2ec5865d38f1c46a1a95c095177febe3f8f729dae1080f2c60", null ],
      [ "PTP_PORT_STATE_E2E_SLAVE", "group___p_t_p___a_p_i.html#gga5093799b09bcf8a2ec5865d38f1c46a1a2ac6341131ac6c84164009a9ce395679", null ],
      [ "PTP_PORT_STATE_P2P_MASTER", "group___p_t_p___a_p_i.html#gga5093799b09bcf8a2ec5865d38f1c46a1a79863aa08217ede2598d0871f2c81164", null ],
      [ "PTP_PORT_STATE_P2P_SLAVE", "group___p_t_p___a_p_i.html#gga5093799b09bcf8a2ec5865d38f1c46a1a4d90b715c4052ef7a3af840562f7d2aa", null ],
      [ "PTP_PORT_STATE_RECEIVE_ALL", "group___p_t_p___a_p_i.html#gga5093799b09bcf8a2ec5865d38f1c46a1ace677b4a995aba5e5240f070314fe4f7", null ],
      [ "PTP_PORT_STATE_DISABLE", "group___p_t_p___a_p_i.html#gga5093799b09bcf8a2ec5865d38f1c46a1aad9f871bd628bc6d5610e8f3545ec84e", null ]
    ] ],
    [ "ptp_clock_delay_mechanism_t", "group___p_t_p___a_p_i.html#gac083daddd3b756a4ef8b381b16d767de", [
      [ "PTP_CLOCK_DELAY_MECHANISM_E2E", "group___p_t_p___a_p_i.html#ggac083daddd3b756a4ef8b381b16d767dea0d77c97a9b9ea5742558e041371cbfd5", null ],
      [ "PTP_CLOCK_DELAY_MECHANISM_P2P", "group___p_t_p___a_p_i.html#ggac083daddd3b756a4ef8b381b16d767deadbb9fa5469907c030148a50e7598a5c1", null ]
    ] ],
    [ "ptp_frame_format_t", "group___p_t_p___a_p_i.html#gad14117b95f42287d2f41f9b8c7787638", [
      [ "PTP_FRAME_FORMAT_ETHERII", "group___p_t_p___a_p_i.html#ggad14117b95f42287d2f41f9b8c7787638af1510f40909015fd8b98a31179572ee9", null ],
      [ "PTP_FRAME_FORMAT_IEEE802_3", "group___p_t_p___a_p_i.html#ggad14117b95f42287d2f41f9b8c7787638a766c81b867628e72fceb48faa475b379", null ],
      [ "PTP_FRAME_FORMAT_ETHERII_IPV4_UDP", "group___p_t_p___a_p_i.html#ggad14117b95f42287d2f41f9b8c7787638aea63f6914d6c216bbc1dd5aeb85decab", null ],
      [ "PTP_FRAME_FORMAT_IEEE802_3_IPV4_UDP", "group___p_t_p___a_p_i.html#ggad14117b95f42287d2f41f9b8c7787638a697487dec1f00af32736cc0203e85196", null ]
    ] ],
    [ "ptp_frame_filter_mode_t", "group___p_t_p___a_p_i.html#ga2934142038c79d935eaeda6b9e47fac3", [
      [ "PTP_FRAME_FILTER_MODE_EXT_PROMISCUOUS_MODE", "group___p_t_p___a_p_i.html#gga2934142038c79d935eaeda6b9e47fac3a3f2fc4e28f83243bd2d9b1c859b3ded1", null ],
      [ "PTP_FRAME_FILTER_MODE_UNICAST_MULTICAST", "group___p_t_p___a_p_i.html#gga2934142038c79d935eaeda6b9e47fac3ac546afd37803ca054fe0dec76b242717", null ],
      [ "PTP_FRAME_FILTER_MODE_UNICAST_MULTICAST_FILTERED", "group___p_t_p___a_p_i.html#gga2934142038c79d935eaeda6b9e47fac3ad8e1e648a176df0e05608dd6e1190e6e", null ],
      [ "PTP_FRAME_FILTER_MODE_UNICAST", "group___p_t_p___a_p_i.html#gga2934142038c79d935eaeda6b9e47fac3a4878be37510427193990ea4da1c7e2c9", null ]
    ] ],
    [ "ptp_stca_clock_freq_t", "group___p_t_p___a_p_i.html#ga1e783497c1170cb2f37547d91dd2838c", [
      [ "PTP_STCA_CLOCK_FREQ_20MHZ", "group___p_t_p___a_p_i.html#gga1e783497c1170cb2f37547d91dd2838cad26487bdad38df472d3ee250bd56349c", null ],
      [ "PTP_STCA_CLOCK_FREQ_25MHZ", "group___p_t_p___a_p_i.html#gga1e783497c1170cb2f37547d91dd2838cabd6ad061463ece71fb6ec8493a0cb7d8", null ],
      [ "PTP_STCA_CLOCK_FREQ_50MHZ", "group___p_t_p___a_p_i.html#gga1e783497c1170cb2f37547d91dd2838ca509d20cdc6dee9fe2deb6132538aac06", null ],
      [ "PTP_STCA_CLOCK_FREQ_100MHZ", "group___p_t_p___a_p_i.html#gga1e783497c1170cb2f37547d91dd2838ca37338d61939684c40431439ca17e4e38", null ]
    ] ],
    [ "ptp_stca_clock_sel_t", "group___p_t_p___a_p_i.html#gade7110068650c2c6db71b542c27c33b0", [
      [ "PTP_STCA_CLOCK_SEL_PCLKA_DIV_1", "group___p_t_p___a_p_i.html#ggade7110068650c2c6db71b542c27c33b0aeda791b95bea71cc53b74a988771b293", null ],
      [ "PTP_STCA_CLOCK_SEL_PCLKA_DIV_2", "group___p_t_p___a_p_i.html#ggade7110068650c2c6db71b542c27c33b0a6cf9d43ff9f8bd4d277573df9fe4718c", null ],
      [ "PTP_STCA_CLOCK_SEL_PCLKA_DIV_3", "group___p_t_p___a_p_i.html#ggade7110068650c2c6db71b542c27c33b0a0e8277920f4738203c51f492f90bc0c0", null ],
      [ "PTP_STCA_CLOCK_SEL_PCLKA_DIV_4", "group___p_t_p___a_p_i.html#ggade7110068650c2c6db71b542c27c33b0af5b7be00b95d8521278314537175c285", null ],
      [ "PTP_STCA_CLOCK_SEL_PCLKA_DIV_5", "group___p_t_p___a_p_i.html#ggade7110068650c2c6db71b542c27c33b0a572e21718b92af048a1094f37ed70e75", null ],
      [ "PTP_STCA_CLOCK_SEL_PCLKA_DIV_6", "group___p_t_p___a_p_i.html#ggade7110068650c2c6db71b542c27c33b0aece7128b8529b933a41650a195e67aa9", null ],
      [ "PTP_STCA_CLOCK_SEL_REF50CK0", "group___p_t_p___a_p_i.html#ggade7110068650c2c6db71b542c27c33b0ab82a644f1e4b2d357124a4fbdcf7c53b", null ]
    ] ],
    [ "ptp_message_interval_t", "group___p_t_p___a_p_i.html#ga328e6fb8531c106b8f8374ae6df93395", [
      [ "PTP_MESSAGE_INTERVAL_1_128", "group___p_t_p___a_p_i.html#gga328e6fb8531c106b8f8374ae6df93395af38ab7ef7f34f7ce90ba546f2287ad23", null ],
      [ "PTP_MESSAGE_INTERVAL_1_64", "group___p_t_p___a_p_i.html#gga328e6fb8531c106b8f8374ae6df93395a5c9b66c93684ca49b8d260a70ca31e85", null ],
      [ "PTP_MESSAGE_INTERVAL_1_32", "group___p_t_p___a_p_i.html#gga328e6fb8531c106b8f8374ae6df93395a885a3eeb4ecad617f081cfdbfec05d21", null ],
      [ "PTP_MESSAGE_INTERVAL_1_16", "group___p_t_p___a_p_i.html#gga328e6fb8531c106b8f8374ae6df93395a4d4ddb5320397f88d77326235dfed99c", null ],
      [ "PTP_MESSAGE_INTERVAL_1_8", "group___p_t_p___a_p_i.html#gga328e6fb8531c106b8f8374ae6df93395a5ff7a089a4afafcbd7fc6716dd895963", null ],
      [ "PTP_MESSAGE_INTERVAL_1_4", "group___p_t_p___a_p_i.html#gga328e6fb8531c106b8f8374ae6df93395ae39a8f25024d9479baa94f9a6fd228bd", null ],
      [ "PTP_MESSAGE_INTERVAL_1_2", "group___p_t_p___a_p_i.html#gga328e6fb8531c106b8f8374ae6df93395aa3565a106f01e2392cf661145f9454e7", null ],
      [ "PTP_MESSAGE_INTERVAL_1", "group___p_t_p___a_p_i.html#gga328e6fb8531c106b8f8374ae6df93395ae423a53b883c8f7a2fa036ef068317a4", null ],
      [ "PTP_MESSAGE_INTERVAL_2", "group___p_t_p___a_p_i.html#gga328e6fb8531c106b8f8374ae6df93395af70677fcb482207f17db8926f8a509c1", null ],
      [ "PTP_MESSAGE_INTERVAL_4", "group___p_t_p___a_p_i.html#gga328e6fb8531c106b8f8374ae6df93395a5c0c8d1fad87a8762a5f0b7e89e066bd", null ],
      [ "PTP_MESSAGE_INTERVAL_8", "group___p_t_p___a_p_i.html#gga328e6fb8531c106b8f8374ae6df93395a9ceca0ee2d52091823d9fb8abc5226a2", null ],
      [ "PTP_MESSAGE_INTERVAL_16", "group___p_t_p___a_p_i.html#gga328e6fb8531c106b8f8374ae6df93395af8f6851d8b3a13dfdc041fed3ddf5236", null ],
      [ "PTP_MESSAGE_INTERVAL_32", "group___p_t_p___a_p_i.html#gga328e6fb8531c106b8f8374ae6df93395abe626745556d83173e60e1445439bba9", null ],
      [ "PTP_MESSAGE_INTERVAL_64", "group___p_t_p___a_p_i.html#gga328e6fb8531c106b8f8374ae6df93395ad00dc6365b215810cc076b72ff5aa510", null ]
    ] ],
    [ "ptp_clock_correction_mode_t", "group___p_t_p___a_p_i.html#ga994397de43f548192e34142b61035199", [
      [ "PTP_CLOCK_CORRECTION_MODE1", "group___p_t_p___a_p_i.html#gga994397de43f548192e34142b61035199a4b867130c3fa4c18d530826caa826f7e", null ],
      [ "PTP_CLOCK_CORRECTION_MODE2", "group___p_t_p___a_p_i.html#gga994397de43f548192e34142b61035199a078f1b26633c586afe29ac01107df029", null ]
    ] ],
    [ "ptp_event_t", "group___p_t_p___a_p_i.html#gabed0a6a111a82eb8e8eb55254e1f3c0c", [
      [ "PTP_EVENT_SYNC_ACQUIRED", "group___p_t_p___a_p_i.html#ggabed0a6a111a82eb8e8eb55254e1f3c0cacfe4e6ee306be48c4cb06409cbdbd3f6", null ],
      [ "PTP_EVENT_SYNC_LOST", "group___p_t_p___a_p_i.html#ggabed0a6a111a82eb8e8eb55254e1f3c0caa3e5ca51b3ee12442840df0aa373e4e5", null ],
      [ "PTP_EVENT_SYNC_MESSAGE_TIMEOUT", "group___p_t_p___a_p_i.html#ggabed0a6a111a82eb8e8eb55254e1f3c0ca86158cace4525a3bb25d0bcf7f31e710", null ],
      [ "PTP_EVENT_WORST10_ACQUIRED", "group___p_t_p___a_p_i.html#ggabed0a6a111a82eb8e8eb55254e1f3c0cab5d714bd96071f5d94596342ffeda730", null ],
      [ "PTP_EVENT_OFFSET_FROM_MASTER_UPDATED", "group___p_t_p___a_p_i.html#ggabed0a6a111a82eb8e8eb55254e1f3c0ca6759c1d55ddf2be9ea3198bb8916298d", null ],
      [ "PTP_EVENT_LOG_MESSAGE_INT_CHANGED", "group___p_t_p___a_p_i.html#ggabed0a6a111a82eb8e8eb55254e1f3c0ca39c73154bf81c4591e609ad9f46fea46", null ],
      [ "PTP_EVENT_MEAN_PATH_DELAY_UPDATED", "group___p_t_p___a_p_i.html#ggabed0a6a111a82eb8e8eb55254e1f3c0ca588c20c262375664379a907dfc15bc4c", null ],
      [ "PTP_EVENT_DELAY_RESP_TIMEOUT", "group___p_t_p___a_p_i.html#ggabed0a6a111a82eb8e8eb55254e1f3c0ca9ee4957d22584f4344bdd8a31e6ce6b5", null ],
      [ "PTP_EVENT_LOG_MESSAGE_INT_OUT_OF_RANGE", "group___p_t_p___a_p_i.html#ggabed0a6a111a82eb8e8eb55254e1f3c0ca0f756aa5404793dbda0ac044e2de2a4c", null ],
      [ "PTP_EVENT_DELAY_REQ_FIFO_OVERFLOW", "group___p_t_p___a_p_i.html#ggabed0a6a111a82eb8e8eb55254e1f3c0ca24ca72b1f21430cc29d36bb54e8097c8", null ],
      [ "PTP_EVENT_LOOP_RECEPTION_DETECTED", "group___p_t_p___a_p_i.html#ggabed0a6a111a82eb8e8eb55254e1f3c0ca0469cd735aefdc956e211cc37fda3c16", null ],
      [ "PTP_EVENT_CTRL_INFO_ABNORMALITY", "group___p_t_p___a_p_i.html#ggabed0a6a111a82eb8e8eb55254e1f3c0ca26806de707783c83bcc3f2a16f7139a3", null ],
      [ "PTP_EVENT_DELAY_RESP_PROCESSING_HALTED", "group___p_t_p___a_p_i.html#ggabed0a6a111a82eb8e8eb55254e1f3c0ca15834a1fc0c790ed15dd52da381a0b48", null ],
      [ "PTP_EVENT_MESSAGE_GENERATION_HALTED", "group___p_t_p___a_p_i.html#ggabed0a6a111a82eb8e8eb55254e1f3c0ca76a45f4f9b527834900993a59fba6132", null ],
      [ "PTP_EVENT_MESSAGE_RECEIVED", "group___p_t_p___a_p_i.html#ggabed0a6a111a82eb8e8eb55254e1f3c0ca46c6365f5cd17178f8ff8ca96d32aae2", null ],
      [ "PTP_EVENT_MESSAGE_TRANSMIT_COMPLETE", "group___p_t_p___a_p_i.html#ggabed0a6a111a82eb8e8eb55254e1f3c0caf2bfc28f06fd82fe3a549fbae72e8768", null ],
      [ "PTP_EVENT_PULSE_TIMER_MINT_RISING_EDGE", "group___p_t_p___a_p_i.html#ggabed0a6a111a82eb8e8eb55254e1f3c0ca5ca8324739e11f59e61a7000029b005a", null ],
      [ "PTP_EVENT_PULSE_TIMER_IPLS_COMMON", "group___p_t_p___a_p_i.html#ggabed0a6a111a82eb8e8eb55254e1f3c0ca1e4b52b9bd48126234bae69440791a96", null ]
    ] ],
    [ "ptp_ethernet_phy_interface_t", "group___p_t_p___a_p_i.html#gaec209fe84b18e38b2475e3c4f7c18e2f", [
      [ "PTP_ETHERNET_PHY_INTERFACE_MII", "group___p_t_p___a_p_i.html#ggaec209fe84b18e38b2475e3c4f7c18e2fa02e11f14940ba1290db3ce76f02c7395", null ],
      [ "PTP_ETHERNET_PHY_INTERFACE_RMII", "group___p_t_p___a_p_i.html#ggaec209fe84b18e38b2475e3c4f7c18e2fadedcec638a9b34a9f47a7a7beaff2b7c", null ]
    ] ],
    [ "e_ptp_ctrl_field", "group___p_t_p___a_p_i.html#ga39443dc04d711c6e382705cd56dedc3b", null ]
];