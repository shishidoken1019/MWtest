<?php

$db1_array = array("id", "email", "test");
$db2_array = array("xxx");
$names = array_merge($db1_array, $db2_array);

vector<validator_clump_unit> $vdbo1 
  = rss_item_clump->get_validate_obj($db1_array);
vector<validator_clump_unit> $vdbo2 
  = rss_channel_clump->get_validate_obj($db2_array);

$valid_objs = array_merge($vdbo1 , $vdbo2);


$obj = new validator_util_width_smarty;
$obj->set_cgi_request($req);
$obj->set_validator_list($valid_objs);

// しくった時の処理
if (false == $obj->check()) {
  // 基本データの設定

  // 現在データの書き込み
  $obj->set_smarty_obj($smarty);
  $obj->set_all_datas();

  // 再帰call

  //
  return ;
}




?>
