<?php

/**
 * ñ���text�᡼����body���饹
 *
 * �Ȥꤢ��������

	There are two limits that this standard places on the number of
characters in a line. Each line of characters MUST be no more than
998 characters, and SHOULD be no more than 78 characters, excluding
the CRLF.
����Ǥ⡢CRLF�������characters��998ʸ���ʲ���
��ǽ�ʤ�78ʸ���ʲ���

	CR and LF MUST only occur together as CRLF; they MUST NOT appear
independently in the body.
CR��LF�ϡ������줫����Ω���Ƹ���ƤϤ����ʤ���

 * �Ȥ������¤�̤�����å�
 * �ޤ���̩�ˤϡ�ezweb�β��ԥ����ɤ�LF�ʤΤ����������դ�̤�б�
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

require_once('internet_message_format_body_base.inc');

class internet_message_format_body_text extends internet_message_format_body_base {

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
  $this->set_from_string('');
}

/**
 * body������ܤ�ʸ����ˤ��Ƽ���
 *
 * �¼���̤����
 *
 * @access abstract public
 * @return string ���꤬����ж�ʸ����
 */
public function get_to_string() { return $this->body_string_; }

/**
 * ʸ���������
 *
 * multipart����¿ʬ�ѡ��������Ȥ������������ʤ�
 *
 * @access abstract public
 * @param string $s ʸ����
 */
public function set_from_string($s) { $this->body_string_ = $s; }

//private:
private $body_string_;

} // end of class
