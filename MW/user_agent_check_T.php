<?php

require_once('user_agent_check.inc');
require_once('mobile_info.inc');

// ��˻Ȥ��ΤǺ��
// DoCoMo/2.0 F902i(c100;TB;W28H15) 
// KDDI-CA23 UP.Browser/6.2.0.4 (GUI) MMP/2.0

putenv('HTTP_USER_AGENT=DoCoMo/2.0 F902i(c100;TB;W28H15) ');
$mobj = new mobile_info();
//var_dump($mobj);

// list
$s = "
# ������
#@docomo\r
@au\r
dymmy\rCA23
F902i
";

$obj = new user_agent_check;
$obj->set_mobile_obj($mobj);
//$obj->set_arrow_string($s); // arrow��denny�Ϥɤä���������������
$obj->set_denny_string($s);

//
$boolean_ret = $obj->is_permission();
var_dump($boolean_ret);
