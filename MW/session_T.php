<?php

// MW config
require_once('/opt/www/mw.conf');

//
require_once('db_manager.inc');
require_once('session.inc');

// �Ȥꤢ����DB�ϥ�ɥ뤲��
$dbh = db_manager::get_handle('./db.conf');
//var_dump($dbh);

// config�����
$obj = new session;
$obj->set_config_filename('./session.conf');
$obj->set_db($dbh);

// �����󤷤Ƥߤ�
$id = 'id';
$pass = 'pass';
$ret = $obj->login($id, $pass);
var_dump($ret);
print $obj->get_error_string() . "\n";

$key = $obj->get_key();
//print "key is $key \n";

// ƿ̾��ȯ�Ԥ��Ƥߤ�

//--

// ���å����ݻ�
$obj2 = new session;
$obj2->set_config_filename('./session.conf');
$obj2->set_db($dbh);

$ret = $obj2->auth($key);
var_dump($ret);
print $obj2->get_error_string() . "\n";

// �桼�����ɲá��Ȥꤢ��������̵�ѷ�
$obj3 = new session;
$obj3->set_config_filename('./session.conf');
$obj3->set_db($dbh);
$obj->add_auth($id, $pass [, $status]);
