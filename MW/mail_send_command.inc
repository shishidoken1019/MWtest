<?php
/**
 * �᡼���������饹
 *
 * sendmail���ޥ�ɤǥ᡼����������륯�饹
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

require_once('mail_send.inc');

class mail_send_command extends mail_send {

public function __construct()
{
  //
  parent::__construct();
  //$this->init();
}


public function init() {
  parent::init();
  $this->set_sendmail_path("/usr/sbin/sendmail");
  $this->params_ = array();
}

/**
 * �᡼��������Ԥ�
 *
 * @access public
 * @param internet_message_format_obj $mobj �᡼��ǡ�����ɽ�����󥹥���
 * @return boolean ���꤬ȯ��������false �ܺ٤��̥᥽�åɤǡ��Ĥ�ͽ�ꡣ
 */
public function send(internet_message_format $mobj) {

  // sendmail���ޥ���ѤΥѥ�᡼��������
  $param = $this->make_param($mobj);

  // sendmail���ޥ���ѤΥ᡼��ǡ���������
  $mail_string = $mobj->get_mail_string();
//var_dump($mail_string);

  // mail�ν���
  $cm = $this->get_sendmail_path() . " " . $param;

  // ��������
//print "sendmail command line is $cm <br />\n";
  $fh = popen($cm, "w");
  if (false === $fh) {
    // XXX ���Ȥǥ��顼�����ɵ����뤳�ȡ���
    return false;
  }
//print "file handle is $fh \n";
//print "write data is " . mb_convert_encoding($this->get_data(), "EUC-JP", "auto") . "\n";

//var_dump($mail_string);
//file_put_contents('/opt/www/MW/log', $mail_string, FILE_APPEND);
  $ret = fwrite($fh, $mail_string);
  if (false === $ret) {
    // XXX ���Ȥǥ��顼�����ɵ����뤳�ȡ���
    return false;
  }

  // XXX ��λ�����ɤ��⤦�ҤȤ����� orz
  $ret = pclose($fh);
  
  //
  return true;
}

/*
 * sendmail���ޥ���ѤΥѥ�᡼��������
 */
protected function make_param(internet_message_format $mobj) {
  // �ޤ��ǥե�
  $pwk = '-i';

  // envelope from��̵ͭ
  $wk = $mobj->get_envelope_from();
  if ("" === $mobj->get_envelope_from()) {
    $pwk .= 't';
  } else {
    $pwk .= ' -f ' . $wk;
  }

  // envelope to��̵ͭ
  $wk = $mobj->get_envelope_to();
  if (empty($wk)) {
    $pwk .= ' -t';
  } else {
    $pwk .= implode(',', $wk);
  }

  // XXX �����Ϥ�����VERP(variable envelope return path)��ǧ����
  // postfix�ξ�� -XV 

  //
  return $pwk;
}


/*
 * sendmail�Υѥ�����
 */
public function set_sendmail_path($p) { $this->sendmail_path_ = $p; }
protected function get_sendmail_path()  { return $this->sendmail_path_; }

  /*
   * Envelope From������
   */
  private function set_envelope_from() {
    if ("" != $this->get_data_obj()->get_envelope_from()) {
      $this->params_[] = "-f " . $this->get_data_obj()->get_envelope_from();
      $this->set_return_path($this->get_data_obj()->get_envelope_from());
    }
  }
  private function get_envelope_from() {}
  
  /*
   * Envelope To������
   */
  private function set_envelope_to() {

    $awk = $this->get_data_obj()->get_envelope_to();
    if (0 < count($awk)) {
      $this->params_[] = implode($awk, ",") . $this->get_data_obj()->get_crlf();
    } else {
      $this->params_[] = "-t";
    }
  }
  private function get_envelope_to() {}

//private:
private $obj_mail_data_;    // �᡼��ǡ������֥�������
private $mail_data_;        // �᡼��ǡ���String
private $return_path_;      // ��ʬ����äƤ�����
private $params_;          // sendmail�Υѥ�᡼������
private $param_;            // sendmail�Υѥ�᡼��
private $sendmail_path_;    // sendmail���ޥ��

} // end of class
