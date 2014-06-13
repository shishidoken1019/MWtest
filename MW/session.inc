<?php

/**
 * ���å���󥯥饹
 *
 * �ºݤˤϡ����Υ��饹��GoF�ˤ��Ȥ�����facade�ѥ�����Ǥ��롣
 * ���Υ��饹�ϥ��󥿥ե������Τߤ��󶡤Ȥʤ롣
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

//require_once('session_auth_add.inc');
require_once('session_id.inc');
require_once('session_start_login.inc');
require_once('session_config.inc');

class session {

public function __construct()
{
  //
  $this->init();
}

//
public function init()
{
  $this->set_config(null);
  $this->set_login(null);
}

//
protected function set_config($o) { $this->config_ = $o; }
public function get_config() { return $this->config_; }

protected function set_login($o) { $this->login_ = $o; }
public function get_login() { return $this->login_; }

protected function set_session_id($s) { $this->sid_ = $s; }
public function get_session_id() { return $this->sid_; }

protected function set_id($s) { $this->id_ = $s; }
public function get_id() { return $this->id_; }

public function set_db($o) { $this->dbh_ = $o; }
protected function get_db() { return $this->dbh_; }

//
protected function set_error_string($s) { $this->error_string_ = $s; }
public function get_error_string() { return $this->error_string_; }


/**
 * ���󥹥��󥹼�ư�����դ�getter
 *
 * ���Ǥ�new����Ƥ�Фʤˤ⤷�ʤ���null�ʤ�ɬ�פ�class��new����
 * �ǡ����ꤵ�줿object���󥹥���(����)���֤�
 *
 * @access protected
 * @param string $class_name new���٤����饹̾
 * @param string $val_name setter/getter�ǻȤ�̾��
 * @return object ɬ�פʥ��󥹥��󥹻��ȡ����顼�ξ��null
 */
protected function get_object($class_name, $val_name = '')
{
  //
  if ('' === $val_name) {
    $val_name = $class_name;
  }

  //
  $o = call_user_func(array($this, 'get_' . $val_name));
  if (is_null($o)) {
    $o = new $class_name;
    call_user_func(array($this, 'set_' . $val_name), $o);
//print "new $class_name \n";
  }
// XXX
//$o = call_user_func(array($this, 'get_' . $val_name));
//var_dump($o);

  //
  return $o;
}

/**
 * config�ե�����̾����
 *
 * �ºݤˤϡ�class new���ƥե�����̾���ꤷ��parce�ޤ�
 *
 * @access public
 * @param string $filename config�ե�����̾
 * @return boolean �ʤ����ꤢ���false
 */
public function set_config_filename($filename)
{
  // ���󥹥��󥹤���
  $o = $this->get_object('session_config', 'config');
//var_dump($o);

  // �ե���������
  $o->set_filename($filename);
//var_dump($o);

  //
  return true;
}

/**
 * ��������
 *
 * ID�ȥѥ���ɥ����å����ơ�OK�ʤ饻�å����򥹥����Ȥ�����
 *
 * @access public
 * @param string $id ���������Ѥ�ID��e-mail�äƥѥ������褯�����ͤ���
 * @param string $pass ���������Ѥ���̩���󡣤�����ѥ����
 * @return boolean ��������Ǥ�����true���Ǥ��ʤ���false��
 */
public function login($id, $pass)
{
//print "$id $pass \n";
  // ���󥹥��󥹤���
  $o = $this->get_object('session_start_login', 'login');

  // XXX ���顼�����å��ɤ����衩
  $o->set_config($this->get_config());
  $o->set_db($this->get_db());
//var_dump($this->get_db());
  $ret = $o->is_member($id, $pass);

  //
  if (false === $ret) {
    $this->set_error_string('login:' . $o->get_error_string());
    return false;
  }

  // OK�äݤ��Τǥ��å������������
  $o = $this->get_object('session_id');
  $o->set_config($this->get_config());
  $o->set_db($this->get_db());
  $ret = $o->create($id);

  //
  if (false === $ret) {
    $this->set_error_string('create session:' . $o->get_error_string());
  } else {
    $this->set_id($id);
  }

  //
  return $ret;
}

/**
 * key�μ���
 *
 * ���ʤ餺��login�ޤ���auth�θ��call���뤳��
 *
 * @access public
 * @return string ���顼�ξ��϶�ʸ��
 */
public function get_key()
{
  //
  $o = $this->get_object('session_id');
  // XXX ��¸�Υ��󥹥��󥹤�����Ϥ��ʤΤǰʲ���ĤϾ�ά
  //$o->set_config($this->get_config());
  //$o->set_db($this->get_db());

  //
  return $o->get_key();
}

/**
 * ǧ��
 *
 * @access public
 * @param string $key key����
 * @return boolean ǧ��OK�ʤ�true���Ǥ��ʤ���false��
 */
public function auth($key)
{
  //
  $o = $this->get_object('session_id');
  $o->set_config($this->get_config());
  $o->set_db($this->get_db());

  //
  $ret = $o->auth($key);
  //
  if (false === $ret) {
    $this->set_error_string('auth:' . $o->get_error_string());
  } else {
    $this->set_id($o->get_id());
  }

  //
  return $ret;
}


//private:
private $config_; // config
private $login_; // session_start_login
private $sid_; // session_id
private $id_; // session_id

private $dbh_;
private $error_string_;

} // end of class
