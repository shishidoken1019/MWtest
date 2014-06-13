<?php

/**
 * MVC Model��ʬ���쥯�饹���Ȥ�
 *
 * ���ʡ��ꤹ�������˺��
 * ����Ū�ˤϤ���ǤϤʤ�������ηѾ����饹�Ǥ���base_model��Ѿ����줿��
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 */

require_once('db_manager.inc');
require_once('debug_util.inc');

abstract class base_model_skeleton {

//public:

//
public function __construct() { $this->init(); }
//
public function init()
{
  // ������off��
  $this->recursive_off();
  //
  $this->set_body("");
  $this->dbh_ = null;
}


//
public function set_config($o) { $this->cfobj_ = $o; }
public function get_config() { return $this->cfobj_; }
//
public function set_mobile($o) { $this->mobobj_ = $o; }
public function get_mobile() { return $this->mobobj_; }
//
public function set_cgi_request($o) { $this->reqobj_ = $o; }
public function get_cgi_request() { return $this->reqobj_; }
//
public function set_cgi_response($o) { $this->resobj_ = $o; }
public function get_cgi_response() { return $this->resobj_; }

//
public function set_my_name($s) { $this->my_name_ = $s; }
public function get_my_name() { return $this->my_name_; }

//
public function set_body($s) { $this->body_ = $s; }
public function get_body() { return $this->body_; }

//
protected function recursive_on() { $this->recursive_flg_ = true; $this->set_tmp_filename(''); }
protected function recursive_off() { $this->recursive_flg_ = false; }
public function is_recursive_on() { return $this->recursive_flg_; }
protected function set_recursive_command($s) { $this->recursive_command_ = $s; }
public function get_recursive_command() { return $this->recursive_command_; }

//
//
public function set_inside_encoding_obj($o)
  { $this->inside_encoding_obj_ = $o; }
public function get_inside_encoding_obj()
  { return $this->inside_encoding_obj_; }

// XXX Skelton�Ǥ����Τ���
public function get_template_dir() { return $this->get_config()->find('tmplate_base_dir'); }

public function set_tmp_filename($s) { $this->set_bag('tmp_filename', $s); }
public function get_tmp_filename() { return $this->get_bag('tmp_filename'); }
public function is_tmp_filename()
{
  if (false === $this->is_bag('tmp_filename')) {
    return false;
  }
  if ("" === $this->get_tmp_filename()) {
    return false;
  }
  return true;
}

public function set_error_tmp_filename($s)
  { $this->set_bag('error_tmp_filename', $s); }
public function get_error_tmp_filename()
  { return $this->get_bag('error_tmp_filename'); }
public function is_error_tmp_filename()
{
  if (false === $this->is_bag('error_tmp_filename')) {
    return false;
  }
  if ("" === $this->get_error_tmp_filename()) {
    return false;
  }
  return true;
}

// ���
// �󥤥󥹥��󥹤��Τ�ΤΥ��å���
// XXX getter���롩 ���Ȥ����ͤ����֤�controller�ΤäƤ뤷�ͤ���
// XXX �Ȥꤢ����protected�ǡ����ɬ�פʤ�public��ľ���ơ�
public function set_bag_obj($o) { $this->bag_ = $o; }
protected function get_bag_obj() { return $this->bag_; }
// XXX �����Ѥ������method w
protected function bag() { return $this->get_bag_obj(); }

// �ʲ����ʻȤ���
// ñ�ȡ���ʣ�Ͼ��
public function set_bag($name, $o) {
  // is��true�ʤ��ö�������
  if (true === $this->is_bag($name)) {
    // �ޤ�iterator��������
    $itr = $this->bag()->find($name);
    // ����������
    $this->bag()->erase($itr);
  }

  // �ɲ�
  $this->push_bag($name, $o);
}
// ����Τ褦���ɲ�
public function push_bag($name, $o) { $this->get_bag_obj()->insert($name, $o); }
// ñ�ͤ�get
public function get_bag($name) { return $this->bag()->real($this->bag()->find($name))->get_second(); }

// �����get
public function get_array_bag($name)
{
  // �ޤ�iterator���󤲤�
  $itr_array = $this->bag()->find_array($name);
  // �֤�󤷤Ĥ����Ǥ����
  $ret = array();
  foreach($itr_array as $itr) {
    $ret[] = $this->bag()->real($itr)->get_second();
  }
  return $ret;
}
// ¸�߳�ǧ
public function is_bag($name) {
//print debug_util::backtrace_string();
//print "\n";

//var_dump($this->get_bag_obj());

  $ret = $this->get_bag_obj()->find_array($name);
  if (empty($ret)) {
    return false;
  }
  // else
  return true;
}

//
// abstract
public function initialize() {}
abstract public function execute();
public function finalize() {}

//private:
private $my_name_;	// ��ʬ���ȤΥ��ޥ�ɤ�̾��

private $cfobj_;	// �����ȸ�ͭ��config��config���饹���󥹥���
private $mobobj_;	// mobile_info ���󥹥���
private $reqobj_;	// CGI REQUEST ���󥹥���
private $resobj_;	// CGI RESPONSE ���󥹥���

private $body_;		// HTML body��ʬ

private $recursive_flg_;	// �Ƶ��ѥե饰��true�ǺƵ�����
private $recursive_command_;	// �Ƶ�����Ȥ��Υ⥸�塼��̾

private $inside_encoding_obj_;  // �������󥳡����� multibyte���󥹥���

private $bag_;  // ��������Ѥ��Ф󥤥󥹥��󥹡�multimap

//private $tmp_filename_;
//private $error_tmp_filename_;

} // end of class
