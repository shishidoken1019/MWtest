<?php

/**
 * ���å����������󥯥饹
 *
 * ID��password�ˤ���������ǥ��å����򳫻Ϥ��뤿��Υ��饹
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

require_once('session_base.inc');
require_once('config_util.inc');

class session_start_login extends session_base {

public function __construct()
{
  //
  //$this->init();
  parent::__construct();
}

//
public function init()
{
  parent::init();
}

/**
 * ���С��γ�ǧ
 *
 * DB�ˤ���ID�ȥѥ���ɤ�����å�
 * ���Υ᥽�åɼ��Τϡ�ID�ȥѥ���ɤ����פ��Ƥ�����true���֤��פ����Ǥ���
 *
 * @access public
 * @param string $id ����������Ѥ�����ID
 * @param string $pass ����������Ѥ�������̩����(�ѥ����)
 * @return boolean ID����̩���󤬰��פ����true������ʳ��ʤ�false
 */
public function is_member($id, $pass)
{
  // password��crypt��ˡ�����
  $crypt_type = $this->get_config()->get_value('password_crypt_type');
//print "crypt type is $crypt_type \n";

  // �ѥ���ɤ�Ź沽 �⤷���� �ϥå��岽
  if ('sha-1' === $crypt_type) {
    $pass = sha1($pass, false);
  } else
  if ('md5' === $crypt_type) {
    $pass = md5($pass, false);
  } else
  if ('none' === $crypt_type) {
    ;
  } else {
//print "crypt type '$crypt_type' is invalid!!\n";
    $this->set_error_string("crypt type '$crypt_type' is invalid");
    return false;
  }
//print "pass is $pass \n";

  // DB����ѥ���ɾ����ҤäѤäƤ���
  // XXX ���Ȥǥ�åԥ󥰤���text�⡼�ɤˤ��б��Ǥ���褦�ˤ��롩
  // auth_clump�β�����
  $wk = $this->get_config()->get_value('auth_clump');
//print "$wk \n";
  $auth_obj = config_util::create_instance($wk);  
//var_dump($auth_obj);
  if (true === is_null($auth_obj)) {
//print "$wk is invalid!! \n";
    $this->set_error_string("$wk is invalid");
    return false;
  }
  // �ơ��֥�̾�����ꤵ��Ƥ�������
  $wk = $this->get_config()->get_value('auth_clump_table_name');
  if ("" !== $wk) {
    $auth_obj->set_table_name($wk);
//print "set table_name $wk \n";
  }


  // auth type�����
  $auth_type = $this->get_config()->get_value('auth_type');
  if ("0" === $auth_type) {
    // ���̤˻��ꤵ�줿ID���ͤù���
    $auth_obj->set_value('id', $id, false);
  } else
  if ("1" === $auth_type) {
    // XXX ̤����!!
    $auth_obj->set_value('id', $id, false);
  } else {
//print "auth type '$auth_type' is invalid!!\n";
    $this->set_error_string("auth type '$auth_type' is invalid");
    return false;
  }
//print "auth type is $auth_type \n";

  // DBH���ꤷ�ƾ��󤲤�
  $auth_obj->set_db($this->get_db());
  $ret = $auth_obj->get();
//var_dump($ret);
//var_dump($auth_obj);

  // ¸�ߤ��Ƥʤ����NG
  if (false === $ret) {
    // no user
    $this->set_error_string("no user");
    return false;
  }

  // ��³Ū����������å��γ�ǧ
  $ret = $this->check_locked($auth_obj->get_value('status'));
  if (false === $ret) {
    // locked
    $this->set_error_string("locked");
    return false;
  }

  // ���Ū���å��γ�ǧ
  if (0 < $auth_obj->get_value('lock_time') ) {
//print "into time lock \n";
    $twk = time();
    if ($twk < $auth_obj->get_value('lock_time')) {
//print "into time lock NG\n";
      // �ޤ����å����֤ʤΤǥ��顼���ͤ��֤�
      $this->set_error_string("time locked");
      return false;
    }
    // ���å����¤�ۤ��Ƥ���Τǡ����å���Ϥ���
    $auth_obj->set_value('lock_time', 0);
  }

  // ���顼������Ȥγ�ǧ
  $error_count = $this->get_config()->get_value('pass_error_count');
//print "$error_count \n";
  if ($auth_obj->get_value('err_count') > $error_count) {
//print "error count in \n";
    // �����ϰϤ�Ķ���Ƥ���Τǥ��å�����
    $lt = $this->get_config()->get_value('pass_error_lock_time');
    $auth_obj->set_value('err_count', 0, true);
    $auth_obj->set_value('lock_time', time() + $lt, true);

    //
    $this->set_error_string("time locked start");
    return false;
  }

  // �ѥ���ɤγ�ǧ
  if ($pass !== $auth_obj->get_value('pass')) {
    // ���顼�����󥿤򥤥󥯥����
    $auth_obj->set_value('err_count', $auth_obj->get_value('err_count') + 1);
    //
//print "error count is invalid\n";
    $this->set_error_string("password invalid");
    return false;
  }

  // �ǽ�Ū��OK�äݤ��Τ�true
  return true;
}

/**
 * ���ơ�������ǧ
 *
 * ���ȤǷѾ���ĥ�Ǥ���褦�ˤ����ˡ�
 * ���ܤϡ֣��ʤ�����ʳ��ʤ���å����֡�
 *
 * @access protected
 * @param int $status ���ơ�����
 * @return boolean ����ʤ�true�����å����֤ʤ�false
 */
protected function check_locked($status)
{
  if (0 == $status) {
    return true;
  }
  // else
  return false;
}


//private:

} // end of class

