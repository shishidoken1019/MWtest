<?php

/**
 * �������饹
 *
 * �����������
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Kohei Yamada <hecomark@gmail.com>
 * @version $Revision$
 **/
require_once('file_util.inc');

class log 
{
//public :

public function __construct() {
  $this->init();
}

/**
 * ���������
 *
 * @access public
 */
public function init() {
  $this->buf_       = "";       // ���Τ�������ѿ���������
  $this->filename_  = "";       // ���ֲ��򸫤Ƥ͡�
  $this->pname_     = "";       //
  $this->flg_       = true;     //
  $this->sflg_      = true;     //
  $this->pauser_    = "\t";     //
}

/**
 * �����ե�������ϥե饰��on�ˤ���
 *
 * @access public
 */
public function on() { $this->flg_ = true; }

/**
 * �����ե�������ϥե饰��off�ˤ���
 *
 * @access public
 */
public function off() { $this->flg_ = false; }

/**
 * ����������ɽ����yyyy/mm/dd�����ˤ���(�ǥե����)
 *
 * @access public
 */
public function spreadtime_on() { $this->sflg_ = true; }

/**
 * ����������ɽ���򥨥ݥå�������ˤ���
 *
 * ®��Ū��ͭ���ʤΤǡ������񤭹��ߤ����٤��㤷���Ȥ��ˡ�
 *
 * @access public
 */
public function spreadtime_off() { $this->sflg_= false; }

/**
 * �ץ������̾����
 *
 * @access public
 * @param string $str �ץ������̾
 */
public function set_pname($str) {
  $this->pname_ = $str;
}

/**
 * �����ե�����񤭹���������
 *
 * @access public
 * @param string $str �����ե�����̾
 */
public function set_filename($str) {
  $this->filename_ = $str;
}

/**
 * ��������å��������ե�����񤭹���������
 *
 * �����ե�����̾�ȳ�ĥ�Ҥδ֤����դ�����
 *
 * @access public
 * @param string $str �����ե�����̾
 */
public function set_rotate_filename($s) {
  // ʬ��
  $wk = file_util::split_filename_by_extension($s);
  //
  $s = $wk[0] . date('Ymd') . $wk[1];
  $this->set_filename($s);
}

/**
 * ������ʸ������ɲ�
 *
 * flush()��ƤӽФ����ʤ鲿��Ǥ���ѤǤ��롣
 * ���ξ�硢����ʸ�����Ϣ�뤵��롣
 * ���ڤ�ʸ����ɬ��̾��� pause�᥽�åɤ�call���뤳��
 *
 * @access public
 * @param string $str �����˽񤭹��ޤ��ʸ����
 */
public function add($str) {
  $this->buf_ .= $str;
}

/**
 * �����˶��ڤ�ʸ�����ɲá�
 *
 * �ǥե���ȤǤ�"\t"(����)���ɲä���롣
 *
 * @access public
 */
public function pause()  {
  $this->add($this->_pauser());
}

/**
 * �����񤭹���
 *
 * �񤭽Ф����塢�����ΥХåե��ϥ��ꥢ����롣
 *
 * @access public
 * @return boolean �񤭹��ߤ˼��Ԥ�����false
 */
public function flush()
{
  ///////
  // �񤭹������Υ����å�

  if (!($this->_is_on())) {      // �񤭹������פξ��Ͻ�λ��
//print "flush off";
    $this->_clear_buf();         // XXX �Хåե��ϥ��ꥢ���Ƥ�����
    return true;
  }
  
  if ("" === $this->_buf()) {    // �Хåե������ξ��⽪λ��
//print "buf empty!";
    $this->_clear_buf();         // �������Ū�˥��ꥢ���Ƥ�����
    return true;
  }

  ///////
  // ���դμ���

  $t = "";
  if ($this->_is_sptime_on()) {  // spreadtime��on�ʤ�
    $t = date("Y/m/d H:i:s");    // ���䤹��ɽ����
  } else {
    $t = time();                 // ����ʳ��ϥ��ݥå�������ǡ�
  }

  ///////
  // �ǡ�������
  $write_str = "";
  $write_str .= $t;                     // ����
  $write_str .= $this->_pauser();       // ���ڤ�ʸ��
  if ($this->_pname()) {
    $write_str .= $this->_pname();      // �ץ������̾
    $write_str .= $this->_pauser();     // ���ڤ�ʸ��
  }
  $write_str .= $this->_buf() . "\n" ;  // ����������
                                        // XXX ���Ԥ�\n���ꡩ
  
  ///////
  // �ե�����񤭹���
  // XXX file_put_contents��LOCK_EX,�Ǥ⤤���Τ��ʤ���

  $fp = @fopen($this->_filename(), "a");
  if(!$fp) {
//print "file open error!";
    $this->_clear_buf();      // XXX �����ϥ��ꥢ���Ƥ����Τ��ġ�
    return false;             // ��λ
  }
  @flock($fp, LOCK_EX);        // LOCK_EX => ��¾���å�
  @fwrite($fp, $write_str);
  @fclose($fp);

  ///////
  // �Хåե��������ꥢ��������

  $this->_clear_buf();
  return true;
}

//private:
private function _filename() { return $this->filename_; }
private function _buf() { return $this->buf_; }
private function _pname() { return $this->pname_; }
private function _pauser() { return $this->pauser_; }
private function _is_on() { return $this->flg_; }
private function _is_sptime_on() { return $this->sflg_; }
private function _clear_buf() { $this->buf_ = ""; }

//private:
private $flg_;        // true(on)   => �ե�������Ϥ���
                      // false(off) => �ե�������Ϥ��ʤ�
private $sflg_;       // true(on)   => ������yyyy/mm/dd�����ǽ񤭹���
                      // false(off) => �����򥨥ݥå�������ǽ񤭹���
private $filename_;   // �����񤭹�����ե�����̾
private $buf_;        // ���������Ƥ�ί���Хåե�
private $pname_;      // ��������Ϥ����ץ������̾
private $pauser_;     // ���ڤ�ʸ��

}  // end of class
