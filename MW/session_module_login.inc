<?php

/**
 * �����ʥ��饹��login��
 *
 * session.inc����ˤ���session���饹����Ȥ����Ȥ�����ˤ���������class
 * ����ե�����Ŭ�ڤ����ꤹ��С��ۤܤ��Τޤ޻Ȥ���Ȥ��⤦��
 * map�ե�����Ǥ��Υե�������ꤹ��Ф��������
 * ̵���ʤ�Ŭ�����ľ���ʤ�Ѿ�����ʤꤷ�Ƥ��硣
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 */

require_once('base_model.inc');
require_once('file_util.inc');
require_once('session.inc');


class session_module_login extends base_model {

//
public function initialize() {  }
public function finalize() {  }

//����
public function execute() {

  // cgi�ꥯ�����Ȥ��ͤޤä����֥������ȼ�äƤ���
  $req = $this->get_cgi_request();

  // config�����
  $obj = new session;
  $obj->set_config_filename($this->get_config()->find('session_config'));
  $obj->set_db($this->get_db());
  $sconfig = $obj->get_config();
//var_dump($sconfig);

  // ID�ȥѥ���ɤ����
  $id = $req->find($sconfig->get_value('login_id_form_name'));
  $pass = $req->find($sconfig->get_value('login_pass_form_name'));
//print "id is " . $id . "\n";
//print "pass is " . $pass . "\n";

  $ret = $obj->login($id, $pass);
//var_dump($ret);
//print $obj->get_error_string() . "\n";

  //
  $conv = $this->get_conv();

  // ���顼�������Ȥꤢ����index���ͤ��֤���
  if (false === $ret) {
    $this->recursive_on();
    $this->set_recursive_command($sconfig->get_value('login_error_return_command'));
    $conv->monoDic('login_error', $obj->get_error_string());
    $sp = new simple_put;
    $conv->multiDic('is_login_error', $sp);
    // XXX ID�Ϥ���Ȥ����Ȥꤢ����
    $conv->monoDic($sconfig->get_value('login_id_form_name'), $id);
    return ;
  }
  // else
  // ���Ⱦ�������Ū�ˤ���������Ǽ
  if (true === $sconfig->is_value('auth_key_cookie')) {
    $name = $sconfig->get_value('auth_key_cookie_name');
    // XXX ��������Ū�б�
    $_COOKIE[$name] = $obj->get_key();
//print "add on Cookie\n";
//print_r($_COOKIE);
  }
  if (true === $sconfig->is_value('auth_key_post')) {
    $name = $sconfig->get_value('auth_key_post_name');
    // XXX ��������Ū�б�
    $_POST[$name] = $obj->get_key();
//print "add on post\n";
//print_r($_POST);
  }
  if (true === $sconfig->is_value('auth_key_get')) {
    $name = $sconfig->get_value('auth_key_get_name');
    // XXX ��������Ū�б�
    $_GET[$name] = $obj->get_key();
//print "add on get\n";
//print_r($_GET);
  }

  // top�˺Ƶ�
  $this->recursive_on();
  $this->set_recursive_command($sconfig->get_value('login_return_command'));
  return ;
}

} // end of class