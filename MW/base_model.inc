<?php

/**
 * MVC Model��ʬ���쥯�饹
 *
 * �����������������˺�롣MVC��M��ô��
 * skelton������ɲäϰʲ����̤�
 * ��DB handle
 * ��Log���饹�Ƽ�
 * ��conv���󥹥��󥹼���
 * ��
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 */

require_once('base_model_skeleton.inc');
require_once('db_manager.inc');
require_once('log.inc');
require_once('log_dummy.inc');
require_once('file_util.inc');
require_once('conv_util.inc');
require_once('is.inc');
require_once('secure_conv.inc');

abstract class base_model extends base_model_skeleton {

//public:

//
public function __construct() {
  parent::__construct();
  // $this->init(); ��̤�á���Ƥ���Ϥ��ʤΤ�
}
//
public function init()
{
  parent::init();
}

//
//public function set_tmp_filename($s) { $this->set_bag('tmp_filename', $s); }
//public function get_tmp_filename() { return $this->get_bag('tmp_filename'); }

/**
 * DB�ϥ�ɥ����
 *
 * DB�ϥ�ɥ��������롣
 * ̤��³�ξ�硢��³���Ƥ���������롣
 *
 * @access public
 * @return object DB�ϥ�ɥ�
 */
public function get_db()
{
  // ̤��³�ʤ���³���Ȥ���
  if ( false === $this->is_bag('dbh') ) {
    $this->set_bag('dbh', db_manager::get_handle( $this->get_config() ));
  }

  // �ϥ�ɥ������
  return $this->get_bag('dbh');
}

/**
 * CONV���󥹥��󥹼���
 *
 * �ǥե���f_conv������config�˵��Ҥ�����а㤦���󥹥��󥹤�
 *
 * @access public
 * @return object conv���󥹥���
 */
public function get_conv()
{
//print "in to get_conv \n";
  if (false === $this->is_bag('conv')) {
//print "new create conv \n";

    if ('secure_conv' === $this->get_config()->find('template_engine')) {
      $this->set_bag('conv', new secure_conv);
    } else 
    if ('smarty' === $this->get_config()->find('template_engine')) {
      require_once('mw_smarty.inc');
      $this->set_bag('conv', new mw_smarty);
    } else
    if ('' === $this->get_config()->find('template_engine')) {
      $this->set_bag('conv', new f_conv);
    } else {
      $cn = $this->get_config()->find('template_engine');
//var_dump($cn);
      $this->set_bag('conv', new $cn);
    }

    // Smarty�Ϥξ����ɲý���
    $cn = get_class($this->get_bag('conv'));
    if (false !== (stristr($cn, 'smarty'))) {
      $this->get_bag('conv')->template_dir = $this->get_config()->find('template_dir');
      if ("" !== ($s = $this->get_config()->find('smarty_compile_dir'))) {
        $this->get_bag('conv')->compile_dir = $s;
      }
      if ("" !== ($s = $this->get_config()->find('smarty_config_dir'))) {
        $this->get_bag('conv')->config_dir = $s;
      }
    }

    // ɬ�פ�config������ɲ�
    $this->get_bag('conv')->monoDic('uri', $this->get_config()->find('uri'));
    $this->get_bag('conv')->monoDic('ssl_uri', $this->get_config()->find('ssl_uri'));
    $this->get_bag('conv')->monoDic('mx_domain', $this->get_config()->find('mx_domain'));

    $mobj = $this->get_mobile();
    $sp = new simple_put;
    if (true === $mobj->is_docomo()) {
      $this->get_bag('conv')->multiDic('is_docomo', $sp);
    } else
    if (true === $mobj->is_au()) {
      $this->get_bag('conv')->multiDic('is_au', $sp);
      $this->get_bag('conv')->multiDic('is_ez', $sp);
    } else
    if (true === $mobj->is_softbank()) {
      $this->get_bag('conv')->multiDic('is_softbank', $sp);
    }
  }
  //
  return $this->get_bag('conv');
}

/**
 * body��ư���� with conv
 *
 * $this��conv���󥹥��󥹤�����ե������template_dir��ˤ���
 * �����ƥ�ץ졼�ȥե������Ȥä�body��ư��������
 * �����ʤ�(���϶�ʸ��)�ξ�硢map�ե���������ꤵ�줿template��ͭ���ˤʤ�
 * �֤¤ĤϤ��Υ᥽�å�call���ʤ��Ƥ⤤�������פȤ����Ť���������
 *
 * @access protected
 * @param string $tmp_filename �ƥ�ץ졼�ȥե�����̾
 * @return boolean �ʤˤ����ꤢ�ä���false
 */
public function make_body_with_conv($tmp_filename = "")
{
  if ("" !== $tmp_filename) {
    $this->set_tmp_filename($tmp_filename);
  }
//var_dump($this->get_tmp_filename());
  //$this->set_body($this->get_conv()->conv(file_util::read_file($this->get_config()->find("template_dir") . $tmp_filename)));

  return true;
}

/**
 * ���顼������log���饹���󥹥��󥹼���
 *
 * @access public
 * @return object log���󥹥��� ���顼�ξ���null
 */
public function get_error_log() { return $this->_get_log('error'); }

/**
 * warning������log���饹���󥹥��󥹼���
 *
 * @access public
 * @return object log���󥹥��� ���顼�ξ���null
 */
public function get_warning_log() { return $this->_get_log('warning'); }

/**
 * debug������log���饹���󥹥��󥹼���
 *
 * @access public
 * @return object log���󥹥��� ���顼�ξ���log_dummy���󥹥���
 */
public function get_debug_log() { return $this->_get_log('debug'); }

//
protected function _get_log($s)
{
  // ���꤬­��ʤ���dummy return 
  $s = $this->get_config()->find($s . '_log_path');
  if ("" === $s) {
    $obj = new log_dummy;
    $this->set_bag($s . '_log', $obj);
    return $this->get_bag($s . '_log');
  }

  //
  if (false === $this->is_bag($s . '_log')) {
//print "new create error_log \n";
    $obj = new log;
    //$obj->set_filename($s);
    $obj->set_rotate_filename($s);
    $obj->set_pname($this->get_my_name());
    $this->set_bag($s . '_log', $obj);
  }
  //
  return $this->get_bag($s . '_log');

}

/*
// ������Ϣ���饹����Ͽ
protected function _get_log($type)
{
  if (isset($this->log_[$type])) {
    // ���󥹥��󥹤����㤱���false
$type . "_log"
  }
  // ����
$type . "_log_mode"
$type . "_log_spreadtime"

}
*/


//private:
} // end of class

