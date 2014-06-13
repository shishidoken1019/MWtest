<?php

/**
 * form�ǡ����� ʸ�����󥳡��ǥ��󥰿�¬���饹
 *
 * �Ȥꤢ�������ܸ����
 * ��Ǥ⤦���礤���äĤ��ꤿ���äƤΤ�����Τǡ�static�ˤϤ��ʤ�
 * �Ȥꤢ����������ͤϰʲ��ΤȤ���
���ҥ�ƥ���ʸ����Υǥե����̾�� encoding_hint
���ҥ�ƥ���ʸ�������ꤵ��Ƥ����礽��ʸ���������оݤˤ���
���ҥ�ƥ��󥰤�GET��POST��ξ��������POSTͥ��
�����ꤵ��Ƥ��ʤ���礹�٤Ƥ�POSTʸ������оݤˤ���
��POSTʸ���󤬶��ξ��˸¤ꡢ���٤Ƥ�GETʸ������оݤˤ���
���ɡ���Win�Ϥ�¿������������Ƚ����֤�sjis����Ť��֤�
 *
 * hintingʸ����ο侩�Ȥ��Ƥϡ������פȤ��ֿ��α���פȤ���ͭ����������פȤ���
<INPUT type="hidden" name="encoding_hint" value="���α���">
 *
 * ͽ��Ǥϡ��⤦���祤�ޤȤ��guess�롼����Ĥ��äƳ�Ψ��ʸ��������Ƚ�ꤷ����
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

class guess_from_data_encoding {

public function __construct()
{
  //
  //parent::__construct();
  $this->init();
}

//
public function init()
{
  $this->set_hinting_name('encoding_hint');
  $this->set_encoding_string('');
}

/**
 * hintingʸ���󤬳�Ǽ����Ƥ���name������
 *
 * @access public
 * @param string $s hinting��ʸ���󤬳�Ǽ����Ƥ���name
 */
public function set_hinting_name($s) { $this->hinting_name_ = $s; }
// XXX protected�Ǥ�褯�ʤ���
public function get_hinting_name() { return $this->hinting_name_; }

/**
 * ��¬�����ʸ��������
 *
 * @access public
 * @return string PHP��mb_detect_encoding�ؿ����֤�ʸ����
 */
public function get_encoding_string() { return $this->encoding_string_; }
//
protected function set_encoding_string($s) { $this->encoding_string_ = $s; }


/**
 * ��¬
 *
 * ʸ�������ɤο�¬��Ԥ�
 * XXX �����ϳ�Ψ�ˤ�����������ɤͤ���
 *
 * @access public
 * @return boolean �������ä���false
 */
public function guess()
{
  // �о�string�γ���
  $target_string = "";

  // hinting�����ä��餽�ä��Ĥ���
  if ("" !== $this->get_hinting_name()) {
    if (true === isset($_POST[$this->get_hinting_name()])) {
      $target_string = $_POST[$this->get_hinting_name()];
    } else
    if (true === isset($_GET[$this->get_hinting_name()])) {
      $target_string = $_GET[$this->get_hinting_name()];
    }
  }
  // �ʤ��ä���POST
  if ("" === $target_string) {
    // XXX stdin�Ȥ������Ȼפä����ɥե�����upload���ݤ��Τǰ�ü����
    $target_string = @implode('', $_POST);
  }
  // POST�����ʤ����GET
  if ("" === $target_string) {
    //$target_string = @implode('', $_GET);
    $target_string = @implode('', urldecode(getenv('QUERY_STRING')));
  }

  // XXX �Ĥ����Ǥʤ���㥨�顼����ͤ���
  if ("" === $target_string) {
    return false;
  }
//var_dump($target_string);

  // ��¬
  // XXX �Ȥꤢ������¬���֤��ᤦ������ǥ᥽�åɤˤϤ����Ф���
  // XXX �����軰�����Ρָ��ʤʥ��󥳡��ǥ��󥰸��Сפ��⤦�ҤȤ�����
  //$ec = mb_detect_encoding($target_string, 'sjis-win,eucjp-win,SJIS,EUC-JP,JIS,UTF-8,ASCII');
  $ec = mb_detect_encoding($target_string,'JIS,eucjp-win,UTF-8,sjis-win,ASCII');

  // ��¬��̤��Ǽ
  $this->set_encoding_string($ec);

  //
  return true;
}


//private:
private $hinting_name_;
private $encoding_string_;

} // end of class
