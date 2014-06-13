<?php

/**
 * ���������ܤǶ��᡼���Ϥ������ѥ��饹
 *
 * ����Ū�ˡ֥桼���Υᥢ�ɤ�μ¤����ꤹ��פ���˻Ȥ�
 *
 * DB����ץ� MySQL��
 *

create table empty_mail_cushion_test (
  id varbinary(64) PRIMARY KEY,
  email varbinary(256) NOT NULL,
  param varbinary(256)
);

 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

require_once('empty_mail_analysis.inc');
require_once('conv.inc');
require_once('internet_message_format.inc');
require_once('mail_send_command.inc');
require_once('tokenizer.inc');
require_once("crypt_factory.inc");
require_once("sql_util.inc");

class empty_mail_cushion {

public function __construct()
{
  //
  //parent::__construct();
  $this->init();
}

//
public function init()
{
  $this->set_db(null);
  $this->set_conv(null);
}

/**
 * DB�ϥ�ɥ������
 *
 * @access public
 * @param db_handle $o db_handle���饹(������������饹)�Υ��󥹥���
 */
public function set_db($o) { $this->dbh_ = $o; }
/**
 * DB�ϥ�ɥ������
 *
 * @access public
 * @return db_handle db_handle���饹(������������饹)�Υ��󥹥���
 */
public function get_db() { return $this->dbh_; }

/**
 * mail body������conv���󥹥��󥹤�����
 *
 * @access public
 * @param conv_inc $o conv���饹(������������饹)�Υ��󥹥���
 */
public function set_conv($o) { $this->conv_ = $o; }

//
protected function get_conv() { return $this->conv_; }


/**
 * �᡼��ƥ�ץ졼�Ȥμ���
 *
 * @access public
 * @param string $s mail template�ե�����̾
 */
public function set_mail_template_filename($s)
  { $this->mail_template_filename_ = $s; }
//
protected function get_mail_template_filename()
  { return $this->mail_template_filename_; }

/**
 * config�ե����������
 *
 * �ºݤˤϥ��󥹥��󥹤��ä��㤦
 *
 * @access public
 * @param stinrg $fn config�ե�����̾
 * @return boolean ���꤬���ä���false
 */
public function set_config_filename($fn)
{
  //
  if ("" === $fn) {
    return false;
  }

  //
  $this->config_obj_ = new config;
  return $this->config_obj_->set_file($fn);
}
protected function get_config() { return $this->config_obj_; }

/**
 * �¹�
 *
 * ����ե�����˰��뤬���������
 * ��DB�ʤɤؤΥᥢ�ɤν񤭹���
 * �����������ѥ�ˡ���URI����
 * ���᡼��Ǥ��ֻ�
 * �򤳤ʤ�
 *
 * @access public
 * @param stinrg $fn config�ե�����̾
 * @return boolean ���꤬���ä���false
 */
