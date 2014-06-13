<?php

/**
 * controller�ѤäƤ�map�ե������Ѥ�config�ե�����������饹
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

require_once('config.inc');
require_once('mw_config_ret.inc');

class mw_config {

public function __construct()
{
  //
  //parent::__construct();
  // XXX �Ȥ��ޤ路�������餳����new�����
  $this->set_config_obj(new config);
  // config���Τ�constructer��init call���뤫���öcomment out
  //$this->init();
}

//
public function init()
{
  $this->get_config_obj()->init();
}

/**
 * config���饹��setter & getter
 *
 */
protected function set_config_obj($o) { $this->config_obj_ = $o; }
protected function get_config_obj() { return $this->config_obj_; }

/**
 * map�ե����������
 *
 * @access public
 * @param string $fn map�ե�����̾
 * @return boolean �ʤˤ������false
 */
public function set_file($fn)
  { return $this->get_config_obj()->set_file($fn); }

/**
 * command�����ꤵ��Ƥ������Ƥ����
 *
 * @access public
 * @param string $cmd ���ޥ��̾
 * @return mw_config_ret_obj mw_config_ret���饹�Υ��󥹥���  ���顼�ʤ�null
 */
public function find($cmd)
{
  // ���ޥ��̾�����ꤵ��Ƥ��ʤ����null
  if ("" === $cmd) {
    return null;
  }

  // ¸�ߤ��Ƥ��ʤ����null
  $base_line = $this->get_config_obj()->find($cmd);
  if ("" === $base_line) {
    return null;
  }

  // �������ѥ��󥹥���
  $ret = new mw_config_ret;

  ////////////////////////
  // �ޤ�SP���ڤ�ʬ����
  ////////////////////////
  $awkbuf = explode(' ', $base_line);
//var_dump($awk);

  // ��ʣ�����������
  $awk = array();
  foreach($awkbuf as $wk) {
    if ("" !== $wk) {
      $awk[] = $wk;
    }
  }

  ////////////////////////
  // include & class̾
  ////////////////////////
  $awk2 = explode(':', $awk[0]);
//var_dump($awk2);
  // include file
  if ('' === $awk2[0]) {
    $ret->set_include_filename($cmd . '.inc');
  } else
  if ('/' === $awk2[0][strlen($awk2[0]) - 1]) {
    $ret->set_include_filename($awk2[0] . $cmd . '.inc');
  } else {
    $ret->set_include_filename($awk2[0]);
  }
  // class name
  if ('' === $awk2[1]) {
    $ret->set_classname($cmd);
  } else {
    $ret->set_classname($awk2[1]);
  }

  ////////////////////////
  // template��
  ////////////////////////
  if (isset($awk[1])) {
    $awk2 = explode(',', $awk[1]);
    $ret->set_template_filename($awk2[0]);
    if (isset($awk2[1])) {
      $ret->set_error_template_filename($awk2[1]);
    }
  }

  ////////////////////////
  // ssl�ϤäƤ���ĥ��
  ////////////////////////
  if (isset($awk[2])) {
    $ret->set_ssl_type($awk[2]);
  }

  //
//var_dump($ret);
  return $ret;
}


//private:
private $config_obj_;

} // end of class
