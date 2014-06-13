<?php

/**
 * ���å����ID��URI����Ϳ���륯�饹
 *
 * ����Ū�˥������ƥ����ȼ������Ȥ��Ȥ���������
 * �Ǥ���Ӥ���Cookie�ʤ�����빽ɬ�ܤʤΤ��(DoCoMo���ϼ�...
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/


class add_session_id {

public function __construct()
{
  //
  $this->init();
}

//
public function init()
{
  // �����Ӥߤ����default����
  $this->set_body("");
  $this->set_session_id("");
  $this->set_session_name("s");
  //
  $this->clear_target_suffix();
  $this->push_target_suffix("php");
  $this->push_target_suffix("cgi");
}

/**
 * �Ѵ�����HTML������
 *
 * @access public
 * @param string $s ����Ū�ˤϸ�HTML
 * @return boolean �ʤˤ����ä���false
 */
public function set_body($s) { $this->body_ = $s; }
public function get_body() { return $this->body_; }

/**
 * �����ߤ���session id������
 *
 * @access public
 * @param string $s ���å����ID
 * @return boolean �ʤˤ����ä���false
 */
public function set_session_id($s) { $this->session_id_ = $s; }
public function get_session_id() { return $this->session_id_; }

/**
 * �����ߤ���session id��name��ʬ������
 *
 * @access public
 * @param string $s ���å����ID��name
 * @return boolean �ʤˤ����ä���false
 */
public function set_session_name($s) { $this->session_name_ = $s; }
public function get_session_name() { return $this->session_name_; }

/**
 * �оݤˤʤ��ĥ�Ҥ�����
 *
 * .php��.cgi�ϥǥե���Ȥ����äƤ�
 *
 * @access public
 * @param string $s ���å����ID��name
 * @return boolean �ʤˤ����ä���false
 */
public function push_target_suffix($s) { $this->target_suffix_[] = $s; }

public function clear_target_suffix() { $this->target_suffix_ = array(); }
public function get_target_suffix() { return $this->target_suffix_; }

/**
 * URI�˥��å����ID���ɲä������
 *
 * @access public
 * @return boolean �ʤˤ����ä���false
 */
public function run()
{
  $base = $this->get_body();
  $ret = "";

  // ����ɽ���ˤ��ʬ��
  // XXX �Ť��ʤ���
  $pattern = "/(.*?)([<])(.*?)([>])(.*)/s";
  while(0 < preg_match($pattern, $base, $wk)) {
    // �ޤ������ְʳ��פ�ʸ������ڤ�Ф�
    $ret .= $wk[1] . $wk[2];
    $base = $wk[4] . $wk[5];

    // ���λ����ǡ������оݤ�$wk[3]
//print "do is $wk[3]\n";
    // ��ĥ�Ҥ�php��cgi��html�ʳ��ʤ�Ȥꤢ�����ʤ�
    $pattern2 =
      '/(.*\.)(' . implode('|', $this->get_target_suffix()) . ')(.*)/si';
    if (0 === preg_match($pattern2, $wk[3], $wk2)) {
      $ret .= $wk[3];
      continue;
    }
    // else 
//var_dump($wk2);
    // �ޤ��ե�����̾�ޤǤ�Ž���դ���
    $ret .= $wk2[1] .  $wk2[2];

    if ('?' === $wk2[3][0]) {
      $wk2[3][0] = '&';
    }
    $ret .= '?' . $this->get_session_name() . '=' . $this->get_session_id() . $wk2[3];
//print "add $buf \n";
    $ret .= $buf;
//print "\n-------------\n";
//print $ret;
//print "\n-------------\n\n";
  }
  // �����
  if ("" != $base) {
    $ret .= $base;
  }

  //
  return $ret;
}


//private:
private $body_;
private $session_id_;
private $session_name_;
private $target_suffix_;

} // end of class

?>