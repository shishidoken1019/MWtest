<?php

/**
 * Internet Message Format���̣���륯�饹
 *
 * RFC2822����ͽ��Υ᡼�륯�饹(��
 * ����facade�����ɡ����ݤʤΤ�header_fields��Ѿ����Ƥ�
 * ʸ�����󥳡��ɤ� EUC -> jis �Ǹ���ˤʤäƤ�Τ�����
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

require_once('internet_message_format_header_fields.inc');
require_once('internet_message_format_body_text.inc');
require_once('multibyte.inc');

class internet_message_format extends internet_message_format_header_fields {

public function __construct()
{
  //
  parent::__construct();
  //$this->init();
}

//
public function init()
{
  parent::init();
  $this->set_envelope_from('');
  $this->envelope_to_ = array();
  //$this->verp_flg_off();
  // XXX ���̾������ꡣ���factoryͽ��
  $this->internet_message_body_obj_ = new internet_message_format_body_text;
}

/**
 * envelope from������
 *
 * �狼��ʤ�������ꤷ�ʤ�����!!
 *
 * @access public
 * @param string $s envelope�Ѥ�from���ɥ쥹
 */
public function set_envelope_from($s) { $this->envelope_from_ = $s; }
// ɽ�ˤϽФ��ʤ�����Document���������ȤϾ�ά
public function get_envelope_from() { return $this->envelope_from_; }


/**
 * envelope to������
 *
 * �狼��ʤ�������ꤷ�ʤ�����!!
 *
 * @access public
 * @param string $s envelope�Ѥ�to���ɥ쥹
 */
public function push_envelope_to($s) { $this->envelope_to_[] = $s; }
// ɽ�ˤϽФ��ʤ�����Document���������ȤϾ�ά
public function get_envelope_to() { return $this->envelope_to_; }

//
protected function get_body_obj() { return $this->internet_message_body_obj_; }

/**
 * mail body������
 *
 * @access public
 * @return string mail���Τ�Τ򤢤�魯ʸ�������꤬����ж�ʸ��
 */
public function set_body($s)
  { $this->get_body_obj()->set_from_string($s); }

/**
 * mail string�μ���
 *
 * internet message���٤Ƥ��ܤ�ʸ����ˤ�������
 *
 * @access public
 * @return string mail���Τ�Τ򤢤�魯ʸ�������꤬����ж�ʸ��
 */
public function get_mail_string()
{
$ret = "";
  // �ޤ��إå��μ��Ф�
  $ret = $this->get_all_headers();
  $ret .= "\r\n";

  // XXX ���ä���iso-2022jp����
  // XXX �������������󥳡���euc����
  $m = new multibyte;
  $m->set_jis();
  $m->set_from_encoding_euc();
  $ret .= $m->convert($this->get_body_obj()->get_to_string());
//var_dump($this->get_body_obj()->get_to_string());
//var_dump($ret);

  //
  return $ret;
}

//
//public function set_mail_string($s) : parse


//private:
private $envelope_from_;
private $envelope_to_;
//private $verp_flg_;
private $internet_message_body_obj_;

} // end of class
