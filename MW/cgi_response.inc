<?php
/**
 * CGI �쥹�ݥ󥹥��饹
 *
 * CGI �إå������ꡢ����(view��)���륯�饹
 * XXX ��üCookie�ϼ������ʤ�����������ˤ��ä��˼����ߤ����ʤ�
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 */



class cgi_response
{

public function __construct()
{
  $this->init();
}

// �����
public function init()
{
  $this->header_ = array();
  $this->put_flg_off();
}

/**
 *  �إå��ɲ�
 *
 * �Ȥꤢ�����ֲ��Ԥ�����̵�ѤǺ����
 * ��Ǥ⤦���礤��ǫ�˽����������ʤ�
 *
 * @access public
 * @param string $n header��̾��
 * @param string $v header����
 */
public function add_header($n, $v)
{
  // ����
  $this->header_[$n] = $v;
  // ���ϥե饰�򿲤�����
  $this->put_flg_off();
  return true;
}
protected function get_all_header() { return $this->header_; }
protected function get_header($n)
{
  if (isset($this->header_[$n])) {
    return $this->header_[$n];
  }
//print "get $n is empty \n";
  return "";
}

private function _set_put_flg($b) { $this->put_flg_ = $b; }
public function put_flg_on() { $this->_set_put_flg(true); }
public function put_flg_off() { $this->_set_put_flg(false); }
public function is_put_flg() { return $this->put_flg_; }


/**
 * ����
 *
 * stdout�˽���
 * ���Ǥ˽��Ϥ�����硢return��false���֤�
 *
 * @access public
 * @return boolean ���ϺѤߤξ��false
 */
public function put()
{
  // ���ϥ����å�
  if (true == $this->is_put_flg()) {
    return false;
  }

  // ����
  foreach ($this->get_all_header() as $key => $value) {
//print $key . ": " . $value . "\n";
    // ��˲��Ԥμ�����
    $n = preg_replace('/[\r\n]/', '', $key);
    $v = preg_replace('/[\r\n]/', '', $value);
    // ����
    header($n . ": " . $v);
  }
  
  // �ե饰��ֽ��ϺѤߡפˤ��ơ���λ
  $this->put_flg_on();
  return true;
}

/**
 * content-type��HTML�ʻ��Υإå�����
 *
 * @access public��private��protected��
 * @param string $jcode_type ���󥳡��ɥ����ס��ǥե���Ȥ�euc
 */
public function set_content_html($jcode_type = "euc")
{
  
  // ������ʬ
  $n = "Content-type";
  $s = "text/html";

  // �ƥ�����Ƚ��
  // XXX �������٤����������б�
  if (preg_match('/euc/i', $jcode_type)) {
    $s .= "; charset=euc-jp";
  } else
  if (preg_match('/sjis/i', $jcode_type)) {
    $s .= "; charset=shift_jis";
  } else
  if (preg_match('/shift[-_]*jis/i', $jcode_type)) {
    $s .= "; charset=shift_jis";
  } else
  if (preg_match('/utf[-_]*8/i', $jcode_type)) {
    $s .= "; charset=utf-8";
  } else
  if (preg_match('/iso-2022-jp/i', $jcode_type)) {
    $s .= "; charset=iso-2022-jp";
  } else
  if (preg_match('/jis/i', $jcode_type)) {
    $s .= "; charset=iso-2022-jp";
  }
  // �⤷���ä�����ʤ����ʸ�������ɤϻ��ꤷ�ʤ�

  // �إå�buffer����Ͽ
  return $this->add_header($n, $s);
}

/**
 * Content-type����
 *
 * ���ޤ��ޤʡ�Content-type��ͳ�����ꤹ��
 *
 * @access public
 * @param string $type type
 */

public function set_content($type = "")
{
  if ("" === $type) {
    return false;
  }
  
  // �ɲ�
  return $this->add_header("Content-type", $type);
}

/**
 * Content-length������
 *
 * @access public
 * @param int $len ����ƥ�Ĥ�Ĺ��
 */

public function set_length($len = 0)
{
  if (0 >= $len) {
    return false;
  }
  
  // �ɲ�
  return $this->add_header("Content-Length", $len);
}

/**
 * plain text��
 *
 * @access public
 */
public function set_content_plain() { return $this->set_content("text/plain"); }

/**
 * Jpeg������
 *
 * @access public
 */
public function set_content_jpeg() { return $this->set_content("image/jpeg"); }

/**
 * GIF������
 *
 * @access public
 */
public function set_content_gif() { return $this->set_content("image/gif"); }

/**
 * PNG������
 *
 * @access public
 */
public function set_content_png() { return $this->set_content("image/png"); }

/**
 * CSV�ե�������
 *
 * @access public
 * @param string $filename �ե�����̾
 */
public function set_content_csv($filename)
{
  $this->set_content("application/octet-stream");
  $this->add_header('Content-Disposition', 'attachment; filename=' . $filename . ';');

  return true;
}

/**
 * Location����
 *
 * ��������ꤹ��Ȥۤ��η빽��header���̵꤬��̣�ˤʤ�Τ����դ��뤳��
 *
 * @access public
 * @param string $loc ���ܤ�������URI
 */
public function set_location($loc) {
  return $this->add_header("Location", $loc);
}

/**
 * status204(���̤��Ѳ������ʤ�)�ν���
 *
 * �ǡ�������������ɤʤ󤫤ΤȤ��ˤ��碌�Ƥɤ���
 *
 * @access public
 */
public function set_status204()
{
  return $this->add_header("Status",  "204 No Response");
}

/**
 * ���̥���å���̵����
 *
 * �֥饦���ˤ�ä���ʬ�㤦�Τǡ����̤�ޤȤ��
 * ưŪPage�ʤ�ȯ�Ԥ���»�Ϥʤ�
 *
 * @access public
 */
public function set_nocache()
{
  $this->add_header("Expires", "0");
  $this->add_header("Pragma", "no-cache");
  $this->add_header("Cache-Control", "no-cache");
  // XXX Cache-Control: private, no-store, no-cache, must-revalidat

  return true;
}

// Content-typeȽ��
// ʸ�������ɤ�����type�ʤ�true������
// XXX �����Ѥäݤ��Τ�PHPDoc�����Υ����Ȥ򤢤��ƾ�ά
public function is_need_convert()
{
  // �ޤ����Ф�
  $type = $this->get_header("Content-type");
//print "type is $type \n";
  // ����äݤʤ�ǥե���Ȥ�text�Ϥ���������true����
  if ("" == $type) {
//print "return true\n";
    return true;
  }
  // text�ʤ�true
  //if (!(strpos($type, "text") === false)) {
  if (0 === (strncmp($type, 'text', 4))) {
//print "return true\n";
    return true;
  }
  // XXX DoCoMo�Ѥ��ʤ���
  if (0 === (strncmp($type, 'application/xhtml+xml', 21))) {
    return true;
  }

  // ��Ұʳ��ʤ饨�顼
//print "return false\n";
  return false;
}


// ���Ϥ���إå��켰
private $header_;

// ���Ϥ������ɤ���
// false�ʤ�̤���� true�ʤ���ϺѤ�
private $put_flg_ = false;

} // end of class
