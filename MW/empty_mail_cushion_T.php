<?php

require_once('/opt/new/wwwroot/cron_base.inc');
require_once('empty_mail_cushion_db.inc');

$obj = new empty_mail_cushion;
$obj->set_db($dbh);
$obj->set_config_filename('/opt/new/conf/registration.conf');

// ����(��
$obj->run();

// XXX �ᥢ�ɼ���¦
// model�Ѿ����饹��Ǽ¹�
  // �ᥢ�ɤ��Ȥä�
  $obj = new empty_mail_cushion;
  $obj->set_db($dbh);
  $obj->set_config_filename($this->get_config()->find('add_config'));

  // ����
  // ¿ʬ�����Ϥ���
  //$obj->get_�ʤ����($req->find('i'));
  //$email = $obj->get_email();
  //
  $email = $obj->get_email($req->find('i'));
//var_dump($email);

  // XXX ǰ�Τ��ᡩ
  if ("" === $email) {
//print "error (email is empty) \n";
//exit;
    $this->make_body_with_conv('member/add_invalid.tpl');
    return ;
  }

  // i��̵���ˤ���
  $obj->delete($req->find('i'));