public function run()
{
  // �Ȥꤢ�����᡼�����Ƥ򤲤�
  $obj = new empty_mail_analysis;
  $obj->set_token_separator($this->get_config()->find('token_separator'));

  // stdin����᡼��ǡ�������
  $obj->analysis_from_stdin();

  $from = $obj->get_mail_from();
  $tkn = $obj->get_mail_to_token();

  // �ȡ��������
  $uri_token = tokenizer::get();

  // DB��insert
  $sqlwk = array();
  $sqlwk['id'] = $uri_token;
  $sqlwk['email'] = $from;
  $sqlwk['param'] = $tkn;
  $sql = sql_util::make_insert($this->get_config()->find('table_name'), $sqlwk);
  // XXX
  $ret = $this->get_db()->query($sql);

  // �ȡ������Ź沽����URI�Υѥ�᥿�ˤ���
  $en_o = crypt_factory::get_instance($this->get_config()->find('crypt_config_name'));
  $en_o->set_plain_text($uri_token);
  $en_o->encrypt();
  $encrypted_text = $en_o->get_encrypted_unit();

/*
$de_o = crypt_factory::get_instance($this->get_config()->find('crypt_config_name'));

// decode
$de_o->set_encrypted_unit($encrypted_text);
$de_o->decrypt();
$id = $de_o->get_plain_text();
//var_dump($id);
*/

  // �᡼�����
  //
  $conv = $this->get_conv();
  if (true === is_null($conv)) {
    $conv = new f_conv;
  }
  $conv->monoDic('token', urlencode($encrypted_text));
  //
  // mail_template
  $mbody = $conv->conv(mb_convert_encoding(file_get_contents($this->get_config()->find('mail_template')), "eucJP-win", array('sjis', 'eucJP-win', 'utf-8') ));
  //$mbody = $conv->conv(file_get_contents($this->get_config()->find('mail_template')));
//var_dump($mbody);

  // �᡼�����
  $mobj = new internet_message_format;

  $mobj->set_from($this->get_config()->find('from'), $this->get_config()->find('from_name'));
  $mobj->push_to($from);
// subject
  $mobj->set_subject($this->get_config()->find('subject'));
  $mobj->set_body($mbody);

  // ���softbank�к��ä� ����ޤ�ɬ�פʤΤ���
  $wk = $this->get_config()->find('envelope_from');
  if ("" === $wk) {
    $wk = $this->get_config()->find('from');
  }
  $mobj->set_envelope_from($wk);
//var_dump($wk);
//var_dump($mobj);

//var_dump($mobj->get_mail_string());
  $sobj = new mail_send_command;
  $sobj->send($mobj);

  //
  return true;
}

/**
 * ID����ᥢ�ɤμ���
 *
 * @access public
 * @param stinrg $s �Ź沽���줿ID
 * @return string �ᥢ�ɡ��ǡ������ʤ����϶�ʸ��
 */
public function get_email($s) {
  $wk = $this->get_param($s);
  if (empty($wk)) {
    return "";
  }
  // else
  return $wk[0];
}

/**
 * ID����ѥ�᥿����
 *
 * @access public
 * @param stinrg $s �Ź沽���줿ID
 * @return array [0]�˥ᥢ�ɡ�[1]�˥ѥ�᥿�����顼���϶�����
 */
public function get_param($s) {
//var_dump($s);
//var_dump($this->get_config());

  // �ޤ�decode
  $de_o = crypt_factory::get_instance($this->get_config()->find('crypt_config_name'));

  // decode
  $de_o->set_encrypted_unit($s);
  $de_o->decrypt();
  $id = $de_o->get_plain_text();
//var_dump($id);
  if ("" === $id) {
    return array();
  }

  //
  $ret = array();

  // XXX
  $sql = 'SELECT email, param FROM ' . $this->get_config()->find('table_name') . ' WHERE id = ' . security::sanitize_db_add_quote($id) . ';';
//print $sql . "\n";
  // XXX
  $res = $this->get_db()->query($sql);
  if ($res->fetch()) {
    $ret[0] = $res->get_data(0);
    $ret[1] = $res->get_data(1);
  }

  //
  return $ret;
}

/**
 * �쥳���ɺ��
 *
 * @access public
 * @param stinrg $s �Ź沽���줿ID
 * @return boolean �������꤬�����false
 */
public function delete($s) {
  //
  $wk = $this->get_param($s);
//var_dump($wk);
  if (empty($wk)) {
    return false;
  }

  // XXX �Ȥꤢ�����٥�
  // DB��insert
  $sqlwk = array();
  $sqlwk['email'] = $wk[0];
  $sql = sql_util::make_delete($this->get_config()->find('table_name'), $sqlwk);
//var_dump($sql);
  // XXX
  $ret = $this->get_db()->query($sql);

  //
  return true;
}

//private:
private $mail_template_filename_;
private $dbh_;
private $config_obj_;
private $conv_obj_;

} // end of class

