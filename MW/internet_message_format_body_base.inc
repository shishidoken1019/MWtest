<?php

/**
 * RFC2822�ˤ��Ȥ����� Internet Message Format ��Body���򤢤�魯���饹
 *
 * ñ���text����꡼��multipart������Τǡ��Ȥꤢ�������쥯�饹����
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/


abstract class internet_message_format_body_base {

public function __construct()
{
  //
  $this->init();
}

//
public function init()
{
}

/**
 * body������ܤ�ʸ����ˤ��Ƽ���
 *
 * @access abstract public
 * @return string ���꤬����ж�ʸ����
 */
abstract public function get_to_string();

/**
 * ʸ���������
 *
 * multipart����¿ʬ�ѡ��������Ȥ������������ʤ�
 *
 * @access abstract public
 * @param string $s ʸ����
 * @return boolean ���꤬�����false
 */
abstract public function set_from_string($s);


} // end of class
