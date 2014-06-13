<?php

/**
 * MVC Model��ʬ �����Ǥ�����Ѵ��쥯�饹
 *
 * ���Υ��饹ľ�Ȥ����ȤϤʤ��Ȼפ�������ɤʤ�
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 */

require_once('base_model.inc');
require_once('session.inc');
require_once('mobile_info.inc');
require_once('conv_util.inc');

abstract class base_model_rich extends base_model {

//public:
public function __construct()
{
  //
  parent::__construct();
  //$this->init();
}


//�����
public function init(){
  parent::init();
  $this->set_session_obj(null);
  $this->auth_state_off();
  $this->set_id('');
  $this->set_authtype_auth();
  $this->with_mobile_off();
}

//
protected function set_session_obj($o) { $this->session_obj_ = $o; }
public function get_session_obj() { return $this->session_obj_; }

//
protected function set_sconfig($o) { $this->sconfig_ = $o; }
protected function get_sconfig() { return $this->sconfig_; }

//
protected function set_authtype($i) { $this->authtype_ = $i; }
protected function get_authtype() { return $this->authtype_; }
protected function _is_authtype($i)
{
  if ($i == $this->get_authtype()) {
    return true;
  }
  // else
  return false;
}
public function set_authtype_auth() { $this->set_authtype(1); }
public function is_authtype_auth() { return $this->_is_authtype(1); }
public function set_authtype_ambiguous_auth() { $this->set_authtype(2); }
public function is_authtype_ambiguous_auth() { return $this->_is_authtype(2); }

//
public function with_mobile_on() { $this->with_mobile_ = 1; }
public function with_mobile_off() { $this->with_mobile_ = 2; }
public function is_with_mobile()
{
//var_dump($this->with_mobile_);
  if (1 === $this->with_mobile_) {
    return true;
  }
  // else
  return false;
}

/**
 * �桼��ID���������
 *
 * �桼��ID�Ȥ�
 * ���̾�ˤ����Ƥ������桼��ID
 * ��ƿ̾���å����ˤ����Ƥϥȡ�����
 * �����Ӥ˴ؤ��Ƥ�uid�ޤ��ϥ��֥����饤��ID����
 * ��DoCoMo�ˤĤ��Ƥ� �����ե饰 ��Ω�äƤ����cgi request��uid
 * ��ؤ���ΤȤ���
 *
 * @access public
 * @return string �桼��ID ¸�ߤ��ʤ�����ʸ��
 */
public function get_id() { return $this->id_; }
protected function set_id($o) { $this->id_ = $o; }

/**
 * ǧ�ھ��֤Υ����å�
 *
 * @access public
 * @return boolean ǧ�ھ��֤ʤ�true����ǧ�ھ��֤ʤ�false
 */
public function is_auth() { return $this->get_auth_state(); }

//
public function get_auth_state() { return $this->auth_state_; }
protected function set_auth_state($b) { $this->auth_state_ = $b; }
public function auth_state_on() { $this->set_auth_state(true); }
public function auth_state_off() { $this->set_auth_state(false); }

/**
 * ǧ������
 *
 * ��̤������ѿ��˳�Ǽ����뤿�ᡢreturn���Τ�void
 *
 * @access protected
 */
protected function _authorization()
{
//print "_authorization Trap1\n";
  // ���Ӥξ��
  if ($this->is_with_mobile()) {
//print "do_auth_mobile_site\n";
    $ret = $this->do_auth_mobile_site();
  } else {
  // PC�ξ��
//print "do_auth\n";
    $ret = $this->do_auth();
  }
  //
  if (true === $ret) {
    $this->auth_state_on();
  } else {
    $this->auth_state_off();
  }
//print "_authorization Trap99\n";

  //
  return;
}


/**
 * ǧ�ڤ��ߤ�(ID��password��
 *
 * �̾�Υ��å���󤫤��ǧ��
 * �б������Τˡָ��������ȷϤ�ǧ�ڡפ�����
 *
 * @access public
 * @return boolean ǧ�ھ��֤ʤ�true����ǧ�ھ��֤ʤ�false
 */
public function do_auth() {
//print "base_model_auth execute Trap 1\n";
  //
  $req = $this->get_cgi_request();

  // ���å���󥯥饹����
  $obj = new session;
  $obj->set_config_filename($this->get_config()->find('session_config'));
  $obj->set_db($this->get_db());
  $this->set_sconfig($obj->get_config());

  // key string����
  // XXX ���֤ϸ����post��Cookie��get�����Ȥǲ��Ѥˤ������ʤ���
  // �����Υ⡼�ɤ�����
  $pm = $req->get_priority();
  $key = "";
  if (true === $this->get_sconfig()->is_value('auth_key_get')) {
    $req->set_only_get();
    $name = $this->get_sconfig()->get_value('auth_key_get_name');
    $value = $req->find($name);
    if ("" !== $value) { $key = $value; }
  }
  if (true === $this->get_sconfig()->is_value('auth_key_post')) {
    $req->set_only_post();
    $name = $this->get_sconfig()->get_value('auth_key_post_name');
    $value = $req->find($name);
    if ("" !== $value) { $key = $value; }
  }
  if (true === $this->get_sconfig()->is_value('auth_key_cookie')) {
    $name = $this->get_sconfig()->get_value('auth_key_cookie_name');
    $value = $req->find_cookie($name);
//print "cookie value is $value \n";
    if ("" !== $value) { $key = $value; }
  }
  // �᤹
  $req->set_priority($pm);
//print "key = $key \n";
 
  // key���ʤ������ǧ�ھ���
  if ("" === $key) {
    $this->auth_state_off();
    return false;
  }

  // ǧ�ڥ��顼�ʤ��äѤ���ǧ��
  $ret = $obj->auth($key);
  if (false === $ret) {
    $this->auth_state_off();
    return false;
  }

  // Cookie�ʤ顢key������򤷤Ƥ���
  if (true === $this->get_sconfig()->is_value('auth_key_cookie')) {
    $name = $this->get_sconfig()->get_value('auth_key_cookie_name');
    setcookie($name, $obj->get_key());
  }

  //
  $this->set_session_obj($obj);
  $this->set_id($this->get_session_obj()->get_id());
  $this->auth_state_on();
  return true;
}

/**
 * ���ӥ����ȤȤ���ǧ�ڤ��ߤ�
 *
 * XXX ǧ�ڤ�true false�ϥ桼���ơ��֥��¸�ߤ��뤫�ɤ����Ǥߤ�
 * �֤ä��㤱���������󤷤Ƥ봶������ͤ�����ä�
 *
 * @access public
 * @return boolean ǧ�ھ��֤ʤ�true����ǧ�ھ��֤ʤ�false
 */
public function do_auth_mobile_site() {
  // �����
  $this->set_id('');
  $this->auth_state_off();

  // ID�μ���
  $miobj = new mobile_info;

  $uid = '';
  if ( (true === $miobj->is_docomo())&&((true === $this->is_official_site())|| ( (false === empty($_SERVER['HTTPS']))&&('off' !== $_SERVER['HTTPS']) )) ) {
//print "official docomo\n";
    // DoCoMo����
    // �������ޤ���SSL�ˤ����³�ξ��
    $uid = $this->get_cgi_request()->find('uid');
  } else {
//print "any mobile\n";
    // ����ʳ�
    $uid = $miobj->get_sid();
  }

  // XXX ���祤���������б���
  // XXX PC�Ǥ���uid���बuser-agent�����ꤵ��Ƥʤ���Хѥ�᥿ uid ��Ȥ�
  // XXX user-agent�ˤ���Фä����ꤷ�Ƥ�ʤ餽�ä�ͥ�褷��������else�¤�ʤ�if
  if (('' === $uid) && (false === $miobj->is_mobile())) {
    $uid = $this->get_cgi_request()->find('uid');
  }
//var_dump($uid);
  if ("" === $uid) {
//print "uid is null\n";
    // XXX ñ���false�¤�ʤ��ơ��ʤˤ����ٹ��������ʤ뤫��
    return false;
  }

  // ���Ȥ줿uid������
  $this->set_id($uid);

  // �桼���ơ��֥��ǧ
  $cobj = $this->get_config();
  // SELECT id FROM table WHERE uid=$id and del_flg = 0;
  // XXX ��ǽ�ľ���� ��ʣ���� orz
  if ("" !== $cobj->find('official_site_user_del_flg')) {
    $sql = sprintf('SELECT %s FROM %s WHERE %s=%s and %s=%s;',
                    $cobj->find('official_site_user_id'),
                    $cobj->find('official_site_user_table'),
                    $cobj->find('official_site_user_uid'),
                    security::sanitize_db_add_quote($uid),
                    $cobj->find('official_site_user_del_flg'),
                    security::sanitize_db_add_quote($cobj->find('official_site_user_del_flg_value'))
                  );
  } else {
    $sql = sprintf('SELECT %s FROM %s WHERE %s=%s;',
                    $cobj->find('official_site_user_id'),
                    $cobj->find('official_site_user_table'),
                    $cobj->find('official_site_user_uid'),
                    security::sanitize_db_add_quote($uid)
                  );
  }
//print $sql . "\n";
  //
//var_dump($this->get_db());
  $res = $this->get_db()->query($sql);
  if (is_null($res)) {
      return false;
  }
  if (false === $res->fetch()) {
    return false;
   }

  // ����Ȥ줿�äݤʤΤǡ�����
  $this->auth_state_on();

  //
  return true;
}


/**
 * ǧ��ɬ�ܷϤˤ�����NG���ä��������ܽ���
 *
 * @access public
 */
public function auth_ng_process() {
  //
  $this->recursive_on();
  // ���꤬�ʤ����index�ˤĤä�����
  $command = 'index';
  if (false === is_null($this->get_sconfig())) {
    if ("" !== $this->get_sconfig()->get_value('auth_error_return_command')) {
      $command = $this->get_sconfig()->get_value('auth_error_return_command');
    }
  }
//var_dump($this->get_sconfig());

  // ���ޥ��̾����
  $this->set_recursive_command($command);

  // �ƥ�ץ졼�ȥե����������ö���
  $this->set_tmp_filename('');

  //
  return ;
}

/**
 * ���������Ȥä�config�˽񤤤Ƥ��뤫�ɤ��������å�
 *
 * XXX ���Ȥǡֳ���������̵������פǤ���褦�ˤ��ʤ��Ȥͤ���
 *
 * @access public
 * @return boolean ���������Ȥʤ�true��������ʤ�false
 */
public function is_official_site() {
  $s = $this->get_config()->find('official_site');
  if(preg_match("/^(yes|y|ok|true|on|1)$/i", $s)) {
    return true;
  }
  // else
  return false;
}

/**
 * model�ޥ���ȥݥ����
 *
 * Ŭ�ڤ�ǧ�ڥ����å��Ȥ���ä�Ŭ�ڤʥ᥽�åɤˤ֤�ʤ���
 *
 * @access public
 */
public function initialize() {
//print "Trap 1\n";
  // authorization �����å�
  // �Ϥ��������ˤäƤ��̥᥽�åɤ�
  $this->_authorization();
}
public function execute() {
  // ���ǰ�Τ���Υޥ���ȥݥ����
  $ret = $this->execute_rich_mount1();
  if (false === $ret) {
    $this->auth_ng_process();
    return;
  }

  // authorization �����å�
  // �Ϥ��������ˤäƤ��̥᥽�åɤ�
  //$this->_authorization();

  // ���ǰ�Τ���Υޥ���ȥݥ����
  $ret = $this->execute_rich_mount2();
  if (false === $ret) {
    $this->auth_ng_process();
    return;
  }

  // OK���ä���NG���ä���
  // auth�ξ��
  if ($this->is_authtype_auth()) {
    if (false === $this->is_auth()) {
      // ���顼
      $this->auth_ng_process();
      return;
    }
    // else
    $ret = $this->execute_auth();
  } else {
    // XXX$this->is_authtype_ambiguous_auth() ���ʤ���Ȥꤢ����
    $ret = $this->execute_ambiguous_auth();
    // XXX �Ĥ��Ǥ˥��å�
    $sp = new simple_put;
    if (true === $this->is_auth()) {
      $this->get_conv()->multiDic('is_auth', $sp);
    } else {
      $this->get_conv()->multiDic('is_noauth', $sp);
    }
  }

  // ���ǰ�Τ���Υޥ���ȥݥ����
  $ret = $this->execute_rich_mount3();
  if (false === $ret) {
    $this->auth_ng_process();
    return;
  }
  //
  return ;
}


// ������ꤿ������
public function execute_rich_mount1() { return true; }
public function execute_rich_mount2() { return true; }
public function execute_rich_mount3() { return true; }

//private:
private $session_obj_;		// ǧ�ڥ��饹���󥹥���
private $auth_state_;		// ǧ�ھ���
private $sconfig_;		// ǧ��config�Υ��饹���󥹥���
private $id_;			// �桼�����̤��뤿���ID
private $authtype_;		// 1:authɬ�� 2:auth���Ƥ⤷�ʤ��Ƥ�
private $with_mobile_;		// 1:with_mobile  2:without_mobile

} // end of class
